#include "LittleWitch.h"
#include "../../../Scene.h"
#include "../../../Constants.h"

C_LittleWitch::C_LittleWitch(Math::Vector2 a_pos) : m_shieldTex(nullptr),
	C_EnemyBase(
		//定数初期値セット
		EnemyType::LittleWitch,//m_enemyType     ...敵の種類
		258,     //m_texWidth      ...画像1枚横サイズ
		260,     //m_texHeight     ...画像1枚縦サイズ
		7,//10,       //m_frameRate     ...アニメーションの更新頻度
		20,      //m_hpMax         ...最大体力
		200,     //m_attackDamage  ...攻撃力
		100,     //m_hitDamage     ...当たったときのダメージ
		2,       //m_attackTexIndex...攻撃判定をする画像
		5,       //m_coinMax       ...所持コインの最大
		30,      //m_elecShockLimit...感電限界値
		1.5f,    //m_moveSpeed     ...移動速度
		0.4f,    //m_gravity       ...重力
		16.0f,   //m_jumpPower     ...ジャンプ力
		0.5f,    //m_scaleSize     ...拡大率
		100.0f,  //m_attackDis     ...攻撃可能射程
		60,      //m_attackHitDis  ...攻撃射程
		60,      //m_attackRadius  ...攻撃範囲
		50.0f,   //m_trackDist     ...追跡をする距離
		20.0f,   //m_noTrackDist   ...追跡をしない距離
		55.0f,   //m_hitWidth      ...当たり判定横サイズ
		55.0f,   //m_hitHeight     ...当たり判定縦サイズ
		{ 1,1,1,1 },//m_defaultColor...通常時の色
		{ 1,0,0,1 } //m_damageColor ...ダメージをくらったときの色
	)
{
	//固有変数の初期化
	m_pos = a_pos;  //座標
	m_scale.x = -m_scaleSize;
	m_nowAnim = WalkAnim;//現在のアニメーション
	m_isCastingSpell = true;
	m_isShieldActive = true;
	m_isShieldDamaged = false;
	m_isSurprised = false;
	m_isLanded = false;
	m_nowShieldState = ShieldState::ON;
	m_shieldDurability = m_shieldDurabilityMax;
	m_enemySpawner = nullptr;
	m_enemySpawnerTex = nullptr;
	m_enemySpawnerCrackTex = nullptr;
	m_shieldColor = { 1,1,1,1 };
	m_isHitWall = true;
}

C_LittleWitch::~C_LittleWitch()
{
	if (m_enemySpawner != nullptr)
	{
		delete m_enemySpawner;
	}
}

//初期化
void C_LittleWitch::Init()
{
	//画像セット
	m_nowEnemyTex = m_enemyTex + m_nowAnim;
}

//動作
void C_LittleWitch::Action(const Math::Vector2 a_playerPos)
{
	//存在していなかったらリターン
	if (!m_isAlive) return;


	//移動量初期化
	m_move.x = 0;

	//重力
	m_move.y -= m_gravity;

	//1フレームを進める
	if (m_frameCnt < INT_MAX)
	{
		m_frameCnt++;
	}
	else
	{
		m_frameCnt = 0;
	}

	//体力が0以下なら死亡フラグをONにして爆発
	if (m_hp <= 0 && !m_isDead)
	{
		m_isShieldActive = false;
		m_isDead = true;

		//死亡エフェクト
		m_eOwner->GetEffectManager()->SetBossDeathEffect(m_pos.x, m_pos.y, true);
	}

	//死亡フラグがONなら
	if (m_isDead)
	{
		AnimationUpdate(DeathAnim);//死亡アニメーション
		return;
	}

	//ダメージ処理
	Damage();

	//感電状態のセット
	ChangeElecShockState();

	//感電状態の更新
	UpdateElecShock();

	//感電状態であればリターン
	if (m_isElecShock)return;

	////スクロールの値を取得
	//const float scrollX = m_eOwner->GetMap()->GetScrollX();
	//const float scrollY = m_eOwner->GetMap()->GetScrollY();

	////画面内にいる場合はアクションフラグをON
	//if (m_pos.x - m_hitWidth - scrollX < SCREEN_RIGHT &&
	//	m_pos.x + m_hitWidth - scrollX > SCREEN_LEFT &&
	//	m_pos.y - m_hitHeight - scrollY < SCREEN_TOP &&
	//	m_pos.y + m_hitHeight - scrollY > SCREEN_BOTTOM)
	//{
	//	//m_isActive = true;
	//}

	//驚きフラグがONなら
	if (m_isSurprised)
	{
		//驚きアニメーション
		AnimationUpdate(SurprisedAnim);
		return;
	}

	//アクティブフラグがOFFならリターン
	if (!m_isActive)
	{
		AnimationUpdate(IdleAnim);
		return;
	}

	//壁にぶつかっていたらジャンプ
	if (m_isHitWall)
	{
		//ジャンプ
		Jump(m_jumpPower);
		m_isHitWall = false;
	}

	//敵スポナーが存在していなかったら
	if (m_enemySpawner == nullptr)
	{
		//魔法詠唱フラグON
		m_isCastingSpell = true;
	}

	//着地フラグがONなら
	if (m_isLanded)
	{
		AnimationUpdate(LandAnim);
		return;
	}

	//ジャンプフラグがONなら
	if (m_isJump)
	{
		//Yの移動量が正の値なら
		if (m_move.y > 0)
		{
			//ジャンプ
			AnimationUpdate(JumpAnim);
		}
		//Yの移動量が負の値なら
		else
		{
			//降下
			AnimationUpdate(FallAnim);
		}
		return;
	}

	//魔法詠唱フラグがONなら
	if (m_isCastingSpell)
	{
		//魔法を唱える
		AnimationUpdate(CastSpellAnim);
		return;
	}

	/*
	{
		//ロボットとプレイヤーの距離の計算
		const float a = m_pos.x - a_playerPos.x;//底辺a
		const float b = m_pos.y - a_playerPos.y;//高さb
		const float c = sqrt(a * a + b * b);  //斜辺(距離)c

		//攻撃判定フラグをOFF
		m_isAttackHit = false;

		//ジャンプしていなかったら
		if (!m_isJump)
		{
			//攻撃可能射程に入った又は攻撃フラグが立っている時
			if (c <= m_attackDis || m_isAttack)
			{
				m_isAttack = true;//攻撃フラグをON
				AnimationUpdate(Attack);//攻撃アニメーション

				//攻撃判定をする画像になったら
				if (m_texIndex == m_attackTexIndex)
				{
					//攻撃判定フラグをON
					m_isAttackHit = true;

					//攻撃座標の設定
					m_attackPos.x = m_scale.x > 0 ? m_pos.x - m_attackHitDis : m_pos.x + m_attackHitDis;
					m_attackPos.y = m_pos.y;
				}
				return;
			}
		}

		if (fabsf(a) < m_noTrackDist)//x座標の差が近すぎると追跡しない
		{
			m_isTracking = false;
		}
		else if (fabsf(a) > m_trackDist)//x座標の差が遠くなると追跡する
		{
			m_isTracking = true;
		}

		//追跡フラグがONなら
		if (m_isTracking)
		{
			//プレイヤーがいる方向に向かう
			m_move.x = a_playerPos.x < m_pos.x ? -m_moveSpeed : m_moveSpeed;
		}
		else
		{
			//向いている方向に合わせてスルー
			m_move.x = m_scale.x > 0 ? m_moveSpeed : -m_moveSpeed;
		}
	}
	*/

	//歩く
	AnimationUpdate(WalkAnim);
}

//更新
void C_LittleWitch::Update(const float a_scrollX, const float a_scrollY)
{
	//シールドの更新
	ShieldUpdate();

	//敵スポナーの更新
	if (m_enemySpawner != nullptr)
	{
		m_enemySpawner->Update(a_scrollX, a_scrollY);

		//存在していなかったら
		if (!m_enemySpawner->GetAlive())
		{
			//deleteして
			delete m_enemySpawner;

			//nullptrで初期化
			m_enemySpawner = nullptr;
		}
	}

	//存在していなかったらリターン
	if (!m_isAlive) return;

	//移動する方向に合わせて向いてる方向を変える
	if (m_move.x > 0)
	{
		m_scale.x = m_scaleSize;
	}
	else if (m_move.x < 0)
	{
		m_scale.x = -m_scaleSize;
	}


	//座標確定
	m_pos += m_move;

	//行列作成
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);     //拡大行列の作成
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x + m_shakeX - a_scrollX, m_pos.y - a_scrollY, 0);//移動行列の作成
	m_mat = m_scaleMat * m_transMat;//行列の合成

	//シールドの行列作成
	m_shieldScaleMat = Math::Matrix::CreateScale(m_shieldScaleSize, m_shieldScaleSize, 0);
	m_shieldMat = m_shieldScaleMat * m_transMat;
}

//描画
void C_LittleWitch::Draw()
{
	//敵スポナーの描画
	if (m_enemySpawner != nullptr)
	{
		m_enemySpawner->Draw();
	}

	//魔法少女の描画
	C_EnemyBase::Draw();

	//シールドの描画
	Math::Rectangle sRect = { m_shield.column * m_shield.texWidth,m_shield.row * m_shield.texHeight,
							m_shield.texWidth,m_shield.texHeight };

	//シールドのエフェクト時の色
	static Math::Color shieldEffectColor = { 1,1,1,0.5f };

	SHADER.m_spriteShader.SetMatrix(m_shieldMat);
	if (m_isShieldActive)
	{
		switch (m_nowShieldState)
		{
		case ShieldState::ON:
			SHADER.m_spriteShader.DrawTex(m_shieldTex + (int)m_nowShieldState, 0, 0, &sRect, &shieldEffectColor);
			break;
		case ShieldState::ACTIVE:
			SHADER.m_spriteShader.DrawTex(m_shieldTex + (int)m_nowShieldState, 0, 0, &sRect, &m_shieldColor);
			break;
		default:
			break;
		}
	}

	//シールドがダメージを受けたら
	if (m_isShieldDamaged)
	{
		SHADER.m_spriteShader.DrawTex(m_shieldTex + (int)ShieldState::OFF, 0, 0, &sRect, &shieldEffectColor);
	}
}

//マップ当たり判定用 Y調整
void C_LittleWitch::MapHitY(float a_posY, float a_moveY, bool a_jump)
{
	m_pos.y = a_posY;
	m_move.y = a_moveY;

	//ジャンプして
	if (m_isJump && !a_jump)
	{
		//着地フラグをON
		m_isLanded = true;
	}
	m_isJump = a_jump;
}

//アニメーション更新
void C_LittleWitch::AnimationUpdate(AnimationType a_animation)
{
	//別のアニメーションを行おうとしている場合
	if (m_nowAnim != a_animation)
	{
		//画像の切取位置を初期値に戻す
		m_texIndex = 0;

		//指定されたアニメーションを設定
		m_nowAnim = a_animation;

		//画像をセット
		m_nowEnemyTex = m_enemyTex + m_nowAnim;
		return;
	}

	//2フレームに1回アニメーションを更新
	if (m_frameCnt % m_frameRate == 0)
	{
		m_texIndex++;//画像の切取位置を進める
		switch (m_nowAnim)
		{
		case IdleAnim:
			//アニメーションをループ
			if (m_texIndex >= m_idleMax)m_texIndex = 0;
			break;
		case WalkAnim:
			//アニメーションをループ
			if (m_texIndex >= m_walkMax)m_texIndex = 0;
			break;
		case JumpAnim:
			//最後の画像までいったら
			if (m_texIndex >= m_jumpMax)
			{
				//最後の画像に維持
				m_texIndex = m_jumpMax - 1;
			}
			break;
		case FallAnim:
			//最後の画像までいったら
			if (m_texIndex >= m_fallMax)
			{
				//最後の画像を維持
				m_texIndex = m_fallMax - 1;
			}
			break;
		case LandAnim:
			//最後の画像までいったら
			if (m_texIndex >= m_landMax)
			{
				m_isLanded = false;
			}
			break;
		case AttackAnim:
			//最後の画像までいったら
			if (m_texIndex >= m_attackMax)
			{
				const float playerX = m_eOwner->GetChara()->GetPos().x;
				m_scale.x = m_pos.x > playerX ? -m_scaleSize : m_scaleSize;//プレイヤーの方向を向かせる
				m_texIndex = 0;//画像の切取位置を初期値に戻す
				m_isAttack = false;//攻撃フラグをOFF
			}
			break;
		case CastSpellAnim:
			//最後の画像までいったら
			if (m_texIndex >= m_castSpellMax)
			{
				m_texIndex = 0;
				m_isCastingSpell = false;
				CreateEnemySpawner();
			}
			break;
		case SurprisedAnim:
			//最後の画像までいったら
			if (m_texIndex >= m_surprisedMax)
			{
				m_isSurprised = false;
			}
			break;
		case DeathAnim:
			//最後の画像まで行ったら存在フラグをOFFにする
			if (m_texIndex >= m_deathMax && m_isAlive)
			{
				m_isAlive = false;
			}
			break;
		default:
			break;
		}
	}
}

//シールドの更新
void C_LittleWitch::ShieldUpdate()
{
	//sinカーブ
	static int sinAngle = 0;
	int angleStep;
	float sinValue;

	//シールドの耐久力が低いほど点滅を早める
	angleStep = m_shieldDurabilityMax - m_shieldDurability + 1;

	sinAngle += angleStep;
	if (sinAngle >= 360)
	{
		sinAngle -= 360;
	}

	//sin値を代入
	sinValue = fabsf(sin(ToRadians(sinAngle)));

	//最低保証
	sinValue += 0.1f;

	//シールドのアルファ値をセット
	m_shieldColor.A(sinValue);

	//シールドの耐久力が0以下なら
	if (m_shieldDurability <= 0)
	{
		//シールドアクティブフラグがONなら
		if (m_isShieldActive)
		{
			//驚く
			m_isSurprised = true;
		}

		//シールドを消す
		m_isShieldActive = false;
	}

	//フレームカウントがフレームレートで割り切れるとき
	if (m_frameCnt % m_shield.frameRate == 0)
	{
		//画像を進める
		m_shield.texIndex++;

		//画像が最後までいったら
		if (m_shield.texIndex >= m_shield.texNumMax)
		{
			//画像を初期画像に戻す
			m_shield.texIndex = 0;

			//シールドダメージフラグをOFF
			m_isShieldDamaged = false;

			switch (m_nowShieldState)
			{
			case ShieldState::ON:
				m_nowShieldState = ShieldState::ACTIVE;
				break;
			case ShieldState::ACTIVE:
				break;
			default:
				break;
			}
		}
		m_shield.row = m_shield.texIndex / m_shield.rowMax;//行数を取得
		m_shield.column = m_shield.texIndex % m_shield.columnMax;//列数を取得
	}
}

//敵スポナーの生成
void C_LittleWitch::CreateEnemySpawner()
{
	//敵スポナーが生成されていたら
	if (m_enemySpawner != nullptr)return;

	static std::random_device rd;
	static std::mt19937 gen(rd());
	EnemyType enemyType;

	//確率でボス召喚
	if (CheckProbability(m_bossSummonProbability))
	{
		static std::uniform_int_distribution<int> dist((int)EnemyType::BossRobot,(int)EnemyType::Skull);

		//ボスの中でランダム
		enemyType = (EnemyType)dist(gen);
	}
	//ボス召喚の確率が当たらなければ
	else
	{
		static std::uniform_int_distribution<int> dist((int)EnemyType::Robot, (int)EnemyType::Gremlin);

		//ボス以外の敵でランダム
		enemyType = (EnemyType)dist(gen);
	}

	const float setPosX = (float)(rand() % 700 - 300);
	const float setPosY = -1000;
	m_enemySpawner = new C_EnemySpawner(enemyType, { setPosX,setPosY });
	m_enemySpawner->SetTex(m_enemySpawnerTex);
	m_enemySpawner->SetCrackTex(m_enemySpawnerCrackTex);
	m_enemySpawner->SetOwner(m_eOwner);
	
	//死亡エフェクト
	m_eOwner->GetEffectManager()->SetBakuhatuEffect(setPosX, setPosY, true);
}

//飛行
void C_LittleWitch::Fly()
{
	m_move.x = m_flyMoveX;
	m_move.y = m_flyMoveY;
}

//感電蓄積値のセット
bool C_LittleWitch::SetElecShockGauge(int a_elecShockGauge)
{
	//シールドがアクティブなら
	if (m_isShieldActive)
	{
		//高電圧回避であればシールドアクティブフラグをOFF
		if (m_eOwner->GetChara()->GetNowAvoidType() == OverAvoid)
		{
			//シールドの耐久力を0に
			m_shieldDurability = 0;

			//シールドのアニメーションを初期画像に
			m_shield.texIndex = 0;
		}

		//リターン
		return false;
	}

	//感電蓄積値をセット
	m_elecShockGauge += a_elecShockGauge;
	return true;
}

//ダメージのセット
bool C_LittleWitch::SetDamage(int a_damage)
{
	//ダメージが0以下ならリターン
	if (a_damage <= 0)return false;

	//シールドがアクティブかつ
	if (m_isShieldActive)
	{
		//シールドの耐久力があるなら
		if (m_shieldDurability > 0)
		{
			//シールドの耐久力を減らす
			m_shieldDurability--;

			//シールドのアニメーションを初期画像に
			m_shield.texIndex = 0;

			//シールドの耐久力がまだあるなら
			if (m_shieldDurability > 0)
			{
				//シールドダメージフラグをON
				m_isShieldDamaged = true;
			}
		}
		return false;
	}

	m_hp -= a_damage;
	m_isDamage = true;
	return true;
}

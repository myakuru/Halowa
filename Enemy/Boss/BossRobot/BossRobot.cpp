#include "BossRobot.h"
#include "../../../Scene.h"
#include "../../../Constants.h"

//C_BossRobot::C_BossRobot(Math::Vector2 a_pos) :
//	C_EnemyBase(
//		//定数初期値セット
//		EnemyType::BossRobot, //m_enemyType     ...敵の種類
//		300,       //m_texWidth      ...画像1枚横サイズ
//		300,       //m_texHeight     ...画像1枚縦サイズ
//		2,         //m_frameRate     ...アニメーションの更新頻度
//		200,       //m_hpMax         ...最大体力
//		400,       //m_attackDamage  ...攻撃力
//		200,       //m_hitDamage     ...当たったときのダメージ
//		8,         //m_attackTexIndex...攻撃判定をする画像
//		30,        //m_coinMax       ...所持コインの最大
//		100,       //m_elecShockLimit...感電限界値
//		9.0f,      //m_moveSpeed     ...移動速度
//		0.9f,      //m_gravity       ...重力
//		15.0f,     //m_jumpPower     ...ジャンプ力
//		1.5f,      //m_scaleSize     ...拡大率
//		190.0f,    //m_attackRange   ...攻撃可能射程
//		120,       //m_attackHitDis  ...攻撃射程
//		120,       //m_attackRadius  ...攻撃範囲
//		150.0f,    //m_trackDist     ...追跡をする距離
//		120.0f,    //m_noTrackDist   ...追跡をしない距離
//		120.0f,    //m_hitWidth      ...当たり判定横サイズ
//		150.0f,     //m_hitHeight     ...当たり判定縦サイズ
//		{ 1,1,1,1 },//m_defaultColor...通常時の色
//		{ 1, 0, 0, 1 }//m_damageColor   ...ダメージをくらったときの色
//	)
//{
//	//固有変数初期化
//	m_nowAnim = IdleAnim;
//	m_animHallo = false;
//	m_isHighJump = true;
//	m_highJumpInterval = m_highJumpIntervalMax;
//	m_landingPosX = 0;
//	m_cooldownTime = 0;
//	m_smoke = nullptr;
//	m_smokeTex = nullptr;
//
//
//	//座標とprivate変数のセット
//	m_pos = a_pos;  //座標
//	m_scale.x = -m_scaleSize;//左を向かせる
//}

C_BossRobot::C_BossRobot(
	//敵共通定数セット用の引数
	int   a_hpMax,         //m_hpMax         ...最大体力
	int   a_attackDamage,  //m_attackDamage  ...攻撃力
	int   a_hitDamage,     //m_hitDamage     ...当たったときのダメージ
	int   a_coinMax,       //m_coinMax       ...所持コインの最大
	int   a_elecShockLimit,//m_elecShockLimit...感電限界値
	int   a_smokeDamage    //m_smokeDamage   ...煙のダメージ
) :
	C_EnemyBase(
		//定数初期値セット
		EnemyType::BossRobot, //m_enemyType     ...敵の種類
		300,             //m_texWidth      ...画像1枚横サイズ
		300,             //m_texHeight     ...画像1枚縦サイズ
		2,               //m_frameRate     ...アニメーションの更新頻度
		a_hpMax,         //m_hpMax         ...最大体力
		a_attackDamage,  //m_attackDamage  ...攻撃力
		a_hitDamage,     //m_hitDamage     ...当たったときのダメージ
		8,               //m_attackTexIndex...攻撃判定をする画像
		a_coinMax,       //m_coinMax       ...所持コインの最大
		a_elecShockLimit,//m_elecShockLimit...感電限界値
		9.0f,            //m_moveSpeed     ...移動速度
		0.9f,            //m_gravity       ...重力
		15.0f,           //m_jumpPower     ...ジャンプ力
		1.5f,            //m_scaleSize     ...拡大率
		190.0f,          //m_attackRange   ...攻撃可能射程
		120,             //m_attackHitDis  ...攻撃射程
		120,             //m_attackRadius  ...攻撃範囲
		150.0f,          //m_trackDist     ...追跡をする距離
		120.0f,          //m_noTrackDist   ...追跡をしない距離
		120.0f,          //m_hitWidth      ...当たり判定横サイズ
		150.0f,          //m_hitHeight     ...当たり判定縦サイズ
		{ 1, 1, 1, 1 },  //m_defaultColor  ...通常時の色
		{ 1, 0, 0, 1 }   //m_damageColor   ...ダメージをくらったときの色
	),
	m_smokeDamage(a_smokeDamage)
{
	m_isAlive = false;
}

C_BossRobot::C_BossRobot(Math::Vector2 a_pos, const C_BossRobot& a_enemyData) :
	C_EnemyBase(a_enemyData),
	m_smokeDamage(a_enemyData.m_smokeDamage)
{
	//固有変数初期化
	m_nowAnim = IdleAnim;
	m_animHallo = false;
	m_isHighJump = true;
	m_highJumpInterval = m_highJumpIntervalMax;
	m_landingPosX = 0;
	m_cooldownTime = 0;
	m_smoke = nullptr;
	m_smokeTex = nullptr;


	//座標とprivate変数のセット
	m_pos = a_pos;  //座標
	m_scale.x = -m_scaleSize;//左を向かせる
}

C_BossRobot::~C_BossRobot()
{
	//メモリを解放
	if (m_smoke != nullptr)
	{
		delete m_smoke;
	}
}

//初期化
void C_BossRobot::Init()
{
	m_nowEnemyTex = m_enemyTex + m_nowAnim;
}

//動作
void C_BossRobot::Action(const Math::Vector2 a_playerPos)
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

	//体力が0以下なら死亡フラグをON
	if (m_hp <= 0)m_isDead = true;

	//死亡フラグがONなら
	if (m_isDead)
	{
		m_texAngle += 10;//画像を回転
		m_scale *= {0.97f, 0.97f};//画像のサイズを小さく
		m_color.A(m_color.A() - 0.02f);//透明にしていく
		//死亡音声を再生していなかったら
		if ((*(m_enemySfx + DeathSfx))->IsPlay() == false)
		{
			//死亡音声を再生
			(*(m_enemySfx + DeathSfx))->Play();
		}
		AnimationUpdate(DeathAnim);
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


	//クールダウンタイムが終わっていなかったら
	if (m_cooldownTime > 0)
	{
		//地面の震えのフレーム間隔に合わせて
		if (m_frameCnt % m_seismicFrameRate == 0)
		{
			//マップのインスタンスを取得
			C_MapBase* map = m_eOwner->GetMap();

			//地震の値を入れる
			float seismicShakeX = rand() % 2 == 0 ? m_seismicShakePower : -m_seismicShakePower;
			float seismicShakeY = rand() % 2 == 0 ? m_seismicShakePower : -m_seismicShakePower;

			//地面を揺らす
			map->SetScrollX(map->GetScrollX() + seismicShakeX);
			map->SetScrollY(map->GetScrollY() + seismicShakeY);
		}

		//クールダウンタイムを減らす
		m_cooldownTime--;
	}

	//挨拶フラグがONなら
	if (m_animHallo)
	{
		AnimationUpdate(HelloAnim);
		return;
	}

	//アクティブフラグOFF
	//またはクールダウンタイムが残っていたら
	if (!m_isActive || m_cooldownTime > 0)
	{
		//立ち姿のアニメーションを行いリターン
		AnimationUpdate(IdleAnim);
		return;
	}

	//インターバルが終わると
	if (m_highJumpInterval <= 0)
	{
		//ハイジャンプをしていないとき
		if (!m_isHighJump)
		{
			//ジャンプできたら
			if (Jump(m_highJumpPower))
			{
				//プレイヤーの現在位置を取得して
				//着地場所に設定
				m_landingPosX = a_playerPos.x;

				//追跡をOFF
				m_isTracking = false;

				//ハイジャンプフラグをON
				m_isHighJump = true;
			}
		}
	}

	//インターバルをデクリメント
	if (m_highJumpInterval > 0)
	{
		m_highJumpInterval--;
	}

	//壁にぶつかっていたら
	if (m_isHitWall)
	{
		//ジャンプ
		Jump(m_jumpPower);
		m_isHitWall = false;
	}


	//ロボットとプレイヤーの距離の計算
	const float a = m_pos.x - a_playerPos.x;//底辺a
	const float b = m_pos.y - a_playerPos.y;//高さb
	const float c = sqrt(a * a + b * b);  //斜辺(距離)c
	
	//攻撃判定フラグをOFF
	m_isAttackHit = false;

	//ジャンプしていないとき
	if (!m_isJump)
	{
		//攻撃可能射程に入った又は攻撃フラグが立っている時
		if (c <= m_attackDis || m_isAttack)
		{
			m_isAttack = true;//攻撃フラグをON
			AnimationUpdate(AttackAnim);//攻撃アニメーション

			//攻撃判定をする画像になったら
			if (m_texIndex == m_attackTexIndex)
			{
				//攻撃判定フラグをON
				m_isAttackHit = true;

				//攻撃座標の設定
				m_attackPos.x = m_scale.x > 0 ? m_pos.x + m_attackHitDis : m_pos.x - m_attackHitDis;
				m_attackPos.y = m_pos.y;
			}
			return;
		}
	}


	//x座標の差が近すぎると追跡しない
	if (fabsf(a) < m_noTrackDist)
	{
		m_isTracking = false;
	}
	//x座標の差が遠くなると追跡
	else if (fabsf(a) > m_trackDist)
	{
		m_isTracking = true;
	}

	//ハイジャンプをしていたら
	if (m_isHighJump)
	{
		const float dis = fabsf(m_pos.x - m_landingPosX);
		if (dis > m_highJumpNoTrackDist)
		{
			//指定された着地場所に向かって追跡
			m_move.x = m_landingPosX < m_pos.x ? -m_moveSpeed : m_moveSpeed;
		}
	}
	//追跡フラグがONなら
	else if (m_isTracking)
	{
		//プレイヤーに向かって追跡
		m_move.x = a_playerPos.x < m_pos.x ? -m_moveSpeed : m_moveSpeed;
	}
	//追跡フラグがOFFなら
	else
	{
		//向いている方向に合わせてスルー
		m_move.x = m_scale.x < 0 ? -m_moveSpeed : m_moveSpeed;
	}
	//歩く
	AnimationUpdate(WalkAnim);

	//ジャンプしていなかったら
	if (!m_isJump)
	{
		//歩き音声を再生していなかったら
		if ((*(m_enemySfx + WalkSfx))->IsPlay() == false)
		{
			//歩き音声を再生
			(*(m_enemySfx + WalkSfx))->Play();
		}
	}
}

//更新
void C_BossRobot::Update(const float a_scrollX, const float a_scrollY)
{
	//存在していなかったらリターン
	if (!m_isAlive) return;

	//煙の更新
	if (m_smoke != nullptr)
	{
		m_smoke->Update(a_scrollX,a_scrollY);
		
		//煙が消えたら
		if (!m_smoke->GetAlive())
		{
			//メモリを解放
			delete m_smoke;

			//ポインタの中のアドレスを消去
			m_smoke = nullptr;
		}
	}

	//右に移動しようとしていたら
	if (m_move.x > 0)
	{
		//右を向かせる
		m_scale.x = m_scaleSize;
	}
	//左に移動しようとしていたら
	else if (m_move.x < 0)
	{
		//左を向かせる
		m_scale.x = -m_scaleSize;
	}
	
	//体力があったら
	if (m_hp > 0)
	{
		//座標確定
		m_pos += m_move;
	}

	//行列作成
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);     //拡大行列の作成
	m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(m_texAngle));//回転行列の作成
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x + m_shakeX - a_scrollX, m_pos.y + m_drawCorrY - a_scrollY, 0);//移動行列の作成
	m_mat = m_scaleMat * m_rotationMat * m_transMat;//行列の合成
}

//描画
void C_BossRobot::Draw()
{
	//煙の描画
	if (m_smoke != nullptr)
	{
		m_smoke->Draw();
	}

	//敵の描画
	C_EnemyBase::Draw();
}

//アニメーション更新
void C_BossRobot::AnimationUpdate(AnimationType a_animation)
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

	//アニメーションを更新
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
			if (m_texIndex >= m_walkingMax)m_texIndex = 0;
			break;
		case AttackAnim:
			//最後の画像まで行ったら
			if (m_texIndex >= m_attackMax)
			{
				const float playerX = m_eOwner->GetChara()->GetPos().x;
				m_scale.x = m_pos.x > playerX ? -m_scaleSize : m_scaleSize;//プレイヤーの方向を向かせる
				m_texIndex = 0;//画像の切取位置を初期値に戻す
				m_isAttack = false;//攻撃フラグをOFF
			}
			break;
		case DeathAnim:
			//最後の画像まで行ったら存在フラグをOFFにする
			if (m_texIndex >= m_deathMax)m_isAlive = false;
			break;
		case HelloAnim:
			if (m_texIndex >= m_helloMax)
			{
				m_texIndex = 0;//画像の切取位置を初期値に戻す
				m_animHallo = false;//挨拶フラグをOFF
			}
			break;
		default:
			break;
		}
	}
}

//マップ当たり判定用 Y調整
void C_BossRobot::MapHitY(float a_posY, float a_moveY, bool a_jump)
{
	C_EnemyBase::MapHitY(a_posY, a_moveY, a_jump);

	//ハイジャンプ後の着地をしていなければリターン
	if (!m_isHighJump || a_jump)return;

	//ハイジャンプフラグをOFF
	m_isHighJump = a_jump;

	//ハイジャンプ後の着地
	HighJumpLand();
}

//ハイジャンプ後の着地
void C_BossRobot::HighJumpLand()
{
	//インターバルをセット
	m_highJumpInterval = m_highJumpIntervalMax;

	//感電状態または体力が0以下ならリターン
	if (m_isElecShock || m_hp <= 0)return;

	//硬直時間のセット
	m_cooldownTime = m_cooldownTimeMax;

	//煙発生
	EmitSmoke();

	//着地音再生
	(*(m_enemySfx + LandingSfx))->Play();
}

//煙発生
void C_BossRobot::EmitSmoke()
{
	//ポインタにまだデータが入っていたらリターン
	if (m_smoke != nullptr) return;

	//メモリを確保しインスタンスの生成
	m_smoke = new C_Smoke(m_pos, m_smokeDamage);

	//生成されたインスタンスに煙画像をセット
	m_smoke->SetTex(m_smokeTex);
}

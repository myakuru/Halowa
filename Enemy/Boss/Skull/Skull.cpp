#include "Skull.h"
#include "../../../Scene.h"
#include "../../../Constants.h"

//C_Skull::C_Skull(Math::Vector2 a_pos) :
//	C_EnemyBase(
//		//定数初期値セット
//		EnemyType::Skull, //m_enemyType     ...敵の種類
//		147,   //m_texWidth      ...画像1枚横サイズ
//		146,   //m_texHeight     ...画像1枚縦サイズ
//		10,    //m_frameRate     ...アニメーションの更新頻度
//		400,   //m_hpMax         ...最大体力
//		400,   //m_attackDamage  ...攻撃力
//		200,   //m_hitDamage     ...当たったときのダメージ
//		0,     //m_attackTexIndex...攻撃判定をする画像
//		50,    //m_coinMax       ...所持コインの最大
//		250,   //m_elecShockLimit...感電限界値
//		8.0f,  //m_moveSpeed     ...移動速度
//		2.0f,  //m_gravity       ...重力
//		20.0f, //m_jumpPower     ...ジャンプ力
//		2.0f,  //m_scaleSize     ...拡大率
//		100.0f,//m_attackDis     ...攻撃可能射程
//		60,    //m_attackHitDis  ...攻撃射程
//		110,    //m_attackRadius  ...攻撃範囲
//		150.0f,//m_trackDist     ...追跡をする距離
//		120.0f,//m_noTrackDist   ...追跡をしない距離
//		110.0f,//m_hitWidth      ...当たり判定横サイズ
//		110.0f,//m_hitHeight     ...当たり判定縦サイズ
//		{ 1,1,1,1 },//m_defaultColor...通常時の色
//		{ 0, 0, 1, 0.5f } //m_damageColor   ...ダメージをくらったときの色
//	),
//	m_bonfire()
//{
//	//固有変数の初期化
//	m_fireVeilTex = nullptr;
//	m_fireballTex = nullptr;
//	m_bonfireTex = nullptr;
//	m_confusedTex = nullptr;
//	m_pos = a_pos;  //座標
//	m_nowAnim = FloatAnim;//現在のアニメーション
//	m_fireVeil.texIndex = 0;
//	m_fireVeil.row = 0;
//	m_fireVeil.column = 0;
//	m_rotationCount = 0;
//	m_rollingCount = 0;
//	m_waitTime = 60;
//	m_isRolling = false;
//	m_isConfused = false;
//	m_setMoveX = 0;
//	m_seismicTime = 0;
//	m_isFireVeilActive = false;
//	m_isAwakened = false;
//	m_isErupting = false;
//	m_fireballCount = 0;
//}

C_Skull::C_Skull(
	//敵共通定数セット用の引数
	int   a_hpMax,         //m_hpMax         ...最大体力
	int   a_attackDamage,  //m_attackDamage  ...攻撃力
	int   a_hitDamage,     //m_hitDamage     ...当たったときのダメージ
	int   a_coinMax,       //m_coinMax       ...所持コインの最大
	int   a_elecShockLimit,//m_elecShockLimit...感電限界値
	int   a_fireballDamage,//m_fireballDamage...火の玉のダメージ
	int   a_bonfireDamage  //m_bonfireDamage ...焚火のダメージ
) :
	C_EnemyBase(
		//定数初期値セット
		EnemyType::Skull,//m_enemyType     ...敵の種類
		147,             //m_texWidth      ...画像1枚横サイズ
		146,             //m_texHeight     ...画像1枚縦サイズ
		10,              //m_frameRate     ...アニメーションの更新頻度
		a_hpMax,         //m_hpMax         ...最大体力
		a_attackDamage,  //m_attackDamage  ...攻撃力
		a_hitDamage,     //m_hitDamage     ...当たったときのダメージ
		0,               //m_attackTexIndex...攻撃判定をする画像
		a_coinMax,       //m_coinMax       ...所持コインの最大
		a_elecShockLimit,//m_elecShockLimit...感電限界値
		8.0f,            //m_moveSpeed     ...移動速度
		2.0f,            //m_gravity       ...重力
		20.0f,           //m_jumpPower     ...ジャンプ力
		2.0f,            //m_scaleSize     ...拡大率
		100.0f,          //m_attackDis     ...攻撃可能射程
		60,              //m_attackHitDis  ...攻撃射程
		110,             //m_attackRadius  ...攻撃範囲
		150.0f,          //m_trackDist     ...追跡をする距離
		120.0f,          //m_noTrackDist   ...追跡をしない距離
		110.0f,          //m_hitWidth      ...当たり判定横サイズ
		110.0f,          //m_hitHeight     ...当たり判定縦サイズ
		{ 1,1,1,1 },     //m_defaultColor  ...通常時の色
		{ 0, 0, 1, 0.5f }//m_damageColor   ...ダメージをくらったときの色
	),
	m_fireballDamage(a_fireballDamage),
	m_bonfireDamage(a_bonfireDamage)
{
	m_isAlive = false;
}

C_Skull::C_Skull(Math::Vector2 a_pos, const C_Skull& a_enemyData) :
	C_EnemyBase(a_enemyData),
	m_fireballDamage(a_enemyData.m_fireballDamage),
	m_bonfireDamage(a_enemyData.m_bonfireDamage)
{
	//固有変数の初期化
	m_fireVeilTex = nullptr;
	m_fireballTex = nullptr;
	m_bonfireTex = nullptr;
	m_confusedTex = nullptr;
	m_pos = a_pos;  //座標
	m_nowAnim = FloatAnim;//現在のアニメーション
	m_fireVeil.texIndex = 0;
	m_fireVeil.row = 0;
	m_fireVeil.column = 0;
	m_rotationCount = 0;
	m_rollingCount = 0;
	m_waitTime = 60;
	m_isRolling = false;
	m_isConfused = false;
	m_setMoveX = 0;
	m_seismicTime = 0;
	m_isFireVeilActive = false;
	m_isAwakened = false;
	m_isErupting = false;
	m_fireballCount = 0;
}

C_Skull::~C_Skull()
{
	for (size_t i = 0; i < m_fireball.size(); i++)
	{
		delete m_fireball[i];
	}
	m_fireball.clear();
	for (size_t i = 0; i < m_bonfire.size(); i++)
	{
		delete m_bonfire[i];
	}
	m_bonfire.clear();
}

//初期化
void C_Skull::Init()
{
	//画像セット
	m_nowEnemyTex = m_enemyTex + m_nowAnim;
}

//動作
void C_Skull::Action(const Math::Vector2 a_playerPos)
{
	//火の玉動作
	for (size_t i = 0; i < m_fireball.size(); i++)
	{
		m_fireball[i]->Action();
	}
	//焚火動作
	for (size_t i = 0; i < m_bonfire.size(); i++)
	{
		m_bonfire[i]->Action();
	}

	//存在していなかったらリターン
	if (!m_isAlive)
	{
		//転がる音声を停止
		(*(m_enemySfx + RollingSfx))->Stop();
		return;
	}

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

	//体力が半分以下になったら
	if (m_hp < m_hpMax / 2)
	{
		//転がりフラグがOFFなら
		if (!m_isRolling)
		{
			//覚醒フラグをON
			m_isAwakened = true;
		}
	}
	//体力が0以下なら
	if (m_hp <= 0 && !m_isDead)
	{
		//死亡エフェクト
		m_eOwner->GetEffectManager()->SetBossDeathEffect(m_pos.x, m_pos.y, true);
		
		//爆発音声を再生
		(*(m_enemySfx + ExplosionSfx))->Play();
		
		//死亡フラグをON
		m_isDead = true;

		//混乱フラグをOFF
		m_isConfused = false;
	}

	//死亡フラグがONなら
	if (m_isDead)
	{
		//転がる音声を停止
		(*(m_enemySfx + RollingSfx))->Stop();

		//死亡アニメーション
		AnimationUpdate(DeathAnim);
		return;
	}

	//ダメージ処理
	Damage();

	//感電状態の変更
	ChangeElecShockState();

	//感電状態の更新
	UpdateElecShock();

	//感電状態であればリターン
	if (m_isElecShock)
	{
		//ファイアベールアクティブフラグをOFF
		m_isFireVeilActive = false;

		//転がる音声を停止
		(*(m_enemySfx + RollingSfx))->Stop();
		return;
	}

	//壁にぶつかっていたら
	if (m_isHitWall)
	{
		//転がり回数カウントを初期化
		m_rollingCount = 0;

		//回転回数を初期化
		m_rotationCount = 0;

		//転がりフラグをOFF
		m_isRolling = false;

		//攻撃判定フラグをOFF
		m_isAttackHit = false;

		//壁衝突フラグをOFF
		m_isHitWall = false;
		
		//混乱していたら
		if (m_isConfused)
		{
			//衝突音声を再生
			(*(m_enemySfx + CollisionSfx))->Play();

			//跳ねる
			Jump(m_jumpPower);

			//混乱時間を設定
			m_waitTime = m_confusionTimeMax;

			//地震の時間をセット
			m_seismicTime = m_seismicTimeMax;
		}
		else
		{
			m_texAngle = 0;

			//覚醒フラグがONなら
			if (m_isAwakened)
			{
				//噴火フラグがOFFなら
				if (!m_isErupting)
				{
					//噴火発生確率
					if (CheckProbability(m_eruptingProb))
					{
						//噴火フラグON
						m_isErupting = true;

						//火の玉の個数の設定
						m_fireballCount = m_fireballCountMax;
					}
				}
			}
		}
	}

	//地震の残り時間があったら
	if (m_seismicTime > 0)
	{
		//地震の時間を減らす
		m_seismicTime--;

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
	}

	//噴火フラグがONかつ転がりフラグがOFFなら
	if (m_isErupting && !m_isRolling)
	{
		//ファイアボールの発生間隔に合わせて
		if (m_frameCnt % m_fireballEmitRate == 0)
		{
			//ファイアボールの個数カウントが0より大きければ
			if (m_fireballCount > 0)
			{
				//ファイアボールの個数カウントを減らす
				m_fireballCount--;

				//火の玉発生
				EmitFireball();

				//ファイアベールアクティブフラグをOFF
				m_isFireVeilActive = false;

				//転がる音声を停止
				(*(m_enemySfx + RollingSfx))->Stop();

				//リターン
				return;
			}
			else
			{
				//噴火フラグをOFF
				m_isErupting = false;
			}
		}
	}

	//アクティブフラグがOFFまたは
	//待機時間なら
	if (!m_isActive || m_waitTime > 0)
	{
		//待機時間を減らす
		if (m_waitTime > 0)
		{
			m_waitTime--;
		}

		//転がる音声を停止
		(*(m_enemySfx + RollingSfx))->Stop();

		//混乱しているなら
		if (m_isConfused)
		{
			//ファイアベールアクティブフラグをOFF
			m_isFireVeilActive = false;

			//再生されてなかったら
			if (!(*(m_enemySfx + ConfusedSfx))->IsPlay())
			{
				//混乱音声を再生
				(*(m_enemySfx + ConfusedSfx))->Play();
			}
			return;
		}

		//その場で浮遊
		AnimationUpdate(FloatAnim);
		return;
	}

	//転がっていなかったら
	if (!m_isRolling)
	{
		//混乱フラグをOFF
		m_isConfused = false;

		//ボタン生成
		m_eOwner->GetGimicMgr()->GetButton()->SetButton();

		//混乱音声を停止
		(*(m_enemySfx + ConfusedSfx))->Stop();

		//転がっている時の横移動量を設定
		m_setMoveX = m_pos.x < a_playerPos.x ? m_moveSpeed : -m_moveSpeed;

		//画像の角度を0度
		m_texAngle = 0;

		//転がりフラグをON
		m_isRolling = true;

		//攻撃判定フラグをON
		m_isAttackHit = true;
	}

	//転がっていたら
	if (m_isRolling)
	{
		//覚醒フラグがONなら
		if (m_isAwakened)
		{
			//ファイアベールアクティブフラグをON
			m_isFireVeilActive = true;
		}

		//転がる音声を再生
		if (!(*(m_enemySfx + RollingSfx))->IsPlay())
		{
			(*(m_enemySfx + RollingSfx))->Play();
		}

		//プレイヤーの方向に移動量を入れる
		m_move.x = m_setMoveX;
		
		//確率で火をつける
		if (CheckProbability(m_bonfireProb))
		{
			EmitBonfire(m_pos);
		}
	}

	//右に移動するなら
	if (m_move.x > 0)
	{
		//左回転
		m_texAngle -= m_rotationAngle;

		//角度を0～359に補正
		if (m_texAngle < 0)
		{
			m_texAngle += 360;
		}

		//1回転したら
		if (m_texAngle == 0)
		{
			//回転回数をカウント
			m_rotationCount++;
		}

	}
	//左に移動するなら
	else if (m_move.x < 0)
	{
		//右回転
		m_texAngle += m_rotationAngle;

		//角度を0～359に補正
		if (m_texAngle >= 360)
		{
			m_texAngle -= 360;
		}

		//1回転したら
		if (m_texAngle == 0)
		{
			//回転回数をカウント
			m_rotationCount++;
		}
	}

	//回転回数カウントが回転回数の最大以下なら
	if (m_rotationCount >= m_rotationCountMax)
	{
		//画像の指標を戻す
		m_texIndex = 0;

		//画像の角度を0度
		m_texAngle = 0;

		//回転回数を初期化
		m_rotationCount = 0;

		//転がり回数をカウント
		m_rollingCount++;

		//転がり回数カウントが転がり回数の最大未満なら
		if (m_rollingCount < m_rollingCountMax)
		{
			//休憩時間を設定
			m_waitTime = m_restTimeMax;

			//転がりフラグをOFF
			m_isRolling = false;

			//攻撃判定フラグをOFF
			m_isAttackHit = false;

			//覚醒フラグがONなら
			if (m_isAwakened)
			{
				//噴火フラグがOFFなら
				if (!m_isErupting)
				{
					//噴火発生確率
					if (CheckProbability(m_eruptingProb))
					{
						//噴火フラグON
						m_isErupting = true;

						//火の玉の個数の設定
						m_fireballCount = m_fireballCountMax;
					}
				}
			}
		}
	}
}

//更新
void C_Skull::Update(const float a_scrollX, const float a_scrollY)
{
	//火の玉更新
	for (size_t i = 0; i < m_fireball.size(); i++)
	{
		m_fireball[i]->Update(a_scrollX, a_scrollY);

		if (!m_fireball[i]->GetGroundHit())continue;

		//着弾座標の取得
		Math::Vector2 fireballPos = m_fireball[i]->GetPos();

		//着弾座標に焚火を発生
		EmitBonfire(fireballPos);

		//削除処理
		delete m_fireball[i];

		auto itr = m_fireball.begin();

		m_fireball.erase(itr + i);
	}

	//焚火の更新
	for (size_t i = 0; i < m_bonfire.size(); i++)
	{
		m_bonfire[i]->Update(a_scrollX, a_scrollY);

		//削除処理
		if (m_bonfire[i]->GetAlive())continue;

		delete m_bonfire[i];

		auto itr = m_bonfire.begin();

		m_bonfire.erase(itr + i);
	}
	
	//ファイアベールエフェクトの更新
	EffectUpdate(&m_fireVeil);
	
	//存在していなかったらリターン
	if (!m_isAlive) return;

	//混乱状態だったら
	if (m_isConfused)
	{
		//混乱エフェクトの更新
		EffectUpdate(&m_confused);
	}

	//移動する方向に合わせて向いてる方向を変える
	if (m_move.x > 0)
	{
		m_scale.x = -m_scaleSize;
	}
	else if (m_move.x < 0)
	{
		m_scale.x = m_scaleSize;
	}


	//座標確定
	m_pos += m_move;

	//行列作成
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);     //拡大行列の作成
	m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(m_texAngle));//回転行列の作成
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x + m_shakeX - a_scrollX, m_pos.y - a_scrollY, 0);//移動行列の作成
	m_mat = m_scaleMat * m_rotationMat * m_transMat;//行列の合成

	//火のベールの行列作成
	m_fireVeilScaleMat = Math::Matrix::CreateScale(m_fireVeilScaleSize, m_fireVeilScaleSize, 0);//拡大行列の作成
	m_fireVeilMat = m_fireVeilScaleMat * m_transMat;
}

void C_Skull::Draw()
{
	//火の玉の描画
	for (size_t i = 0; i < m_fireball.size(); i++)
	{
		m_fireball[i]->Draw();
	}

	//ファイアベールの描画
	Math::Rectangle fRect = { m_fireVeil.column * m_fireVeil.texWidth,m_fireVeil.row * m_fireVeil.texHeight,
								m_fireVeil.texWidth,m_fireVeil.texHeight };
	Math::Color fColor = { 1,1,1,0.5f };
	if (m_isFireVeilActive)
	{
		D3D.SetBlendState(BlendMode::Add);
		SHADER.m_spriteShader.SetMatrix(m_fireVeilMat);
		SHADER.m_spriteShader.DrawTex(m_fireVeilTex, 0, 0, &fRect, &fColor);
		D3D.SetBlendState(BlendMode::Alpha);
	}

	//敵の描画
	C_EnemyBase::Draw();

	//ファイアベールの描画
	if (m_isFireVeilActive)
	{
		D3D.SetBlendState(BlendMode::Add);
		SHADER.m_spriteShader.SetMatrix(m_fireVeilMat);
		SHADER.m_spriteShader.DrawTex(m_fireVeilTex, 0, 0, &fRect, &fColor);
		D3D.SetBlendState(BlendMode::Alpha);
	}

	//焚火描画
	for (size_t i = 0; i < m_bonfire.size(); i++)
	{
		m_bonfire[i]->Draw();
	}

	//混乱していなければリターン
	if (m_isConfused)
	{
		//混乱画像
		Math::Rectangle cRect = { m_confused.texIndex * m_confused.texWidth,0,
								  m_confused.texWidth,m_confused.texHeight };
		Math::Color cColor = { 1,1,1,1 };
		SHADER.m_spriteShader.SetMatrix(m_transMat);
		SHADER.m_spriteShader.DrawTex(m_confusedTex, 0, 0, &cRect, &cColor);
	}
}

//火の玉発生関数
void C_Skull::EmitFireball()
{
	//発射音
	(*(m_enemySfx + ShotSfx))->Play();
	m_fireball.push_back(new C_Fireball(m_pos, m_fireballDamage));
	m_fireball.back()->SetTex(m_fireballTex);
}

//焚火発生関数
void C_Skull::EmitBonfire(Math::Vector2 a_pos)
{
	//発火音声を再生
	(*(m_enemySfx + IgnitionSfx))->Play();
	m_bonfire.push_back(new C_Bonfire(a_pos, m_bonfireDamage));
	m_bonfire.back()->SetTex(m_bonfireTex);
}

//アニメーション更新
void C_Skull::AnimationUpdate(AnimationType a_animation)
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
		case FloatAnim:
			//アニメーションをループ
			if (m_texIndex >= m_floatMax)m_texIndex = 0;
			break;
		case DeathAnim:
			//最後の画像まで行ったら存在フラグをOFFにする
			if (m_texIndex >= m_deathMax && m_isAlive)m_isAlive = false;
			break;
		default:
			break;
		}
	}
}

void C_Skull::MapHitX(float a_posX, float a_moveX, char a_mapData)
{
	C_EnemyBase::MapHitX(a_posX, a_moveX);

	//透明ブロックにぶつかっていた場合
	if (a_mapData == '!')
	{
		//休憩時間をセット
		m_waitTime = m_restTimeMax;
	}
	//透明ブロック以外なら
	else
	{
		//混乱フラグをON
		m_isConfused = true;
	}
}
#include "Coin.h"

C_Coin::C_Coin(Math::Vector2 a_pos) : 
	m_eTex(nullptr),
	m_pos(a_pos)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	//-10～10の乱数
	std::uniform_real_distribution<> distX(0.0f, 10.0f);
	float moveX = distX(gen) * (rand() % 2 == 0 ? 1 : -1);
	
	//5～15の乱数
	std::uniform_real_distribution<> distY(5.0f, 15.0f);
	float moveY = distY(gen);

	//変数の初期化
	m_isAlive = true;
	m_isActive = false;
	m_move = { moveX,moveY };
	m_scale = { m_scaleSize,m_scaleSize };
	m_color = { 1,1,1,1 };
	m_lifespan = m_lifespanMax;
	m_frameCnt = 0;
	m_sinAngle = 0;
}

//動作
void C_Coin::Action(const Math::Vector2 playerPos)
{
	//生存フラグがOFFならリターン
	if (!m_isAlive)return;

	//移動量の減衰
	m_move.x *= 0.97;

	//重力
	m_move.y -= m_gravity;
	
	//残り生存時間が9割を切ったら
	if (m_lifespan < m_noActiveLifespan)
	{
		//アクティブフラグをON
		m_isActive = true;
	}

	//アクティブフラグがOFFならリターン
	if (!m_isActive)return;

	//プレイヤーとの距離を求める
	const float a = m_pos.x - playerPos.x;
	const float b = m_pos.y - playerPos.y;
	const float c = sqrt(a * a + b * b);

	//プレイヤーとの距離が追跡する距離より近かったら
	if (c < m_trackDist)
	{
		//コインがプレイヤーより左にあったら
		if (a < 0.0f)
		{
			//右に行く
			m_move.x = m_moveSpeed;
		}
		//コインがプレイヤーより右にあったら
		else
		{
			//左に行く
			m_move.x = -m_moveSpeed;
		}
	}
}

//更新
void C_Coin::Update(const float a_scrollX, const float a_scrollY)
{
	//表示時間を減らしていく
	if (m_lifespan > 0)
	{
		m_lifespan--;
	}
	//表示時間がなくなったら
	else
	{
		//生存フラグ消す
		m_isAlive = false;
	}

	//生存フラグがOFFならリターン
	if (!m_isAlive)return;

	//フレームを進める
	m_frameCnt++;

	//表示時間が少なくなったら点滅させる
	if (m_lifespan < m_lifespanBlink)
	{
		//指定されたフレームごとに
		if (m_frameCnt % m_lifeDecayFrameRate == 0)
		{
			//不透明だったら
			if (m_color.A() == 1.0f)
			{
				//半透明にする
				m_color.A(0.1f);
			}
			//半透明だったら
			else
			{
				//不透明にする
				m_color.A(1.0f);
			}
		}
	}

	//サインカーブ用角度を増やす
	m_sinAngle += 3;
	
	//0～359度に調整する
	if (m_sinAngle >= 360)
	{
		m_sinAngle -= 360;
	}

	//X軸回転
	m_scale.x = sin(ToRadians(m_sinAngle));

	//座標確定
	m_pos += m_move;
	
	//拡大行列作成
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);

	//移動行列作成
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - a_scrollX, m_pos.y - a_scrollY, 0);

	//合成行列の作成
	m_mat = m_scaleMat * m_transMat;
}

//描画
void C_Coin::Draw()
{
	//生存フラグがOFFならリターン
	if (!m_isAlive)return;

	//切取判定をセット
	const Math::Rectangle rect = { 0,0,m_texHeight,m_texWidth };

	//行列のセット
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//描画
	SHADER.m_spriteShader.DrawTex(m_eTex, 0, 0, &rect, &m_color);
}

//マップ当たり判定用 X調整
void C_Coin::MapHitX(float a_posX, float a_moveX)
{
	m_pos.x = a_posX;
	m_move.x = a_moveX;
}

//マップ当たり判定用 Y調整
void C_Coin::MapHitY(float a_posY, float a_moveY)
{
	m_pos.y = a_posY;
	m_move.y = a_moveY;
}

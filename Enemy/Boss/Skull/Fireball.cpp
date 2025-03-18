#include "Fireball.h"

C_Fireball::C_Fireball(Math::Vector2 a_pos, int a_damage) :m_fTex(nullptr), m_damage(a_damage)
{
	m_pos = a_pos;
	m_scale = { m_scaleSize,m_scaleSize };
	m_isAlive = true;
	m_isGroundHit = false;
	m_frameCnt = 0;
	m_texRow = 0;
	m_texColumn = 0;
	m_texIndex = 0;

	//乱数シード
	static std::random_device rd;
	static std::mt19937 gen(rd());

	//飛んでいく角度のの乱数
	static std::uniform_real_distribution<> dist(60.0f, 120.0f);

	//画像の角度に乱数を代入
	m_texAngle = dist(gen);

	//角度に合わせた移動量を入れる
	m_move.x = cos(ToRadians(m_texAngle)) * m_initialMoveSpeed;
	m_move.y = sin(ToRadians(m_texAngle)) * m_initialMoveSpeed;
}

void C_Fireball::Action()
{
	//存在していなかったらまたは着弾したらリターン
	if (!m_isAlive || m_isGroundHit)return;

	//重力
	m_move.y -= m_gravity;
}

void C_Fireball::Update(float a_scrollX, float a_scrollY)
{
	//存在していなかったらまたは着弾したらリターン
	if (!m_isAlive || m_isGroundHit)return;

	//1フレームを進める
	if (m_frameCnt < INT_MAX)
	{
		m_frameCnt++;
	}
	else
	{
		m_frameCnt = 0;
	}

	//移動量に合わせた角度にする
	m_texAngle = ToDegrees(atan2(m_move.y, m_move.x));

	//座標確定
	m_pos += m_move;

	//アニメーション更新
	//アニメーションフレームレートに合わせて更新
	if (m_frameCnt % m_animFrameRate == 0)
	{
		//画像を進める
		m_texIndex++;

		//画像をループする
		if (m_texIndex >= m_texNumMax)
		{
			m_texIndex = 0;
		}

		//列取得
		m_texColumn = m_texIndex / m_texRowMax;

		//行取得
		m_texRow = m_texIndex % m_texColumnMax;
	}

	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);//拡大行列作成
	m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(m_texAngle));//回転行列作成
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - a_scrollX, m_pos.y - a_scrollY, 0);//移動行列作成
	m_mat = m_scaleMat * m_rotationMat * m_transMat;//行列合成
}

void C_Fireball::Draw() const
{
	//存在していなかったらまたは着弾したらリターン
	if (!m_isAlive || m_isGroundHit)return;

	Math::Rectangle rect = { m_texRow * m_texWidth,m_texColumn * m_texHeight,
								m_texWidth,m_texHeight };
	Math::Color color = { 1,1,1,1 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_fTex, 0, 0, &rect, &color);
}

//マップ当たり判定用 X調整
void C_Fireball::MapHitX(float a_posX, float a_moveX)
{
	m_pos.x = a_posX;
	m_move.x = a_moveX;
}

//マップ当たり判定用 Y調整
void C_Fireball::MapHitY(float a_posY, float a_moveY, bool a_isGroundHit)
{
	m_pos.y = a_posY;
	m_move.y = a_moveY;
	m_isGroundHit = a_isGroundHit;
}

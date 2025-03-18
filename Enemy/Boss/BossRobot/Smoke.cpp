#include "Smoke.h"
#include "../../../Scene.h"

C_Smoke::C_Smoke(Math::Vector2 a_pos, int a_damage) : m_sTex(nullptr), m_damage(a_damage)
{
	m_isAlive = true;
	m_isHitChk = false;
	m_texIndex = 0;
	m_frameCnt = 0;
	m_pos.x = a_pos.x;
	m_pos.y = a_pos.y - 100;
	m_scale = { m_scaleSize,m_scaleSize };
}

void C_Smoke::Update(float a_scrollX, float a_scrollY)
{
	if (!m_isAlive)return;

	m_frameCnt++;

	//当たり判定フラグをOFF
	m_isHitChk = false;

	if (m_frameCnt % m_animFrameRate == 0)
	{
		m_texIndex++;

		if (m_texIndex == m_damageTexIndex)
		{
			//当たり判定フラグをON
			m_isHitChk = true;
		}
		else if (m_texIndex >= m_texNumMax)
		{
			m_isAlive = false;
		}
	}

	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - a_scrollX, m_pos.y - a_scrollY + m_drawCorrY, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Smoke::Draw() const
{
	if (!m_isAlive)return;

	Math::Rectangle rect = {m_texWidth * m_texIndex,0,m_texWidth,m_texHeight };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_sTex, rect);



	////仮
	//if (m_texIndex != m_damageTexIndex)return;
	//SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	//SHADER.m_spriteShader.DrawBox(m_pos.x, m_pos.y, m_hitWidth, m_hitHeight, &Math::Color{ 1,1,1,0.3f });
}

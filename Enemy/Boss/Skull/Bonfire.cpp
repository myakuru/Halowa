#include "Bonfire.h"

C_Bonfire::C_Bonfire(Math::Vector2 a_pos, int a_damage): m_bTex(nullptr), m_damage(a_damage)
{
	m_pos.x = a_pos.x;
	m_pos.y = a_pos.y;
	m_isAlive = true;
	m_frameCnt = 0;
	m_texIndex = 0;
	m_texColumn = 0;
	m_texRow = 0;
	m_scale = { m_scaleSize,m_scaleSize };
	m_isActive = false;
	m_isHitChk = false;	
	m_moveY = 0;
}

void C_Bonfire::Action()
{
	if (m_isActive)return;
	//d—Í
	m_moveY -= m_gravity;
}

void C_Bonfire::Update(float a_scrollX, float a_scrollY)
{
	if (!m_isAlive)return;

	if (m_isActive)
	{
		m_pos.y += m_moveY;
	}
	else
	{
		return;
	}

	m_frameCnt++;

	if (m_frameCnt % m_animFrameRate == 0)
	{
		m_texIndex++;

		if (m_texIndex == m_startHitChkTexIndex)
		{
			m_isHitChk = true;
		}
		else if (m_texIndex >= m_texNumMax)
		{
			m_isAlive = false;
		}
		m_texRow = m_texIndex / m_texRowMax;
		m_texColumn = m_texIndex % m_texColumnMax;
	}

	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - a_scrollX, m_pos.y - a_scrollY + m_drawCorrY , 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Bonfire::Draw() const
{
	if (!m_isAlive) return;
	if (!m_isActive)return;

	Math::Rectangle rect = { m_texColumn * m_texWidth,m_texRow * m_texHeight,
								m_texWidth,m_texHeight };
	Math::Color color = { 1,1,1,1 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_bTex, 0, 0, &rect, &color);

	////‰¼
	//SHADER.m_spriteShader.SetMatrix(m_mat);
	//SHADER.m_spriteShader.DrawBox(0, 0, m_hitWidth, m_hitHeight, &Math::Color{ 1,1,1,0.3f });
	//SHADER.m_spriteShader.DrawCircle(0,0,10, &Math::Color{ 1,1,1,0.3f });
}

void C_Bonfire::MapHitY(float a_posY, float a_moveY)
{
	m_pos.y = a_posY;
	m_moveY = a_moveY;
	m_isActive = true;
}

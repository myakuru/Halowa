#include "ButtonBase.h"
#include"../Scene.h"

void C_ButtonBase::Init()
{
	buttonHit = false;
	m_button.scale = 2.0f;
}

void C_ButtonBase::Update()
{
	C_MapBase* map = m_owner->GetMap();

	if (nextStage) {
		m_button.scaleMat = Math::Matrix::CreateScale(m_button.scale, m_button.scale, 1.0f);
		m_button.rotateMat = Math::Matrix::CreateRotationZ(ToRadians(-90));
		m_button.transMat = Math::Matrix::CreateTranslation(m_button.pos.x - map->GetScrollX(), m_button.pos.y - map->GetScrollY(), 0);
		m_button.mat = m_button.scaleMat * m_button.rotateMat * m_button.transMat;
	}
}

void C_ButtonBase::Draw()
{
	if (nextStage) {
		if (!buttonHit) {
			SHADER.m_spriteShader.SetMatrix(m_button.mat);
			SHADER.m_spriteShader.DrawTex(m_buttonbaseTex, Math::Rectangle(0, 0, 32, 32), 1.0f);
		}
	}
}

void C_ButtonBase::SetButtonPos(Math::Vector2 pos)
{
	nextStage = true;
	buttonHit = false;
	EffectOnce = false;
	m_button.pos = pos;
}

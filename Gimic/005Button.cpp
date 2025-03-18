#include "005Button.h"
#include "../Scene.h"

void C_005Button::ButtonInit()
{
	buttonHit = false;
	Once = false;

	m_message.transparent = 0.0f;
	fading = false;
	//���ʏ����l
	//vol = 0.4f; //MAX��1.0f

	//SE
	//�@�������̈�̊m��
	se = std::make_shared<KdSoundEffect>();

	//�A���f�[�^�̓ǂݍ���
	se->Load("Sound/Gimic/anvilhammer.WAV");

	//�B�X�s�[�J�[�̃������m�ہ����f�[�^��n��
	seInst = se->CreateInstance(false);
	//seInst->SetVolume(vol); //�{�����[������(�Z�b�^�[�ŉ��𗬂�)
}

void C_005Button::ButtonUpdate()
{
	C_MapBase* map = m_owner->GetMap();
	Scene& scene = SCENE;

	if (nextStage) {
		if (!EffectOnce) {
			scene.GetEffectManager()->SetTechSquareEffect(m_button.pos.x, m_button.pos.y, true);
			EffectOnce = true;
		}
		if (buttonHit && !Once) {
			scene.GetEffectManager()->GetTechSquareEffect()->Init();
			Once = true;
			m_owner->GetGimicMgr()->GetBCButton()->SetEffect(true);
		}

		static int frame = 0;

		if (buttonHit) {
			for (int w = 44; w < 46; w++) {
				for (int h = 32; h < 36; h++) {
					map->ChangeMapData(h, w, '0');
				}
			}
			frame++;

			if (!fading) {
				m_message.transparent += 0.1f;
				if (m_message.transparent >= 1.0f) {
					m_message.transparent = 1.0f;
					fading = true;
				}
			}
			else if (frame >= 120) {
				m_message.transparent -= 0.01f;
				if (m_message.transparent <= 0.0f) {
					m_message.transparent = 0.0f;
				}
			}
		}

		m_message.scaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 1.0f);
		m_message.transMat = Math::Matrix::CreateTranslation(0, 0, 0);
		m_message.mat = m_message.scaleMat * m_message.transMat;
	}
}

void C_005Button::ButtonDraw()
{
	if (nextStage) {
		SHADER.m_spriteShader.SetMatrix(m_message.mat);
		SHADER.m_spriteShader.DrawTex(&m_messageTex, Math::Rectangle(0, 0, 1280, 720), m_message.transparent);
	}
}

void C_005Button::PlaySE()
{
	seInst->Play(); //���[�v�Đ��I�t
}

void C_005Button::Load()
{
	m_messageTex.Load("Texture/Gimic/messagewall.png");
}

void C_005Button::Release()
{
	m_messageTex.Release();
}

//void C_BRButton::SELoad()
//{
//}

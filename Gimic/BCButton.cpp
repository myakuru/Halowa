#include "BCButton.h"
#include "../Scene.h"

void C_BCButton::ButtonInit()
{
	buttonHit = false;
	nextEffect = false;
	Once = false;

	m_message.transparent = 0.0f;
	fading = false;
	//���ʏ����l
	//vol = 0.4f; //MAX��1.0f

	//SE
	//�@�������̈�̊m��
	se = std::make_shared<KdSoundEffect>();

	//�A���f�[�^�̓ǂݍ���
	se->Load("Sound/Gimic/cartoon.wav");

	//�B�X�s�[�J�[�̃������m�ہ����f�[�^��n��
	seInst = se->CreateInstance(false);
	//seInst->SetVolume(vol); //�{�����[������(�Z�b�^�[�ŉ��𗬂�)
}

void C_BCButton::ButtonUpdate()
{
	C_MapBase* map = m_owner->GetMap();

	Scene& scene = SCENE;

	if (nextStage) {
		if (!EffectOnce && nextEffect) {
			scene.GetEffectManager()->SetTechSquareEffect(m_button.pos.x, m_button.pos.y, true);
			EffectOnce = true;
		}
		if (buttonHit && !Once) {
			scene.GetEffectManager()->GetTechSquareEffect()->Init();
			Once = true;
			m_owner->GetGimicMgr()->GetRodButton()->SetEffect(true);
		}

		static int frame = 0;
		static int frame2 = 0;

		if (buttonHit) {
			if (frame % 4 == 0) // 4�t���[�����Ƃ�1�̃}�b�v�f�[�^��ύX
			{
				static int i = 0;
				static int j = 0;

				map->ChangeMapData(42 + i, 74 + j, '0');

				j++;
				if (j >= 2)
				{
					j = 0;
					i++;
				}
				if (i >= 6)
				{
					i = 0;
				}
			}
			if (frame2 % 4 == 0) // 4�t���[�����Ƃ�1�̃}�b�v�f�[�^��ύX
			{
				static int i = 0;
				static int j = 0;

				map->ChangeMapData(48 + i, 67 + j, 'B');

				i++;
				if (i >= 1)
				{
					i = 0;
					j++;
				}
				if (j >= 7)
				{
					j = 0;
				}
			}
			frame++;
			frame2++;

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

void C_BCButton::ButtonDraw()
{
	if (nextStage) {
		SHADER.m_spriteShader.SetMatrix(m_message.mat);
		SHADER.m_spriteShader.DrawTex(&m_messageTex, Math::Rectangle(0, 0, 1280, 720), m_message.transparent);
	}
}

void C_BCButton::PlaySE()
{
	seInst->Play(); //���[�v�Đ��I�t
}

void C_BCButton::Load()
{
	m_messageTex.Load("Texture/Gimic/messagebridge.png");
}

void C_BCButton::Release()
{
	m_messageTex.Release();
}

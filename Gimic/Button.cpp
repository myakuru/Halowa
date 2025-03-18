#include "Button.h"
#include"../Scene.h"

void C_Button::Init()
{
	buttonActive = false;
	buttonHit = false;
	blockAlive = false;

	m_button.scale = 2.0f;

	buttonNum = 2;

	//���ʏ����l
	//vol = 0.4f; //MAX��1.0f

	//SE
	//�@�������̈�̊m��
	se = std::make_shared<KdSoundEffect>();

	//�A���f�[�^�̓ǂݍ���
	se->Load("Sound/Gimic/Electric_Shock02-1(Short).WAV");

	//�B�X�s�[�J�[�̃������m�ہ����f�[�^��n��
	seInst = se->CreateInstance(false);
	//seInst->SetVolume(vol); //�{�����[������(�Z�b�^�[�ŉ��𗬂�)
}

void C_Button::Update()
{
	C_MapBase* map = m_owner->GetMap();
	Scene& scene = SCENE;

	if (nextStage) {
		if (buttonActive) {
			if (buttonHit) {
				for (h = 10 - 1; h < 14 - 1; h++) {
					w = (7 - 1) + (3 * buttonNum);
					map->ChangeMapData(h, w, 'W');
					blockAlive = true;
				}
			}
			m_button.pos = { -258 + ((float)buttonNum * 192),-410 };

			//�O�ɂ����`�b�v�̈ʒu�ɉ��G�t�F�N�g���Đ�
			if (!EffectOnce) {
				scene.GetEffectManager()->SetTechSquareEffect(m_button.pos.x, m_button.pos.y, true);
				EffectOnce = true;
			}

			if (buttonHit) {
				buttonActive = false;
				scene.GetEffectManager()->GetTechSquareEffect()->Init();
			}

			m_button.scaleMat = Math::Matrix::CreateScale(m_button.scale, m_button.scale, 1.0f);
			m_button.rotateMat = Math::Matrix::CreateRotationZ(ToRadians(-90));
			m_button.transMat = Math::Matrix::CreateTranslation(m_button.pos.x - map->GetScrollX(), m_button.pos.y - map->GetScrollY(), 0);
			m_button.mat = m_button.scaleMat * m_button.rotateMat * m_button.transMat;
		}
	}
}

void C_Button::Draw()
{
	if (nextStage) {
		if (buttonActive) {
			SHADER.m_spriteShader.SetMatrix(m_button.mat);
			SHADER.m_spriteShader.DrawTex(m_buttonTex, Math::Rectangle(0, 0, 32, 32), 1.0f);
		}
	}
}

void C_Button::PlaySE()
{
	//���Đ�
	seInst->Play(); //���[�v�Đ��I�t
}

void C_Button::SetButton()
{
	if (buttonActive || blockAlive)return;
	nextStage = true;
	buttonActive = true;
	buttonHit = false;
	buttonNum = rand() % 12;
	EffectOnce = false;
}

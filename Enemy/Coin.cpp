#include "Coin.h"

C_Coin::C_Coin(Math::Vector2 a_pos) : 
	m_eTex(nullptr),
	m_pos(a_pos)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	//-10�`10�̗���
	std::uniform_real_distribution<> distX(0.0f, 10.0f);
	float moveX = distX(gen) * (rand() % 2 == 0 ? 1 : -1);
	
	//5�`15�̗���
	std::uniform_real_distribution<> distY(5.0f, 15.0f);
	float moveY = distY(gen);

	//�ϐ��̏�����
	m_isAlive = true;
	m_isActive = false;
	m_move = { moveX,moveY };
	m_scale = { m_scaleSize,m_scaleSize };
	m_color = { 1,1,1,1 };
	m_lifespan = m_lifespanMax;
	m_frameCnt = 0;
	m_sinAngle = 0;
}

//����
void C_Coin::Action(const Math::Vector2 playerPos)
{
	//�����t���O��OFF�Ȃ烊�^�[��
	if (!m_isAlive)return;

	//�ړ��ʂ̌���
	m_move.x *= 0.97;

	//�d��
	m_move.y -= m_gravity;
	
	//�c�萶�����Ԃ�9����؂�����
	if (m_lifespan < m_noActiveLifespan)
	{
		//�A�N�e�B�u�t���O��ON
		m_isActive = true;
	}

	//�A�N�e�B�u�t���O��OFF�Ȃ烊�^�[��
	if (!m_isActive)return;

	//�v���C���[�Ƃ̋��������߂�
	const float a = m_pos.x - playerPos.x;
	const float b = m_pos.y - playerPos.y;
	const float c = sqrt(a * a + b * b);

	//�v���C���[�Ƃ̋������ǐՂ��鋗�����߂�������
	if (c < m_trackDist)
	{
		//�R�C�����v���C���[��荶�ɂ�������
		if (a < 0.0f)
		{
			//�E�ɍs��
			m_move.x = m_moveSpeed;
		}
		//�R�C�����v���C���[���E�ɂ�������
		else
		{
			//���ɍs��
			m_move.x = -m_moveSpeed;
		}
	}
}

//�X�V
void C_Coin::Update(const float a_scrollX, const float a_scrollY)
{
	//�\�����Ԃ����炵�Ă���
	if (m_lifespan > 0)
	{
		m_lifespan--;
	}
	//�\�����Ԃ��Ȃ��Ȃ�����
	else
	{
		//�����t���O����
		m_isAlive = false;
	}

	//�����t���O��OFF�Ȃ烊�^�[��
	if (!m_isAlive)return;

	//�t���[����i�߂�
	m_frameCnt++;

	//�\�����Ԃ����Ȃ��Ȃ�����_�ł�����
	if (m_lifespan < m_lifespanBlink)
	{
		//�w�肳�ꂽ�t���[�����Ƃ�
		if (m_frameCnt % m_lifeDecayFrameRate == 0)
		{
			//�s������������
			if (m_color.A() == 1.0f)
			{
				//�������ɂ���
				m_color.A(0.1f);
			}
			//��������������
			else
			{
				//�s�����ɂ���
				m_color.A(1.0f);
			}
		}
	}

	//�T�C���J�[�u�p�p�x�𑝂₷
	m_sinAngle += 3;
	
	//0�`359�x�ɒ�������
	if (m_sinAngle >= 360)
	{
		m_sinAngle -= 360;
	}

	//X����]
	m_scale.x = sin(ToRadians(m_sinAngle));

	//���W�m��
	m_pos += m_move;
	
	//�g��s��쐬
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);

	//�ړ��s��쐬
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - a_scrollX, m_pos.y - a_scrollY, 0);

	//�����s��̍쐬
	m_mat = m_scaleMat * m_transMat;
}

//�`��
void C_Coin::Draw()
{
	//�����t���O��OFF�Ȃ烊�^�[��
	if (!m_isAlive)return;

	//�؎攻����Z�b�g
	const Math::Rectangle rect = { 0,0,m_texHeight,m_texWidth };

	//�s��̃Z�b�g
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//�`��
	SHADER.m_spriteShader.DrawTex(m_eTex, 0, 0, &rect, &m_color);
}

//�}�b�v�����蔻��p X����
void C_Coin::MapHitX(float a_posX, float a_moveX)
{
	m_pos.x = a_posX;
	m_move.x = a_moveX;
}

//�}�b�v�����蔻��p Y����
void C_Coin::MapHitY(float a_posY, float a_moveY)
{
	m_pos.y = a_posY;
	m_move.y = a_moveY;
}

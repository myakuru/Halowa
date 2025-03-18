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

	//�����V�[�h
	static std::random_device rd;
	static std::mt19937 gen(rd());

	//���ł����p�x�̗̂���
	static std::uniform_real_distribution<> dist(60.0f, 120.0f);

	//�摜�̊p�x�ɗ�������
	m_texAngle = dist(gen);

	//�p�x�ɍ��킹���ړ��ʂ�����
	m_move.x = cos(ToRadians(m_texAngle)) * m_initialMoveSpeed;
	m_move.y = sin(ToRadians(m_texAngle)) * m_initialMoveSpeed;
}

void C_Fireball::Action()
{
	//���݂��Ă��Ȃ�������܂��͒��e�����烊�^�[��
	if (!m_isAlive || m_isGroundHit)return;

	//�d��
	m_move.y -= m_gravity;
}

void C_Fireball::Update(float a_scrollX, float a_scrollY)
{
	//���݂��Ă��Ȃ�������܂��͒��e�����烊�^�[��
	if (!m_isAlive || m_isGroundHit)return;

	//1�t���[����i�߂�
	if (m_frameCnt < INT_MAX)
	{
		m_frameCnt++;
	}
	else
	{
		m_frameCnt = 0;
	}

	//�ړ��ʂɍ��킹���p�x�ɂ���
	m_texAngle = ToDegrees(atan2(m_move.y, m_move.x));

	//���W�m��
	m_pos += m_move;

	//�A�j���[�V�����X�V
	//�A�j���[�V�����t���[�����[�g�ɍ��킹�čX�V
	if (m_frameCnt % m_animFrameRate == 0)
	{
		//�摜��i�߂�
		m_texIndex++;

		//�摜�����[�v����
		if (m_texIndex >= m_texNumMax)
		{
			m_texIndex = 0;
		}

		//��擾
		m_texColumn = m_texIndex / m_texRowMax;

		//�s�擾
		m_texRow = m_texIndex % m_texColumnMax;
	}

	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);//�g��s��쐬
	m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(m_texAngle));//��]�s��쐬
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - a_scrollX, m_pos.y - a_scrollY, 0);//�ړ��s��쐬
	m_mat = m_scaleMat * m_rotationMat * m_transMat;//�s�񍇐�
}

void C_Fireball::Draw() const
{
	//���݂��Ă��Ȃ�������܂��͒��e�����烊�^�[��
	if (!m_isAlive || m_isGroundHit)return;

	Math::Rectangle rect = { m_texRow * m_texWidth,m_texColumn * m_texHeight,
								m_texWidth,m_texHeight };
	Math::Color color = { 1,1,1,1 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_fTex, 0, 0, &rect, &color);
}

//�}�b�v�����蔻��p X����
void C_Fireball::MapHitX(float a_posX, float a_moveX)
{
	m_pos.x = a_posX;
	m_move.x = a_moveX;
}

//�}�b�v�����蔻��p Y����
void C_Fireball::MapHitY(float a_posY, float a_moveY, bool a_isGroundHit)
{
	m_pos.y = a_posY;
	m_move.y = a_moveY;
	m_isGroundHit = a_isGroundHit;
}

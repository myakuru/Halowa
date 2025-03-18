#pragma once

//�R�C���N���X
class C_Coin
{
public:
	C_Coin(Math::Vector2 a_pos);//�R���X�g���N�^
	~C_Coin() = default;        //�f�X�g���N�^

	void Action(const Math::Vector2 playerPos);//����
	void Update(const float a_scrollX, const float a_scrollY);//�X�V
	void Draw();//�`��

	void MapHitX(float a_posX, float a_moveX);//�}�b�v�����蔻��p X����
	void MapHitY(float a_posY, float a_moveY);//�}�b�v�����蔻��p Y����

	//�摜�̃Z�b�g
	void SetTex(KdTexture* a_eTex) { m_eTex = a_eTex; }
	//�����t���O�̃Z�b�g
	void SetAlive(bool a_alive) { m_isAlive = a_alive; }


	//���W�̃Q�b�g
	const Math::Vector2 GetPos()     const { return m_pos; }
	//�������W�̃Q�b�g
	const Math::Vector2 GetNextPos() const { return m_pos + m_move; }
	//�����蔻�艡�T�C�Y�̃Q�b�g
	const float GetHitWidth()        const { return m_hitWidth; }
	//�����蔻��c�T�C�Y�̃Q�b�g
	const float GetHitHeight()       const { return m_hitHeight; }
	//�����t���O�̃Q�b�g
	const bool GetAlive()            const { return m_isAlive; }
	//�A�N�e�B�u�t���O
	const bool GetActive()           const { return m_isActive; }
	//�c�萶�����Ԃ̃Q�b�g
	const int GetLifespan()          const { return m_lifespan; }

private:


	KdTexture* m_eTex;

	static const int m_texWidth  = 32;//�摜���T�C�Y
	static const int m_texHeight = 32;//�摜�c�T�C�Y
	static const int m_lifeDecayFrameRate = 10;//�\�����Ԃ��c�菭�Ȃ��Ƃ��̃t���[�����[�g
	static const int m_lifespanMax = 60 * 8;//�\������
	static const int m_noActiveLifespan = m_lifespanMax * 0.9;//��������Ă���A�N�e�B�u�ɂȂ�܂ł̕\������
	static const int m_lifespanBlink = 180;//�_�ł���悤�ɂȂ�\������
	const float m_hitWidth  = 16.0f;//�����蔻�艡�T�C�Y
	const float m_hitHeight = 16.0f;//�����蔻��c�T�C�Y
	const float	m_moveSpeed = 5;    //�ړ����x
	const float	m_gravity   = 0.7f;	//�d��
	const float m_scaleSize = 1.0f; //�g��T�C�Y
	const float m_trackDist = 100;  //�ǐՂ����鋗��

	bool  m_isAlive; //�����t���O
	bool  m_isActive;//�A�N�e�B�u�t���O
	int   m_sinAngle;//�T�C���J�[�u�p�p�x
	int   m_lifespan;//�c�萶������
	int   m_frameCnt;//�t���[���J�E���g�p

	Math::Vector2 m_scale;//�g�嗦
	Math::Vector2 m_move; //�ړ���
	Math::Vector2 m_pos;  //���W
	Math::Color m_color;  //�F

	Math::Matrix m_scaleMat;//�g��s��
	Math::Matrix m_transMat;//�ړ��s��
	Math::Matrix m_mat;     //�����s��
};
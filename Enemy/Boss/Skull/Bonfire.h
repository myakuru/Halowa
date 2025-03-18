#pragma once

//���΃N���X
class C_Bonfire
{
public:
	C_Bonfire(Math::Vector2 a_pos, int a_damage);
	~C_Bonfire() = default;

	void Action();
	void Update(float a_scrollX, float a_scrollY);
	void Draw() const;

	void SetTex(KdTexture* a_bTex) { m_bTex = a_bTex; }

	const Math::Vector2 GetPos() const { return m_pos; }
	const float GetNextPosY()const { return m_pos.y + m_moveY; }
	const bool GetAlive() const { return m_isAlive; }
	const bool GetActive() const { return m_isActive; }
	const bool GetHitCnk()const { return m_isHitChk; }
	const float GetHitWidth() const { return m_hitWidth; }
	const float GetHitHeight()const { return m_hitHeight; }
	const int GetDamage() const { return m_damage; }
	const float GetKnockForce()const { return m_knockForce; }

	void MapHitY(float a_posY, float a_moveY);//�}�b�v�����蔻��p Y����

private:

	KdTexture* m_bTex;

	static const int m_texNumMax = 64;
	static const int m_texWidth  = 512;
	static const int m_texHeight = 512;
	static const int m_texColumnMax = 8;
	static const int m_texRowMax    = 8;

	//static const int m_damage = 200;//�_���[�W
	const int m_damage;//�_���[�W
	static const int m_startHitChkTexIndex = 12;//�_���[�W��������n�߂�摜
	const float m_knockForce = 10;//�m�b�N�o�b�N
	static const int m_animFrameRate = 5;
	const float m_scaleSize = 1.0f;
	const float m_hitWidth  = 50.0f;
	const float m_hitHeight = 20.0f;
	const float m_drawCorrY = 100;//Y���W�̕`�悸��␳�l
	const float m_gravity = 10.0f;//�d��


	bool m_isAlive;
	bool m_isActive;
	bool m_isHitChk;//�����蔻��
	int  m_frameCnt;
	int  m_texIndex;
	int  m_texColumn;
	int  m_texRow;

	float m_moveY;
	Math::Vector2 m_pos;
	Math::Vector2 m_scale;

	Math::Matrix m_scaleMat;
	Math::Matrix m_transMat;
	Math::Matrix m_mat;
};


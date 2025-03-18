#pragma once

class C_Smoke
{
public:
	C_Smoke(Math::Vector2 a_pos, int a_damage);
	~C_Smoke() = default;

	void Update(float a_scrollX, float a_scrollY);
	void Draw() const;

	void SetTex(KdTexture* a_sTex) { m_sTex = a_sTex; }

	const Math::Vector2 GetPos() const { return m_pos; }
	const bool GetAlive() const { return m_isAlive; }
	const bool GetHitCnk() const { return m_isHitChk; }
	const float GetHitWidth() const { return m_hitWidth; }
	const float GetHitHeight()const { return m_hitHeight; }
	const int GetDamage() const { return m_damage; }//���̃_���[�W
	const float GetKnockForce()const { return m_knockForce; }

private:

	KdTexture* m_sTex;

	static const int m_texNumMax = 13;
	static const int m_texWidth  = 128;
	static const int m_texHeight = 26;
	//static const int m_damage = 500;//���̃_���[�W
	const int m_damage;//���̃_���[�W
	const float m_knockForce = 20;//�m�b�N�o�b�N
	static const int m_animFrameRate  = 5;
	static const int m_damageTexIndex = 4;//�_���[�W���������摜
	const float m_scaleSize = 7.0f;
	const float m_hitWidth  = 350.0f;
	const float m_hitHeight = 50.0f;
	const float m_drawCorrY = 20;//Y���W�̕`�悸��␳�l


	bool m_isAlive;
	bool m_isHitChk;//�����蔻��
	int  m_texIndex;
	int  m_frameCnt;

	Math::Vector2 m_pos;
	Math::Vector2 m_scale;

	Math::Matrix m_scaleMat;
	Math::Matrix m_transMat;
	Math::Matrix m_mat;
};
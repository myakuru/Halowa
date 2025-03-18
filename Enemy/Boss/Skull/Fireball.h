#pragma once

//火の玉クラス
class C_Fireball
{
public:
	C_Fireball(Math::Vector2 a_pos, int a_damage);
	~C_Fireball() = default;


	void Action();
	void Update(float a_scrollX, float a_scrollY);
	void Draw() const;

	void SetTex(KdTexture* a_fTex) { m_fTex = a_fTex; }

	const Math::Vector2 GetPos() const { return m_pos; }
	const Math::Vector2 GetNextPos() const { return m_pos + m_move; }
	const bool GetAlive() const { return m_isAlive; }
	const bool GetGroundHit()const { return m_isGroundHit; }
	const float GetHitWidth() const { return m_hitWidth; }
	const float GetHitHeight()const { return m_hitHeight; }
	const int GetDamage() const { return m_damage; }
	const float GetKnockForce()const { return m_knockForce; }

	void MapHitX(float a_posX, float a_moveX);//マップ当たり判定用 X調整
	void MapHitY(float a_posY, float a_moveY, bool a_isGroundHit);//マップ当たり判定用 Y調整

private:

	KdTexture* m_fTex;

	static const int m_texNumMax = 64;
	static const int m_texWidth = 512;
	static const int m_texHeight = 512;
	static const int m_texColumnMax = 8;
	static const int m_texRowMax = 8;

	//static const int m_damage = 300;//ダメージ
	const int m_damage;//ダメージ
	static const int m_animFrameRate = 5;
	const float m_knockForce = 10;//ノックバック
	const float m_scaleSize = 0.5f;
	const float m_hitWidth = 100.0f * m_scaleSize;
	const float m_hitHeight = 100.0f * m_scaleSize;
	const float m_gravity = 0.4f;//重力
	const float m_initialMoveSpeed = 20.0f;


	bool  m_isAlive;
	bool  m_isGroundHit;//地面着弾フラグ
	float m_texAngle;
	int  m_frameCnt;
	int  m_texIndex;
	int  m_texRow;
	int  m_texColumn;

	Math::Vector2 m_move;
	Math::Vector2 m_pos;
	Math::Vector2 m_scale;

	Math::Matrix m_scaleMat;
	Math::Matrix m_rotationMat;
	Math::Matrix m_transMat;
	Math::Matrix m_mat;
};


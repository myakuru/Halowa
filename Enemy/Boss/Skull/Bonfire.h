#pragma once

//焚火クラス
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

	void MapHitY(float a_posY, float a_moveY);//マップ当たり判定用 Y調整

private:

	KdTexture* m_bTex;

	static const int m_texNumMax = 64;
	static const int m_texWidth  = 512;
	static const int m_texHeight = 512;
	static const int m_texColumnMax = 8;
	static const int m_texRowMax    = 8;

	//static const int m_damage = 200;//ダメージ
	const int m_damage;//ダメージ
	static const int m_startHitChkTexIndex = 12;//ダメージ判定をし始める画像
	const float m_knockForce = 10;//ノックバック
	static const int m_animFrameRate = 5;
	const float m_scaleSize = 1.0f;
	const float m_hitWidth  = 50.0f;
	const float m_hitHeight = 20.0f;
	const float m_drawCorrY = 100;//Y座標の描画ずれ補正値
	const float m_gravity = 10.0f;//重力


	bool m_isAlive;
	bool m_isActive;
	bool m_isHitChk;//当たり判定
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


#pragma once

//コインクラス
class C_Coin
{
public:
	C_Coin(Math::Vector2 a_pos);//コンストラクタ
	~C_Coin() = default;        //デストラクタ

	void Action(const Math::Vector2 playerPos);//動作
	void Update(const float a_scrollX, const float a_scrollY);//更新
	void Draw();//描画

	void MapHitX(float a_posX, float a_moveX);//マップ当たり判定用 X調整
	void MapHitY(float a_posY, float a_moveY);//マップ当たり判定用 Y調整

	//画像のセット
	void SetTex(KdTexture* a_eTex) { m_eTex = a_eTex; }
	//生存フラグのセット
	void SetAlive(bool a_alive) { m_isAlive = a_alive; }


	//座標のゲット
	const Math::Vector2 GetPos()     const { return m_pos; }
	//未来座標のゲット
	const Math::Vector2 GetNextPos() const { return m_pos + m_move; }
	//当たり判定横サイズのゲット
	const float GetHitWidth()        const { return m_hitWidth; }
	//当たり判定縦サイズのゲット
	const float GetHitHeight()       const { return m_hitHeight; }
	//生存フラグのゲット
	const bool GetAlive()            const { return m_isAlive; }
	//アクティブフラグ
	const bool GetActive()           const { return m_isActive; }
	//残り生存時間のゲット
	const int GetLifespan()          const { return m_lifespan; }

private:


	KdTexture* m_eTex;

	static const int m_texWidth  = 32;//画像横サイズ
	static const int m_texHeight = 32;//画像縦サイズ
	static const int m_lifeDecayFrameRate = 10;//表示時間が残り少ないときのフレームレート
	static const int m_lifespanMax = 60 * 8;//表示時間
	static const int m_noActiveLifespan = m_lifespanMax * 0.9;//生成されてからアクティブになるまでの表示時間
	static const int m_lifespanBlink = 180;//点滅するようになる表示時間
	const float m_hitWidth  = 16.0f;//当たり判定横サイズ
	const float m_hitHeight = 16.0f;//当たり判定縦サイズ
	const float	m_moveSpeed = 5;    //移動速度
	const float	m_gravity   = 0.7f;	//重力
	const float m_scaleSize = 1.0f; //拡大サイズ
	const float m_trackDist = 100;  //追跡をする距離

	bool  m_isAlive; //生存フラグ
	bool  m_isActive;//アクティブフラグ
	int   m_sinAngle;//サインカーブ用角度
	int   m_lifespan;//残り生存時間
	int   m_frameCnt;//フレームカウント用

	Math::Vector2 m_scale;//拡大率
	Math::Vector2 m_move; //移動量
	Math::Vector2 m_pos;  //座標
	Math::Color m_color;  //色

	Math::Matrix m_scaleMat;//拡大行列
	Math::Matrix m_transMat;//移動行列
	Math::Matrix m_mat;     //合成行列
};
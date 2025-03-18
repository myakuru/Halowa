#pragma once
enum class EnemyType;
class Scene;

//敵スポナークラス
class C_EnemySpawner
{
public:
	C_EnemySpawner(EnemyType a_enemyType, Math::Vector2 a_pos);
	~C_EnemySpawner() {};

	void Update(const float a_scrollX, const float a_scrollY);
	void Draw();

	//敵スポナー画像
	void SetTex(KdTexture* a_tex) { m_tex = a_tex; }
	//ひび割れ画像
	void SetCrackTex(KdTexture* a_tex) { m_crackTex = a_tex; }
	//オーナーのインスタンスをセット
	void SetOwner(Scene* a_eOwner) { m_eOwner = a_eOwner; }
	//ダメージ
	void SetDamage(int a_damage) { m_durability -= a_damage; }

	//存在フラグ
	bool GetAlive() { return m_isAlive; }
	//当たり判定縦サイズ
	float GetHitHeight() { return m_hitHeight; }
	//当たり判定横サイズ
	float GetHitWidth() { return m_hitWidth; }
	//現在の座標
	Math::Vector2 GetPos() { return m_pos; }


private:

	Scene* m_eOwner;      
	KdTexture* m_tex;     //敵スポナー画像
	KdTexture* m_crackTex;//ひび割れ画像

	EnemyType m_spawnEnemyType;//召喚する敵の種類

	static const int m_texNumMax = 11;   //画像枚数
	static const int m_texHeight = 140;  //画像縦サイズ
	static const int m_texWidth = 100;   //画像横サイズ
	static const int m_animFrameRate = 5;//アニメーション更新頻度
	static const int m_durabilityMax = 5;//耐久力の最大
	static const int m_summonWaitTimeMax = 60 * 8;//召喚までの時間の最大
	const float m_scaleSize = 1.5f;      //拡大率
	const float m_hitHeight = m_texHeight / 2 * m_scaleSize;//当たり判定縦サイズ
	const float m_hitWidth  = m_texWidth / 2 * m_scaleSize; //当たり判定横サイズ


	int  m_summonWaitTime;//召喚までの時間
	int  m_texIndex;
	int  m_frameCnt;
	int  m_durability;//耐久力
	bool m_isAlive;        //存在フラグ
	bool m_isSpawnCompleted;

	Math::Vector2 m_pos;

	Math::Matrix m_scaleMat;
	Math::Matrix m_transMat;
	Math::Matrix m_mat;
	Math::Color  m_color;
};
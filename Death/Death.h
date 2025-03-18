#pragma once
class Scene;

class C_Death
{
public:

	C_Death();
	~C_Death();

	void Init();
	void Update();
	void Draw();
	void LoadTex();
	void ReleaseTex();

	void SetOwner(Scene* owner) { m_dOwner = owner; }

	int flame;

	void SetPos_Death(bool m_pos) { pos = m_pos; }
	bool GetPos_Death() { return pos; }



private:


	float m_blackalpha;
	
	bool pos = false;


	enum Death {
		gameover,
		back,
		restart,
		title,
		DeathtypeMax
	};

	Scene* m_dOwner;
	Scene* m_dmOwner;

	KdTexture m_GameoverTex;	//ゲームオーバー
	KdTexture m_BackTex;		//背景
	KdTexture m_RestartTex;		//リスタート選択
	KdTexture m_TitleTex;		//タイトルに戻る



	Math::Color m_color;

	struct object {
		Math::Vector2 pos;//座標
		Math::Vector2 move;//移動量
		Math::Matrix scalemat;//拡大行列
		Math::Matrix transmat;//移動行列
		Math::Matrix mat;//合成行列
	};

	object m_death[DeathtypeMax];

};
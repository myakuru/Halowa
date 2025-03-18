#pragma once
//前方宣言
class Scene;

class C_GroupPlants
{
public:
	C_GroupPlants();
	~C_GroupPlants();
	void InitPlants();
	void DrawPlants();
	void UpdatePlants();
	void LoadTexture();
	void ReleaseTexture();

	//草の位置のセッター	
	void SetPlantsPos(int num, float posX,float posY) { Plants[num].m_pos.x = posX, Plants[num].m_pos.y=posY; }

	//草の色のセッター
	void SetPlantsColor(Math::Color color) { this->color = color; }

	//オーナーの設定
	void SetOwner(Scene* owner) { m_mOwner = owner; }

private:
	struct s_Plants {
		Math::Vector2 m_pos;
		Math::Matrix m_mat;
		Math::Matrix m_scaleMat;
		Math::Matrix m_transMat;
	};

	struct s_AnimeFunction {
		int m_fFrameCnt = 0;
		int m_fTexNum = 0;
	}Animetion;

	static const int TextureMax = 44;	//植物の最大数
	static const int PlantsMax = 2;	//植物の最大数
	KdTexture Tex[TextureMax][PlantsMax];//植物のテクスチャ
	char str[100] = {0};				//テクスチャのパス
	Math::Color color = { 1,1,1,1 };	//色

	s_Plants Plants[PlantsMax];				//植物の構造体

	Scene* m_mOwner = nullptr;


};
#include "GroupPlants.h"
#include "../Scene.h"

C_GroupPlants::C_GroupPlants():
	Animetion(),
	Plants()
{
}

C_GroupPlants::~C_GroupPlants()
{
}

void C_GroupPlants::InitPlants()
{
		//植物の初期位置
		Plants[0].m_pos = { 700,-1980 };
		Plants[1].m_pos = { 500,-1990 };
		//植物のアニメーション
		Animetion.m_fFrameCnt = 0;
		Animetion.m_fTexNum = 0;
		//植物のテクスチャ読み込み
		LoadTexture();
}

void C_GroupPlants::DrawPlants()
{
	for (int i = 0; i < PlantsMax; i++)
	{
		//植物の描画
		SHADER.m_spriteShader.SetMatrix(Plants[i].m_mat);
		Math::Rectangle rect = { 0,0,512,256 };
		SHADER.m_spriteShader.DrawTex(&Tex[Animetion.m_fTexNum][i], Plants[i].m_pos.x, Plants[i].m_pos.y, &rect, &color);
	}
}

void C_GroupPlants::UpdatePlants()
{
	//植物のアニメーション
	Animetion.m_fFrameCnt++;
	if (Animetion.m_fFrameCnt >= 5) {		//10フレームごとにテクスチャを変更
		Animetion.m_fTexNum++;				//テクスチャ番号を増やす
		if (Animetion.m_fTexNum >= 44) {	//テクスチャ番号が44以上になったら0に戻す
			Animetion.m_fTexNum = 0;		//テクスチャ番号を0に戻す
		}
		Animetion.m_fFrameCnt = 0;			//フレームカウントを0に戻す
	}
	C_MapBase* map = m_mOwner->GetMap();

	for (int i = 0; i < PlantsMax; i++)
	{
		//植物の行列
		Plants[i].m_transMat = Math::Matrix::CreateTranslation(Plants[i].m_pos.x - map->GetScrollX(), Plants[i].m_pos.y - map->GetScrollY(), 0);
		Plants[i].m_scaleMat = Math::Matrix::CreateScale(0.3f, 0.3f, 1);
		Plants[i].m_mat = Plants[i].m_scaleMat * Plants[i].m_transMat;
	}
	//植物の行列
}

void C_GroupPlants::LoadTexture()
{
	for (int i = 0; i < TextureMax; i++)
	{
		for (int j = 0; j < PlantsMax; j++)
		{
			sprintf_s(str, "Texture/Map/Vegetation/Group Plant/GroupPlants_000%d.png", i + 1);
			Tex[i][j].Load(str);
		}
	}
}

void C_GroupPlants::ReleaseTexture()
{
	for (int i = 0; i < TextureMax; i++)
	{
		for (int j = 0; j < PlantsMax; j++)
		{
			Tex[i][j].Release();
		}
	}
}

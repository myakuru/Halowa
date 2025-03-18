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
		//�A���̏����ʒu
		Plants[0].m_pos = { 700,-1980 };
		Plants[1].m_pos = { 500,-1990 };
		//�A���̃A�j���[�V����
		Animetion.m_fFrameCnt = 0;
		Animetion.m_fTexNum = 0;
		//�A���̃e�N�X�`���ǂݍ���
		LoadTexture();
}

void C_GroupPlants::DrawPlants()
{
	for (int i = 0; i < PlantsMax; i++)
	{
		//�A���̕`��
		SHADER.m_spriteShader.SetMatrix(Plants[i].m_mat);
		Math::Rectangle rect = { 0,0,512,256 };
		SHADER.m_spriteShader.DrawTex(&Tex[Animetion.m_fTexNum][i], Plants[i].m_pos.x, Plants[i].m_pos.y, &rect, &color);
	}
}

void C_GroupPlants::UpdatePlants()
{
	//�A���̃A�j���[�V����
	Animetion.m_fFrameCnt++;
	if (Animetion.m_fFrameCnt >= 5) {		//10�t���[�����ƂɃe�N�X�`����ύX
		Animetion.m_fTexNum++;				//�e�N�X�`���ԍ��𑝂₷
		if (Animetion.m_fTexNum >= 44) {	//�e�N�X�`���ԍ���44�ȏ�ɂȂ�����0�ɖ߂�
			Animetion.m_fTexNum = 0;		//�e�N�X�`���ԍ���0�ɖ߂�
		}
		Animetion.m_fFrameCnt = 0;			//�t���[���J�E���g��0�ɖ߂�
	}
	C_MapBase* map = m_mOwner->GetMap();

	for (int i = 0; i < PlantsMax; i++)
	{
		//�A���̍s��
		Plants[i].m_transMat = Math::Matrix::CreateTranslation(Plants[i].m_pos.x - map->GetScrollX(), Plants[i].m_pos.y - map->GetScrollY(), 0);
		Plants[i].m_scaleMat = Math::Matrix::CreateScale(0.3f, 0.3f, 1);
		Plants[i].m_mat = Plants[i].m_scaleMat * Plants[i].m_transMat;
	}
	//�A���̍s��
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

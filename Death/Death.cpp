#include <windows.h>
#include "../Scene.h"  
#include "Death.h"
#include "../Chara/chara.h"
#include "../Title/Title.h"

C_Death::C_Death()
{
	m_color = { 1,1,0,1.0f };
}

C_Death::~C_Death()
{
	
}

void C_Death::Init()
{
	


}

void C_Death::Update()
{
	
	m_death[back].scalemat = Math::Matrix::CreateScale(1.0f, 1.0f, 1.0f);
	m_death[back].transmat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_death[back].mat = m_death[back].scalemat * m_death[back].transmat;

	C_Chara* death = m_dOwner->GetChara();

	death->GetAlive();

	if (!death->GetAlive())
	{

		flame++;


		m_death[back].scalemat = Math::Matrix::CreateScale(1.0f, 1.0f, 1);
		m_death[back].transmat = Math::Matrix::CreateTranslation(0, 0, 0);
		m_death[back].mat = m_death[back].scalemat * m_death[back].transmat;


		m_color.A(m_color.A() + 0.01f);


		Math::Color color = { 1.0f,1.0f,1.0f,m_blackalpha };
		Math::Rectangle rect = { 0,0,800,800 };
		SHADER.m_spriteShader.SetMatrix(m_death[back].mat);
		SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 50, &rect, &color);

		if (flame <= 60 * 4)
		{


			if (m_blackalpha <= 1.0f)
			{
				m_blackalpha += 0.01f;
			}
			else {
				m_blackalpha = 1.0f;
				if (flame==110) {
					C_Title* save = m_dOwner->GetTitle();
					if (save->GetSaveDataExists() == false)
					{
						pos = true;
						m_dOwner->GetSceneChange()->Init_L(Game2);
					}
					else
					{
						m_dOwner->AllDataLoad();
					}
				}
			}

			



			
		}

		if (flame >= 60 * 4)
		{

			C_Chara* hp = m_dOwner->GetChara();

			float ratio = (float)hp->GetNowHp() / hp->GetMaxHp();

			hp->GetSaveScene();

			

			if (m_blackalpha >= 1.0f)
			{
				m_blackalpha -= 0.01f;
			}
			else {
				m_blackalpha = 0.0f;
			}

			

		}


	}
	else {
		m_blackalpha = 0.0f;
		flame = 0;
	}
	
}

void C_Death::Draw()
{
	C_Chara* death = m_dOwner->GetChara();

	death->GetAlive();


	if (!death->GetAlive())
	{
		SHADER.m_spriteShader.SetMatrix(m_death[back].mat);
		SHADER.m_spriteShader.DrawTex(&m_BackTex, Math::Rectangle{ 0,0,1280,720 }, m_blackalpha);

	}
}

void C_Death::LoadTex()
{
	m_BackTex.Load("Texture/UI/black.png");
}

void C_Death::ReleaseTex()
{
	m_BackTex.Release();
	m_RestartTex.Release();
	m_TitleTex.Release();
}

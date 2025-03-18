#include "Endroll.h"
#include"../Scene.h"

void C_Endroll::Update()
{
	if (!m_FadeinEnd) {
		if (m_Cnt < 45)m_Cnt++;
		else {
			if (BlackFront.m_Alpha > 0) BlackFront.m_Alpha -= 0.02;
			else {
				m_Cnt = 0;
				BlackFront.m_Alpha = 0;
				m_FadeinEnd = true;
			}
			BlackFront.m_Color = { BlackFront.m_Alpha,BlackFront.m_Alpha,BlackFront.m_Alpha,BlackFront.m_Alpha };
		}
	}
	else if (!m_ScrollEnd) {
		if (Endroll.m_Pos.y > 1080) {
			if (m_Cnt < 120) m_Cnt++;
			else {
				if (BlackFront.m_Alpha < 1)BlackFront.m_Alpha += 0.02;
				else {
					BlackFront.m_Alpha = 1;
					m_Cnt = 0;
					m_ScrollEnd = true;
				}
				BlackFront.m_Color = { BlackFront.m_Alpha,BlackFront.m_Alpha,BlackFront.m_Alpha,BlackFront.m_Alpha };
			}
		}
		else {
			Endroll.m_Pos.y += 1.5;
		}
	}
	else if(!m_EndrollEnd){
		if (ThankYou.m_Alpha < 1) ThankYou.m_Alpha += 0.02;
		else {
			if (m_Cnt < 240) {
				m_Cnt++;
				ThankYou.m_Alpha = 1;
			}
			else {
				m_Cnt = 0;
				m_EndrollEnd = true;
			}
		}
		ThankYou.m_Color = { ThankYou.m_Alpha,ThankYou.m_Alpha ,ThankYou.m_Alpha ,ThankYou.m_Alpha };
	}
	else {
		if(ThankYou.m_Alpha>0) ThankYou.m_Alpha -= 0.01;
		else {
			if (m_Cnt < 60) m_Cnt++;
			else {
				m_Cnt = 0;
				ThankYou.m_Alpha = 0;
				if (!m_ChangeToTitle) {
					m_EndOwner->GetSceneChange()->Init_L(Title);
					m_ChangeToTitle = true;
				}
			}
		}
		ThankYou.m_Color = { ThankYou.m_Alpha,ThankYou.m_Alpha ,ThankYou.m_Alpha ,ThankYou.m_Alpha };
	}

	ObjectMatrix(BlackBack);
	if (!m_ScrollEnd) {
		ObjectMatrix(Endroll);
		ObjectMatrix(BlackFront);
	}
	else {
		ObjectMatrix(ThankYou);
	}
}

void C_Endroll::Draw()
{
	DrawObject(BlackBack, { 0,0,1280,720 });
	if (!m_ScrollEnd) {
		DrawObject(Endroll, { 0,0,1280,2880 });
	}
	DrawObject(BlackFront, { 0,0,1280,720 });
	if (m_ScrollEnd) {
		DrawObject(ThankYou, { 0,0,1280,720 });
	}
}

void C_Endroll::LoadTex()
{
	BlackBack.m_Tex.Load("Texture/Endroll/BlackBack.png");
	BlackFront.m_Tex.Load("Texture/Endroll/BlackFront.png");
	Endroll.m_Tex.Load("Texture/Endroll/EndRoll.png");
	ThankYou.m_Tex.Load("Texture/Endroll/Thank You For Playing.png");
}

void C_Endroll::ReleaseTex()
{
	BlackBack.m_Tex.Release();
	BlackFront.m_Tex.Release();
	Endroll.m_Tex.Release();
	ThankYou.m_Tex.Release();
}

#include "LightningPar.h"
#include"Chara.h"
#include "../Scene.h"

C_LightningPar::C_LightningPar()
{
	LiHit.m_alive = false;
}

C_LightningPar::~C_LightningPar()
{
}

void C_LightningPar::LightInit()
{
	for (int i = 0; i < LightNum; i++) {
		Lightning[i].m_color = {0,0,0,0};
		Lightning[i].m_pos = {0,0};
		Lightning[i].m_alive = false;
	}
	lightningEnd = false;
	LightHitInit();
}

void C_LightningPar::LightAction()
{

	for (int i = 0; i < LightNum; i++) {
		Lightning[i].m_move = { 0,0 };
		if (!lightningEnd) {
			if (Lightning[i].m_alive) {
				Lightning[i].m_exprtime -= 5;
				if (Lightning[i].m_exprtime <= 0) {
					Lightning[i].m_color = Lightning[i].m_SetColor;
					if (Lightning[i].m_exprtime <= -10) {
						Lightning[i].m_alive = false;
					}
				}
				else {
					Lightning[i].m_color = { 0,0,0,0 };
				}
			}
			else if (m_type == 1) {
				Lightning[i].m_color = { 0,0,0,0 };
				Lightning[i].m_exprtime = 0;
				Lightning[i].m_move.x = 10 * Lightning[i].m_direct.x * 16;
				Lightning[i].m_move.y = 10 * Lightning[i].m_direct.y * 16;
				Lightning[i].m_alive = true;
			}
			else if (m_type == 2) {
				Lightning[i].m_color = { 0, 0, 0, 0 };
			}
		}
		else {
			Lightning[i].m_color = { 0,0,0,0 };
		}
	}

	LightHitAction();

}

void C_LightningPar::LightUpdate(float scrollX,float scrollY)
{
	
	for (int i = 0; i < LightNum; i++) {
		
		Lightning[i].m_pos += Lightning[i].m_move;

		Lightning[i].m_scaleMat = Math::Matrix::CreateScale(Lightning[i].m_scale.x, Lightning[i].m_scale.y, 1);
		Lightning[i].m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(Lightning[i].m_angle));
		Lightning[i].m_transMat = Math::Matrix::CreateTranslation(Lightning[i].m_pos.x - scrollX, Lightning[i].m_pos.y - scrollY, 0);
		Lightning[i].m_matrix = Lightning[i].m_scaleMat * Lightning[i].m_rotationMat * Lightning[i].m_transMat;
	}

	LightHitUpdate(scrollX, scrollY);
}

void C_LightningPar::LightDraw()
{
	for (int i = 0; i < LightNum; i++) {
		SHADER.m_spriteShader.SetMatrix(Lightning[i].m_matrix);
		Math::Rectangle rect = { 0,0,32,32 };
		SHADER.m_spriteShader.DrawTex(&LightTex, 0, 0, &rect, &Lightning[i].m_color);
	}

	LightHitDraw();
}

void C_LightningPar::LightEmit(float a_posX, float a_posY,
	int a_exprtime, float a_scaleX, float a_scaleY, float a_angle, Math::Color a_color, float a_a, float a_b,int a_i,Math::Vector2 a_playerPos,int a_type)
{
	m_i = a_i;
	Lightning[m_i].m_pos = {a_posX,a_posY};
	Lightning[m_i].m_move = { 0,0 };
	Lightning[m_i].m_exprtime = a_exprtime;
	Lightning[m_i].m_SetColor = a_color;
	Lightning[m_i].m_scale = {a_scaleX,a_scaleY};
	Lightning[m_i].m_angle = a_angle;
	Lightning[m_i].m_alive = true;
	Lightning[m_i].m_bExpr = false;
	Lightning[m_i].m_direct = {a_a,a_b};
	lightningEnd = false;
	m_type = a_type;

	LightHitEmit(a_playerPos, { a_a,a_b });
}

void C_LightningPar::LightHitInit()
{
	LiHit.m_pos = { 0,0 };
	LiHit.m_move = { 0,0 };
	LiHit.m_alive = false;
}

void C_LightningPar::LightHitDraw()
{
}

void C_LightningPar::LightHitRelease()
{
}

void C_LightningPar::LightHitAction()
{
	//C_Chara* player = m_hOwner->GetChara();
	//if (LiHit.m_alive) {
	//	if (LiHit.m_cnt == 30) {
	//		LiHit.m_alive = false;
	//		player->SetPos(LiHit.m_pos);
	//		player->SetIsAvoid(false);
	//		lightningEnd = true;
	//	}
	//	if (LiHit.m_cnt!=10) {
	//		LiHit.m_move.x = LiHit.m_direct.x * 32;
	//		LiHit.m_move.y = LiHit.m_direct.y * 32;
	//		LiHit.m_cnt++;
	//	}
	//	else {
	//		if (m_type == 1) {
	//			//LiHit.m_move.x = LiHit.m_direct.x * 320;
	//			//LiHit.m_move.y = LiHit.m_direct.y * 320;
	//			LiHit.m_cnt++;
	//		}
	//		else if (m_type == 2) {
	//			LiHit.m_alive = false;
	//			player->SetPos(LiHit.m_pos);
	//			player->SetIsAvoid(false);
	//		}
	//	}
	//}

	C_Chara* player = m_hOwner->GetChara();
	if (LiHit.m_alive) {
		if (LiHit.m_cnt == 30) {
			LiHit.m_alive = false;
			player->SetPos(LiHit.m_pos);
			player->SetIsAvoid(false);
			lightningEnd = true;
		}
		if (LiHit.m_cnt != 10) {
			if (m_type == 2) {
				LiHit.m_move.x = LiHit.m_direct.x * 44;
				LiHit.m_move.y = LiHit.m_direct.y * 44;
				LiHit.m_cnt++;
			}
			else {
				LiHit.m_move.x = LiHit.m_direct.x * 48;
				LiHit.m_move.y = LiHit.m_direct.y * 48;
				LiHit.m_cnt++;
			}
		}
		else {
			if (m_type == 1) {
				//LiHit.m_move.x = LiHit.m_direct.x * 320;
				//LiHit.m_move.y = LiHit.m_direct.y * 320;
				LiHit.m_cnt++;
			}
			else if (m_type == 2) {
				LiHit.m_alive = false;
				player->SetPos(LiHit.m_pos);
				player->SetIsAvoid(false);
			}
		}
	}
	
}

void C_LightningPar::LightHitUpdate(float scrollX, float scrollY)
{
	C_Chara* player = m_hOwner->GetChara();
	LiHit.m_pos += LiHit.m_move;
	if(player->GetIsAvoid()) player->SetPos(LiHit.m_pos);

	LiHit.m_move = { 0,0 };
	LiHit.m_transMat = Math::Matrix::CreateTranslation(LiHit.m_pos.x-scrollX, LiHit.m_pos.y-scrollY, 0);
	LiHit.m_matrix = LiHit.m_transMat;
}

void C_LightningPar::LightHitEmit(Math::Vector2 a_pos,Math::Vector2 a_AorB)
{
	LiHit.m_pos = a_pos;
	LiHit.m_move = { 0,0 };
	LiHit.m_direct = a_AorB;
	LiHit.m_alive = true;
	LiHit.m_firstf = false;
	LiHit.m_cnt = 0;
}

void C_LightningPar::LiEffInit()
{
	for (int i = 0; i < LiEffNum; i++) {
		LiEff[i].m_color = { 1,1,1,1 };
		LiEff[i].m_pos = { 0,0 };
		LiEff[i].m_move = { 0,0 };
		LiEff[i].m_scale = { 0.5,1 };
	}
	lightningEnd = false;
}

void C_LightningPar::LiEffUpdate(float scrollX, float scrollY)
{
	C_Chara* player = m_hOwner->GetChara();
	for (int i = 0; i <LiEffNum; i++) {
		if (player->GetIsAvoid()) {
			if (LiEff[i].m_alive) {
				LiEff[i].m_exprtime -= 3;
				if (LiEff[i].m_exprtime <= 0) {
					LiEff[i].m_color = LiEff[i].m_SetColor;
					LiEff[i].m_pos.x += LiEff[i].m_move.x;
					LiEff[i].m_pos.y += LiEff[i].m_move.y;
					if (LiEff[i].m_exprtime <= -21) {
						LiEff[i].m_alive = false;
					}
				}
				else {
					LiEff[i].m_color = { 0,0,0,0 };
				}
			}
			else {
				LiEff[i].m_color = { 0,0,0,0 };
				LiEff[i].m_exprtime = 0;
				LiEff[i].m_setPos.x += LiEff[i].m_direct.x * 320;
				LiEff[i].m_setPos.y += LiEff[i].m_direct.y * 320;
				LiEff[i].m_pos = LiEff[i].m_setPos;
				LiEff[i].m_alive = true;
			}
		}
		else {
			if (LiEff[i].m_alive) {
				LiEff[i].m_exprtime -= 3;
				if (LiEff[i].m_exprtime <= 0) {
					LiEff[i].m_color = LiEff[i].m_SetColor;
					LiEff[i].m_pos.x += LiEff[i].m_move.x;
					LiEff[i].m_pos.y += LiEff[i].m_move.y;
					if (LiEff[i].m_exprtime <= -21) {
						LiEff[i].m_alive = false;
					}
				}
				else {
					LiEff[i].m_color = { 0,0,0,0 };
				}
			}
			else {
				LiEff[i].m_color = { 0,0,0,0 };
			}
		}
	


		LiEff[i].m_scaleMat = Math::Matrix::CreateScale(LiEff[i].m_scale.x, LiEff[i].m_scale.y, 1);
		LiEff[i].m_rotationMat = Math::Matrix::CreateRotationZ(LiEff[i].m_angle);
		LiEff[i].m_transMat = Math::Matrix::CreateTranslation(LiEff[i].m_pos.x - scrollX, LiEff[i].m_pos.y - scrollY, 0);
		LiEff[i].m_matrix = LiEff[i].m_scaleMat * LiEff[i].m_rotationMat * LiEff[i].m_transMat;
	}
}

void C_LightningPar::LiEffDraw()
{
	for (int i = 0; i < LiEffNum; i++) {
		SHADER.m_spriteShader.SetMatrix(LiEff[i].m_matrix);
		Math::Rectangle rect = { 0,0,32,32 };
		SHADER.m_spriteShader.DrawTex(&LiEffTex, 0, 0, &rect, &LiEff[i].m_color);
	}
}

void C_LightningPar::LiEffEmit(float a_posX, float a_posY, float a_moveX, float a_moveY,
	int a_exprtime, float a_scaleX, float a_scaleY, float a_angle, Math::Color a_color, float a_a, float a_b, int a_i)
{
	m_i = a_i;
	LiEff[m_i].m_pos = { a_posX,a_posY };
	LiEff[m_i].m_setPos = { a_posX,a_posY };
	LiEff[m_i].m_move = { a_moveX,a_moveY };
	LiEff[m_i].m_exprtime = a_exprtime;
	LiEff[m_i].m_scale = { a_scaleX,a_scaleY };
	LiEff[m_i].m_angle = a_angle;
	LiEff[m_i].m_SetColor = a_color;
	LiEff[m_i].m_direct = { a_a,a_b };
	LiEff[m_i].m_alive = true;
}

void C_LightningPar::LiChargeInit()
{
}

void C_LightningPar::LiChargeUpdate(float scrollX, float scrollY)
{		
		
	

		if (LiCharge.m_alive) {
			LiCharge.m_cnt++;
				if (LiCharge.m_cnt % 6 < 3) {
					LiCharge.m_color = { 1,1,1,1 };
				}
				else {
					LiCharge.m_color = { 0,0,0,0 };
				}
				if (LiCharge.m_scale.x < 6) {
					LiCharge.m_scale.x += 0.1;
					LiCharge.m_scale.y += 0.1;
				}
				else {
					LiCharge.m_alive = false;
				}
		}
		else {
			LiCharge.m_color = { 0,0,0,0 };
		}

		LiCharge.m_scaleMat = Math::Matrix::CreateScale(LiCharge.m_scale.x, LiCharge.m_scale.y,1);
		LiCharge.m_transMat = Math::Matrix::CreateTranslation(LiCharge.m_pos.x-scrollX, LiCharge.m_pos.y-scrollY, 0);
		LiCharge.m_matrix = LiCharge.m_scaleMat * LiCharge.m_transMat;
}

void C_LightningPar::LiChargeDraw()
{
	SHADER.m_spriteShader.SetMatrix(LiCharge.m_matrix);
	Math::Rectangle rect = { 0,0,32,32 };
	SHADER.m_spriteShader.DrawTex(&LiChargeTex, 0, 0, &rect, &LiCharge.m_color);
}

void C_LightningPar::LiChargeEmit(Math::Vector2 a_pos)
{
	C_Chara* player = m_hOwner->GetChara();
	LiCharge.m_alive = true;
	if (player->GetisJump()) LiCharge.m_pos = { a_pos.x,a_pos.y + 50 };
	else LiCharge.m_pos = a_pos;
	LiCharge.m_scale = { 1,1 };
	LiCharge.m_cnt = 0;
}

void C_LightningPar::SmokeInit()
{
}

void C_LightningPar::SmokeUpdate(float scrollX, float scrollY)
{

	C_Chara* player = m_hOwner->GetChara();

	for (int i = 0; i < SmokeNum; i++) {
	
		if (!Smoke[i].m_alive) {
			Smoke[i].m_color = { 0,0,0,0 };
			Smoke[i].m_move = {0,2};
			Smoke[i].m_scale.x = Rnd();
			Smoke[i].m_pos = player->GetPos();
			Smoke[i].m_cnt = 40+rand()%20;
			if (player->GetFuseBlows()) Smoke[i].m_alive = true;
		}
		else {
			Smoke[i].m_color = { 1,1,1,1 };
			Smoke[i].m_cnt--;
			if (Smoke[i].m_cnt <= 0) Smoke[i].m_alive = false;
		}

	
		Smoke[i].m_pos += Smoke[i].m_move;
	
		Smoke[i].m_scaleMat = Math::Matrix::CreateScale(Smoke[i].m_scale.x, Smoke[i].m_scale.x, 1);
		Smoke[i].m_transMat = Math::Matrix::CreateTranslation(Smoke[i].m_pos.x - scrollX, Smoke[i].m_pos.y - scrollY, 0);
		Smoke[i].m_matrix = Smoke[i].m_scaleMat * Smoke[i].m_transMat;
	}
}

void C_LightningPar::SmokeDraw()
{
	for (int i = 0; i < SmokeNum; i++) {
		SHADER.m_spriteShader.SetMatrix(Smoke[i].m_matrix);
		Math::Rectangle rect = { 0,0,32,32 };
		SHADER.m_spriteShader.DrawTex(&smokeTex, 0, 0, &rect, &Smoke[i].m_color);
	}
}

void C_LightningPar::ChargeAtkUpdate(float scrollX, float scrollY)
{
	C_Chara* player = m_hOwner->GetChara();
	if (player->GetAtkAniNum() <= 2) {
		if (player->GetIsAtk()) {
			switch (player->GetChargeCnt()) {
			case 0:
				for (int i = 0; i < ChargeAtkNum; i++) {
					ChargeAtk[i].m_alive = false;
				}
				break;
			case 1:
				ChargeAtk[0].m_alive = true;
				break;
			case 2:
				ChargeAtk[1].m_alive = true;
				break;
			case 3:
				ChargeAtk[2].m_alive = true;
				break;
			case 4:
				ChargeAtk[3].m_alive = true;
				ChargeAtk[4].m_alive = true;
				break;
			}

			float a, b;
			for (int i = 0; i < ChargeAtkNum; i++) {
				if (player->GetDirectX()) {
					ChargeAtk[i].m_angle = 15;
					a = cos(ChargeAtk[i].m_angle * 3.14 / 180);
					b = sin(ChargeAtk[i].m_angle * 3.14 / 180);
					ChargeAtk[i].m_pos = { player->GetPos().x - a * (i * 32) - 10 + (rand() % 20 - 10),player->GetPos().y + b * (i * 32) - 15 + (rand() % 20 - 10) };
				}
				else {
					ChargeAtk[i].m_angle = 165;
					a = cos(ChargeAtk[i].m_angle * 3.14 / 180);
					b = sin(ChargeAtk[i].m_angle * 3.14 / 180);
					ChargeAtk[i].m_pos = { player->GetPos().x - a * (i * 32) + 10 + (rand() % 20 - 10), player->GetPos().y + b * (i * 32) - 15 + (rand() % 20 - 10) };
				}
			}
		}
		else {
			for (int i = 0; i < ChargeAtkNum; i++) ChargeAtk[i].m_alive = false;
		}
	}
	else {
		for (int i = 0; i < ChargeAtkNum; i++) ChargeAtk[i].m_alive = false;
	}

	for (int i = 0; i < ChargeAtkNum; i++) {

		if (ChargeAtk[i].m_alive)ChargeAtk[i].m_color = { 1,1,1,1 };
		else ChargeAtk[i].m_color = { 0,0,0,0 };

		ChargeAtk[i].m_scaleMat = Math::Matrix::CreateScale(ChargeAtk[i].m_scale.x, ChargeAtk[i].m_scale.y, 1);
		ChargeAtk[i].m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(360 - ChargeAtk[i].m_angle));
		ChargeAtk[i].m_transMat = Math::Matrix::CreateTranslation(ChargeAtk[i].m_pos.x - scrollX, ChargeAtk[i].m_pos.y - scrollY, 0);
		ChargeAtk[i].m_matrix = ChargeAtk[i].m_scaleMat * ChargeAtk[i].m_rotationMat * ChargeAtk[i].m_transMat;
	}

	if (GetAsyncKeyState('E') & 0x8000 || GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		if (player->GetIsAtk()) {
			if (player->GetChargeCnt() >= 1) {
				ChargeSmoke.m_alive = true;
				ChargeSmoke.m_texNum = AnimationLoop(2, 16, ChargeSmoke);
			}
			else {
				ChargeSmoke.m_alive = false;
				ChargeSmoke.m_changecnt = 0;
			}
		}
		else {
			ChargeSmoke.m_alive = false;
			ChargeSmoke.m_changecnt = 0;
		}
	}
	else {
		ChargeSmoke.m_alive = false;
		ChargeSmoke.m_changecnt = 0;
	}
	if (ChargeSmoke.m_alive) ChargeSmoke.m_color = { 1,1,1,1 };
	else ChargeSmoke.m_color = { 0,0,0,0 };

	if (player->GetDirectX()) {
		ChargeSmoke.m_pos = { player->GetPos().x + 50 ,player->GetPos().y };
		ChargeSmoke.m_scale.x = 1;
	}
	else {
		ChargeSmoke.m_pos = { player->GetPos().x - 50,player->GetPos().y };
		ChargeSmoke.m_scale.x = -1;
	}

	ChargeSmoke.m_scaleMat = Math::Matrix::CreateScale(ChargeSmoke.m_scale.x, ChargeSmoke.m_scale.y, 1);
	ChargeSmoke.m_transMat = Math::Matrix::CreateTranslation(ChargeSmoke.m_pos.x-scrollX, ChargeSmoke.m_pos.y-scrollY, 0);
	ChargeSmoke.m_matrix = ChargeSmoke.m_scaleMat * ChargeSmoke.m_transMat;

}

void C_LightningPar::ChargeAtkDraw()
{
	for (int i = 0; i < ChargeAtkNum; i++) {
		SHADER.m_spriteShader.SetMatrix(ChargeAtk[i].m_matrix);
		Math::Rectangle rect = { 0,0,32,32 };
		SHADER.m_spriteShader.DrawTex(&LightTex, 0, 0, &rect, &ChargeAtk[i].m_color);
	}

	SHADER.m_spriteShader.SetMatrix(ChargeSmoke.m_matrix);
	int a, b;
	a = ChargeSmoke.m_texNum % 4;
	b = ChargeSmoke.m_texNum / 4;
	Math::Rectangle rect = {512*a,512*b,512,512};
	SHADER.m_spriteShader.DrawTex(&ChargeSmokeTex, 0, 0, &rect, &ChargeSmoke.m_color);

}

void C_LightningPar::ChargeAtkInit()
{
	for (int i = 0; i < ChargeAtkNum; i++) {
		ChargeAtk[i].m_alive = false;
		ChargeAtk[i].m_scale = { 3,0.7 };
		ChargeAtk[i].m_color = { 1,1,1,1 };
		ChargeAtk[i].m_pos = { 0,0 };
	}

	ChargeSmoke.m_alive = true;
	ChargeSmoke.m_scale = { 1,1 };

}

void C_LightningPar::DeathEmit(Math::Vector2 a_Pos)
{
	DeathAni.m_pos = a_Pos;
	DeathAni.m_alive = true;
	DeathAni.m_bOne = false;
	DeathAni.m_scale = { 0.7,0.7 };
}

void C_LightningPar::DeathUpdate(float scrollX, float scrollY)
{
	if (DeathAni.m_alive) {
		if (!DeathAni.m_bOne) {
			DeathAni.m_color = { 1,1,1,1 };
			DeathAni.m_texNum = AnimationLoop(3, 16, DeathAni);
		}
		else DeathAni.m_alive = false;
	}
	else {
		DeathAni.m_color = { 0,0,0,0 };
	}

	DeathAni.m_scaleMat = Math::Matrix::CreateScale(DeathAni.m_scale.x, DeathAni.m_scale.y, 1);
	DeathAni.m_transMat = Math::Matrix::CreateTranslation(DeathAni.m_pos.x - scrollX, DeathAni.m_pos.y - scrollY, 0);
	DeathAni.m_matrix = DeathAni.m_scaleMat * DeathAni.m_transMat;
}

void C_LightningPar::DeathDraw()
{
	SHADER.m_spriteShader.SetMatrix(DeathAni.m_matrix);
	int a, b;
	a = DeathAni.m_texNum % 8;
	b = DeathAni.m_texNum / 8;
	Math::Rectangle rect = { 512 * a,512 * b,512,512 };
	SHADER.m_spriteShader.DrawTex(&DeathTex, 0, 0, &rect, &DeathAni.m_color);
}

int C_LightningPar::AnimationLoop(int frame, int changeMaxCnt,particle &type)
{
	type.m_framecnt++;

	if (type.m_framecnt >= frame) {
		type.m_changecnt++;
		type.m_framecnt = 0;
	}

	if (type.m_changecnt >= changeMaxCnt) {
		type.m_changecnt = 0;
		type.m_bOne = true;
	}

	return type.m_changecnt;
}

void C_LightningPar::LoadTexture()
{
	LightTex.Load("Texture/Player/BlueLightning_transparent.png");
	//LightTex.Load("Texture/Lightning_transparent.png");
	LiEffTex.Load("Texture/Player/LightningEffect_transparent.png");
	smokeTex.Load("Texture/Player/smoke_transparent.png");
	LiChargeTex.Load("Texture/Player/Charge_transparent.png");
	ChargeSmokeTex.Load("Texture/Player/Stab_Hand Drawn_v1 Spritesheets/Stab_Hand Drawn_v1_Ground Wind_Only_spritesheet.png");
	DeathTex.Load("Texture/Player/Explosion_Energy_v2_spritesheet.png");
}

void C_LightningPar::ReleaseTexture()
{
	LightTex.Release();
	LiEffTex.Release();
	smokeTex.Release();
	LiChargeTex.Release();
	ChargeSmokeTex.Release();
	DeathTex.Release();
}

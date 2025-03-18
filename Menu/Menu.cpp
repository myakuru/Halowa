#include "Menu.h"
#include"../Scene.h"

//状態メニュー==========================================================================================
void C_StatusMenu::Update()
{
	if (!m_Active) return;

	int OldNowSelect = m_NowSelect;

	if (!m_AutoUpdate) {
		if (GetAsyncKeyState('A') & 0x8000) {
			if (!m_KeyFlg) {
				m_KeyFlg = true;
				m_NowSelect--;
			}
		}
		else if (GetAsyncKeyState('D') & 0x8000) {
			if (!m_KeyFlg) {
				m_KeyFlg = true;
				m_NowSelect++;
			}
		}
		else {
			m_KeyFlg = false;
		}
	}

	if (m_NowSelect == -1)m_NowSelect = 3-1;
	if (m_NowSelect == 3) m_NowSelect = 0;

	if (SelectFrame.m_pos.x != -550 + (m_NowSelect * 110)) {
		if (SelectFrame.m_pos.x > -550 + (m_NowSelect * 110)) SelectFrame.m_move.x -= 55;
		if (SelectFrame.m_pos.x < -550 + (m_NowSelect * 110))SelectFrame.m_move.x += 55;
	}
	
	GetMousePos(&m_MousePos);

	if (!m_AutoUpdate) {
		for (int i = 0; i < AvoidMax; i++) {
			SkillHit(SkillType[i]);
			if (SkillType[i].m_Hit) m_NowSelect = SkillType[i].m_Num;
		}
	}

	ObjectMatrix(AllFrame);
	ObjectMatrix(SelectFrame);
	ObjectMatrix(UnderLine);


	for (int i = 0; i < 3; i++) {
		MpCost[i].m_Alive = false;
		ElectricPow[i].m_Alive = false;
		OverDamage[i].m_Alive = false;
	}

	for (int i = 0; i < AvoidMax; i++) SkillMatrix(SkillType[i]);

	C_Chara* player = m_mOwner->GetChara();

	//数値表示

	for (int i = 0; i < 3; i++) {
		NowHP[i].m_Alive = false;
		MaxHP[i].m_Alive = false;
		MaxMP[i].m_Alive = false;
		Money[i].m_Alive = false;
	}

	std::string NowHpStr = std::to_string(player->GetNowHp()/10);
	int NowHpDigits = NowHpStr.length();
	for (int i = 0; i < NowHpDigits; i++) {
		NowHP[i].m_Alive = true;
		NowHP[i].m_scale = { 0.8,0.8 };
		NowHP[i].m_value= std::stoi(NowHpStr.substr(i, 1));
		NowHP[i].m_pos = { (float)(-525 + i * 20),165 };
	}

	std::string MaxHpStr = std::to_string(player->GetMaxHp() / 10);
	int MaxHpDigits = MaxHpStr.length();
	for (int i = 0; i < MaxHpDigits; i++) {
		MaxHP[i].m_Alive = true;
		MaxHP[i].m_scale = { 0.8,0.8 };
		MaxHP[i].m_value = std::stoi(MaxHpStr.substr(i, 1));
		MaxHP[i].m_pos = { (float)(-450 + i * 20),165 };
	}

	std::string MaxMpStr = std::to_string(player->GetMaxMp() / 10);
	int MaxMpDigits = MaxMpStr.length();
	for (int i = 0; i < MaxHpDigits; i++) {
		MaxMP[i].m_Alive = true;
		MaxMP[i].m_scale = { 0.8,0.8 };
		MaxMP[i].m_value = std::stoi(MaxMpStr.substr(i, 1));
		MaxMP[i].m_pos = { (float)(-470 + i * 20),130 };
	}

	std::string MoneyStr = std::to_string(player->GetCoin());
	int MoneyDigits = MoneyStr.length();
	if (MoneyDigits <= 3) {
		for (int i = 0;i < MoneyDigits;i++) {
			Money[i].m_Alive = true;
			Money[i].m_scale = { 0.8,0.8 };
			Money[i].m_value = std::stoi(MoneyStr.substr(i, 1));
			Money[i].m_pos = { (float)(-495 + i * 20),203 };
		}
	}
	else {
		for (int i = 0;i < 3;i++) {
			Money[i].m_Alive = true;
			Money[i].m_scale = { 0.8,0.8 };
			Money[i].m_value =9;
			Money[i].m_pos = { (float)(-495 + i * 20),203 };
		}
	}

	std::string AtkBoostStr = std::to_string(player->GetAtkBoost());
	BoostAtkLv.m_pos = { -445,95 };
	BoostAtkLv.m_scale = { 0.8,0.8 };
	BoostAtkLv.m_value = std::stoi(AtkBoostStr.substr(0, 1));
	
	for (int i = 0; i < 3; i++) {
		NumberMatrix(NowHP[i]);
		NumberMatrix(MaxHP[i]);
		NumberMatrix(MaxMP[i]);
		NumberMatrix(Money[i]);
		NumberMatrix(MpCost[i]);
		NumberMatrix(ElectricPow[i]);
		NumberMatrix(OverDamage[i]);
	}
	NumberMatrix(BoostAtkLv);

	if (m_NowSelect != OldNowSelect) {
		seInst[StatusSelectSE]->Play();
	}

}

void C_StatusMenu::Draw()
{
	if (!m_Active) return;

	DrawObject(AllFrame, { 0,0,1280,720 });
	DrawObject(SelectFrame, { 0,0,100,100 });
	DrawObject(UnderLine, { 0,0,1280,60 });

	for (int i = 0; i < AvoidMax; i++) DrawSkill(SkillType[i]);

	for (int i = 0; i < 3; i++) {
		DrawNumber(NowHP[i]);
		DrawNumber(MaxHP[i]);
		DrawNumber(MaxMP[i]);
		DrawNumber(Money[i]);
		DrawNumber(MpCost[i]);
		DrawNumber(ElectricPow[i]);
		DrawNumber(OverDamage[i]);
	}
	DrawNumber(BoostAtkLv);

}

void C_StatusMenu::Init()
{
	UnderLine.m_pos = { 0,-330 };
	for (int i = 0; i < AvoidMax; i++) {
		SkillType[i].m_AvoidType = static_cast<AvoidType>(i);
		SkillType[i].m_Num = i;
	}

}

void C_StatusMenu::ImGuiUpdate()
{
	ImGui::Checkbox(u8"AutoUpdate", &m_AutoUpdate);
}

void C_StatusMenu::SkillMatrix(Skill& a_Skill)
{
	if (a_Skill.m_Num == m_NowSelect) {
		a_Skill.m_InfoAlive = true;
		if (m_AutoUpdate) {
			if (m_ShakeMove != 0) {
				if (m_Shake) {
					a_Skill.m_pos.x += (float)m_ShakeMove;
					m_Shake = false;
				}
				else {
					a_Skill.m_pos.x -= (float)m_ShakeMove;
					m_Shake = true;
					m_ShakeCnt++;
				}

				if (m_ShakeCnt == 3) {
					m_ShakeCnt = 0;
					m_ShakeMove--;
				}

			}
			else {
				if (a_Skill.m_InfoAlive) {
					static float trans = 1;
					if(trans==1)seInst[UnLockSE]->Play();
					a_Skill.m_color = { trans,trans,trans,trans };
					if (trans > 0) trans -= 0.05;
					else {
						trans = 1;
						a_Skill.m_color = { 1,1,1,1 };
						m_AutoUpdate = false;
						m_mOwner->GetChara()->SetAvoidFlg(a_Skill.m_AvoidType);
						m_mOwner->GetMenu()->SetAutoUpdate();
					}
				}
			}

		}
	}
	else a_Skill.m_InfoAlive = false;

	a_Skill.m_transMat = Math::Matrix::CreateTranslation(a_Skill.m_pos.x, a_Skill.m_pos.y, 0);
	a_Skill.m_scaleMat = Math::Matrix::CreateScale(a_Skill.m_scale.x, a_Skill.m_scale.y, 1);
	a_Skill.m_mat = a_Skill.m_scaleMat * a_Skill.m_transMat;

	if (a_Skill.m_InfoAlive) {
		a_Skill.m_InfoMat = Math::Matrix::CreateTranslation(a_Skill.m_InfoPos.x, a_Skill.m_InfoPos.y, 0);
		C_Chara* player = m_mOwner->GetChara();
		
		if (a_Skill.m_Alive) {
			std::string MPCostStr = std::to_string(player->GetAvoidMP(a_Skill.m_AvoidType) / 10);
			int MPCostDigits = MPCostStr.length();
			for (int i = 0; i < MPCostDigits; i++) {
				MpCost[i].m_Alive = true;
				MpCost[i].m_scale = { 0.8,0.8 };
				MpCost[i].m_value = std::stoi(MPCostStr.substr(i, 1));
				MpCost[i].m_pos = { (float)(180 + i * 20),-111 };
			}

			std::string ElectricPowStr = std::to_string(player->GetAvoidElectricPow(a_Skill.m_AvoidType));
			int ElectricPowDigits = ElectricPowStr.length();
			for (int i = 0; i < ElectricPowDigits; i++) {
				ElectricPow[i].m_Alive = true;
				ElectricPow[i].m_scale = { 0.8,0.8 };
				ElectricPow[i].m_value = std::stoi(ElectricPowStr.substr(i, 1));
				ElectricPow[i].m_pos = { (float)(180 + i * 20),-170 };
			}

			if (a_Skill.m_AvoidType == OverAvoid) {
				std::string OverDamageStr = std::to_string(player->GetOverDamage());
				int OverDamageDigits = OverDamageStr.length();
				for (int i = 0; i < OverDamageDigits; i++) {
					OverDamage[i].m_Alive = true;
					OverDamage[i].m_scale = { 0.8,0.8 };
					OverDamage[i].m_value = std::stoi(OverDamageStr.substr(i, 1));
					OverDamage[i].m_pos = { (float)(150 + i * 20),-225 };
				}
			}
		}

	}

}

void C_StatusMenu::DrawSkill(Skill& a_Skill)
{
	SHADER.m_spriteShader.SetMatrix(a_Skill.m_mat);
	Math::Rectangle rect = { 0,0,100,100 };
	if (a_Skill.m_Alive)SHADER.m_spriteShader.DrawTex(&a_Skill.m_tex, 0, 0, &rect, &a_Skill.m_color);
	else {
		if(!m_AutoUpdate) SHADER.m_spriteShader.DrawTex(&m_LockTex, 0, 0, &rect, &a_Skill.m_color);
		else if(m_ShakeMove!=0)SHADER.m_spriteShader.DrawTex(&m_LockTex, 0, 0, &rect, &a_Skill.m_color);
		else if(!a_Skill.m_InfoAlive)SHADER.m_spriteShader.DrawTex(&m_LockTex, 0, 0, &rect, &a_Skill.m_color);
		else SHADER.m_spriteShader.DrawTex(&m_UnLockTex, 0, 0, &rect, &a_Skill.m_color);
	}

	if (a_Skill.m_InfoAlive) {

		SHADER.m_spriteShader.SetMatrix(a_Skill.m_InfoMat);
		rect = { 0,0,600,600 };
		if (a_Skill.m_Alive)SHADER.m_spriteShader.DrawTex(&a_Skill.m_InfoTex, 0, 0, &rect, &a_Skill.m_InfoColor);
		else SHADER.m_spriteShader.DrawTex(&a_Skill.m_LockInfoTex, 0, 0, &rect, &a_Skill.m_InfoColor);
	}

}

void C_StatusMenu::LoadTex()
{
	AllFrame.m_Tex.Load("Texture/Menu/StatusMenu/StatusFrame.png");
	SelectFrame.m_Tex.Load("Texture/Menu/StatusMenu/SelectFrame.png");
	UnderLine.m_Tex.Load("Texture/Menu/StatusMenu/StatusUnderLine.png");

	m_NumTex.Load("Texture/Menu/StatusMenu/Number2.png");

	SkillType[NormalAvoid].m_tex.Load("Texture/Menu/StatusMenu/NormalSkill.png");
	SkillType[NormalAvoid].m_InfoTex.Load("Texture/Menu/StatusMenu/NormalSkillInfo.png");
	SkillType[NormalAvoid].m_LockInfoTex.Load("Texture/Menu/StatusMenu/LockNormalSkillInfo2.png");

	SkillType[LongAvoid].m_tex.Load("Texture/Menu/StatusMenu/LongSkill.png");
	SkillType[LongAvoid].m_InfoTex.Load("Texture/Menu/StatusMenu/LongSkillInfo.png");
	SkillType[LongAvoid].m_LockInfoTex.Load("Texture/Menu/StatusMenu/LockLongSkillInfo2.png");

	SkillType[OverAvoid].m_tex.Load("Texture/Menu/StatusMenu/OverSkill.png");
	SkillType[OverAvoid].m_InfoTex.Load("Texture/Menu/StatusMenu/OverSkillInfo.png");
	SkillType[OverAvoid].m_LockInfoTex.Load("Texture/Menu/StatusMenu/LockOverSkillInfo2.png");

	m_LockTex.Load("Texture/Menu/StatusMenu/Lock.png");
	m_UnLockTex.Load("Texture/Menu/StatusMenu/UnLock.png");
}

void C_StatusMenu::ReleaseTex()
{
	AllFrame.m_Tex.Release();
	SelectFrame.m_Tex.Release();
	UnderLine.m_Tex.Release();
	
	SkillType[NormalAvoid].m_tex.Release();
	SkillType[NormalAvoid].m_InfoTex.Release();

	SkillType[LongAvoid].m_tex.Release();
	SkillType[LongAvoid].m_InfoTex.Release();
	SkillType[LongAvoid].m_LockInfoTex.Release();

	SkillType[OverAvoid].m_tex.Release();
	SkillType[OverAvoid].m_InfoTex.Release();
	SkillType[OverAvoid].m_LockInfoTex.Release();

	m_LockTex.Release();
	m_UnLockTex.Release();
}

void C_StatusMenu::LoadSE()
{
	//メモリ領域の確保
	for (int i = 0; i < StatusMenuSEMAX; i++) se[i] = std::make_shared<KdSoundEffect>();

	se[StatusSelectSE]->Load("Sound/Menu/lowbon.wav");
	se[UnLockSE]->Load("Sound/Menu/カセットデッキ開ける.wav");

	for (int i = 0; i < StatusMenuSEMAX; i++) {
		//スピーカーのメモリ確保&音データを渡す
		seInst[i] = se[i]->CreateInstance(false);
		//ボリューム調整
		seInst[i]->SetVolume(vol);
	}
}

void C_StatusMenu::SetActive(bool a_Active, Scene* a_Owner)
{
	m_Active = a_Active;
	m_mOwner = a_Owner;
	SelectFrame.m_pos.y = -130;
	C_Chara* player = a_Owner->GetChara();
	if (player->GetHaveAvoid(NormalAvoid))SkillType[NormalAvoid].m_Alive = true;
	else SkillType[NormalAvoid].m_Alive = false;
	SkillType[NormalAvoid].m_pos = { (float)(-550 + (0 * 110)),-130 };
	SkillSetRange(SkillType[NormalAvoid]);

	if (player->GetHaveAvoid(LongAvoid))SkillType[LongAvoid].m_Alive = true;
	else SkillType[LongAvoid].m_Alive = false;
	SkillType[LongAvoid].m_pos = {(float)( - 550 + (1 * 110)),-130};
	SkillSetRange(SkillType[LongAvoid]);

	if (player->GetHaveAvoid(OverAvoid))SkillType[OverAvoid].m_Alive = true;
	else SkillType[OverAvoid].m_Alive = false;
	SkillType[OverAvoid].m_pos = { (float)( - 550 + (2 * 110)),-130};
	SkillSetRange(SkillType[OverAvoid]);

}

//アイテムメニュー==========================================================================================

void C_ItemMenu::Update()
{
	if (!m_Active)return;
	C_Chara* player = m_mOwner->GetChara();

	if (player->GetHaveItemAll() > 0) {
		int OldNowSelect = m_NowSelect;

		if (GetAsyncKeyState('A') & 0x8000) {
			if (!m_KeyFlg) {
				m_KeyFlg = true;
				m_NowSelect--;
			}
		}
		else if (GetAsyncKeyState('D') & 0x8000) {
			if (!m_KeyFlg) {
				m_KeyFlg = true;
				m_NowSelect++;
			}
		}
		else if (GetAsyncKeyState('E') & 0x8000) {
			if (!m_KeyFlg) {
				if(!seInst[EquipmentSE]->IsPlay())seInst[EquipmentSE]->Play();
				m_KeyFlg = true;
				CharacterE.m_Alive = true;
				C_Chara* player = m_mOwner->GetChara();
				if (m_NowSelect == HPPotion.m_Num) player->SetNowHaveItem(SetHaveHPPotion);
				if (m_NowSelect == MPPotion.m_Num)player->SetNowHaveItem(SetHaveMPPotion);
				CharacterE.m_pos = { (float)(-550 + (m_NowSelect * 110) + 30),160 };
			}
		}
		else {
			m_KeyFlg = false;
		}

		GetMousePos(&m_MousePos);

		ItemHit(HPPotion);
		ItemHit(MPPotion);



		if (HPPotion.m_Hit) {
			m_NowSelect = HPPotion.m_Num;
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				if (!seInst[EquipmentSE]->IsPlay())seInst[EquipmentSE]->Play();
				CharacterE.m_Alive = true;
				player->SetNowHaveItem(SetHaveHPPotion);
				CharacterE.m_pos = { (float)(-550 + (m_NowSelect * 110) + 30),160 };
			}
		}

		if (MPPotion.m_Hit) {
			m_NowSelect = MPPotion.m_Num;
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				if (!seInst[EquipmentSE]->IsPlay())seInst[EquipmentSE]->Play();
				CharacterE.m_Alive = true;
				player->SetNowHaveItem(SetHaveMPPotion);
				CharacterE.m_pos = { (float)(-550 + (m_NowSelect * 110) + 30),160 };
			}
		}

		switch (player->GetNowHaveItem()) {
		case HaveHPPotion:
			CharacterE.m_pos = { (float)(-550 + (HPPotion.m_Num * 110) + 30),160 };
			break;
		case HaveMPPotion:
			CharacterE.m_pos = { (float)(-550 + (MPPotion.m_Num * 110) + 30),160 };
			break;
		case ItemEmpty:
			CharacterE.m_Alive = false;
		}

		if (m_NowSelect == -1)m_NowSelect = m_HaveItemCnt - 1;
		if (m_NowSelect == m_HaveItemCnt) m_NowSelect = 0;

		if (SelectFrame.m_pos.x != -550 + (m_NowSelect * 110)) {
			if (SelectFrame.m_pos.x > -550 + (m_NowSelect * 110)) SelectFrame.m_move.x -= 55;
			if (SelectFrame.m_pos.x < -550 + (m_NowSelect * 110))SelectFrame.m_move.x += 55;
		}

		if (player->GetNowHaveItem()==ItemEmpty) {
			CharacterE.m_Alive = false;
		}

		if (OldNowSelect != m_NowSelect) {
			seInst[ItemSelectSE]->Play();
		}

		ObjectMatrix(SelectFrame);
	}
	ObjectMatrix(AllFrame);
	ObjectMatrix(CharacterE);
	ObjectMatrix(UnderLine);

	if (HPPotion.m_Alive)ItemMatrix(HPPotion,HPPotionNum);
	if (MPPotion.m_Alive)ItemMatrix(MPPotion,MPPotionNum);



}

void C_ItemMenu::Draw()
{
	if (!m_Active)return;
	C_Chara* player = m_mOwner->GetChara();
	if(player->GetHaveItemAll()>0) DrawObject(SelectFrame, { 0,0,100,100 });
	DrawObject(AllFrame,{ 0,0,1280,720 });
	DrawObject(UnderLine, { 0,0,1280,60 });
	if (CharacterE.m_Alive)DrawObject(CharacterE, { 0,0,32,32 });

	if (HPPotion.m_Alive)DrawItems(HPPotion);
	if (MPPotion.m_Alive)DrawItems(MPPotion);

}

void C_ItemMenu::Init()
{
	UnderLine.m_pos = { 0,-330 };
}

void C_ItemMenu::ItemMatrix(Items& a_Items,ItemsNum a_ItemsNum)
{
	if (a_Items.m_Num == m_NowSelect) a_Items.m_InfoAlive = true;
	else a_Items.m_InfoAlive = false;

	a_Items.m_transMat = Math::Matrix::CreateTranslation(a_Items.m_pos.x, a_Items.m_pos.y, 0);
	a_Items.m_scaleMat = Math::Matrix::CreateScale(a_Items.m_scale.x, a_Items.m_scale.y, 1);
	a_Items.m_mat = a_Items.m_scaleMat * a_Items.m_transMat;

	if (a_Items.m_InfoAlive) {
		a_Items.m_InfoMat = Math::Matrix::CreateTranslation(a_Items.m_InfoPos.x, a_Items.m_InfoPos.y, 0);

		C_Chara* player = m_mOwner->GetChara();
		std::string ItemCntStr = std::to_string(player->GetHaveItems(a_ItemsNum));
		a_Items.ItemCnt.m_pos = { 480,130 };
		a_Items.ItemCnt.m_scale = { 1,1 };
		a_Items.ItemCnt.m_value = std::stoi(ItemCntStr.substr(0, 1));

		NumberMatrix(a_Items.ItemCnt);
	}
}

void C_ItemMenu::DrawItems(Items& a_Items)
{
	SHADER.m_spriteShader.SetMatrix(a_Items.m_mat);
	Math::Rectangle rect = { 0,0,100,100 };
	SHADER.m_spriteShader.DrawTex(&a_Items.m_tex, 0, 0, &rect, &a_Items.m_color);

	if (a_Items.m_InfoAlive) {
		SHADER.m_spriteShader.SetMatrix(a_Items.m_InfoMat);
		rect = { 0,0,400,400 };
		SHADER.m_spriteShader.DrawTex(&a_Items.m_InfoTex, 0, 0, &rect, &a_Items.m_InfoColor);

		DrawNumber(a_Items.ItemCnt);

	}

}

void C_ItemMenu::LoadTex()
{
	SelectFrame.m_Tex.Load("Texture/Menu/ItemMenu/SelectFrame.png");
	AllFrame.m_Tex.Load("Texture/Menu/ItemMenu/ItemMenuFrame.png");
	CharacterE.m_Tex.Load("Texture/Menu/ItemMenu/E.png");
	UnderLine.m_Tex.Load("Texture/Menu/ItemMenu/ItemUnderLine.png");

	m_NumTex.Load("Texture/Menu/ItemMenu/Number2.png");

	HPPotion.m_tex.Load("Texture/Menu/ItemMenu/HPPotion.png");
	HPPotion.m_InfoTex.Load("Texture/Menu/ItemMenu/HPPotionInfo.png");
	MPPotion.m_tex.Load("Texture/Menu/ItemMenu/MPPotion.png");
	MPPotion.m_InfoTex.Load("Texture/Menu/ItemMenu/MPPotionInfo.png");
}

void C_ItemMenu::ReleaseTex()
{
	SelectFrame.m_Tex.Release();
	AllFrame.m_Tex.Release();
	CharacterE.m_Tex.Release();
	UnderLine.m_Tex.Release();

	HPPotion.m_tex.Release();
	HPPotion.m_InfoTex.Release();
	MPPotion.m_tex.Release();
	MPPotion.m_InfoTex.Release();
}

void C_ItemMenu::LoadSE()
{
	//メモリ領域の確保
	for (int i = 0; i < ItemMenuSEMAX; i++) se[i] = std::make_shared<KdSoundEffect>();

	se[ItemSelectSE]->Load("Sound/Menu/dishes_on_cloth.wav");
	se[EquipmentSE]->Load("Sound/Menu/put_book2.wav");

	for (int i = 0; i < ItemMenuSEMAX; i++) {
		//スピーカーのメモリ確保&音データを渡す
		seInst[i] = se[i]->CreateInstance(false);
		//ボリューム調整
		seInst[i]->SetVolume(vol);
	}

}

void C_ItemMenu::SetActive(bool a_Active, Scene* a_Owner)
{
	if (!m_Active) {
		m_mOwner = a_Owner;
		m_HaveItemCnt = 0;
		SelectFrame.m_pos.y = 140;
		C_Chara* player = a_Owner->GetChara();
		if (player->GetHaveItems(HPPotionNum) > 0) {
			HPPotion.m_Alive = true;
			HPPotion.m_pos = { (float)(-550 + (m_HaveItemCnt * 110)),140 };
			ItemSetRange(HPPotion);
			HPPotion.m_Num = m_HaveItemCnt;
			m_HaveItemCnt++;
		}
		else {
			HPPotion.m_Alive = false;
		}
		if (player->GetHaveItems(MPPotionNum) > 0) {
			MPPotion.m_Alive = true;
			MPPotion.m_pos = { (float)(-550 + (m_HaveItemCnt * 110)),140 };
			ItemSetRange(MPPotion);
			MPPotion.m_Num = m_HaveItemCnt;
			m_HaveItemCnt++;
		}
		else {
			MPPotion.m_Alive = false;
		}
	}

	m_Active = a_Active;
}

void C_ItemMenu::ImGuiUpdate()
{
	ImGui::Checkbox(u8"StatusTabHit", &HPPotion.m_Hit);
	ImGui::Checkbox(u8"StatusTabHit", &MPPotion.m_Hit);
}

//コレクションメニュー==========================================================================================

void C_CollectItemMenu::Update()
{
	ObjectMatrix(AllFrame);
	ObjectMatrix(UnderLine);
	ObjectMatrix(SelectFrame);

	int OldSelect = m_NowSelect;

	if (m_CollectItemCnt != 0) {
		

		if (GetAsyncKeyState('A') & 0x8000) {
			if (!m_KeyFlg) {
				m_NowSelect--;
				m_KeyFlg = true;
			}
		}
		else if (GetAsyncKeyState('D') & 0x8000) {
			if (!m_KeyFlg) {
				m_NowSelect++;
				m_KeyFlg = true;
			}
		}
		else if (GetAsyncKeyState('W') & 0x8000) {
			if (!m_KeyFlg) {
				m_NowSelect -= 5;
				m_KeyFlg = true;
			}
		}
		else if (GetAsyncKeyState('S') & 0x8000) {
			if (!m_KeyFlg) {
				m_NowSelect += 5;
				m_KeyFlg = true;
			}
		}
		else {
			m_KeyFlg = false;
		}
	}

	if (m_NowSelect <= 0) m_NowSelect = m_CollectItemCnt;
	if (m_NowSelect >= m_CollectItemCnt+1)m_NowSelect = 1;

	m_NowCol = (m_NowSelect-1) % 5;
	m_NowRow = (m_NowSelect-1) / 5;

	if (SelectFrame.m_pos.x != -550 + (m_NowCol * 110)) {
		if (SelectFrame.m_pos.x > -550 + (m_NowCol * 110)) SelectFrame.m_move.x -= 55;
		if (SelectFrame.m_pos.x < -550 + (m_NowCol * 110))SelectFrame.m_move.x += 55;
	}

	if (SelectFrame.m_pos.y != 140 - (m_NowRow * 110)) {
		if (SelectFrame.m_pos.y > 140 - (m_NowRow * 110))SelectFrame.m_move.y -= 55;
		if (SelectFrame.m_pos.y < 140 - (m_NowRow * 110))SelectFrame.m_move.y += 55;
	}

	GetMousePos(&m_MousePos);


	for (int i = 0; i < CollectItemsMax; i++) {
		CollectMatrix(CollectItem[i]);
		CollectHit(CollectItem[i]);
		if (CollectItem[i].m_Hit)m_NowSelect = CollectItem[i].m_Num;
	}

	if (OldSelect != m_NowSelect) {
		seInst[CollectSelectSEA]->Play();
		//seInst[CollectSelectSEB]->Play();
	}
	
	


	for (int i = 0; i < 2; i++) {
		NumberMatrix(AllCollectItem[i]);
		NumberMatrix(HaveCollectItem[i]);
	}

}

void C_CollectItemMenu::Draw()
{
	DrawObject(AllFrame,{0,0,1280,720});
	if (m_CollectItemCnt != 0) DrawObject(SelectFrame,{0,0,100,100});
	DrawObject(UnderLine, { 0,0,1280,60 });

	for (int i = 0; i < CollectItemsMax; i++) {
		DrawCollect(CollectItem[i]);
	}

	for (int i = 0; i < 2; i++) {
		DrawNumber(AllCollectItem[i]);
		DrawNumber(HaveCollectItem[i]);
	}
}

void C_CollectItemMenu::Init()
{
	UnderLine.m_pos = { 0,-330 };
	SelectFrame.m_pos = { -550,140 };
	/*for (int i = 0; i < CollectItemsMax; i++) {
		CollectItem[i].m_InfoPos = { 320,-90 };
	}*/
}

void C_CollectItemMenu::LoadTex()
{
	AllFrame.m_Tex.Load("Texture/Menu/CollectMenu/AllFrame2.png");
	SelectFrame.m_Tex.Load("Texture/Menu/CollectMenu/SelectFrame.png");
	UnderLine.m_Tex.Load("Texture/Menu/CollectMenu/CollectUnderLine.png");

	CollectItem[FirstKey].m_Tex.Load("Texture/Menu/CollectMenu/ITEMS_B_118.png");
	CollectItem[FirstKey].m_InfoTex.Load("Texture/Menu/CollectMenu/FirstKeyInfo.png");

	CollectItem[SecondKey].m_Tex.Load("Texture/Menu/CollectMenu/ITEMS_B_111.png");
	CollectItem[SecondKey].m_InfoTex.Load("Texture/Menu/CollectMenu/SecondKeyInfo.png");

	CollectItem[ThirdKey].m_Tex.Load("Texture/Menu/CollectMenu/ITEMS_B_121.png");
	CollectItem[ThirdKey].m_InfoTex.Load("Texture/Menu/CollectMenu/ThirdKeyInfo.png");

	CollectItem[AncientBook].m_Tex.Load("Texture/Menu/CollectMenu/AncientBook.png");
	CollectItem[AncientBook].m_InfoTex.Load("Texture/Menu/CollectMenu/AncientBookInfo.png");

	CollectItem[SunBook].m_Tex.Load("Texture/Menu/CollectMenu/SunBook.png");
	CollectItem[SunBook].m_InfoTex.Load("Texture/Menu/CollectMenu/SunBookInfo.png");

	CollectItem[PocketWatch].m_Tex.Load("Texture/Menu/CollectMenu/PocketWatch.png");
	CollectItem[PocketWatch].m_InfoTex.Load("Texture/Menu/CollectMenu/PocketWatchInfo.png");

	CollectItem[SuperLuckCrystal].m_Tex.Load("Texture/Menu/CollectMenu/Crystal.png");
	CollectItem[SuperLuckCrystal].m_InfoTex.Load("Texture/Menu/CollectMenu/CrystalInfo.png");

	CollectItem[Horn].m_Tex.Load("Texture/Menu/CollectMenu/Horn.png");
	CollectItem[Horn].m_InfoTex.Load("Texture/Menu/CollectMenu/HornInfo.png");

	m_NumTex.Load("Texture/Menu/ItemMenu/Number2.png");

}

void C_CollectItemMenu::ReleaseTex()
{

	AllFrame.m_Tex.Release();
	SelectFrame.m_Tex.Release();
	UnderLine.m_Tex.Release();

	CollectItem[FirstKey].m_Tex.Release();
	CollectItem[FirstKey].m_InfoTex.Release();
	CollectItem[SecondKey].m_Tex.Release();
	CollectItem[SecondKey].m_InfoTex.Release();
	CollectItem[ThirdKey].m_Tex.Release();
	CollectItem[ThirdKey].m_InfoTex.Release();

	CollectItem[AncientBook].m_Tex.Release();
	CollectItem[AncientBook].m_InfoTex.Release();

	CollectItem[SunBook].m_Tex.Release();
	CollectItem[SunBook].m_InfoTex.Release();

	CollectItem[PocketWatch].m_Tex.Release();
	CollectItem[PocketWatch].m_InfoTex.Release();

	CollectItem[SuperLuckCrystal].m_Tex.Release();
	CollectItem[SuperLuckCrystal].m_InfoTex.Release();

	CollectItem[Horn].m_Tex.Release();
	CollectItem[Horn].m_InfoTex.Release();
}

void C_CollectItemMenu::LoadSE()
{
	//メモリ領域の確保
	for (int i = 0; i < CollectMenuSEMAX; i++) se[i] = std::make_shared<KdSoundEffect>();

	se[CollectSelectSEA]->Load("Sound/Menu/lowbon.wav");
	se[CollectSelectSEB]->Load("Sound/Menu/put_ring_of_keys.wav");

	for (int i = 0; i < CollectMenuSEMAX; i++) {
		//スピーカーのメモリ確保&音データを渡す
		seInst[i] = se[i]->CreateInstance(false);
		//ボリューム調整
		seInst[i]->SetVolume(vol);
	}
}

void C_CollectItemMenu::ImGuiUpdate()
{
	if (ImGui::Button(u8"全て取得")) {
		for (int i = 0; i < CollectItemsMax; i++) {
			SetCollectItem(static_cast<CollectItemsNum>(i));
		}
	}

	ImGui::Text("FIrstKeyNum:%d", CollectItem[FirstKey].m_Num);
	ImGui::Text("SecondKeyNum:%d", CollectItem[SecondKey].m_Num);
	ImGui::Text("SecondKeyNum:%d", CollectItem[ThirdKey].m_Num);
	ImGui::Text("AncientBookNum:%d", CollectItem[AncientBook].m_Num);
	ImGui::Text("SunBookNum:%d", CollectItem[SunBook].m_Num);
	ImGui::Text("PocketWatchNum:%d", CollectItem[PocketWatch].m_Num);
	ImGui::Text("CrystalNum:%d", CollectItem[SuperLuckCrystal].m_Num);
	ImGui::Text("HornNum:%d", CollectItem[Horn].m_Num);

	if (ImGui::Button(u8"FirstKey取得"))SetCollectItem(FirstKey);

	if (ImGui::Button(u8"SecondKey取得"))SetCollectItem(SecondKey);

	if (ImGui::Button(u8"ThirdKey取得"))SetCollectItem(ThirdKey);

	if (ImGui::Button(u8"AncientBook取得"))SetCollectItem(AncientBook);

	if (ImGui::Button(u8"SunBook取得"))SetCollectItem(SunBook);

	if (ImGui::Button(u8"PocketWatch取得"))SetCollectItem(PocketWatch);

	


	ImGui::Text("ColectItemCnt:%d",m_CollectItemCnt);
	ImGui::Text("NowSelectCnt:%d",m_NowSelect);
	
}

void C_CollectItemMenu::SetActive(bool a_Active, Scene* a_Owner)
{
	
	if (!m_Active) {
		m_mOwner = a_Owner;
		for (int i = 0; i < CollectItemsMax; i++) {
			if (CollectItem[i].m_Alive) {
				CollectItem[i].m_Pos = { (float)(-550 + CollectItem[i].m_col * 110),
										(float)(140- CollectItem[i].m_row*110)};

				CollectSetRange(CollectItem[i]);
			}
		}

		

		for (int i = 0; i < 2; i++) {
			AllCollectItem[i].m_Alive = false;
			HaveCollectItem[i].m_Alive = false;
		}

		C_Chara* player = m_mOwner->GetChara();
		std::string AllCollectStr = std::to_string(static_cast<int>(CollectItemsMax));
		int AllCollectDigits = AllCollectStr.length();
		for (int i = 0; i < AllCollectDigits; i++) {
			AllCollectItem[i].m_Alive = true;
			AllCollectItem[i].m_pos = { -375,215 };
			AllCollectItem[i].m_scale = { 0.8,0.8 };
			AllCollectItem[i].m_value = std::stoi(AllCollectStr.substr(0, 1));
		}

		std::string HaveCollectStr = std::to_string(m_CollectItemCnt);
		int HaveCollectDigits = HaveCollectStr.length();
		for (int i = 0; i < HaveCollectDigits; i++) {
			HaveCollectItem[i].m_Alive = true;
			HaveCollectItem[i].m_pos = { -410,215 };
			HaveCollectItem[i].m_scale = { 0.8,0.8 };
			HaveCollectItem[i].m_value = std::stoi(HaveCollectStr.substr(0, 1));
		}

	}
	m_Active = a_Active;
}

void C_CollectItemMenu::CollectMatrix(S_CollectItem& a_CollectItem)
{
	if (a_CollectItem.m_Alive) {
		a_CollectItem.m_Mat = Math::Matrix::CreateTranslation(a_CollectItem.m_Pos.x, a_CollectItem.m_Pos.y, 0);

		if (m_NowSelect == a_CollectItem.m_Num) a_CollectItem.m_InfoAlive = true;
		else a_CollectItem.m_InfoAlive = false;

		if (a_CollectItem.m_InfoAlive) {
			a_CollectItem.m_InfoMat = Math::Matrix::CreateTranslation(a_CollectItem.m_InfoPos.x, a_CollectItem.m_InfoPos.y, 0);
		}
	}
}

void C_CollectItemMenu::DrawCollect(S_CollectItem& a_CollectItem)
{
	if (a_CollectItem.m_Alive) {
		SHADER.m_spriteShader.SetMatrix(a_CollectItem.m_Mat);
		Math::Rectangle rect = { 0,0,100,100 };
		SHADER.m_spriteShader.DrawTex(&a_CollectItem.m_Tex, 0, 0, &rect, &a_CollectItem.m_Color);

		if (a_CollectItem.m_InfoAlive) {
			SHADER.m_spriteShader.SetMatrix(a_CollectItem.m_InfoMat);
			rect = { 0,0,600,600 };
			SHADER.m_spriteShader.DrawTex(&a_CollectItem.m_InfoTex, 0, 0, &rect, &a_CollectItem.m_Color);
		}

	}
}

void C_CollectItemMenu::MenuDatSave()
{
	std::ofstream file("SaveDat/MenuSave/MenuSaveDat.dat");
	if (!file)return;

	file << "FirstKey,SecondKey,ThirdKey,AncientBook,SunBook,PocketWatch,SuperLuckCrystal,Horn,CollectItemCnt\n";

	for (int i = 0; i < CollectItemsMax; i++) {
		file << BoolToString(CollectItem[i].m_Alive);
		file << ",";
	}
	file << m_CollectItemCnt;
	file << "\n";

	for (int i = 0; i < CollectItemsMax; i++) {
		file << CollectItem[i].m_Num;
		if (i != static_cast<int>(CollectItemsMax) - 1) file << ",";
	}

	file.close();
}

void C_CollectItemMenu::MenuDatLoad()
{
	std::ifstream ifs("SaveDat/MenuSave/MenuSaveDat.dat");
	if (ifs.fail())return;

	std::string line;
	bool IsHeader = true;
	bool IsSecond = true;

	while (std::getline(ifs, line)) {
		if (IsHeader) {
			IsHeader = false;
			continue;
		}

		std::stringstream ss(line);
		std::string cell;

		if (IsSecond) {
			IsSecond = false;
			for (int i = 0; i < CollectItemsMax; i++) {
				std::getline(ss, cell, ',');
				CollectItem[i].m_Alive = ParseBool(cell);
			}
			std::getline(ss, cell, ',');
			m_CollectItemCnt = stoi(cell);

			continue;
		}

		for (int i = 0; i < CollectItemsMax; i++) {
			std::getline(ss, cell, ',');
			CollectItem[i].m_Num = stoi(cell);
			CollectItem[i].m_row = (CollectItem[i].m_Num - 1) / 5;
			CollectItem[i].m_col = (CollectItem[i].m_Num - 1) % 5;
		}

	}

	ifs.close();

}

void C_CollectItemMenu::MenuDatDelete()
{
	std::remove("SaveDat/MenuSave/MenuSaveDat.dat");
}

//マップメニュー==========================================================================================

void C_MapMenu::Update()
{
	ObjectMatrix(AllFrame);
	C_MapBook* mapbook = m_mOwner->GetMapBook();
	mapbook->SetMapUiFlg(true);
}

void C_MapMenu::Draw()
{
	DrawObject(AllFrame, { 0,0,1280,720 });
}

void C_MapMenu::LoadTex()
{
	AllFrame.m_Tex.Load("Texture/Menu/MapMenu/WhiteBack.png");
}

void C_MapMenu::ReleaseTex()
{

	AllFrame.m_Tex.Release();
}

//メニュー==========================================================================================

void C_Menu::Update()
{
	if (!m_Active) return;

	int OldMenuNum = m_MenuNum;

	if (!m_AutoUpdate) {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (!m_KeyFlg) {
				m_KeyFlg = true;
				m_MenuNum = static_cast<MenuNum>(static_cast<int>(m_MenuNum) - 1);
				seInst[MenuTabSelectSE]->Play();
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (!m_KeyFlg) {
				m_KeyFlg = true;
				m_MenuNum = static_cast<MenuNum>(static_cast<int>(m_MenuNum) + 1);
				seInst[MenuTabSelectSE]->Play();
			}
		}
		else {
			m_KeyFlg = false;
		}
	}

	switch (m_MenuNum) {
	case Status:
		OverSelectFrame.m_pos = { -297,335 };
		break;
	case Item:
		OverSelectFrame.m_pos = { -102,335 };
		break;
	case Collect:
		OverSelectFrame.m_pos = { 97,335 };
		break;
	case Map:
		OverSelectFrame.m_pos = { 277,335 };
		break;
	default:
		break;
	}

	if (!m_AutoUpdate) {
		if (GetAsyncKeyState(VK_TAB) & 0x8000 || GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
			if (!m_TabKeyFlg) {
				seInst[ExitMenuSE]->Play();
				m_TabKeyFlg = true;
				m_Active = false;
				C_Chara* player = m_mOwner->GetChara();
				player->SetTabKeyFlg(true);
				seInst[ExitMenuSE]->Play();
			}
		}
		else {
			m_TabKeyFlg = false;
		}
	}

	if (m_MenuNum == MenuMax)m_MenuNum = static_cast<MenuNum>(static_cast<int>(MenuMin) + 1);
	if (m_MenuNum == MenuMin)m_MenuNum = static_cast<MenuNum>(static_cast<int>(MenuMax) - 1);

	m_StatusMenu.SetAlive(false);
	m_ItemMenu.SetAlive(false);

	StatusTab.m_scale = { 1,1 };
	ItemTab.m_scale = { 1,1 };
	CollectTab.m_scale = { 1,1 };
	MapTab.m_scale = { 1,1 };
	

	ObjectMatrix(UnderLine);
	ObjectMatrix(OverLine);
	ObjectMatrix(OverSelectFrame);
	ObjectMatrix(BackGround);

	//マウス処理
	GetMousePos(&m_MousePos);


	TabSetRange(StatusTab);
	TabSetRange(ItemTab);
	TabSetRange(CollectTab);
	TabSetRange(MapTab);

	TabHit(StatusTab);
	TabHit(ItemTab);
	TabHit(CollectTab);
	TabHit(MapTab);

	if (!StatusTab.m_Hit) {
		if (!ItemTab.m_Hit) {
			if (!CollectTab.m_Hit) {
				if (!MapTab.m_Hit) {
					SEOneFlg = false;
				}
			}
		}
	}

	if (!m_AutoUpdate) {
		if (StatusTab.m_Hit) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				m_MenuNum = Status;
				seInst[MenuTabSelectSE]->Play();
			}
		}
		if (ItemTab.m_Hit) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				m_MenuNum = Item;
				seInst[MenuTabSelectSE]->Play();
			}
		}
		if (CollectTab.m_Hit) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				m_MenuNum = Collect;
				seInst[MenuTabSelectSE]->Play();
			}
		}
		if (MapTab.m_Hit) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				m_MenuNum = Map;
				seInst[MenuTabSelectSE]->Play();
			}
		}
	}
	
	
	switch (m_MenuNum) {
	case Status:
		m_StatusMenu.SetActive(true, m_mOwner);
		m_StatusMenu.Update();
		StatusTab.m_scale = { 1.1,1.1 };
		break;
	case Item:
		m_ItemMenu.SetActive(true, m_mOwner);
		m_ItemMenu.Update();
		ItemTab.m_scale = { 1.1,1.1 };
		break;
	case Collect:
		m_CollectItemMenu.SetActive(true, m_mOwner);
		m_CollectItemMenu.Update();
		CollectTab.m_scale = { 1.1,1.1 };
		break;
	case Map:
		m_MapMenu.SetOwner(m_mOwner);
		m_MapMenu.Update();
		MapTab.m_scale = { 1.1,1.1 };
		break;
	default:
		break;
	}

	if (OldMenuNum != m_MenuNum) {
		m_CollectItemMenu.SetFActive();
	}

	TabMatrix(StatusTab);
	TabMatrix(ItemTab);
	TabMatrix(CollectTab);
	TabMatrix(MapTab);
}

void C_Menu::Draw()
{
	if (!m_Active) return;
	DrawObject(BackGround, { 0,0,1280,720 });

	DrawObject(UnderLine, { 0,0,1280,60 });
	DrawObject(OverLine, { 0,0,1280,60 });

	switch (m_MenuNum) {
	case Status:
		m_StatusMenu.Draw();
		break;
	case Item:
		m_ItemMenu.Draw();
		break;
	case Collect:
		m_CollectItemMenu.Draw();
		break;
	case Map:
		m_MapMenu.Draw();
		break;
	default:
		break;

	}
	
	

	DrawTab(StatusTab);
	DrawTab(ItemTab);
	DrawTab(CollectTab);
	DrawTab(MapTab);

	DrawObject(OverSelectFrame, { 0,0,150,70 });
	
}

void C_Menu::Init()
{
	StatusTab.m_Pos = { -297,335 };
	ItemTab.m_Pos = { -102,335 };
	CollectTab.m_Pos = { 97,335 };
	MapTab.m_Pos = { 277,335 };

	TabSetRange(StatusTab);
	TabSetRange(ItemTab);
	TabSetRange(CollectTab);
	TabSetRange(MapTab);

	StatusTab.m_Num = Status;
	ItemTab.m_Num = Item;
	CollectTab.m_Num = Collect;
	MapTab.m_Num = Map;

	m_ItemMenu.Init();
	m_StatusMenu.Init();
	m_CollectItemMenu.Init();

}

void C_Menu::LoadTex()
{
	UnderLine.m_Tex.Load("Texture/Menu/UnderLine.png");
	OverLine.m_Tex.Load("Texture/Menu/OverLine.png");
	OverSelectFrame.m_Tex.Load("Texture/Menu/OverSelectFrame.png");
	BackGround.m_Tex.Load("Texture/Menu/BlackBack.png");

	m_ItemMenu.LoadTex();
	m_StatusMenu.LoadTex();
	m_CollectItemMenu.LoadTex();
	m_MapMenu.LoadTex();

	StatusTab.m_Tex.Load("Texture/Menu/status.png");
	ItemTab.m_Tex.Load("Texture/Menu/Item.png");
	CollectTab.m_Tex.Load("Texture/Menu/collection.png");
	MapTab.m_Tex.Load("Texture/Menu/map.png");

}

void C_Menu::ReleaseTex()
{
	UnderLine.m_Tex.Release();
	OverLine.m_Tex.Release();
	OverSelectFrame.m_Tex.Release();

	m_ItemMenu.ReleaseTex();
	m_StatusMenu.ReleaseTex();
	m_CollectItemMenu.ReleaseTex();
	m_MapMenu.ReleaseTex();

	StatusTab.m_Tex.Release();
	ItemTab.m_Tex.Release();
	CollectTab.m_Tex.Release();
	MapTab.m_Tex.Release();

}

void C_Menu::LoadSE()
{
	//メモリ領域の確保
	for (int i = 0; i < MenuSEMAX; i++) se[i] = std::make_shared<KdSoundEffect>();

	se[MenuTabSelectSE]->Load("Sound/Menu/put_cardboard_box.wav");
	se[MenuTabMouseHitSE]->Load("Sound/Menu/put_light_object.wav");
	se[ExitMenuSE]->Load("Sound/Menu/lift_bag.wav");
	se[OpenMenuSE]->Load("Sound/Menu/bag_on_car_seat.wav");
	se[LiberationSE]->Load("Sound/Menu/Onoma-Sparkle05-1(Low).wav");

	for (int i = 0; i < MenuSEMAX; i++) {
		//スピーカーのメモリ確保&音データを渡す
		seInst[i] = se[i]->CreateInstance(false);
		//ボリューム調整
		seInst[i]->SetVolume(vol);
	}

	m_ItemMenu.LoadSE();
	m_StatusMenu.LoadSE();
	m_CollectItemMenu.LoadSE();

}

void C_Menu::ImGuiUpdate()
{
	m_StatusMenu.ImGuiUpdate();
	m_CollectItemMenu.ImGuiUpdate();

	return;
	m_ItemMenu.ImGuiUpdate();

	if (ImGui::Button(u8"Menu起動"))
	{
		SetActive(true);
	}

	ImGui::Checkbox(u8"MenuActive", &m_Active);
	

	ImGui::Text("Mouse Pos : %.2f, %.2f", (float)m_MousePos.x, (float)m_MousePos.y);
	ImGui::Checkbox(u8"StatusTabHit", &StatusTab.m_Hit);
	ImGui::Checkbox(u8"StatusTabHit", &ItemTab.m_Hit);
	ImGui::Checkbox(u8"StatusTabHit", &CollectTab.m_Hit);
	ImGui::Checkbox(u8"StatusTabHit", &MapTab.m_Hit);
}



#include "Chara.h"
#include"../Scene.h"
#include "../XInputManager.h"

C_Chara::C_Chara()
{
}

void C_Chara::Init()
{
	m_player.m_pos = { 0,0 };
	m_player.m_move = { 0,0 };
	m_player.m_scroll = { 0,0 };
	m_player.m_scale = {ScaleSize,ScaleSize };
	m_player.m_color = { 1,1,1,1 };
	m_player.m_isRun = false;
	m_player.m_isJump = false;
	m_player.m_isHurt = false;
	m_player.m_isAlive = true;
	m_player.m_isAvoid = false;

	RunEndAni.m_bOne = true;
	AttackStdAni.m_bOne = true;

    PlayerData.m_AvoidHaveFlg[NormalAvoid] = true;

	m_bThunDirectX = true;
	m_bThunDirectDw = false;
	m_bThunDirectUp = false;

	Test.m_half = NormalAtkHalf;
	TestKeyFlg = false;

	m_Nor.m_PosAdjust = 150;
	m_player.NowAvoidType = NormalAvoid;
	m_player.m_MaxHp = level1;
	m_player.m_MaxMp = 1000;
	m_player.m_NowHp = m_player.m_MaxHp;
	m_player.m_NowMp = m_player.m_MaxMp;
	m_player.m_AtkUp[0] = true;

	ItemUsing.m_scale = { 3,3 };

	m_player.m_HaveItemAll = PlayerData.m_HaveHPPotion + PlayerData.m_HaveMPPotion;
	RunCnt = 0;

	//パーティクル
	Light.LightInit();
	Light.LiEffInit();
	Light.LiChargeInit();
	Light.ChargeAtkInit();
	TestInit();
	Light.SetOwner(m_owner);

	m_owner->GetEnemyAtkHit()->SetPlayer(this);

	LightningCharge.m_color = { 0,1,1,1 };
	LightningCharge.m_scale = { 0.9,0.9 };

}

void C_Chara::Update()
{
	if (!m_player.m_isAlive) {
		if (m_player.m_IsPoison) m_player.m_IsPoison = false;
		if (!HurtAni.m_bOne) {
			HurtAni.m_Num = NeoAnimation(3, HurtMax, HurtAni);
		}
		else if (!DeathAni.m_bOne) {
			DeathAni.m_Num = NeoAnimation(1, 50, DeathAni);
			C_MapBase* map = m_owner->GetMap();
			DeathEff.m_pos = m_player.m_pos;
			DeathEff.m_scaleMat = Math::Matrix::CreateScale(DeathEff.m_scale.x, DeathEff.m_scale.y, 1);
			DeathEff.m_transMat = Math::Matrix::CreateTranslation(DeathEff.m_pos.x-map->GetScrollX(), DeathEff.m_pos.y-map->GetScrollY(), 0);
			DeathEff.m_mat = DeathEff.m_scaleMat * DeathEff.m_transMat;
		}
		return;
	}


	C_StatusMenu* StatusMenu = m_owner->GetMenu()->GetStatusMenu();
	C_CollectItemMenu* collectmenu = m_owner->GetMenu()->GetCollectMenu();
	if (!PlayerData.m_AvoidHaveFlg[LongAvoid]) {
		if (collectmenu->GetCollectItemAlive(AncientBook)) {
			if (!collectmenu->GetFirstGetFlg(AncientBook)) {
				m_owner->GetMenu()->SetActive(LongAvoid);
			}
		}
	}
	if (!PlayerData.m_AvoidHaveFlg[OverAvoid]) {
		if (collectmenu->GetCollectItemAlive(SunBook)) {
			if (!collectmenu->GetFirstGetFlg(SunBook)) {
				m_owner->GetMenu()->SetActive(OverAvoid);
			}
		}
	}

	if(DeathAni.m_bOne) DeathAni.m_bOne = false;

	XInputManager::GetInstance().Update();
	AttackUpdate();
	ItemUse();

	//メニュー起動
	if (GetAsyncKeyState(VK_TAB) & 0x8000) {
		if (!m_TabKeyFlg) {
			m_TabKeyFlg = true;
			C_Menu* menu = m_owner->GetMenu();
			menu->SetActive(true);
			menu->SetTabKeyFlg(m_TabKeyFlg);
		}
	}
	else {
		m_TabKeyFlg = false;
	}

	if (!m_player.m_isAttackStd) {
		if (m_player.m_move.y < 0) {
			m_player.m_IsFall = true;
		}
	}
	
	//プレイヤーアニメーションまとめ
	PlayerAnimeUpdate();
	
	if (!m_player.m_isAvoid) {
		if (!m_player.m_isAttackStd) {
			if (!m_player.m_isAttackAir) {
				m_player.m_pos.x += m_player.m_move.x;
				m_player.m_pos.y += m_player.m_move.y;
			}
			else {
				m_player.m_move.y = 0;
			}
		}
		else {
			m_player.m_pos.x += m_player.m_move.x;
			m_player.m_move.y = 0;
		}
	}
	else {
		if (m_player.m_move.y < 0) {

			m_player.m_move.y = 0;
		}
	}

	if (!m_player.m_Events) {
		m_player.m_move.x = 0;
	}

	

	C_MapBase* map = m_owner->GetMap();

	if (!m_player.m_FuseBlows) {
		ThunUpdate();
	}
	
	HPMPUpdate();

	m_player.m_scaleMat = Math::Matrix::CreateScale(m_player.m_scale.x, m_player.m_scale.y, 1);
	m_player.m_transMat = Math::Matrix::CreateTranslation(m_player.m_pos.x-map->GetScrollX(), m_player.m_pos.y-map->GetScrollY(), 0);
	m_player.m_mat = m_player.m_scaleMat * m_player.m_transMat;

	Light.LightUpdate(map->GetScrollX(), map->GetScrollY());
	Light.LiEffUpdate(map->GetScrollX(), map->GetScrollY());
	Light.LiChargeUpdate(map->GetScrollX(), map->GetScrollY());
	Light.SmokeUpdate(map->GetScrollX(), map->GetScrollY());
	TestUpdate();
	

}

void C_Chara::PlayerAnimeUpdate()
{
	if (m_player.m_isAlive) {
		if (!m_player.m_isHurt) {
			if (!m_player.m_isJump) {
				if (!m_player.m_isAttackAir) {
					AttackAirAni.m_bOne = false;
					if (m_player.m_IsFall) {
						if (!FallAni.m_bOne) {
							FallAni.m_Num = NeoAnimation(3, FallMax, FallAni);
						}
						else {
							FallAni.m_Num = 4;
						}
					}
					else {
						FallAni.m_Num = 0;
						FallAni.m_TexNum = 0;
						FallAni.m_bOne = false;
					}
				}
				else {
					if (!AttackAirAni.m_bOne) {
						AttackAirAni.m_Num = NeoAnimation(3, AttackAirMax, AttackAirAni);
					}
					else {
						m_player.m_isAttackAir = false;
					}
				}

				if (!m_player.m_isAttackStd) {
					AttackStdAni.m_bOne = false;
					if (!m_player.m_isAvoid) {
						if (!m_player.m_IsFall) {
							if (!m_player.m_isRun) {
								RunAni.m_TexNum = 0;
								if (RunEndAni.m_bOne) {
									IdleAni.m_Num = Animation(3, IdleMax, IdleAni);
								}
								else {
									RunEndAni.m_Num = NeoAnimation(2, RunEndMax, RunEndAni);
								}
							}
							else {
								RunEndAni.m_bOne = false;
								RunEndAni.m_TexNum = 0;
								IdleAni.m_TexNum = 0;
								RunAni.m_Num = Animation(2, RunMax, RunAni);
							}
						}
					}
					else {
						switch (m_player.NowAvoidType) {
						case NormalAvoid:
							break;
						case LongAvoid:
							break;
						case OverAvoid:
							break;
						case Debug:
							if (!NorThunAni.m_bOne) {
								NorThunAni.m_Num = NeoAnimation(1, NorThunMax, NorThunAni);
							}
							else {
								m_player.m_isAvoid = false;
								NorThunAni.m_bOne = false;
							}
							break;
						default:
							break;
						}
					}
				}
				else {
					if (!AttackStdAni.m_bOne) {
						AttackStdAni.m_Num = NeoAnimation(3, AttackStdMax, AttackStdAni);
					}
					else {
						m_player.m_isAttackStd = false;
						AttackStdAni.m_bOne = false;
					}
				}
			}
			else {
				if (!m_player.m_isAttackAir) {
					AttackAirAni.m_bOne = false;
					if (!m_player.m_isAvoid) {
						if (!JumpAni.m_bOne) {
							FallAni.m_bOne = false;
							JumpAni.m_Num = NeoAnimation(4, JumpMax, JumpAni);
							FallAni.m_Num = 0;
						}
						else {
							if (m_player.m_move.y < 0) {
								if (!FallAni.m_bOne) {
									FallAni.m_Num = NeoAnimation(3, FallMax, FallAni);
									JumpAni.m_Num = 0;
								}
								else {
									FallAni.m_Num = 4;
								}
							}
						}
					}
					else {
						switch (m_player.NowAvoidType) {
						case NormalAvoid:
							break;
						case LongAvoid:
							break;
						case OverAvoid:
							break;
						case Debug:
							if (!NorThunAni.m_bOne) {
								NorThunAni.m_Num = NeoAnimation(1, NorThunMax, NorThunAni);
							}
							else {
								m_player.m_isAvoid = false;
								NorThunAni.m_bOne = false;
							}
							break;
						default:
							break;
						}
					}
				}
				else {
					if (!AttackAirAni.m_bOne) {
						AttackAirAni.m_Num = NeoAnimation(3, AttackAirMax, AttackAirAni);
					}
					else {
						m_player.m_isAttackAir = false;
					}
				}
			}
		}
		else {
			AttackStdAni.m_Num = 0;
			AttackAirAni.m_Num = 0;
			AttackStdAni.m_TexNum = 0;
			AttackAirAni.m_TexNum = 0;
			m_player.m_isAttackStd = false;
			m_player.m_isAttackAir = false;
			if (!HurtAni.m_bOne) {
				HurtAni.m_Num = NeoAnimation(3, HurtMax, HurtAni);
			}
			else {
				//m_player.m_isHurt = false;
				HurtAni.m_bOne = false;
			}
		}
	}
	else {
		if (!HurtAni.m_bOne) {
			HurtAni.m_Num = NeoAnimation(3, HurtMax, HurtAni);
		}
	}
}

void C_Chara::ThunUpdate()
{
	float a, b;
	if (m_bThunDirectRi) {
		ThuderAngle = 90;
		if (m_bThunDirectUp) {
			ThuderAngle = 135;
		}
		else if (m_bThunDirectDw) {
			ThuderAngle = 45;
		}
	}
	else if (m_bThunDirectLe) {
		ThuderAngle = 270;
		if (m_bThunDirectUp) {
			ThuderAngle = 225;
		}
		else if (m_bThunDirectDw) {
			ThuderAngle = 315;
		}
	}
	else {
		if (m_bThunDirectUp) {
			ThuderAngle = 180;
		}
		else if (m_bThunDirectDw) {
			ThuderAngle =360;
		}
	}

	if (!m_bThunDirectRi && !m_bThunDirectLe && !m_bThunDirectUp && !m_bThunDirectDw) {
		if (m_bThunDirectX) ThuderAngle = 90;
		else ThuderAngle = 270;
	}

	for (int i = 0; i < m_owner->GetGimicMgr()->GetMaxRod(); i++) {
		C_Rod* rod = m_owner->GetGimicMgr()->GetRod(i);
		if (rod->GetRodStage()) {
			if (rod->GetIsRange()) {
				ThuderAngle = GetAngle(m_player.m_pos, rod->GetPos());
			}

			if (rod->GetMPRange()) {
				m_player.m_NowMp += 50;
			}
		}

	}

	for (int i = 0; i < m_owner->GetGimicMgr()->GetMaxRod(); i++) {
		C_Rod2* rod2 = m_owner->GetGimicMgr()->GetRod2(i);
		if (rod2->GetRodStage()) {
			if (rod2->GetIsRange()) {
				ThuderAngle = GetAngle(m_player.m_pos, rod2->GetPos());
			}

			if (rod2->GetMPRange()) {
				m_player.m_NowMp += 50;
			}
		}
	}

	switch (m_player.NowAvoidType) {
	case NormalAvoid:
		if (m_Nor.m_Flg) {
			seInst[LightningSE]->Play();
			m_player.m_NowMp -= NorMp;
			//雷パーティクル方向指定・呼び出し============================================

			a = cos((AngleAdjust + ThuderAngle) * 3.14 / 180);
			b = sin((AngleAdjust + ThuderAngle) * 3.14 / 180);



			for (int i = 0; i < LightNum; i++) {
				m_Long.m_pos.x = m_player.m_pos.x + a * (i * 32) + (rand() % 20 - 10);
				m_Long.m_pos.y = m_player.m_pos.y + b * (i * 32) + (rand() % 20 - 10);
				Light.LightEmit(
					m_Long.m_pos.x, m_Long.m_pos.y,
					i + 10, 3.5, 0.7, ThuderAngle + AngleAdjust,
					{ 1,1,1,1 }, a, b, i, m_player.m_pos, 2);
			}

			for (int i = 0; i < LiEffNum; i++) {
				Light.LiEffEmit(m_player.m_pos.x + a * (i * 32),
					m_player.m_pos.y + b * (i * 32),
					(Rnd() * 4 - 2), Rnd() * 4 - 2, i + 10,
					Rnd(), Rnd(), rand() % 360, { 1,1,1,1 }, a, b, i);
			}
			m_Nor.m_Flg = false;
			//m_player.m_isAvoid = false;
		}
		break;
	case LongAvoid:
		if (m_Long.m_Flg) {
			seInst[LightningSE]->Play();
			m_player.m_NowMp -= LongMp;
			//雷パーティクル方向指定・呼び出し============================================

			

			a = cos((AngleAdjust+ThuderAngle) * 3.14 / 180);
			b = sin((AngleAdjust + ThuderAngle) * 3.14 / 180);

			for (int i = 0; i < LightNum; i++) {
				m_Long.m_pos.x = m_player.m_pos.x + a * (i * 32) + (rand() % 20 - 10);
				m_Long.m_pos.y = m_player.m_pos.y + b * (i * 32) + (rand() % 20 - 10);
				Light.LightEmit(
					m_Long.m_pos.x, m_Long.m_pos.y,
					i *5, 3.5, 0.7, ThuderAngle + AngleAdjust,
					{ 1,1,1,1 }, a, b, i, m_player.m_pos, 1);
			}

			/*for (int i = 0; i < LightNum; i++) {
				m_Long.m_pos.x = m_player.m_pos.x + a * (i * 32) + (rand() % 20 - 10);
				m_Long.m_pos.y = m_player.m_pos.y + b * (i * 32) + (rand() % 20 - 10);
				Light.LightEmit(
					m_Long.m_pos.x,m_Long.m_pos.y,
					i+10, 3, 0.7,ThuderAngle+AngleAdjust, 
					{ 1,1,1,1 },a,b,i,m_player.m_pos,1);
			}*/

			for (int i = 0; i < LiEffNum; i++) {
				Light.LiEffEmit(m_player.m_pos.x + a * (i * 32),
					m_player.m_pos.y + b * (i * 32),
					(Rnd() * 4 - 2), Rnd() * 4 - 2, i + 10,
					Rnd(), Rnd(), rand() % 360, { 1,1,1,1 }, a, b, i);
			}

			//===========================================================================
			m_Long.m_Flg = false;
			//m_player.m_isAvoid = false;

		}
		break;
	case OverAvoid:
		if (m_Over.m_Flg) {
			seInst[LightningSE]->Play();
			m_player.m_NowMp -= OverMp;
			//雷パーティクル方向指定・呼び出し============================================


			a = cos((AngleAdjust + ThuderAngle) * 3.14 / 180);
			b = sin((AngleAdjust + ThuderAngle) * 3.14 / 180);



			for (int i = 0; i < LightNum; i++) {
				m_Long.m_pos.x = m_player.m_pos.x + a * (i * 32) + (rand() % 20 - 10);
				m_Long.m_pos.y = m_player.m_pos.y + b * (i * 32) + (rand() % 20 - 10);
				Light.LightEmit(
					m_Long.m_pos.x, m_Long.m_pos.y,
					i + 10, 3, 0.7, ThuderAngle + AngleAdjust,
					{ 1,1,1,1 }, a, b, i, m_player.m_pos,1);
			}

			for (int i = 0; i < LiEffNum; i++) {
				Light.LiEffEmit(m_player.m_pos.x + a * (i * 32),
					m_player.m_pos.y + b * (i * 32),
					(Rnd() * 4 - 2), Rnd() * 4 - 2, i + 10,
					Rnd(), Rnd(), rand() % 360, { 1,1,1,1 }, a, b, i);
			}
			m_Over.m_Flg = false;
			//m_player.m_isAvoid = false;
		}
		break;
	case Debug:
		a = cos((AngleAdjust + ThuderAngle) * 3.14 / 180) * m_Nor.m_PosAdjust;
		b = sin((AngleAdjust + ThuderAngle) * 3.14 / 180) * m_Nor.m_PosAdjust;


		m_Debug.m_pos.x = m_player.m_pos.x + a;
		m_Debug.m_pos.y = m_player.m_pos.y + b;
	}

	if (NorThunAni.m_bOne) {
		if (m_bThunDirectRi) {
			m_player.m_pos.x = m_Debug.m_pos.x + m_Nor.m_PosAdjust;
		}
		else if (m_bThunDirectLe) {
			m_player.m_pos.x = m_Debug.m_pos.x - m_Nor.m_PosAdjust;
		}

		if (m_bThunDirectUp) {
			m_player.m_pos.y = m_Debug.m_pos.y + m_Nor.m_PosAdjust;
		}
		else if (m_bThunDirectDw) {
			m_player.m_pos.y = m_Debug.m_pos.y - m_Nor.m_PosAdjust;
		}

		if (!m_bThunDirectRi && !m_bThunDirectLe && !m_bThunDirectUp && !m_bThunDirectDw) {
			if (m_bThunDirectX) {
				m_player.m_pos.x = m_Debug.m_pos.x + m_Nor.m_PosAdjust;
			}
			else {
				m_player.m_pos.x = m_Debug.m_pos.x - m_Nor.m_PosAdjust;
			}
		}
	}

	//float a=cos(ThuderAngle)

	//ThuderAngle=GetAngle(m_player.m_pos, m_Nor.m_pos);

	C_MapBase* map = m_owner->GetMap();

	m_Debug.m_scaleMat = Math::Matrix::CreateScale(m_Debug.m_scale.x, m_Debug.m_scale.y, 1);
	m_Debug.m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(ThuderAngle));
	m_Debug.m_transMat = Math::Matrix::CreateTranslation(m_Debug.m_pos.x - map->GetScrollX(), m_Debug.m_pos.y - map->GetScrollY(), 0);
	m_Debug.m_mat = m_Debug.m_scaleMat * m_Debug.m_rotationMat * m_Debug.m_transMat;

	
}

void C_Chara::HPMPUpdate()
{
	//Updateで呼び出し
	//HP関連=============================================================

	//HP強化

	switch (PlayerData.m_HPBoostCnt) {
	case 2:
		m_player.m_HPUP[1] = true;
		break;
	case 3:
		m_player.m_HPUP[2] = true;
		break;
	case 4:
		m_player.m_HPUP[3] = true;
		break;
	case 5:
		m_player.m_HPUP[4] = true;
		break;
	default:
		break;
	}

	if (m_player.m_HPUP[4]) m_player.m_MaxHp = level5;
	else if (m_player.m_HPUP[3]) m_player.m_MaxHp = level4;
	else if (m_player.m_HPUP[2]) m_player.m_MaxHp = level3;
	else if (m_player.m_HPUP[1]) m_player.m_MaxHp = level2;
	else if (m_player.m_HPUP[0]) m_player.m_MaxHp = level1;

	if (m_owner->GetMenu()->GetCollectMenu()->GetCollectItemAlive(SuperLuckCrystal)) {
		static bool only;
		if (!only) {
			only = true;
			m_player.m_MaxHp += 200;
		}
	}

	//HPが三割以下ならピンチ演出
	if (m_player.m_NowHp <= m_player.m_MaxHp * 0.3) {
		static int DangerCnt;
		static int addcnt = 1;
		DangerCnt += addcnt;
		if (DangerCnt >= 50) addcnt *= -1;
		if (DangerCnt <= 0) addcnt *= -1;

		float transColor = (float)(DangerCnt) / 100 * 2;

		if (DangerCnt >= 10) {
			int a = 1;
		}

		Danger.m_color = { 1,transColor,transColor,transColor };

		Danger.m_mat = Math::Matrix::CreateTranslation(Danger.m_pos.x, Danger.m_pos.y, 0);
	}

	//HPが０以下で生存フラグオフ
	if (m_player.m_NowHp <= 0) {
		m_player.m_NowHp = 0;
		m_player.m_isAlive = false;
		return;
	}

	//毒状態ダメージ
	static int PoisonCnt;
	if (m_player.m_IsPoison) {
		PoisonCnt++;
		if (PoisonCnt >= 30) {
			PoisonCnt = 0;
			m_player.m_NowHp -= 50;
			m_owner->SetNumber(5, m_player.m_pos, false);
		}
	}
	else {
		PoisonCnt = 0;
	}

	//MP関連============================================================

	//MP強化

	switch (PlayerData.m_MPBoostCnt) {
	case 2:
		m_player.m_MPUP[1] = true;
		break;
	case 3:
		m_player.m_MPUP[2] = true;
		break;
	case 4:
		m_player.m_MPUP[3] = true;
		break;
	case 5:
		m_player.m_MPUP[4] = true;
		break;
	default:
		break;
	}

	if (m_player.m_MPUP[4]) m_player.m_MaxMp = level5;
	else if (m_player.m_MPUP[3]) m_player.m_MaxMp = level4;
	else if (m_player.m_MPUP[2]) m_player.m_MaxMp = level3;
	else if (m_player.m_MPUP[1])m_player.m_MaxMp = level2;
	else if (m_player.m_MPUP[0])m_player.m_MaxMp = level1;

	//MPが０以下でヒューズ切断フラグオン
	if (m_player.m_NowMp <= 0) {
		m_player.m_NowMp = 0;
		m_player.m_FuseBlows = true;
	}
	//ヒューズが切れた4秒後ヒューズ復活
	if (m_player.m_FuseBlows) {
		m_player.m_FuseCnt++;
		if (m_player.m_FuseCnt >= 300) {
			m_player.m_NowMp = m_player.m_MaxMp/10;
			m_player.m_FuseBlows = false;
		}
	}
	else {
		m_player.m_FuseCnt = 0;
	}

	//NowMPがMaxMPより小さければNowMPを増やす
	if (m_player.m_NowMp < m_player.m_MaxMp) {
		if (!m_player.m_FuseBlows) {
			m_player.m_NowMp++;
			if (m_owner->GetMenu()->GetCollectMenu()->GetCollectItemAlive(PocketWatch)) {
				static int cnt;
				cnt++;
				if (cnt >= 2) {
					cnt = 0;
					m_player.m_NowMp++;
				}
			}
		}
	}
	else {
		if (!m_player.m_FuseBlows) {
			m_player.m_NowMp = m_player.m_MaxMp;
		}
	}
}

void C_Chara::ItemUse()
{
	if (GetAsyncKeyState('C') & 0x8000) {
		if (!m_player.m_ItemUsing) {
			if (!m_player.m_ItemUseKeyFlg) {
				m_player.m_ItemUseKeyFlg = true;
				if (PlayerData.m_NowHaveItem != ItemEmpty) {
					m_player.m_ItemUsing = true;
					seInst[HealSE]->Play();
				}
			}
		}
	}
	else {
		m_player.m_ItemUseKeyFlg = false;
	}

	static int UseCnt;
	if (m_player.m_ItemUsing) {
		
		UseCnt++;
		if (UseCnt >= 45) {
			UseCnt = 0;
			C_ItemMenu* itemmenu = m_owner->GetMenu()->GetItemMenu();
			switch (PlayerData.m_NowHaveItem) {
			case ItemEmpty:
				break;
			case HaveHPPotion:
				if (PlayerData.m_HaveHPPotion > 0) {
					PlayerData.m_HaveHPPotion--;
					m_player.m_HaveItemAll--;
					m_player.m_NowHp += m_player.m_MaxHp/3;
					if (m_player.m_NowHp >= m_player.m_MaxHp) m_player.m_NowHp = m_player.m_MaxHp;

					if (PlayerData.m_HaveHPPotion == 0) {
						PlayerData.m_NowHaveItem = ItemEmpty;
						
						itemmenu->SetCharacterE(false);
					}
				}
				break;
			case HaveMPPotion:
				if (PlayerData.m_HaveMPPotion > 0) {
					PlayerData.m_HaveMPPotion--;
					m_player.m_HaveItemAll--;
					if (!m_player.m_FuseBlows) {
						m_player.m_NowMp += 300;
						if (m_player.m_NowMp >= m_player.m_MaxMp)m_player.m_NowMp = m_player.m_MaxMp;
					}
					if (PlayerData.m_HaveMPPotion == 0) {
						PlayerData.m_NowHaveItem = ItemEmpty;

						itemmenu->SetCharacterE(false);
					}
				}
				break;
			default:
				break;
			}
			m_player.m_ItemUsing = false;
		}

		if (m_player.m_isHurt) {
			if (seInst[HealSE]->IsPlay()) seInst[HealSE]->Stop();
			m_player.m_ItemUsing = false;
		}

		ItemUsing.m_pos = m_player.m_pos;
		

		ItemUsingAni.m_Num=NeoAnimation(4, 14, ItemUsingAni);

		C_MapBase* map = m_owner->GetMap();
		ItemUsing.m_scaleMat = Math::Matrix::CreateScale(ItemUsing.m_scale.x, ItemUsing.m_scale.y, 1);
		ItemUsing.m_transMat = Math::Matrix::CreateTranslation(ItemUsing.m_pos.x-map->GetScrollX(), ItemUsing.m_pos.y-map->GetScrollY(), 0);
		ItemUsing.m_mat = ItemUsing.m_scaleMat * ItemUsing.m_transMat;

	}
	else {
		UseCnt = 0;
		ItemUsingAni.m_bOne = false;
		ItemUsingAni.m_TexNum = 0;
	}
	

}

void C_Chara::HurtUpdate()
{
	//Actionにて呼び出し
	//Hit判定時にgetInvincibleを使い無敵の間Hit判定をしない

	//ダメージを受けたら無敵開始
	if (m_player.m_isHurt) {
		m_player.m_isHurtInvincible = true;
		m_player.m_isInvincible = true;
	}

	//無敵の間無敵時間カウント
	if (m_player.m_isHurtInvincible) {
		m_player.m_InvincibleCnt++;

		//4fごとに点滅
		if (m_player.m_InvincibleCnt % 8 < 4) {
			m_player.m_color = { 1,1,1,1 };
		}
		else {
			m_player.m_color = { 0,0,0,0 };
		}
	}

	//無敵時間が1.5秒経ったら無敵解除
	if (m_player.m_InvincibleCnt > 90) {
		m_player.m_isHurtInvincible = false;
		m_player.m_isInvincible = false;
		m_player.m_InvincibleCnt = 0;
	}

	//被弾ノックバック
	if (m_player.m_isHurt) {
		m_player.m_move = m_player.m_hurtMove;

		m_player.m_hurtMove.y--;
		m_player.m_hurtMove.x *= 0.95;

	}

	
	//m_player.m_hurtMove = { 10,20 };

	

}

void C_Chara::AttackUpdate()
{
	//Updateで呼び出し

	//攻撃力アップ
	switch (PlayerData.m_AtkBoostCnt) {
	case 2:
		m_player.m_AtkUp[1] = true;
		break;
	case 3:
		m_player.m_AtkUp[2] = true;
		break;
	case 4:
		m_player.m_AtkUp[3] = true;
		break;
	case 5:
		m_player.m_AtkUp[4] = true;
		break;
	default:
		break;
	}

	if (m_player.m_AtkUp[4]) m_player.m_AtkPow = AttackPowLevel[4];
	else if (m_player.m_AtkUp[3]) m_player.m_AtkPow = AttackPowLevel[3];
	else if (m_player.m_AtkUp[2]) m_player.m_AtkPow = AttackPowLevel[2];
	else if (m_player.m_AtkUp[1]) m_player.m_AtkPow = AttackPowLevel[1];
	else if (m_player.m_AtkUp[0]) m_player.m_AtkPow = AttackPowLevel[0];

	if (m_owner->GetMenu()->GetCollectMenu()->GetCollectItemAlive(Horn)) {
		static bool only;
		if (!only) {
			only = true;
			m_player.m_AtkPow += 10;
		}
	}

	//地上・空中攻撃の起動、ため攻撃のカウント

	if (!m_player.m_Events) {
		if (!m_Over.m_bAvoidCharge) {
			if (!m_player.m_isHurt) {
				if (!m_player.m_ItemUsing) {
					if (!m_player.m_isAvoid) {
						if (!m_player.m_AtkKeyFlg) {
							if (GetAsyncKeyState('E') & 0x8000 || XInputManager::GetInstance().IsBPressed_B() || GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								if (!m_player.m_AttackStdCha) {
									if (!m_player.m_isJump) {
										if (m_player.m_move.y == 0) {
											if (!m_player.m_isAttackAir) {
												if (!m_player.m_isAttackStd) {
													m_player.AttackChargeCnt = 0;
													m_player.m_isAttackStd = true;
												}
												m_player.AttackChargeCnt++;
												if (m_player.AttackChargeCnt / 40 == 1 && m_player.AttackChargeCnt % 40 == 0) seInst[ChargeAtkSEOne]->Play();
												if (m_player.AttackChargeCnt / 40 == 2 && m_player.AttackChargeCnt % 40 == 0) seInst[ChargeAtkSETwo]->Play();
												if (m_player.AttackChargeCnt / 40 == 3 && m_player.AttackChargeCnt % 40 == 0) seInst[ChargeAtkSEThree]->Play();
												AttackStdAni.m_TexNum = 0;
											}
										}
										else {
											if (!m_player.m_isAttackAir) {
												m_player.m_isAttackAir = true;
											}
										}
									}
									else {
										if (!m_player.m_isAttackAir) {
											m_player.m_isAttackAir = true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	C_MapBase* map = m_owner->GetMap();
	Light.ChargeAtkUpdate(map->GetScrollX(), map->GetScrollY());
}

void C_Chara::AttackAction()
{
	if (!m_player.m_Events) {
		if (!m_Over.m_bAvoidCharge) {
			if (!m_player.m_isHurt) {
				if (!m_player.m_isAvoid) {
					if (!m_player.m_AtkKeyFlg) {
						if (GetAsyncKeyState('E') & 0x8000||GetAsyncKeyState(VK_LBUTTON)&0x8000) {}
						else {
							if (m_player.AttackChargeCnt / 40 >= 1) m_player.m_AtkKeyFlg = true;
							if (m_player.m_isAttackStd)m_player.m_AttackStdCha = true;
							else m_player.m_AttackStdCha = false;
						}
					}

					if (m_player.m_AtkKeyFlg) {
						static int AttackEndCnt;
						if (m_player.m_isAttackStd) {
							m_player.m_AttackStdCha = true;
							if (AttackStdAni.m_TexNum == 2) {
								m_player.m_AtkFirstPos = m_player.m_pos;
								seInst[ChargeSlashSE]->Play();
							}
							if (AttackStdAni.m_TexNum == 3 || AttackStdAni.m_TexNum == 4) {
								m_player.m_isInvincible = true;
								if (m_player.AttackChargeCnt / 40 >= 1) {
									if (AttackStdAni.m_Num == 1 && AttackStdAni.m_FrameCnt == 1)seInst[ChargeSlashSE]->Play();
									if (m_bThunDirectX) m_player.m_move.x = 60;
									else m_player.m_move.x = -60;
									m_player.m_move.y = 0;
								}
							}
							else
								if (AttackStdAni.m_TexNum == 5) {
									m_player.m_AtkEndPos = m_player.m_pos;
									if (m_player.AttackChargeCnt / 40 >= 1) {
										if (AttackEndCnt < 30) {
											AttackEndCnt++;
											AttackStdAni.m_FrameCnt = 0;
										}
									}
								}
								else {
									m_player.m_isInvincible = false;
								}
						}
						else {
							m_player.m_AttackStdCha = false;
							m_player.m_ChargeAtkStart = false;
							m_player.m_AtkKeyFlg = false;
							m_player.AttackChargeCnt = 0;
							AttackEndCnt = 0;
						}
					}
					
				}
			}
		}
	}
}

void C_Chara::SEUpdate()
{
	static int SEcnt[SEMAX];
	//RunSE
	if (m_player.m_isRun) {
		if (m_player.m_move.y > -1) {
			if (!m_player.m_isAttackStd) {
				if (!m_player.m_isAttackAir) {
					if (!m_player.m_isJump) {
						SEcnt[RunSE]++;
						if(SEcnt[RunSE]==1)seInst[RunSE]->Play();
						if (SEcnt[RunSE] >= 25) {
							SEcnt[RunSE] = 0;
						}
					}
				}
			}
		}
	}
	else {
		SEcnt[RunSE] = 0;
	}

	//HurtSE
	if (m_player.m_isHurt) {
		SEcnt[HurtSE]++;
		if (SEcnt[HurtSE] == 1) {
			seInst[HurtSE]->Play();
		}
	}
	else {
		SEcnt[HurtSE] = 0;
	}

	//FuseBlowsSE
	if (m_player.m_FuseBlows) {
		SEcnt[FuseBlowsSE]++;
		if (SEcnt[FuseBlowsSE] == 1) {
			seInst[FuseBlowsSE]->Play();
		}
	}
	else {
		SEcnt[FuseBlowsSE] = 0;
	}

	//ChargeSE
	if (!m_player.m_isHurt) {
		if (m_Over.m_avoidChargeCnt == 1) {
			seInst[AvoidChargeSE]->Play();
		}
	}
	else {
		seInst[AvoidChargeSE]->Stop();
	}

}

void C_Chara::SEPlay(int a_num)
{
	hitseInst[a_num]->Play();
}

void C_Chara::TestUpdate()
{
	C_MapBase* map = m_owner->GetMap();
	static int slashrushCnt;
	if (slashrushCnt > 9) slashrushCnt = 0;
	//Updateで呼び出し
	//ためなし攻撃
	if (m_player.AttackChargeCnt / 40 < 1) {
		if (AttackStdAni.m_Num == 1 && AttackStdAni.m_FrameCnt == 1 ||
			AttackAirAni.m_Num == 1 && AttackAirAni.m_FrameCnt == 1) {
			seInst[AttackSE]->Play();
		}

		if (AttackStdAni.m_Num == 3 && AttackStdAni.m_FrameCnt == 2) {
			Test.m_half = NormalAtkHalf;
			if (m_bThunDirectX) Test.m_pos.x = m_player.m_pos.x + 70;
			else Test.m_pos.x = m_player.m_pos.x - 70;

			m_player.m_AttackHit = true;
			Test.m_pos.y = m_player.m_pos.y;
			Test.m_color = { 1,1,1,1 };
		}
		else if (AttackAirAni.m_Num == 3 && AttackAirAni.m_FrameCnt == 2) {

			if (m_bThunDirectX) Test.m_pos.x = m_player.m_pos.x + 70;
			else Test.m_pos.x = m_player.m_pos.x - 70;

			m_player.m_AttackHit = true;
			Test.m_pos.y = m_player.m_pos.y + 50;
			Test.m_color = { 1,1,1,1 };
		}
		else {
			m_player.m_AttackHit = false;
			Test.m_color = { 0,0,0,0 };
		}
	}
	else {
		if (AttackStdAni.m_TexNum == 5&&AttackStdAni.m_FrameCnt!=0) {
			m_player.m_ChargeAtkStart = true;
		}
	}

	static int FrameCnt;
	if (m_player.m_ChargeAtkStart) {
		Test.m_pos.x = (m_player.m_AtkFirstPos.x + m_player.m_AtkEndPos.x) / 2;
		Test.m_pos.y = m_player.m_pos.y;

		Test.m_half.x = abs(m_player.m_AtkEndPos.x - m_player.m_AtkFirstPos.x) / 2;
		Test.m_half.y = NormalAtkHalf.y;

		FrameCnt++;
		if (FrameCnt % 6 < 3) {
			if(FrameCnt%6==2) m_player.m_AttackHit = true;
			SlashRushInst[slashrushCnt]->Play();
			slashrushCnt++;
			Test.m_color = { 1,1,1,1 };
		}
		else {
			m_player.m_AttackHit = false;
			Test.m_color = { 0,0,0,0 };
		}
		ChargeSlashAni.m_Num=Animation(2, 14, ChargeSlashAni);


		ChargeSlash.m_Alive = true;

		ChargeSlash.m_scale = { Test.m_half.x / 180,0.4 };
		if (ChargeSlash.m_scale.x < 0.4) {
			ChargeSlash.m_Alive = false;
		}
		if (m_bThunDirectX) {
			if (ChargeSlash.m_scale.x < 0) ChargeSlash.m_scale *= -1;
		}
		else {
			if (ChargeSlash.m_scale.x > 0)ChargeSlash.m_scale *= -1;
		}

		ChargeSlash.m_pos = Test.m_pos;

		ChargeSlash.m_scaleMat = Math::Matrix::CreateScale(ChargeSlash.m_scale.x, ChargeSlash.m_scale.y, 1);
		ChargeSlash.m_transMat = Math::Matrix::CreateTranslation(ChargeSlash.m_pos.x-map->GetScrollX(), ChargeSlash.m_pos.y-map->GetScrollY(), 0);
		ChargeSlash.m_mat = ChargeSlash.m_scaleMat * ChargeSlash.m_transMat;

	}
	else {
		FrameCnt = 0;
		slashrushCnt = 0;
	}


		


		
	Test.m_transMat = Math::Matrix::CreateTranslation(Test.m_pos.x-map->GetScrollX(), Test.m_pos.y - map->GetScrollY(), 0);
	Test.m_mat = Test.m_transMat;

	float a, b, c;
	static float deg;
	if (deg < 360) deg += 70;
	else deg -= 360;
	if (abs(m_Shake.x) > 0.1 || abs(m_Shake.y) > 0.1) {

		a = cos(deg * 3.14 / 180) * m_Shake.x;
		b = sin(deg * 3.14 / 180) * m_Shake.y;

		m_Shake.x *= 0.92;
		m_Shake.y *= 0.92;

		map->SetScrollX(map->GetScrollX() + a);
		map->SetScrollY(map->GetScrollY() + b);
	}
	
	


}

void C_Chara::TestDraw()
{
	SHADER.m_spriteShader.SetMatrix(Test.m_mat);
	Math::Rectangle rect = { 0,0,(long)Test.m_half.x,(long)Test.m_half.y*2 };
	SHADER.m_spriteShader.DrawTex(&Test.Tex, 0, 0, &rect, &Test.m_color);
}

void C_Chara::TestInit()
{
	Test.m_pos = { 0,0 };
}

void C_Chara::PlayerDataSave()
{
	std::ofstream file("SaveDat/PlayerSave/SaveData.dat");
	if (!file)return;

	//セーブ中テキスト表示
	m_owner->GetSaving()->SaveFlg(true);

	PlayerData.m_SaveMap=m_owner->GetScene();

	file << "現在のマップ,現在のx座標,現在のy座標,現在の所持金,装備しているアイテム,通常回避所持,長距離回避所持,高電圧回避所持,現在の回避,HPポーション所持数,MPポーション所持数,HP強化回数,MP強化回数,攻撃強化回数\n";
	
	file << static_cast<int>(PlayerData.m_SaveMap) << ","
		<< m_player.m_pos.x << ","
		<< m_player.m_pos.y << ","
		<< PlayerData.m_NowCoin << ","
		<< static_cast<int>(PlayerData.m_NowHaveItem) << ","
		<< BoolToString(PlayerData.m_AvoidHaveFlg[NormalAvoid]) << ","
		<< BoolToString(PlayerData.m_AvoidHaveFlg[LongAvoid]) << ","
		<< BoolToString(PlayerData.m_AvoidHaveFlg[OverAvoid]) << ","
		<< static_cast<int>(m_player.NowAvoidType) << ","
		<< PlayerData.m_HaveHPPotion << ","
		<< PlayerData.m_HaveMPPotion << ","
		<< PlayerData.m_HPBoostCnt << ","
		<< PlayerData.m_MPBoostCnt << ","
		<< PlayerData.m_AtkBoostCnt << ",";



	file.close();
	
}

void C_Chara::PlayerDataLoad()
{
	std::ifstream ifs("SaveDat/PlayerSave/SaveData.dat");
	if (ifs.fail())return;

	std::string line;
	bool IsHeader = true;

	while (std::getline(ifs, line)) {
		if (IsHeader) {
			IsHeader = false;
			continue;
		}

		std::stringstream ss(line);
		std::string cell;

		std::getline(ss, cell, ',');
		PlayerData.m_SaveMap = static_cast<SceneType>(std::stoi(cell));

		std::getline(ss, cell, ',');
		PlayerData.m_SavePos.x = static_cast<float>(std::stoi(cell));

		std::getline(ss, cell, ',');
		PlayerData.m_SavePos.y = static_cast<float>(std::stoi(cell));

		m_owner->GetSceneChange()->Init_L(PlayerData.m_SaveMap,PlayerData.m_SavePos);

		std::getline(ss, cell, ',');
		PlayerData.m_NowCoin = std::stoi(cell);

		std::getline(ss, cell, ',');
		PlayerData.m_NowHaveItem = static_cast<HaveItems>(std::stoi(cell));

		for (int i = 0; i < AvoidMax; i++) {
			std::getline(ss, cell, ',');
			PlayerData.m_AvoidHaveFlg[i] = ParseBool(cell);
		}

		std::getline(ss, cell, ',');
		m_player.NowAvoidType = static_cast<AvoidType>(std::stoi(cell));

		std::getline(ss, cell, ',');
		PlayerData.m_HaveHPPotion = std::stoi(cell);

		std::getline(ss, cell, ',');
		PlayerData.m_HaveMPPotion = std::stoi(cell);

		std::getline(ss, cell, ',');
		PlayerData.m_HPBoostCnt = std::stoi(cell);

		std::getline(ss, cell, ',');
		PlayerData.m_MPBoostCnt = std::stoi(cell);

		std::getline(ss, cell, ',');
		PlayerData.m_AtkBoostCnt = std::stoi(cell);

	}

	ifs.close();

}

void C_Chara::PlayerDataDelete()
{
	const char* saveDataFile = "SaveDat/PlayerSave/SaveData.dat";
	if (std::remove(saveDataFile) == 0) {
		// メッセージボックスで削除成功を通知
	}
}

void C_Chara::Draw()
{
	if (!m_player.m_isAlive) {
		Math::Rectangle rect;
		if (!HurtAni.m_bOne) {
			SHADER.m_spriteShader.SetMatrix(m_player.m_mat);
			rect = { 0,0,900,900 };
			SHADER.m_spriteShader.DrawTex(&m_Texture[Hurt][HurtAni.m_Num], 0, 0, &rect, &m_player.m_color);
		}
		else if (!DeathAni.m_bOne) {
			SHADER.m_spriteShader.SetMatrix(DeathEff.m_mat);
			int row = DeathAni.m_Num % 8, col = DeathAni.m_Num / 8;
			rect = { row * 512,col * 512,512,512 };
			SHADER.m_spriteShader.DrawTex(&DeathEff.m_tex, 0, 0, &rect, &DeathEff.m_color);
		}else return;
	}
	Light.SmokeDraw();

	D3D.SetBlendState(BlendMode::Add);
	Light.ChargeAtkDraw();
	D3D.SetBlendState(BlendMode::Alpha);

	SHADER.m_spriteShader.SetMatrix(m_player.m_mat);
	Math::Rectangle rect;
	if (!m_player.m_isAvoid) {
		rect = { 0,0,900,900 };
	}
	if (m_player.m_isAlive) {
		if (!m_player.m_isHurt) {
			if (!m_player.m_isJump) {
				if (m_player.m_isAttackAir) {
					if (!AttackAirAni.m_bOne) {
						SHADER.m_spriteShader.DrawTex(&m_Texture[AttackAir][AttackAirAni.m_Num], 0, 0, &rect, &m_player.m_color);
					}
				}
				else
					if (m_player.m_IsFall) {
						SHADER.m_spriteShader.DrawTex(&m_Texture[Fall][FallAni.m_Num], 0, 0, &rect, &m_player.m_color);
					}
					else if (!m_player.m_isAttackStd) {
						if (!m_player.m_isAvoid) {
							if (!m_player.m_isRun) {
								if (RunEndAni.m_bOne) {
									SHADER.m_spriteShader.DrawTex(&m_Texture[Idle][IdleAni.m_Num], 0, 0, &rect, &m_player.m_color);
								}
								else {
									SHADER.m_spriteShader.DrawTex(&m_Texture[RunEnd][RunEndAni.m_Num], 0, 0, &rect, &m_player.m_color);
								}
							}
							else {
								//if (!m_player.m_move.x == 0) {
								SHADER.m_spriteShader.DrawTex(&m_Texture[Run][RunAni.m_Num], 0, 0, &rect, &m_player.m_color);
								//}
							}
						}
						else {
							switch (m_player.NowAvoidType) {
							case Debug:
								if (!NorThunAni.m_bOne) {
									SHADER.m_spriteShader.SetMatrix(m_Debug.m_mat);
									int i = NorThunAni.m_Num % 4;
									int j = NorThunAni.m_Num / 4;
									rect = { 512 * i,512 * j,512,512 };
									SHADER.m_spriteShader.DrawTex(&m_ThunderTexture, 0, 0, &rect);
								}
								break;
							default:
								break;
							}
						}
					}
					else {
						if (!AttackStdAni.m_bOne) {
							SHADER.m_spriteShader.DrawTex(&m_Texture[AttackStd][AttackStdAni.m_Num], 0, 0, &rect, &m_player.m_color);
						}
					}
			}
			else {
				if (!m_player.m_isAttackAir) {
					if (!m_player.m_isAvoid) {
						if (!JumpAni.m_bOne) {
							SHADER.m_spriteShader.DrawTex(&m_Texture[Jump][JumpAni.m_Num], 0, 0, &rect, &m_player.m_color);
						}
						else {
							SHADER.m_spriteShader.DrawTex(&m_Texture[Fall][FallAni.m_Num], 0, 0, &rect, &m_player.m_color);
						}
					}
					else {
						switch (m_player.NowAvoidType) {
						case Debug:
							if (!NorThunAni.m_bOne) {
								SHADER.m_spriteShader.SetMatrix(m_Debug.m_mat);
								int i = NorThunAni.m_Num % 4;
								int j = NorThunAni.m_Num / 4;
								rect = { 512 * i,512 * j,512,512 };
								SHADER.m_spriteShader.DrawTex(&m_ThunderTexture, 0, 0, &rect);
							}
							break;
						default:
							break;
						}
					}
				}
				else {
					if (!AttackAirAni.m_bOne) {
						SHADER.m_spriteShader.DrawTex(&m_Texture[AttackAir][AttackAirAni.m_Num], 0, 0, &rect, &m_player.m_color);
					}
				}
			}
		}
		else {
			if (!HurtAni.m_bOne) {
				SHADER.m_spriteShader.DrawTex(&m_Texture[Hurt][HurtAni.m_Num], 0, 0, &rect, &m_player.m_color);
			}
		}
	}
	else {
		if (!HurtAni.m_bOne) {
			SHADER.m_spriteShader.DrawTex(&m_Texture[Hurt][HurtAni.m_Num], 0, 0, &rect, &m_player.m_color);
		}
	}

	D3D.SetBlendState(BlendMode::Add);
	
	Light.LightDraw();
	Light.LiEffDraw();
	Light.LiChargeDraw();
	
	if (m_player.m_ItemUsing) {
		SHADER.m_spriteShader.SetMatrix(ItemUsing.m_mat);
		rect = { 0 + ItemUsingAni.m_Num * 64,5 * 64,64,64 };
		SHADER.m_spriteShader.DrawTex(&ItemUsing.m_tex, 0, 0, &rect, &ItemUsing.m_color);
	}

	D3D.SetBlendState(BlendMode::Alpha);

	TestDraw();

	if (m_player.m_NowHp <= m_player.m_MaxHp * 0.3) {
		SHADER.m_spriteShader.SetMatrix(Danger.m_mat);
		rect = { 0,0,1280,720 };
		SHADER.m_spriteShader.DrawTex(&Danger.m_tex, 0, 0, &rect, &Danger.m_color);
	}

	if (m_player.m_ChargeAtkStart) {
		if (ChargeSlash.m_Alive) {
			SHADER.m_spriteShader.SetMatrix(ChargeSlash.m_mat);
			int Row = ChargeSlashAni.m_Num % 4, Col = ChargeSlashAni.m_Num / 4;
			rect = { Row * 512,Col * 512,512,512 };
			SHADER.m_spriteShader.DrawTex(&ChargeSlash.m_tex, 0, 0, &rect, &ChargeSlash.m_color);
		}
	}

	if (m_Over.m_bAvoidCharge) {
		SHADER.m_spriteShader.SetMatrix(LightningCharge.m_mat);
		int Row = LightningChargeAni.m_Num % 8, Col = LightningChargeAni.m_Num / 8;
		rect = { Row * 512,Col * 512,512,512 };
		SHADER.m_spriteShader.DrawTex(&LightningCharge.m_tex, 0, 0, &rect, &LightningCharge.m_color);
	}

	
}

void C_Chara::Action()
{
	
	//スティックの入力を取得
	float leftStickX = XInputManager::GetInstance().GetLeftStickX();
	float leftStickY = XInputManager::GetInstance().GetLeftStickY();

	SEUpdate();
	if (!m_player.m_Events) {
		if (!m_Over.m_bAvoidCharge) {
			if (!m_player.m_isAvoid) {
				if (!m_player.m_isAttackAir) {
					if(m_player.m_move.y<32) m_player.m_move.y -= Gravity;
				}
			}
		}
		else {
			m_player.m_move.y = 0;
		}
	}
	else {
		m_player.m_move.y = 0;
	}

	if (m_player.m_isAlive) {						
		if (!m_player.m_Events) {
			if (!m_Over.m_bAvoidCharge) {
				if (!m_player.m_isAttackStd) {
					m_player.m_isRun = false;
					if (!m_player.m_isHurt) {
						if (!m_player.m_ItemUsing) {
							if (!m_player.m_isAvoid) {
								//スティックがお倒されたときの処理
									//左スティックが右に倒されたとき
								if (leftStickX > 0.1f) {
									m_player.m_isRun = true;
									m_player.m_isRunEnd = true;
									m_bThunDirectX = true;
									m_player.m_move.x += RunPow;
								}
								//左スティックが左に倒されたとき
								if (leftStickX < -0.1f) {
									m_player.m_isRun = true;
									m_player.m_isRunEnd = true;
									m_bThunDirectX = false;
									m_player.m_move.x -= RunPow;
								}
								if (!m_bThunDirectLe) {
									if (GetAsyncKeyState('D') & 0x8000) {
										m_player.m_isRun = true;
										m_player.m_isRunEnd = true;
										m_bThunDirectX = true;
										m_player.m_move.x += RunPow;
									}
								}
								if (!m_bThunDirectRi) {
									if (GetAsyncKeyState('A') & 0x8000) {
										m_player.m_isRun = true;
										m_player.m_isRunEnd = true;
										m_bThunDirectX = false;
										m_player.m_move.x -= RunPow;
									}
								}

								
								if (m_player.NowAvoidType != NoAvoid) {
									if (GetAsyncKeyState('Q') & 0x8000 || XInputManager::GetInstance().IsLTriggerPressed_LTrigger()) {
										if (!m_player.m_bAvoidChangeKey) {
											seInst[AvoidChangeSE]->Play();
											switch (m_player.NowAvoidType) {
											case NormalAvoid:
												if (PlayerData.m_AvoidHaveFlg[LongAvoid])m_player.NowAvoidType = LongAvoid;
												else if (PlayerData.m_AvoidHaveFlg[OverAvoid])m_player.NowAvoidType = OverAvoid;
												m_player.m_bAvoidChangeKey = true;
												break;
											case LongAvoid:
												if (PlayerData.m_AvoidHaveFlg[OverAvoid])m_player.NowAvoidType = OverAvoid;
												else if (PlayerData.m_AvoidHaveFlg[NormalAvoid])m_player.NowAvoidType = NormalAvoid;
												m_player.m_bAvoidChangeKey = true;
												break;
											case OverAvoid:
												if (PlayerData.m_AvoidHaveFlg[NormalAvoid])m_player.NowAvoidType = NormalAvoid;
												else if (PlayerData.m_AvoidHaveFlg[LongAvoid]) m_player.NowAvoidType = LongAvoid;
												m_player.m_bAvoidChangeKey = true;
												break;
											}
										}
									}
									else {
										m_player.m_bAvoidChangeKey = false;
									}
								}

								if (!m_bThunDirectDw) {
									if (GetAsyncKeyState('W') & 0x8000) m_bThunDirectUp = true;
									else m_bThunDirectUp = false;
								}

								if (!m_bThunDirectUp) {
									if (GetAsyncKeyState('S') & 0x8000) m_bThunDirectDw = true;
									else m_bThunDirectDw = false;
								}

								if (!m_bThunDirectLe) {
									if (GetAsyncKeyState('D') & 0x8000) m_bThunDirectRi = true;
									else m_bThunDirectRi = false;
								}

								if (!m_bThunDirectRi) {
									if (GetAsyncKeyState('A') & 0x8000) m_bThunDirectLe = true;
									else m_bThunDirectLe = false;
								}

								/*if (GetAsyncKeyState('G') & 0x8000) {
									if (!m_player.m_DebugKey) {
										if (m_player.NowAvoidType != Debug) m_player.NowAvoidType = Debug;
										else m_player.NowAvoidType = Nor;
										m_player.m_DebugKey = true;
									}
								}
								else {
									m_player.m_DebugKey = false;
								}*/

							}





							//if (!GetAsyncKeyState('D') & 0x8000 && !GetAsyncKeyState('A') & 0x8000) m_player.m_isRun = false;

							static bool JumpKeyFlg;
							if (GetAsyncKeyState(VK_SPACE) & 0x8000 || XInputManager::GetInstance().IsYPressed_Y()) {
								if (!JumpKeyFlg) {
									JumpKeyFlg = true;
									if (!m_player.m_isJump) {
										m_player.m_move.y += JumpPow;
										m_player.m_isJump = true;
									}
									else {
										if (!m_player.m_DoubleJumpFlg) {
											JumpAni.m_bOne = false;
											m_player.m_move.y = 0;
											m_player.m_move.y += JumpPow;
											m_player.m_DoubleJumpFlg = true;
										}
									}
								}
							}
							else {
								JumpKeyFlg = false;
							}

							if (!m_player.m_FuseBlows) {
								if (!EnterFlag) {
									if (m_player.NowAvoidType != NoAvoid) {
										if (GetAsyncKeyState(VK_SHIFT) & 0x8000 || XInputManager::GetInstance().IsRTriggerPressed_RTrigger() || GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
											if (!m_player.m_AvoidKey) {
												if (!m_Over.m_bAvoidCharge) {
													if (!m_player.m_isAvoid) {
														m_player.m_AvoidKey = true;
														switch (m_player.NowAvoidType) {
														case NormalAvoid:
															m_player.m_isAvoid = true;
															m_Nor.m_Flg = true;
															break;
														case LongAvoid:
															m_player.m_isAvoid = true;
															m_Long.m_Flg = true;
															break;
														case OverAvoid:
															m_Over.m_bAvoidCharge = true;
															LightningCharge.m_pos = m_player.m_pos;
															break;
														case Debug:
															m_player.m_isAvoid = true;
															break;
														default:
															break;
														}
													}
												}
											}
										}
										else {
											m_player.m_AvoidKey = false;
										}
									}
								}
							}
						}


					}
					else {
						m_Over.m_bAvoidCharge = false;
						m_Over.m_avoidChargeCnt = 0;
						LightningChargeAni.m_TexNum = 0;
						LightningChargeAni.m_bOne = false;
					}
				}
			}
			else {
				if (!m_player.m_isHurt) {
					m_player.m_isRun = false;
					m_player.m_isRunEnd = false;
					//ためカウント開始
					if (!LightningChargeAni.m_bOne) {
						LightningChargeAni.m_Num = NeoAnimation(2, 40, LightningChargeAni);
						if (!seInst[AvoidChargeSE]->IsPlay()) {
							seInst[AvoidChargeSE]->Play();
						}
					}
					else {
						m_player.m_isAvoid = true;
						m_Over.m_Flg = true;
						m_Over.m_bAvoidCharge = false;
					}

					C_MapBase* map = m_owner->GetMap();

					LightningCharge.m_scaleMat = Math::Matrix::CreateScale(LightningCharge.m_scale.x, LightningCharge.m_scale.y, 1);
					LightningCharge.m_transMat = Math::Matrix::CreateTranslation(LightningCharge.m_pos.x-map->GetScrollX(), LightningCharge.m_pos.y-map->GetScrollY(), 0);
					LightningCharge.m_mat = LightningCharge.m_scaleMat * LightningCharge.m_transMat;

					/*m_Over.m_avoidChargeCnt++;
					if (m_Over.m_avoidChargeCnt == 2) Light.LiChargeEmit(m_player.m_pos);
					if (m_Over.m_avoidChargeCnt >= 60) {
						m_Over.m_bAvoidCharge = false;
						m_Over.m_avoidChargeCnt = 0;
						m_player.m_isAvoid = true;
						m_Over.m_Flg = true;
					}*/
				}
				else {
					//m_Over.m_avoidChargeCnt = 0;
					if (seInst[AvoidChargeSE]->IsPlay()) seInst[AvoidChargeSE]->Stop();
					LightningChargeAni.m_TexNum = 0;
					LightningChargeAni.m_bOne = false;
					m_Over.m_bAvoidCharge = false;
				}
			}
		}
	}

	AttackAction();

	

	if (!m_player.m_isAvoid) {
		m_player.m_color = { 1,1,1,1 };
	}
	else {
		m_player.m_color = { 0,0,0,0 };
	}

	if (m_bThunDirectX) m_player.m_scale.x = ScaleSize;
	else m_player.m_scale.x = -ScaleSize;
	HurtUpdate();

	
	
	
	Light.LightAction();

	
}

int C_Chara::Animation(int a_changeframe, int a_changemax, s_Animation& a_Anitype)
{
	
	a_Anitype.m_FrameCnt++;
	if (a_Anitype.m_FrameCnt >= a_changeframe) {
		a_Anitype.m_TexNum++;
		a_Anitype.m_FrameCnt = 0;
	}

	if (a_Anitype.m_TexNum >= a_changemax - 1) {
		a_Anitype.m_TexNum = 0;
	}

	return a_Anitype.m_TexNum;

}



int C_Chara::NeoAnimation(int a_changeframe, int a_changemax, s_Animation &a_Anitype)
{

	a_Anitype.m_FrameCnt++;
	if (a_Anitype.m_FrameCnt >= a_changeframe) {
		a_Anitype.m_TexNum++;
		a_Anitype.m_FrameCnt = 0;
	}

	if (a_Anitype.m_TexNum >= a_changemax - 1) {
		a_Anitype.m_bOne = true;
		a_Anitype.m_TexNum = 0;
	}

	if (!a_Anitype.m_bOne) {
		return a_Anitype.m_TexNum;
	}
	else {
		return a_changemax - 1;
	}
}

void C_Chara::LoadTexture()
{
	for (int i = 0; i < IdleMax; i++) {
		sprintf(strp, "Texture/Player/PNG Sequences/Idle/Sword Hero - 1 - Idle%d.png", i + 1);
		m_Texture[Idle][i].Load(strp);
	}

	for (int i = 0; i < RunMax; i++) {
		sprintf(strp, "Texture/Player/PNG Sequences/Run/Sword Hero - 1 - Run%d.png", i + 1);
		m_Texture[Run][i].Load(strp);
	}

	for (int i = 0; i < RunEndMax; i++) {
		sprintf(strp, "Texture/Player/PNG Sequences/Run End/Sword Hero - 1 - Run End%d.png", i + 1);
		m_Texture[RunEnd][i].Load(strp);
	}

	for (int i = 0; i < JumpMax; i++) {
		sprintf(strp, "Texture/Player/PNG Sequences/Jump/Sword Hero - 1 - Jump%d.png", i + 1);
		m_Texture[Jump][i].Load(strp);
	}

	for (int i = 0; i < FallMax; i++) {
		sprintf(strp, "Texture/Player/PNG Sequences/Fall/Sword Hero - 1 - Fall%d.png", i + 1);
		m_Texture[Fall][i].Load(strp);
	}

	for (int i = 0; i < AttackStdMax; i++) {
		sprintf(strp, "Texture/Player/PNG Sequences/Attack Standing/Sword Hero - 1 - Attack_Standing%d.png", i + 1);
		m_Texture[AttackStd][i].Load(strp);
	}

	for (int i = 0; i < AttackAirMax; i++) {
		sprintf(strp, "Texture/Player/PNG Sequences/Attack Air/Sword Hero - 1 - Jump Attack%d.png", i + 1);
		m_Texture[AttackAir][i].Load(strp);
	}

	for (int i = 0; i < HurtMax; i++) {
		sprintf(strp, "Texture/Player/PNG Sequences/Hurt/Sword Hero - 1 - Hurt%d.png", i + 1);
		m_Texture[Hurt][i].Load(strp);
	}

	m_ThunderTexture.Load("Texture/Player/Lightning_Bolt_v1_spritesheet.png");
	Test.Tex.Load("Texture/Player/test.png");
	Danger.m_tex.Load("Texture/Player/Danger.png");
	ItemUsing.m_tex.Load("Texture/Player/16.png");
	ChargeSlash.m_tex.Load("Texture/Player/Blue_Slash_v26_-_Flurry_A_spritesheet.png");
	LightningCharge.m_tex.Load("Texture/Player/Charge_Lightning_v1_B_No Center_spritesheet.png");
	DeathEff.m_tex.Load("Texture/Player/Explosion_Energy_v2_spritesheet.png");

	Light.LoadTexture();
}

void C_Chara::ReleaseTexture()
{
	for (int i = 0; i < IdleMax; i++) m_Texture[Idle][i].Release();
	for (int i = 0; i < RunMax; i++)m_Texture[Run][i].Release();
	for (int i = 0; i < RunEndMax; i++)m_Texture[RunEnd][i].Release();
	for (int i = 0; i < JumpMax; i++)m_Texture[Jump][i].Release();
	for (int i = 0; i < AttackStdMax; i++)m_Texture[AttackStd][i].Release();
	for (int i = 0; i < AttackAirMax; i++)m_Texture[AttackAir][i].Release();
	for (int i = 0; i < FallMax; i++)m_Texture[Fall][i].Release();
	for (int i = 0; i < HurtMax; i++)m_Texture[Hurt][i].Release();

	m_ThunderTexture.Release();
	Test.Tex.Release();
	Danger.m_tex.Release();
	ItemUsing.m_tex.Release();
	ChargeSlash.m_tex.Release();
	LightningCharge.m_tex.Release();
	DeathEff.m_tex.Release();


	Light.ReleaseTexture();

	Light.LightHitRelease();
}

void C_Chara::LoadSE()
{
	//メモリ領域の確保
	for (int i = 0; i < SEMAX; i++) se[i] = std::make_shared<KdSoundEffect>();
	
	//読み込み
	se[RunSE]->Load("Sound/Chara/学校歩く (mp3cut.net).wav");
	se[HurtSE]->Load("Sound/Chara/ダメージ音01.wav");
	se[AttackSE]->Load("Sound/Chara/ES_Short, Dry 01 - Epidemic Sound - 1083-1668.wav");
	se[ChargeSlashSE]->Load("Sound/Chara/ES_Organic, Wind, Classic, Fast - Epidemic Sound - 2773-3728.wav");
	se[SlashRushSE]->Load("Sound/Chara/ES_Short, Dry 01 - Epidemic Sound - 1083-1668.wav");
	se[ChargeAtkSEOne]->Load("Sound/Chara/ES_Organic, Wind, Soft, Short - Epidemic Sound - 4742-5885.wav");
	se[ChargeAtkSETwo]->Load("Sound/Chara/ES_Organic, Wind, Soft, Short - Epidemic Sound - 1517-2574.wav");
	se[ChargeAtkSEThree]->Load("Sound/Chara/ES_Organic, Wind, Soft, Short - Epidemic Sound - 0000-1112.wav");
	se[AttackHitSe]->Load("Sound/Chara/Cut01-1.wav");
	se[LightningSE]->Load("Sound/Chara/Electric_Shock06-1(Short).wav");
	se[HealSE]->Load("Sound/Chara/heal01.wav");
	se[FuseBlowsSE]->Load("Sound/Chara/Electric_Shock04-1(Mid) (mp3cut.net).wav");
	se[AvoidChargeSE]->Load("Sound/Chara/Electric_Shock02-1(Short).wav");
	se[AvoidChangeSE]->Load("Sound/Chara/unplug_USB2.wav");


	for (int i = 0; i < SEMAX; i++) {
		//スピーカーのメモリ確保&音データを渡す
		seInst[i] = se[i]->CreateInstance(false);
		//ボリューム調整
		 seInst[i]->SetVolume(vol);
	}

	for (int i = 0; i < 10; i++) {
		hitseInst[i] = se[AttackHitSe]->CreateInstance(false);
		SlashRushInst[i] = se[SlashRushSE]->CreateInstance(false);
		hitseInst[i]->SetVolume(vol);
		SlashRushInst[i]->SetVolume(vol);
	}

}

float C_Chara::GetAngle(Math::Vector2 a_srcPos, Math::Vector2 a_destPos)
{
	float deg;
	deg = atan2(a_destPos.y - a_srcPos.y, a_destPos.x - a_srcPos.x) * 180 / 3.14;
	if (deg < 0) {
		deg += 360;
	}
	return deg+90;
}

void C_Chara::ImGuiUpdate()
{
	/*ImGui::Checkbox(u8"HPLevel1", &m_player.m_HPUP[0]);
	ImGui::Checkbox(u8"HPLevel2", &m_player.m_HPUP[1]);
	ImGui::Checkbox(u8"HPLevel3", &m_player.m_HPUP[2]);

	ImGui::Checkbox(u8"MPLevel1", &m_player.m_MPUP[0]);
	ImGui::Checkbox(u8"MPLevel2", &m_player.m_MPUP[1]);
	ImGui::Checkbox(u8"MPLevel3", &m_player.m_MPUP[2]);

	ImGui::Checkbox(u8"AtkLevel1", &m_player.m_AtkUp[0]);
	ImGui::Checkbox(u8"AtkLevel2", &m_player.m_AtkUp[1]);
	ImGui::Checkbox(u8"AtkLevel3", &m_player.m_AtkUp[2]);*/

	//ImGui::Checkbox(u8"死亡フラグ", &m_player.m_isAlive);

	//ImGui::Checkbox(u8"落下ワンフラグ", &FallAni.m_bOne); 
	//ImGui::Text(u8"落下画像:%d枚目", FallAni.m_Num);
	//ImGui::Checkbox(u8"落下フラグ", &m_player.m_IsFall);


	//ImGui::Checkbox(u8"ジャンプフラグ", &m_player.m_isJump);
	//ImGui::Checkbox(u8"ジャンプbフラグ", &m_player.m_DoubleJumpFlg);
	/*
	ImGui::Checkbox(u8"ダッシュエンドフラグ", &RunEndAni.m_bOne);
	ImGui::Checkbox(u8"onejump", &JumpAni.m_bOne);
	*/
	/*ImGui::Text(u8"posX/posY:%.0f/%.0f",m_player.m_pos.x,m_player.m_pos.y);
	*/
	//ImGui::Checkbox(u8"アタックフラグ", &m_player.m_isAttackStd);
	//ImGui::Checkbox(u8"アタックワン", &AttackStdAni.m_bOne);
	//ImGui::Checkbox(u8"ため攻撃", &m_player.m_AttackStdCha);
	//ImGui::Checkbox(u8"ため攻撃フラグ", &m_player.m_AtkKeyFlg);
	//ImGui::Checkbox(u8"攻撃フラグ", &m_player.m_bAttackKey);
	//ImGui::Checkbox(u8"空中アタックフラグ", &m_player.m_isAttackAir);
	//ImGui::Checkbox(u8"空中アタックワン", &AttackAirAni.m_bOne);
	//ImGui::Text("OneAni.m_fTexNum:%d", OneAni.m_fTexNum);
	//ImGui::Text(u8"チャージ攻撃Cnt:%d", m_player.AttackChargeCnt/40);
	//ImGui::Text("AtkFirstPos: %.2f, %.2f", m_player.m_AtkFirstPos.x, m_player.m_AtkFirstPos.y);
	//ImGui::Text("AtkEndPos: %.2f, %.2f", m_player.m_AtkEndPos.x,m_player.m_AtkEndPos.y);
	//ImGui::Text("AtkHalf: %.2f, %.2f", Test.m_half.x,Test.m_half.y);
	//ImGui::Text("AtkPos: %.2f, %.2f", Test.m_pos.x,Test.m_pos.y);
	//ImGui::Checkbox(u8"ため攻撃判定スタート", &m_player.m_ChargeAtkStart);
	//ImGui::Text(u8"攻撃画像:%d枚目", AttackStdAni.m_Num);
	//ImGui::Text(u8"攻撃画像フレーム:%dフレーム", AttackStdAni.m_FrameCnt);

	//ImGui::Checkbox(u8"回避フラグ", &m_player.m_isAvoid);
	//ImGui::Checkbox(u8"回避ワン", &NorThunAni.m_bOne);
	//ImGui::Checkbox(u8"長距離回避取得", &PlayerData.m_AvoidHaveFlg[Long]);
	//ImGui::Checkbox(u8"高電圧回避取得", &PlayerData.m_AvoidHaveFlg[Over]);
	//ImGui::Checkbox(u8"回避キー", &m_player.m_AvoidKey);
	//ImGui::Checkbox(u8"回避チェンジキー", &m_player.m_bAvoidChangeKey);
	//ImGui::Checkbox(u8"通常回避フラグ", &m_Nor.m_Flg);
	//ImGui::Checkbox(u8"長距離回避フラグ", &m_Long.m_Flg);
	//ImGui::Checkbox(u8"高電圧回避フラグ", &m_Over.m_Flg);
	//ImGui::Checkbox(u8"高電圧回避チャージフラグ", &m_Over.m_bAvoidCharge);
	/*ImGui::Text("LiHitcnt:%d", Light.GetLiHitcnt());
	ImGui::Checkbox(u8"ヒューズ切断フラグ", &m_player.m_FuseBlows);*/

	ImGui::Text(u8"HP:%d/%d", m_player.m_NowHp/10,m_player.m_MaxHp/10);
	ImGui::Text(u8"MP:%d/%d", m_player.m_NowMp/10,m_player.m_MaxMp/10);
	if (ImGui::Button(u8"プレイヤーダメージ700"))SetEnemyDamage(1000);
	if (ImGui::Button(u8"プレイヤーダメージ300"))SetEnemyDamage(300);
	/*ImGui::Text(u8"thuderangle:%.2f", ThuderAngle);
	*/
	//ImGui::Checkbox(u8"DirectX", &m_bThunDirectX);
	/*
	ImGui::Checkbox(u8"DirectRi", &m_bThunDirectRi);
	ImGui::Checkbox(u8"DirectLe", &m_bThunDirectLe);
	ImGui::Checkbox(u8"DirectUp", &m_bThunDirectUp);
	ImGui::Checkbox(u8"DirectDw", &m_bThunDirectDw);*/
	
	//ImGui::Checkbox(u8"被弾フラグ", &m_player.m_isHurt);
	
	//ImGui::Checkbox(u8"被弾ワン", &HurtAni.m_bOne);
	//ImGui::Checkbox(u8"無敵フラグ", &m_player.m_isInvincible);

	/*ImGui::Text("playermovey:%.2f", m_player.m_move.y);
	ImGui::Checkbox(u8"onejump", &JumpAni.m_bOne);
	ImGui::Checkbox(u8"onefall", &FallAni.m_bOne);*/
	//ImGui::Text(u8"体力%d", m_owner->GetEnemyMgr()->GetRobot()[0]->GetHp());

}

void C_Chara::SetEnemyDamage(int a_damage)
{
	if (m_player.m_isAlive) {
		if (!m_player.m_isInvincible) {
			if (!m_player.m_isAvoid) {
				m_owner->SetNumber(a_damage / 10, m_player.m_pos, false);
				m_owner->GetEffectManager()->SetCharaHit_E(m_player.m_pos.x, m_player.m_pos.y, true);
				m_player.m_NowHp -= a_damage;
				m_player.m_isHurt = true;
			}
		}
	}
}

// マップとプレイヤーの処理
void C_Chara::MapHitX(Math::Vector2 Pos, float moveX)
{
	m_player.m_pos = Pos;
	m_player.m_move.x = moveX;
}

void C_Chara::SampleMapHitX(float x, float movex)
{
	m_player.m_pos.x = x;
	m_player.m_move.x = movex;
}

void C_Chara::MapHitY(Math::Vector2 Pos, float moveY, bool Jump, bool a_bOne, bool a_Hurt)
{
	m_player.m_pos = Pos;
	m_player.m_move.y = moveY;
	m_player.m_isJump = Jump;
	m_player.m_IsFall = Jump;
	if(!Jump)m_player.m_DoubleJumpFlg = Jump;
	JumpAni.m_bOne = a_bOne;
	if(m_player.m_isHurt) m_player.m_isHurt = a_Hurt;
}



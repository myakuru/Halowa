// EffectManager.h
#pragma once
#include "EffectBase.h"
#include "SmokeEffect.h"
#include "ExplosionEffect.h"
#include"BlockBurst.h"
#include"Charge.h"
#include"BurstFlog.h"
#include"CharaHit_E.h"
#include"Point_E.h"
#include"TechSquare.h"
#include"EmberEffect.h"
#include"BossDeathEffect.h"
#include"WarpEffect.h"
#include"bakuhatu.h"
#include "Charge_Darkness.h"
#include"Glass_Shatter.h"
#include"Impact_Darkness.h"
#include"Impact_Lightning.h"
#include"Healing.h"

class EffectManager {
public:
    void Init(Scene* owner);
    void Update();
    void Draw();
    void Release();

    void SetSmokeEffect(float posX, float posY, bool isActive);
    void SetExplosionEffect(float posX, float posY, bool isActive);
	void SetBlockBurstEffect(float posX, float posY, bool isActive);
	void SetChargeEffect(float posX, float posY, bool isActive);
	void SetBurstFlogEffect(float posX, float posY, bool isActive);
	void SetCharaHit_E(float posX, float posY, bool isActive);
	void SetPointEffect(float posX, float posY,bool isActive);
	void SetTechSquareEffect(float posX, float posY, bool isActive);
	void SetEmberEffect(float posX, float posY, bool isActive);
	void SetBossDeathEffect(float posX, float posY, bool isActive);
	void SetWarpEffect(float posX, float posY, bool isActive);
	void SetBakuhatuEffect(float posX, float posY, bool isActive);
	void SetCharge_DarknessEffect(float posX, float posY, bool isActive);
	void SetGlass_ShatterEffect(float posX, float posY, bool isActive);
	void SetImpact_DarknessEffect(float posX, float posY, bool isActive);
	void SetImpact_LightningEffect(float posX, float posY, bool isActive);
	void SetHealingEffect(float posX, float posY, bool isActive);
    bool IsSmokeEffectActive();

	void InitPointEffect() {
		m_pointEffect.Init();
	}
	void EffectClear();

private:
    SmokeEffect m_smokeEffect;
    ExplosionEffect m_explosionEffect;
	BloakBurstEffect m_blockBurst;
	ChargeEffect m_charge;
	BurstFlogEffect m_burstFlog;
	C_CharaHit_E m_charaHit_E;
	PointEffect m_pointEffect;
	TechSquareEffect m_techsqEffect;
	EmberEffect m_emberEffect;
	BossDeathEffect m_bossDeathEffect;
	WarpEffect m_warpEffect;
	bakuhatuEffect m_bakuhatuEffect;
	Charge_DarknessEffect m_charge_DarknessEffect;
	Glass_ShatterEffect m_glass_ShatterEffect;
	Impact_DarknessEffect m_impact_DarknessEffect;
	Impact_LightningEffect m_impact_LightningEffect;
	HealingEffect m_healingEffect;
    Scene* m_owner;

public:
	EmberEffect* GetEmberEffect() { return &m_emberEffect; }
	TechSquareEffect* GetTechSquareEffect() { return &m_techsqEffect; }
};
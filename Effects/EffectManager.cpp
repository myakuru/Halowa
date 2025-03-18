// Src/Application/Effects/EffectManager.cpp
#include "EffectManager.h"
#include "../Scene.h"
			
void EffectManager::Init(Scene* owner) {
    m_owner = owner;
    m_smokeEffect.SetOwner(owner);
    m_explosionEffect.SetOwner(owner);
	m_blockBurst.SetOwner(owner);
	m_charge.SetOwner(owner);
	m_burstFlog.SetOwner(owner);
	m_charaHit_E.SetOwner(owner);
	m_pointEffect.SetOwner(owner);
	m_techsqEffect.SetOwner(owner);
	m_emberEffect.SetOwner(owner);
	m_bossDeathEffect.SetOwner(owner);
	m_warpEffect.SetOwner(owner);
	m_bakuhatuEffect.SetOwner(owner);
	m_charge_DarknessEffect.SetOwner(owner);
	m_glass_ShatterEffect.SetOwner(owner);
	m_impact_DarknessEffect.SetOwner(owner);
	m_impact_LightningEffect.SetOwner(owner);
	m_healingEffect.SetOwner(owner);

    m_smokeEffect.LoadTexture();
    m_explosionEffect.LoadTexture();
	m_blockBurst.LoadTexture();
	m_charge.LoadTexture();
	m_burstFlog.LoadTexture();
	m_charaHit_E.LoadTexture();
	m_pointEffect.LoadTexture();
	m_techsqEffect.LoadTexture();
	m_emberEffect.LoadTexture();
	m_bossDeathEffect.LoadTexture();
	m_warpEffect.LoadTexture();
	m_bakuhatuEffect.LoadTexture();
	m_charge_DarknessEffect.LoadTexture();
	m_glass_ShatterEffect.LoadTexture();
	m_impact_DarknessEffect.LoadTexture();
	m_impact_LightningEffect.LoadTexture();
	m_healingEffect.LoadTexture();
}

void EffectManager::Update() {
    m_smokeEffect.Update();
    m_explosionEffect.Update();
	m_blockBurst.Update();
	m_charge.Update();
	m_burstFlog.Update();
	m_charaHit_E.Update();
	m_pointEffect.Update();
	m_techsqEffect.Update();
	m_emberEffect.Update();
	m_bossDeathEffect.Update();
	m_warpEffect.Update();
	m_bakuhatuEffect.Update();
	m_charge_DarknessEffect.Update();
	m_glass_ShatterEffect.Update();
	m_impact_DarknessEffect.Update();
	m_impact_LightningEffect.Update();
	m_healingEffect.Update();
}

void EffectManager::Draw() {
    m_smokeEffect.Draw();
    m_explosionEffect.Draw();
	m_blockBurst.Draw();
	m_charge.Draw();
	m_burstFlog.Draw();
	m_charaHit_E.Draw();
	m_pointEffect.Draw();
	m_techsqEffect.Draw();
	m_emberEffect.Draw();
	m_bossDeathEffect.Draw();
	m_warpEffect.Draw();
	m_bakuhatuEffect.Draw();
	m_charge_DarknessEffect.Draw();
	m_glass_ShatterEffect.Draw();
	m_impact_DarknessEffect.Draw();
	m_impact_LightningEffect.Draw();
	m_healingEffect.Draw();
}

void EffectManager::Release() {
    m_smokeEffect.Release();
    m_explosionEffect.Release();
	m_blockBurst.Release();
	m_charge.Release();	
	m_burstFlog.Release();
	m_charaHit_E.Release();
	m_pointEffect.Release();
	m_techsqEffect.Release();
	m_emberEffect.Release();
	m_bossDeathEffect.Release();
	m_warpEffect.Release();
	m_bakuhatuEffect.Release();
	m_charge_DarknessEffect.Release();
	m_glass_ShatterEffect.Release();
	m_impact_DarknessEffect.Release();
	m_impact_LightningEffect.Release();
	m_healingEffect.Release();
}

void EffectManager::SetSmokeEffect(float posX, float posY, bool isActive) {
    m_smokeEffect.SetEffect(posX, posY, isActive);
}

void EffectManager::SetExplosionEffect(float posX, float posY, bool isActive) {
    m_explosionEffect.SetEffect(posX, posY, isActive);
}

void EffectManager::SetBlockBurstEffect(float posX, float posY, bool isActive)
{ 
	m_blockBurst.SetEffect(posX, posY, isActive);
}

void EffectManager::SetChargeEffect(float posX, float posY, bool isActive)
{
	m_charge.SetEffect(posX, posY, isActive);
}

void EffectManager::SetBurstFlogEffect(float posX, float posY, bool isActive)
{
	m_burstFlog.SetEffect(posX, posY, isActive);
}

void EffectManager::SetCharaHit_E(float posX, float posY, bool isActive)
{
	m_charaHit_E.SetEffect(posX, posY, isActive);
}

void EffectManager::SetPointEffect(float posX, float posY,bool isActive)
{
	m_pointEffect.SetEffect(posX, posY,isActive);
}

bool EffectManager::IsSmokeEffectActive() {
    return m_smokeEffect.GetActive();
}

void EffectManager::EffectClear()
{
	m_techsqEffect.Init();
	m_emberEffect.Init();
}

void EffectManager::SetTechSquareEffect(float posX, float posY, bool isActive)
{
	m_techsqEffect.SetEffect(posX, posY, isActive);
}

void EffectManager::SetEmberEffect(float posX, float posY, bool isActive)
{
	m_emberEffect.SetEffect(posX, posY, isActive);
}

void EffectManager::SetBossDeathEffect(float posX, float posY, bool isActive)
{
	m_bossDeathEffect.SetEffect(posX, posY, isActive);
}

void EffectManager::SetWarpEffect(float posX, float posY, bool isActive)
{
	m_warpEffect.SetEffect(posX, posY, isActive);
}

void EffectManager::SetBakuhatuEffect(float posX, float posY, bool isActive)
{
	m_bakuhatuEffect.SetEffect(posX, posY, isActive);
}

void EffectManager::SetCharge_DarknessEffect(float posX, float posY, bool isActive)
{
	m_charge_DarknessEffect.SetEffect(posX, posY, isActive);
}

void EffectManager::SetGlass_ShatterEffect(float posX, float posY, bool isActive)
{
	m_glass_ShatterEffect.SetEffect(posX, posY, isActive);
}

void EffectManager::SetImpact_DarknessEffect(float posX, float posY, bool isActive)
{
	m_impact_DarknessEffect.SetEffect(posX, posY, isActive);
}

void EffectManager::SetImpact_LightningEffect(float posX, float posY, bool isActive)
{
	m_impact_LightningEffect.SetEffect(posX, posY, isActive);
}

void EffectManager::SetHealingEffect(float posX, float posY, bool isActive)
{
	m_healingEffect.SetEffect(posX, posY, isActive);
}

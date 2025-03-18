// ExplosionEffect.h
#pragma once
#include "EffectBase.h"

class C_CharaHit_E : public EffectBase {
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void LoadTexture() override;
    void Release() override;
    void SetEffect(float posX, float posY, bool isActive) override;

private:
    const int spriteSheetColumns = 4;
    const int spriteSheetRows = 4;
    const int totalFrames = spriteSheetColumns * spriteSheetRows;
};

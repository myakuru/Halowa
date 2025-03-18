// SmokeEffect.h
#pragma once
#include "EffectBase.h"

class ChargeEffect : public EffectBase {
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void LoadTexture() override;
    void Release() override;
    void SetEffect(float posX, float posY, bool isActive) override;

    bool IsEffectActive() const;

private:
    const int spriteSheetColumns = 4;
    const int spriteSheetRows = 8;
    const int totalFrames = spriteSheetColumns * spriteSheetRows;
    KdTexture texture2;
    KdTexture texture3;
};

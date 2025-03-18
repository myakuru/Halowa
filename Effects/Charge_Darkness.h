#pragma once
#include "EffectBase.h"
class Charge_DarknessEffect : public EffectBase
{
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void LoadTexture() override;
    void Release() override;
    void SetEffect(float posX, float posY, bool isActive) override;

private:
    const int spriteSheetColumns = 8;
    const int spriteSheetRows = 8;
    const int totalFrames = spriteSheetColumns * spriteSheetRows;
};

#include "EmberEffect.h"
#include"../Scene.h"

void EmberEffect::Init()
{
	effects.clear();
}

void EmberEffect::Update()
{
    for (auto& effect : effects) {
        if (!effect.isActive) continue;

        effect.animation.elapsedFrames++;
        if (effect.animation.elapsedFrames >= effect.animation.frameTime) {
            effect.animation.currentFrame++;
            if (effect.animation.currentFrame >= totalFrames) {
                effect.animation.currentFrame = 0;
                //effect.isActive = false;
                //continue;
            }
            effect.animation.elapsedFrames = 0;
        }

        effect.animation.currentColumn = effect.animation.currentFrame % spriteSheetRows;
        effect.animation.currentRow = effect.animation.currentFrame / spriteSheetRows;

        C_MapBase* map = owner->GetMap();

        effect.transMat = DirectX::SimpleMath::Matrix::CreateTranslation(effect.pos.x, effect.pos.y, 0);
        effect.scaleMat = DirectX::SimpleMath::Matrix::CreateScale(1.0f, 1.0f, 0.0f);
        effect.effectMatrix = effect.scaleMat * effect.transMat;
    }

    effects.erase(std::remove_if(effects.begin(), effects.end(), [](const Effect& e) { return !e.isActive; }), effects.end());
}

void EmberEffect::Draw()
{
    for (const auto& effect : effects) {
        if (!effect.isActive) continue;

        SHADER.m_spriteShader.SetMatrix(effect.effectMatrix);
        //DirectX::SimpleMath::Rectangle srcRect = { effect.animation.currentColumn * 256, effect.animation.currentRow * 256, 256, 256 };
        DirectX::SimpleMath::Rectangle srcRect = { effect.animation.currentColumn * 512, effect.animation.currentRow * 512, 512, 512 };
        DirectX::SimpleMath::Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
        SHADER.m_spriteShader.DrawTex(&texture, 0, 0, &srcRect, &color);
    }
}

void EmberEffect::LoadTexture()
{
    texture.Load("Texture/EffectTexture/Aura_Fire_v3_A_spritesheet.png");
}

void EmberEffect::Release()
{
    effects.clear();
    texture.Release();
}

void EmberEffect::SetEffect(float posX, float posY, bool isActive)
{
    Effect newEffect;
    newEffect.pos.x = posX;
    newEffect.pos.y = posY;
    newEffect.animation.currentFrame = 0; // フレームをリセット
    newEffect.animation.frameTime = 2;
    newEffect.animation.elapsedFrames = 0;
    newEffect.isActive = isActive;
    effects.push_back(newEffect);
}

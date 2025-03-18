#include "Glass_Shatter.h"
#include "../Scene.h"

void Glass_ShatterEffect::Init()
{
	effects.clear();
}

void Glass_ShatterEffect::Update()
{
    for (auto& effect : effects) {
        if (!effect.isActive) continue;

        effect.animation.elapsedFrames++;
        if (effect.animation.elapsedFrames >= effect.animation.frameTime) {
            effect.animation.currentFrame++;
            if (effect.animation.currentFrame >= totalFrames) {
                effect.animation.currentFrame = 0;
                effect.isActive = false; // エフェクトを非アクティブにする
                effect.isEffectPlayed = true; // エフェクトが再生されたことを記録
                continue;
            }
            effect.animation.elapsedFrames = 0;
        }

        effect.animation.currentColumn = effect.animation.currentFrame % spriteSheetRows;
        effect.animation.currentRow = effect.animation.currentFrame / spriteSheetRows;

        C_MapBase* map = owner->GetMap();

        effect.transMat = DirectX::SimpleMath::Matrix::CreateTranslation(effect.pos.x - map->GetScrollX(), effect.pos.y - map->GetScrollY(), 0);
        effect.scaleMat = DirectX::SimpleMath::Matrix::CreateScale(1.0f, 1.0f, 0.0f);
        effect.effectMatrix = effect.scaleMat * effect.transMat;
    }

    effects.erase(std::remove_if(effects.begin(), effects.end(), [](const Effect& e) { return e.isEffectPlayed; }), effects.end());
}

void Glass_ShatterEffect::Draw()
{
    for (const auto& effect : effects) {
        if (!effect.isActive) continue;

        SHADER.m_spriteShader.SetMatrix(effect.effectMatrix);
        DirectX::SimpleMath::Rectangle srcRect = { effect.animation.currentColumn * 512, effect.animation.currentRow * 512, 512, 512 };
        DirectX::SimpleMath::Color color = { 1.0f, 1.0f, 1.0f, 0.6f };
        SHADER.m_spriteShader.DrawTex(&texture, 0, 0, &srcRect, &color);
    }
}

void Glass_ShatterEffect::LoadTexture()
{
    texture.Load("Texture/EffectTexture/Glass_Shatter_V1_A_spritesheet.png");
}

void Glass_ShatterEffect::Release()
{
    effects.clear();
    texture.Release();
}

void Glass_ShatterEffect::SetEffect(float posX, float posY, bool isActive)
{
    // 同じ位置に既存のエフェクトがないか確認
    for (const auto& effect : effects) {
        if (effect.pos.x == posX && effect.pos.y == posY && effect.isActive) {
            return; // 同じ位置に既存のエフェクトがある場合、新しいエフェクトを追加しない
        }
    }

    Effect newEffect;
    newEffect.pos.x = posX;
    newEffect.pos.y = posY;
    newEffect.animation.currentFrame = 0; // フレームをリセット
    newEffect.animation.frameTime = 2;
    newEffect.animation.elapsedFrames = 0;
    newEffect.isActive = isActive;
    newEffect.isEffectPlayed = false; // エフェクトが再生されていないことを記録
    effects.push_back(newEffect);
}

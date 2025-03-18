#include"BossDeathEffect.h"
#include"../Scene.h"

void BossDeathEffect::Init()
{
	effects.clear();
}

void BossDeathEffect::Update() {
    for (auto& effect : effects) {
        if (!effect.isActive) continue;

        effect.animation.elapsedFrames++;
        if (effect.animation.elapsedFrames >= effect.animation.frameTime) {
            effect.animation.currentFrame++;
            if (effect.animation.currentFrame >= totalFrames) {
                effect.isActive = false;
                continue;
            }
            effect.animation.elapsedFrames = 0;
        }

        effect.animation.currentColumn = effect.animation.currentFrame % spriteSheetRows;
        effect.animation.currentRow = effect.animation.currentFrame / spriteSheetRows;

        C_MapBase* map = owner->GetMap();

        effect.transMat = DirectX::SimpleMath::Matrix::CreateTranslation(effect.pos.x - map->GetScrollX(), effect.pos.y - map->GetScrollY(), 0);
        effect.scaleMat = DirectX::SimpleMath::Matrix::CreateScale(1.5f, 1.5f, 0.0f);
        effect.effectMatrix = effect.scaleMat * effect.transMat;
    }

    effects.erase(std::remove_if(effects.begin(), effects.end(), [](const Effect& e) { return !e.isActive; }), effects.end());
}

void BossDeathEffect::Draw() {
    for (const auto& effect : effects) {
        if (!effect.isActive) continue;

        SHADER.m_spriteShader.SetMatrix(effect.effectMatrix);
        DirectX::SimpleMath::Rectangle srcRect = { effect.animation.currentColumn * 512, effect.animation.currentRow * 512, 512, 512 };
        DirectX::SimpleMath::Color color = { 1.0f, 1.0f, 1.0f, 0.8f };
        SHADER.m_spriteShader.DrawTex(&texture, 0, 0, &srcRect, &color);
        SHADER.m_spriteShader.DrawTex(&texture2, 0, 0, &srcRect, &color);

    }
}

void BossDeathEffect::LoadTexture()
{
    texture.Load("Texture/EffectTexture/Explosion_Bomb_V5_spritesheet.png");
}

void BossDeathEffect::Release()
{
    effects.clear();
    texture.Release();
}

void BossDeathEffect::SetEffect(float posX, float posY, bool isActive)
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

#include "Point_E.h"
#include"../Scene.h"

void PointEffect::Init()
{
	effects.clear();
}

void PointEffect::Update() {
    for (auto& effect : effects) {
        if (!effect.isActive) return;

        effect.animation.elapsedFrames++;
        if (effect.animation.elapsedFrames >= effect.animation.frameTime) {
            effect.animation.currentFrame++;
            if (effect.animation.currentFrame >= totalFrames) {
                //effect.isActive = false;
				effect.animation.currentFrame = 0;
            }
            effect.animation.elapsedFrames = 0;
        }

        effect.animation.currentColumn = effect.animation.currentFrame % spriteSheetRows;
        effect.animation.currentRow = effect.animation.currentFrame / spriteSheetRows;

        C_MapBase* map = owner->GetMap();

        effect.transMat = Math::Matrix::CreateTranslation(effect.pos.x, effect.pos.y, 0);
        effect.scaleMat = Math::Matrix::CreateScale(0.2f, 0.2f, 0.0f);
		effect.rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(-90));
        effect.effectMatrix = effect.scaleMat * effect.rotationMat * effect.transMat;
    }

    effects.erase(std::remove_if(effects.begin(), effects.end(), [](const Effect& e) { return !e.isActive; }), effects.end());
}

void PointEffect::Draw() {
    for (const auto& effect : effects) {
        if (!effect.isActive) return;

        SHADER.m_spriteShader.SetMatrix(effect.effectMatrix);
        DirectX::SimpleMath::Rectangle srcRect = { effect.animation.currentColumn * 512, effect.animation.currentRow * 512, 512, 512 };
        DirectX::SimpleMath::Color color = { 1.0f, 1.0f, 1.0f, 0.7f };
        SHADER.m_spriteShader.DrawTex(&texture, 0, 0, &srcRect, &color);
    }
}

void PointEffect::LoadTexture()
{
    texture.Load("Texture/EffectTexture/Projectile_Darkness_Ball_Lv3_spritesheet.png");
}

void PointEffect::Release()
{
    effects.clear();
    texture.Release();
}

void PointEffect::SetEffect(float posX, float posY,bool isActive)
{
    Effect newEffect;
    newEffect.pos.x = posX;
    newEffect.pos.y = posY;
    newEffect.animation.currentFrame = 0; // フレームをリセット
    newEffect.animation.frameTime = 2;
    newEffect.animation.elapsedFrames = 0;
    newEffect.isActive = isActive;
    effects.push_back(newEffect);
    //もしisActiveがfalseだったら
    if(!isActive){ effects.clear(); }
}

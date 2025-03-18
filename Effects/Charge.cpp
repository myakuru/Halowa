#include "Charge.h"
#include "../Scene.h"

void ChargeEffect::Init() {
    effects.clear();
}

void ChargeEffect::Update() {
    // Eキーが押されたらエフェクトを発生させる
    // 長押ししたらループ再生
    //if (GetAsyncKeyState('E') & 0x8000) {
    //    C_Chara* player = owner->GetChara();

    //    // エフェクトがアクティブでない場合にのみ新しいエフェクトを発生させる
    //    if (!IsEffectActive()) {
    //        SetEffect(player->GetPos().x, player->GetPos().y, true);
    //    }
    //}
    //else {
    //    // Eキーが離されたらエフェクトを非アクティブにする
    //    for (auto& effect : effects) {
    //        effect.isActive = false;
    //    }
    //}

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
        effect.scaleMat = DirectX::SimpleMath::Matrix::CreateScale(2.0f, 2.0f, 0.0f);
        effect.effectMatrix = effect.scaleMat * effect.transMat;
    }

    effects.erase(std::remove_if(effects.begin(), effects.end(), [](const Effect& e) { return !e.isActive; }), effects.end());
}

void ChargeEffect::Draw() {

	D3D.SetBlendState(BlendMode::Add);

    for (const auto& effect : effects) {
        if (!effect.isActive) continue;

        SHADER.m_spriteShader.SetMatrix(effect.effectMatrix);
        DirectX::SimpleMath::Rectangle srcRect = { effect.animation.currentColumn * 512, effect.animation.currentRow * 512, 512, 512 };
        DirectX::SimpleMath::Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
        SHADER.m_spriteShader.DrawTex(&texture, 0, 0, &srcRect, &color);
        SHADER.m_spriteShader.DrawTex(&texture2, 0, 0, &srcRect, &color);
    }

	D3D.SetBlendState(BlendMode::Alpha);
}

void ChargeEffect::LoadTexture() {
    texture.Load("Texture/EffectTexture/Charge_Energy_v1_B_Charge Only_spritesheet.png");
	texture2.Load("Texture/EffectTexture/Charge_Energy_v1_B_Charge Only_spritesheet.png");
}

void ChargeEffect::Release() {
    effects.clear();
    texture.Release();
}

void ChargeEffect::SetEffect(float posX, float posY, bool isActive) {
    Effect newEffect;
    newEffect.pos.x = posX;
    newEffect.pos.y = posY;
    newEffect.animation.currentFrame = 0; // フレームをリセット
    newEffect.animation.frameTime = 1;
    newEffect.animation.elapsedFrames = 0;
    newEffect.isActive = isActive;
    effects.push_back(newEffect);
}

bool ChargeEffect::IsEffectActive() const {
    for (const auto& effect : effects) {
        if (effect.isActive) {
            return true;
        }
    }
    return false;
}


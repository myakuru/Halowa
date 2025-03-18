// EffectBase.h
#pragma once
#include <vector>

class Scene;

class EffectBase {
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void LoadTexture() = 0;
	virtual void Release() = 0;
    virtual void SetEffect(float posX, float posY, bool isActive) = 0;

    void SetOwner(Scene* scene) { owner = scene; }

protected:
    struct Animation {
        int currentFrame;
        int frameTime;
        int elapsedFrames;
        int currentRow;
        int currentColumn;
    };

    struct Effect {
        DirectX::SimpleMath::Vector2 pos;
        DirectX::SimpleMath::Matrix transMat;
        DirectX::SimpleMath::Matrix scaleMat;
        DirectX::SimpleMath::Matrix effectMatrix;
		DirectX::SimpleMath::Matrix rotationMat;
		float rot = 0;
        Animation animation;
        bool isActive = false;
        bool isEffectPlayed = false; // ’Ç‰Á
    };

    std::vector<Effect> effects;
    KdTexture texture;
    Scene* owner = nullptr;
};

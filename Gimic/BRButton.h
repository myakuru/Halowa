#pragma once
#include "ButtonBase.h"
class Scene;

class C_BRButton :public C_ButtonBase {
public:
	C_BRButton() {}
	~C_BRButton() {}

	void ButtonInit() override;
	void ButtonUpdate() override;
	void ButtonDraw() override;
	void PlaySE()override;
	//void SELoad() override;

	void Load() override;
	void Release()override;

private:


	int h;
	int w;

	bool Once;

	KdTexture m_messageTex;

	struct Message {
		Math::Vector2 pos;
		float  scale;
		float  transparent;
		Math::Matrix scaleMat;
		Math::Matrix rotateMat;
		Math::Matrix transMat;
		Math::Matrix mat;
	}m_message;

	bool fading;
};
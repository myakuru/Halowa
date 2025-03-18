#pragma once
class Scene;

class C_ButtonBase {
public:
	C_ButtonBase() {}
	~C_ButtonBase() {}

	void Init();
	void Update();
	void Draw();

	virtual void ButtonInit() { return; }
	virtual void ButtonUpdate() { return; }
	virtual void ButtonDraw() { return; }

	virtual void Load() { return; }
	virtual void Release() { return; }

	//virtual void SELoad() { return; }

	void SetTex(KdTexture* buttonbaseTex) { m_buttonbaseTex = buttonbaseTex; }
	void SetButtonStage(bool stage) { nextStage = stage; }
	void SetButtonHit(bool hit) { buttonHit = hit; }
	void SetButtonPos(Math::Vector2 pos);
	virtual void PlaySE() { return; }

	Math::Vector2 GetPos() { return m_button.pos; }
	int GetRadius() { return buttonRadius; }
	bool GetButtonHit() { return buttonHit; }
	bool GetButtonStage() { return nextStage; }

	void SetOwner(Scene* owner) { m_owner = owner; }

	void SetVol(float a_Vol) {
		seInst->SetVolume(a_Vol);
	}

protected:
	struct ButtonBase {
		Math::Vector2 pos;
		float  scale;
		float  transparent;
		Math::Matrix scaleMat;
		Math::Matrix rotateMat;
		Math::Matrix transMat;
		Math::Matrix mat;
	}m_button;

	bool buttonHit;
	static const int buttonRadius = 32;
	bool EffectOnce;

	Scene* m_owner;

	bool nextStage;

	KdTexture* m_buttonbaseTex;

	//SE用
	std::shared_ptr<KdSoundEffect>   se; //音データの設計図
	std::shared_ptr<KdSoundInstance> seInst; //スピーカーの設計図

	float vol;
};
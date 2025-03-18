#pragma once
class Scene;

class C_Button
{
public:
	C_Button() :m_owner(nullptr),m_buttonTex(),m_messageTex(),nextStage(),EffectOnce(),buttonActive(),buttonHit(),buttonNum(),h(),w(){}
	~C_Button() {}

	void Init();
	void Update();
	void Draw();
	void PlaySE();

	void SetTex(KdTexture* buttonTex, KdTexture* messageTex) { m_buttonTex = buttonTex; m_messageTex = messageTex; }
	void SetButtonStage(bool stage) { nextStage = stage; }
	void SetOwner(Scene* owner) { m_owner = owner; }
	void SetButton();
	void SetButtonHit(bool hit) { buttonHit = hit;}
	void SetBlockAlive(bool alive) { blockAlive = alive; }

	Math::Vector2 GetPos() { return m_button.pos; }
	int GetRadius() { return buttonRadius; }
	bool GetButtonHit() { return buttonHit; }
	int GetButtonNum() { return buttonNum; }
	bool GetButtonStage() { return nextStage; }

	void SetVol(float a_Vol) {
		seInst->SetVolume(a_Vol);
	}

private:

	struct Button {
		Math::Vector2 pos;
		float  scale;
		float  transparent;
		Math::Matrix scaleMat;
		Math::Matrix rotateMat;
		Math::Matrix transMat;
		Math::Matrix mat;
	}m_button, m_message;

	KdTexture* m_buttonTex;
	KdTexture* m_messageTex;

	int w;
	int h;

	static const int buttonRadius = 32;

	bool EffectOnce;

	int buttonNum;
	bool buttonActive;
	bool buttonHit;

	Scene* m_owner;

	bool nextStage;
	bool blockAlive;

	//SE用
	std::shared_ptr<KdSoundEffect>   se; //音データの設計図
	std::shared_ptr<KdSoundInstance> seInst; //スピーカーの設計図

	//float vol;
};
#pragma once

class Scene;

class C_Endroll {
private:

	bool m_FadeinEnd;
	bool m_ScrollEnd;
	bool m_EndrollEnd;
	bool m_ChangeToTitle;
	int m_Cnt;

	struct Object {
		Math::Vector2 m_Pos = {0,0};
		Math::Matrix m_Mat;
		KdTexture m_Tex;

		Math::Color m_Color = { 1,1,1,1 };
		float m_Alpha = 1;
	};

	Object BlackBack,BlackFront, Endroll, ThankYou;

	Scene* m_EndOwner;


public:
	C_Endroll() {}
	~C_Endroll() {}

	void Update();
	void Draw();
	void Init() {
		Endroll.m_Pos.y = -1240;
		ThankYou.m_Alpha = 0;
		m_Cnt = 0;
		BlackFront.m_Alpha = 1;
		ThankYou.m_Color = { 0,0,0,0 };
		BlackFront.m_Color = { 1,1,1,1 };
		m_FadeinEnd = false;
		m_ScrollEnd = false;
		m_EndrollEnd = false;
		m_ChangeToTitle = false;
	}

	void LoadTex();
	void ReleaseTex();

	void ObjectMatrix(Object& a_Object) {
		a_Object.m_Mat = Math::Matrix::CreateTranslation(a_Object.m_Pos.x, a_Object.m_Pos.y, 0);
	}

	void DrawObject(Object& a_Object,Math::Rectangle a_Rect) {
		SHADER.m_spriteShader.SetMatrix(a_Object.m_Mat);
		SHADER.m_spriteShader.DrawTex(&a_Object.m_Tex, 0, 0, &a_Rect, &a_Object.m_Color);
	}

	void SetOwner(Scene* a_Owner) { m_EndOwner = a_Owner; }


};
#pragma once
class Scene;

class C_Fog {

public:
	C_Fog(Math::Vector2 pos, float width, float height);
	~C_Fog();

	void Init();
	void Update(); //更新
	void Draw();   //描画
	void DynamicDraw();
	void DynamicPlayerDraw();

	void Release();

	//セッター
	void SetScale(float scaleX) { m_fog.scaleX = scaleX; }
	void SetOwner(Scene* owner) { m_owner = owner; }
	void SetFogHit(bool hit) { fogHit = hit; }
	void SetFogLeave(bool leave) { fogLeave = leave; }

	Math::Vector2 GetPos() { return m_fog.pos; };
	float GetWidth() { return FogWidth; }
	float GetHeight() { return FogHeight; }
	bool GetFogHit() { return fogHit; }
	bool GetFogLeave() { return fogLeave; }

	//げったー

private:

	struct Fog {
		Math::Vector2 pos;
		Math::Vector2 move;
		float scaleX;
		float scaleY;
		Math::Matrix transMat;
		Math::Matrix scaleMat;
		Math::Matrix rotateMat;
		Math::Matrix mat;
		float angle;
	}m_fog, m_stencil,m_tmp;

	bool fogHit;
	bool fogLeave;
	bool fogFull;

	float m_transparent;

	Scene* m_owner;

	KdTexture m_fogTex;
	KdTexture m_fog1Tex;

	KdTexture m_stencilTex;
	KdTexture m_stencil2Tex;
	KdTexture m_backTex;

	KdTexture m_tmpTex;
	KdTexture tmpStencilTex;		// 型抜きされた画像
	KdTexture tmpLastTex;		// 型抜きされた画像

	float FogWidth;
	float FogHeight;

	int m_currentFrame; 
	int m_frameCount;  
	int m_frameTime;   
	int m_elapsedFrames; 

	int m_currentColumn;;
	int m_currentRow;

	int frame;

	int randomValueX;
	int randomValueY;
};
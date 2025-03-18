#pragma once

class Scene;

class C_LightningPar {
	
private:

	Scene* m_hOwner;

	struct particle {
		Math::Vector2 m_pos;
		Math::Vector2 m_setPos;
		Math::Vector2 m_move;
		Math::Vector2 m_scale;
		Math::Vector2 m_direct;
		bool m_firstf;
		int m_cnt;
		int m_exprtime;
		float m_angle;
		Math::Color m_color;
		Math::Color m_SetColor;
		bool m_alive;
		Math::Matrix m_scaleMat;
		Math::Matrix m_transMat;
		Math::Matrix m_rotationMat;
		Math::Matrix m_matrix;
		bool m_bExpr;

		int m_framecnt;
		int m_changecnt;
		int m_texNum;
		bool m_bOne;

	};


	static const int LightNum = 10;
	static const int LiEffNum = 10;
	static const int SmokeNum = 20;
	static const int LiChargeNum = 10;
	static const int ChargeAtkNum = 5;
	

	particle Lightning[LightNum], LiEff[LiEffNum],Smoke[SmokeNum],LiCharge;
	particle LiHit, ChargeAtk[ChargeAtkNum],ChargeSmoke,DeathAni;

	int m_i;
	int m_type;
	bool lightningEnd;

	const Math::Vector2 m_radius = { 16,16 };
	
	KdTexture LightTex;
	KdTexture LiEffTex;
	KdTexture smokeTex;
	KdTexture LiChargeTex;
	KdTexture ChargeSmokeTex;
	KdTexture DeathTex;
	KdTexture testTex;
public:

	

	C_LightningPar();
	~C_LightningPar();

	//雷
	void LightInit();
	void LightAction();
	void LightUpdate(float scrollX, float scrollY);
	void LightDraw();
	void LightEmit(float a_posX, float a_posY,
		int a_exprtime, float a_scaleX, float a_scaleY, float a_angle, Math::Color a_color,float a_a,float a_b,int a_i,Math::Vector2 a_playerPos,int a_type);

	//雷当たり判定
	void LightHitInit();
	void LightHitDraw();
	void LightHitRelease();
	void LightHitAction();
	void LightHitUpdate(float scrollX, float scrollY);
	void LightHitEmit(Math::Vector2 a_pos, Math::Vector2 a_AorB);

	//雷残像
	void LiEffInit();
	void LiEffUpdate(float scrollX, float scrollY);
	void LiEffDraw();
	void LiEffEmit(float a_posX, float a_posY, float a_moveX, float a_moveY,
		int a_exprtime, float a_scaleX, float a_scaleY, float a_angle, Math::Color a_color, float a_a, float a_b, int a_i);

	//チャージ
	void LiChargeInit();
	void LiChargeUpdate(float scrollX, float scrollY);
	void LiChargeDraw();
	void LiChargeEmit(Math::Vector2 a_pos);

	//煙
	void SmokeInit();
	void SmokeUpdate(float scrollX, float scrollY);
	void SmokeDraw();

	//ため攻撃エフェクト
	void ChargeAtkUpdate(float scrollX,float scrollY);
	void ChargeAtkDraw();
	void ChargeAtkInit();

	//死亡エフェクト
	void DeathEmit(Math::Vector2 a_Pos);
	void DeathUpdate(float scrollX, float scrollY);
	void DeathDraw();

	int AnimationLoop(int frame, int changeMaxCnt,particle &type);
	void LoadTexture();
	void ReleaseTexture();

	Math::Vector2 GetPos() { return LiHit.m_pos; }
	Math::Vector2 GetMove() { return LiHit.m_move; }
	Math::Vector2 GetFuturePos() { return LiHit.m_pos + LiHit.m_move; }
	Math::Vector2 GetRadius() { return m_radius; }
	Math::Vector2 GetDirect() { return LiHit.m_direct; }
	bool GetAlive() { return LiHit.m_alive; }
	int GetLiHitcnt() { return LiHit.m_cnt; }

	void SetAlive(bool a_alive) {
		LiHit.m_alive = a_alive; 
		lightningEnd = !a_alive;
	}

	float Rnd() { return rand() / (float)RAND_MAX; }

	void SetOwner(Scene* owner) { m_hOwner = owner; }
};
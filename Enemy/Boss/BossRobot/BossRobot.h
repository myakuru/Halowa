#pragma once
#include "../../EnemyBase.h"
#include "Smoke.h"


//ボスロボットクラス
class C_BossRobot : public C_EnemyBase
{
public:
	//C_BossRobot(Math::Vector2 a_pos);
	C_BossRobot(
		int   a_hpMax,
		int   a_attackDamage,
		int   a_hitDamage,
		int   a_coinMax,
		int   a_elecShockLimit,
		int   a_smokeDamage
	);
	~C_BossRobot();

	C_BossRobot(Math::Vector2 a_pos, const C_BossRobot& a_enemyData);

	//初期化
	void Init()override;
	//動作
	void Action(const Math::Vector2 playerPos)override;
	//更新
	void Update(const float a_scrollX, const float a_scrollY)override;

	//描画
	void Draw()override;

	//マップ当たり判定用 Y調整
	void MapHitY(float a_posY, float a_moveY, bool a_jump) override;

	//挨拶アニメーションの実行
	void ExecuteHello() { m_animHallo = true; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// セッター
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	//アクティブフラグ
	void SetActive(bool a_isActive) { m_isActive = a_isActive; }

	//煙画像
	void SetSmokeTex(KdTexture* a_smokeTex) { m_smokeTex = a_smokeTex; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// ゲッター
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	//煙のインスタンス取得
	const C_Smoke* GetSmoke() { return m_smoke; }

	//攻撃のノックバック角度
	const float GetAttackAngle() { return m_attackAngle; }


private:

	//ハイジャンプ後の着地
	void HighJumpLand();

	//煙発生関数
	void EmitSmoke();

	//煙パーティクル用のポインタ
	C_Smoke* m_smoke;

	//煙画像
	KdTexture* m_smokeTex;

	//アニメーションの種類
	enum AnimationType
	{
		IdleAnim,  //立ち姿
		WalkAnim,  //歩く
		AttackAnim,//攻撃
		DeathAnim, //死亡
		HelloAnim  //挨拶
	};
	//サウンドの種類
	enum SoundEffectType
	{
		LandingSfx,//着地
		WalkSfx,   //歩き
		DeathSfx   //死亡
	};

	//アニメーション更新
	void AnimationUpdate(AnimationType a_animation);

	//アニメーション最大数
	static const int m_idleMax    = 21;//立ち姿
	static const int m_walkingMax = 25;//歩く
	static const int m_runMax     = 25;//走る
	static const int m_attackMax  = 21;//攻撃
	static const int m_deathMax   = 27;//死亡
	static const int m_helloMax   = 41;//挨拶

	static const int m_highJumpIntervalMax = 60 * 2;//ハイジャンプのインターバルのセット時間
	static const int m_cooldownTimeMax = 60;//ハイジャンプ後の硬直時間の最大
	static const int m_seismicFrameRate = 5;//地面の震えのフレーム間隔

	const int m_smokeDamage;
	const float m_highJumpPower = 30.0f;    //ハイジャンプのジャンプ力
	const float m_highJumpNoTrackDist = 20; //ハイジャンプ後の着地場所までの距離
	const float m_drawCorrY = 70;           //Y座標の描画ずれ補正値
	const float m_seismicShakePower = 10.0f;//着地による地面の震えの力
	const float m_attackAngle = 60.0f;//攻撃のノックバック角度
	
	AnimationType m_nowAnim; //現在のアニメーション
	bool  m_animHallo;       //挨拶フラグ
	bool  m_isHighJump;      //ハイジャンプフラグ
	int   m_highJumpInterval;//ハイジャンプのインターバル
	int   m_cooldownTime;    //ハイジャンプ後の硬直時間
	float m_landingPosX;     //ハイジャンプ後の着地場所
};
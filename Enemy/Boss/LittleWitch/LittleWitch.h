#pragma once
#include "../../EnemyBase.h"
#include "EnemySpawner.h"

//魔法少女クラス
class C_LittleWitch : public C_EnemyBase
{
public:
	C_LittleWitch(Math::Vector2 a_pos);
	~C_LittleWitch();

	//初期化
	void Init()override;
	//動作
	void Action(const Math::Vector2 a_playerPos)override;
	//更新
	void Update(const float a_scrollX, const float a_scrollY)override;
	//描画
	void Draw()override;

	//マップ当たり判定用 Y調整
	void MapHitY(float a_posY, float a_moveY, bool a_jump) override;

	//アクティブフラグ
	void SetActive(bool a_isActive) { m_isActive = a_isActive; }
	//感電蓄積値のセット					        
	bool SetElecShockGauge(int a_elecShockGauge) override;
	//ダメージのセット
	bool SetDamage(int a_damage)override;
	//シールド画像
	void SetShieldTex(KdTexture* a_sTex) { m_shieldTex = a_sTex; }
	//敵スポナー画像のセット
	void SetEnemySpawnerTex(KdTexture* a_eTex) { m_enemySpawnerTex = a_eTex; }
	//敵スポナーのひび割れ画像のセット
	void SetEnemySpawnerCrackTex(KdTexture* a_eTex) { m_enemySpawnerCrackTex = a_eTex; }
	
	//シールドの耐久力
	int GetShieldDurability() { return m_shieldDurability; }
	//敵スポナー
	C_EnemySpawner* GetEnemySpawner() { return m_enemySpawner; }

private:
	//アニメーションの種類
	enum AnimationType
	{
		IdleAnim,     //立ち姿
		WalkAnim,     //歩く
		JumpAnim,     //ジャンプ
		FallAnim,     //降下
		LandAnim,     //着地
		AttackAnim,   //攻撃
		CastSpellAnim,//魔法を唱える
		SurprisedAnim,//驚き
		DeathAnim,    //死亡
	};

	//アニメーション更新
	void AnimationUpdate(AnimationType a_animation);

	//現在のアニメーション
	AnimationType m_nowAnim;

	//アニメーション最大数
	static const int m_idleMax      = 8; //立ち姿
	static const int m_walkMax      = 8; //歩く
	static const int m_jumpMax      = 3; //ジャンプ
	static const int m_fallMax      = 2; //降下
	static const int m_landMax      = 2; //着地
	static const int m_attackMax    = 2; //攻撃
	static const int m_castSpellMax = 11;//魔法を唱える
	static const int m_surprisedMax = 6; //驚き
	static const int m_deathMax     = 12;//死亡

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// シールド
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	//シールドの状態
	enum class ShieldState {
		OFF,    // シールドがOFF
		ON,     // シールドがON
		ACTIVE  // シールドがアクティブ
	};

	//シールド画像
	KdTexture* m_shieldTex;

	//現在のシールドの状態
	ShieldState m_nowShieldState;


	//シールドエフェクト用構造体
	Effect2 m_shield = {
		512,//画像横サイズ
		512,//画像縦サイズ
		8,  //行最大枚数
		8,  //列最大枚数
		64, //画像枚数
		3   //フレームレート
	};
	const float m_shieldScaleSize = 0.7f;//シールドサイズ
	bool m_isShieldActive;//シールドアクティブフラグ

	Math::Matrix m_shieldScaleMat;//シールド拡大行列
	Math::Matrix m_shieldMat;     //シールド合成行列
	Math::Color  m_shieldColor;   //シールドの色

	//シールドの更新
	void ShieldUpdate();

	static const int m_shieldDurabilityMax = 5;//シールドの耐久力の最大
	int m_shieldDurability;//シールドの耐久力
	bool m_isShieldDamaged;//シールドダメージフラグ

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 敵スポナー
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	//敵スポナーインスタンス
	C_EnemySpawner* m_enemySpawner;

	//敵スポナー画像
	KdTexture* m_enemySpawnerTex;

	//敵スポナーのひび割れ画像
	KdTexture* m_enemySpawnerCrackTex;

	//ボス召喚確率
	static const int m_bossSummonProbability = 20;

	//敵スポナー生成
	void CreateEnemySpawner();

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 飛行
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	//飛行
	void Fly();

	const float m_flyMoveX = 3;//飛行時の移動量X
	const float m_flyMoveY = 3;//飛行時の移動量Y

	bool m_isFlying;//飛行フラグ

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	bool m_isCastingSpell;//魔法詠唱フラグ
	bool m_isSurprised;   //驚きフラグ
	bool m_isLanded;      //着地フラグ
};
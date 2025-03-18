#pragma once
#include "../../EnemyBase.h"
#include "Bonfire.h"
#include "Fireball.h"
#include <vector>
#include <random>

//ロボットクラス
class C_Skull : public C_EnemyBase
{
public:
	//C_Skull(Math::Vector2 a_pos);
	C_Skull(
		int   a_hpMax,
		int   a_attackDamage,
		int   a_hitDamage,
		int   a_coinMax,
		int   a_elecShockLimit,
		int   a_fireballDamage,
		int   a_bonfireDamage
	);
	~C_Skull();

	C_Skull(Math::Vector2 a_pos, const C_Skull& a_enemyData);

	//初期化
	void Init()override;
	//動作
	void Action(const Math::Vector2 a_playerPos)override;
	//更新
	void Update(const float a_scrollX, const float a_scrollY)override;

	//描画
	void Draw()override;

	//アクティブフラグ
	void SetActive(bool a_isActive) { m_isActive = a_isActive; }

	//火のベール画像
	void SetFireVeilTex(KdTexture* a_fTex) { m_fireVeilTex = a_fTex; }

	//焚火の画像
	void SetBonfireTex(KdTexture* a_bTex) { m_bonfireTex = a_bTex; }

	//混乱画像
	void SetConfusedTex(KdTexture* a_cTex) { m_confusedTex = a_cTex; }

	//火の玉画像
	void SetFireballTex(KdTexture* a_fTex) { m_fireballTex = a_fTex; }

	//ダメージのセット
	bool SetDamage(int a_damage)override
	{
		if (m_isFireVeilActive)return false;
		m_hp -= a_damage;
		m_isDamage = true;
		return true;
	}

	//火の玉のインスタンス取得
	const std::vector<C_Fireball*> GetFireball() { return m_fireball; }

	//焚火のインスタンス取得
	const std::vector<C_Bonfire*> GetBonfire() { return m_bonfire; }

	//マップ当たり判定用 X調整
	void MapHitX(float a_posX, float a_moveX, char a_mapData);

private:
	//アニメーションの種類
	enum AnimationType
	{
		FloatAnim,      //浮遊
		DeathAnim       //死亡
	};

	//サウンドの種類
	enum SoundEffectType
	{
		CollisionSfx,//衝突
		ConfusedSfx, //混乱
		IgnitionSfx, //着火
		ShotSfx,     //発射
		RollingSfx,  //転がる
		ExplosionSfx//爆発
	};

	//アニメーション更新
	void AnimationUpdate(AnimationType a_animation);

	//現在のアニメーション
	AnimationType m_nowAnim;

	//アニメーション最大数
	static const int m_floatMax = 5;//浮遊
	static const int m_deathMax = 2;//死亡

	const float m_rotationAngle = 360.0f / 60.0f;//回転していく角度

	static const int m_rotationCountMax = 3;//回転回数の最大
	int m_rotationCount;//回転回数カウント

	static const int m_rollingCountMax = 3;//転がり回数の最大
	int m_rollingCount;//転がり回数カウント

	static const int m_restTimeMax = 60 * 2;//休憩時間の最大
	static const int m_confusionTimeMax = 60 * 5;//混乱時間の最大
	int m_waitTime;//待機時間

	static const int m_seismicTimeMax = 60 * 2;//地震の最大時間
	static const int m_seismicFrameRate = 5;//地面の震えのフレーム間隔
	const float m_seismicShakePower = 10.0f;//着地による地面の震えの力
	int m_seismicTime;//地震の時間


	bool m_isRolling; //転がりフラグ
	bool m_isConfused;//混乱フラグ
	bool m_isAwakened;//覚醒フラグ

	float m_setMoveX;//転がっている時の横移動量の設定

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// ファイアベール
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	//ファイアベール画像
	KdTexture* m_fireVeilTex;

	//ファイアベールエフェクト用構造体
	Effect2 m_fireVeil = {
		512,//画像横サイズ
		512,//画像縦サイズ
		8,  //行最大枚数
		8,  //列最大枚数
		64, //画像枚数
		2   //フレームレート
	};
	const float m_fireVeilScaleSize = 1.0f;//ファイアベールサイズ
	bool m_isFireVeilActive;//ファイアベールアクティブフラグ

	Math::Matrix m_fireVeilScaleMat;//ファイアベール拡大行列
	Math::Matrix m_fireVeilMat;     //ファイアベール合成行列
	
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 火の玉
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	//火の玉画像
	KdTexture* m_fireballTex;

	//火の玉インスタンス
	std::vector<C_Fireball*> m_fireball;

	//火の玉発生関数
	void EmitFireball();

	//火の玉ダメージ
	const int m_fireballDamage;

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 噴火
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	//噴火フラグ
	bool m_isErupting;

	//噴火発生確率
	const float m_eruptingProb = 100.0f;

	//噴火の際に発生するファイアボールの個数最大
	static const int m_fireballCountMax = 5;

	//噴火の際に発生するファイアボールの個数カウント
	int m_fireballCount;

	//噴火の際に発生する火の玉の発生間隔
	static const int m_fireballEmitRate = 10;
	
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 焚火
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	//焚火画像
	KdTexture* m_bonfireTex;

	//焚火インスタンス
	std::vector<C_Bonfire*> m_bonfire;
	
	//焚火発生関数
	void EmitBonfire(Math::Vector2 a_pos);

	//焚火発生確率
	const float m_bonfireProb = 1.0f;//0.7f;//%

	//焚火ダメージ
	const int m_bonfireDamage;

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 混乱
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	//混乱画像
	KdTexture* m_confusedTex;

	//混乱エフェクト用構造体
	Effect1 m_confused = { 
		300,//画像横サイズ
		300,//画像縦サイズ
		13,	//画像枚数
		4	//フレームレート
	};
};
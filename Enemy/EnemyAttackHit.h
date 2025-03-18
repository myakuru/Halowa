#pragma once
class Scene;
class C_EnemyMgr;
class C_Chara;

//敵攻撃判定クラス
class C_EnemyAtkHit
{
public:
	C_EnemyAtkHit();
	~C_EnemyAtkHit() = default;

	//プレイヤーと敵の当たり判定
	void Player_EnemyHit();

	//全ての敵の攻撃
	void AllEnemiesAttack();

	//敵管理クラスのインスタンスセット
	void SetEnemyMgr(C_EnemyMgr* a_enemyMgr) { m_hEnemyMgr = a_enemyMgr; }

	//プレイヤークラスのインスタンスセット
	void SetPlayer(C_Chara* a_player) { m_hPlayer = a_player; }

	// オーナーの設定
	void SetOwner(Scene* owner) { m_hOwner = owner; };

private:
	//ロボットの攻撃判定
	void RobotAttackHit();

	//グレムリンの攻撃判定
	void GremlinAttackHit();

	//ボスロボットの攻撃判定
	void BossRobotAttackHit();

	//スカルの攻撃判定
	void SkullAttackHit();

	//煙の当たり判定
	void SmokeHit();

	//魔法の当たり判定
	void SpellHit();
	
	//火の玉の当たり判定
	void FireballHit();

	//焚火との当たり判定
	void BonfireHit();

	//プレイヤーと円の当たり判定
	bool PlayerHitCircle(float circleX, float circleY, float circleRadius);

	//ノックバック計算
	void Knockback(Math::Vector2 a_srcPos, float a_knockForce);
	void Knockback(Math::Vector2 a_srcPos, float a_knockForce, float a_knockAngle);

	// メンバ変数
	Scene* m_hOwner;
	C_EnemyMgr* m_hEnemyMgr;
	C_Chara* m_hPlayer;
};
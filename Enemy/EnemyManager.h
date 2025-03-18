#pragma once
#include <vector>
#include "EnemyBase.h"
#include "Standard/Robot/Robot.h"
#include "Standard/Frog/Frog.h"
#include "Standard/Ghost/Ghost.h"
#include "Standard/Gremlin/Gremlin.h"
#include "Standard/Sentinel/Sentinel.h"
#include "Boss/BossRobot/BossRobot.h"
#include "Boss/Skull/Skull.h"
#include "Boss/LittleWitch/LittleWitch.h"
#include "Coin.h"

class Scene;
/// 「このクラスの使い方」
/// ●インスタンスの作成
/// C_EnemyMgr* enemyMgr = [オーナー]->GetEnemyMgr();
/// 
/// ●関数の呼び出し方
/// for (int i = 0; i < m_enemyMgr.Get[敵の種類]().size(); i++)
/// {
/// 	m_enemyMgr->Get[敵の種類]()[i]->[呼び出したい関数]();
/// }

//敵管理クラス
class C_EnemyMgr
{
public:
	C_EnemyMgr();
	~C_EnemyMgr(){}

	//初期化
	void Init();
	//動作
	void Action();
	//更新
	void Update();
	//描画
	void Draw();

	//読み込み
	void Load();
	//解放
	void Release();

	//サウンドエフェクトの音量セット
	void SetSoundVolume(float a_multiplier);

	//インスタンスが存在するか確認
	bool IsInstanceActive(C_EnemyBase* a_enemy);

	//敵のインスタンスと配列を全消去
	void DestroyAllEnemies();

	//コインの生成
	void CreateCoin(float a_posX, float a_posY);

	//コインのサウンドを鳴らす
	void PlayCoinSound();

	//スポーン関数...戻り値で生成した敵のインスタンス返る
	
	//ロボットの生成
	C_Robot* SpawnRobot(float a_posX, float a_posY);

	//カエルの生成
	C_Frog* SpawnFrog(float a_posX, float a_posY);

	//ゴーストの生成
	C_Ghost* SpawnGhost(float a_posX, float a_posY);
	
	//グレムリンの生成
	C_Gremlin* SpawnGremlin(float a_posX, float a_posY);

	//センチネル生成
	C_Sentinel* SpawnSentinel(float a_posX, float a_posY);

	//ボスロボットの生成
	C_BossRobot* SpawnBossRobot(float a_posX, float a_posY, bool a_isLittleWitchSummoned = false);

	//スカルの生成
	C_Skull* SpawnSkull(float a_posX, float a_posY, bool a_isLittleWitchSummoned = false);

	//魔法少女の生成
	C_LittleWitch* SpawnLittleWitch(float a_posX, float a_posY);

	//////////////セッター///////////////////////////////////////////////

	//オーナーのインスタンス取得
	void SetOwner(Scene* a_eOwner) { m_mOwner = a_eOwner; }
	/////////////////////////////////////////////////////////////////////


	//////////////ゲッター///////////////////////////////////////////////
	
	//コインのインスタンスを取得
	const std::vector<C_Coin*>GetCoin() { return m_coin; }

	//ロボットのインスタンス取得
	const std::vector<C_Robot*>GetRobot() { return m_robot; }

	//カエルのインスタンス取得
	const std::vector<C_Frog*>GetFrog() { return m_frog; }

	//ゴーストのインスタンス取得
	const std::vector<C_Ghost*>GetGhost() { return m_ghost; }

	//グレムリンのインスタンス取得
	const std::vector<C_Gremlin*>GetGremlin() { return m_gremlin; }

	//センチネルのインスタンス取得
	const std::vector<C_Sentinel*>GetSentinel() { return m_sentinel; }

	//ボスロボットのインスタンス取得
	const std::vector<C_BossRobot*>GetBossRobot() { return m_bossRobot; }
	
	//スカルのインスタンス取得
	const std::vector<C_Skull*>GetSkull() { return m_skull; }
	
	//魔法少女のインスタンス取得
	C_LittleWitch* GetLittleWitch() { return m_littleWitch; }

	//全ての敵のインスタンスを取得
	const std::vector<C_EnemyBase*>GetAllEnemies() { return m_allEnemies; }
	/////////////////////////////////////////////////////////////////////

private:

	//ボス敵のステータスの強さ
	enum BossEnemyStrength {
		Weak,        // 弱め...魔法少女召喚用
		Normal,      // 普通
		StrengthCount// ステータスの種類の数
	};

	//敵共通スポーン初期化
	void SpawnInit();

	//オーナー
	Scene* m_mOwner;

	//フレームカウント用
	int   m_frameCnt;

	//コイン生成フレームレート
	static const int m_createCoinFrameRate = 3;

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// インスタンス
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	std::vector<C_Coin*>m_coin;//コイン

	//ボスステータス保管
	C_BossRobot* m_bossRobotStatus[StrengthCount];
	C_Skull*     m_skullStatus[StrengthCount];

	std::vector<C_Robot*>m_robot;            //ロボット
	std::vector<C_Frog*> m_frog;             //カエル
	std::vector<C_Ghost*>m_ghost;	         //ゴースト
	std::vector<C_Gremlin*>m_gremlin;	     //グレムリン
	std::vector<C_Sentinel*>m_sentinel;	     //センチネル
	std::vector<C_BossRobot*>m_bossRobot;    //ボスロボット
	std::vector<C_Skull*>m_skull;            //スカル
	C_LittleWitch* m_littleWitch;            //魔法少女
	std::vector<C_EnemyBase*>m_allEnemies;   //全ての敵インスタンス管理用

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 画像
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	//コイン
	KdTexture m_coinTex;

	KdTexture m_elecShockTex;//感電
	KdTexture m_smokeTex;    //煙
	KdTexture m_spellTex;    //魔法
	KdTexture m_dustTex;     //砂埃
	KdTexture m_fireVeilTex; //火のベール
	KdTexture m_bonfireTex;  //焚火
	KdTexture m_confusedTex; //混乱
	KdTexture m_fireballTex; //火の玉
	KdTexture m_enemySpawnerTex;     //敵スポナー
	KdTexture m_enemySpawnerCrackTex;//敵スポナーのひび割れ

	//シールド
	static const int m_shieldTexNum = 3;
	KdTexture m_shieldTex[m_shieldTexNum];

	//ロボット
	static const int m_robotTexNum = 3;
	KdTexture m_robotTex[m_robotTexNum];

	//カエル
	static const int m_frogTexNum = 3;
	KdTexture m_frogTex[m_frogTexNum];

	//ゴースト
	static const int m_ghostTexNum = 2;
	KdTexture m_ghostTex[m_ghostTexNum];

	//グレムリン
	static const int m_gremlinTexNum = 4;
	KdTexture m_gremlinTex[m_gremlinTexNum];
	
	//センチネル
	static const int m_sentinelTexNum = 5;
	KdTexture m_sentinelTex[m_sentinelTexNum];

	//ボスロボット
	static const int m_bossRobotTexNum = 5;     
	KdTexture m_bossRobotTex[m_bossRobotTexNum];

	//スカル
	static const int m_skullTexNum = 2; 
	KdTexture m_skullTex[m_skullTexNum];

	//魔法少女
	static const int m_littleWitchTexNum = 9;
	KdTexture m_littleWitchTex[m_littleWitchTexNum];


	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// サウンド
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	//コイン
	std::shared_ptr<KdSoundEffect>  m_coinSfxData;//音データ
	std::shared_ptr<KdSoundInstance>m_coinSfxInst;//サウンドインスタンス

	//感電
	std::shared_ptr<KdSoundEffect>  m_elecShockSfxData;//音データ
	std::shared_ptr<KdSoundInstance>m_elecShockSfxInst;//サウンドインスタンス
	
	//ロボット
	static const int m_robotSfxNum = 1;
	std::shared_ptr<KdSoundEffect>  m_robotSfxData[m_robotSfxNum]; //音データ
	std::shared_ptr<KdSoundInstance>m_robotSfxInst[m_robotSfxNum];//サウンドインスタンス

	//カエル
	static const int m_frogSfxNum = 2;
	std::shared_ptr<KdSoundEffect>  m_frogSfxData[m_frogSfxNum]; //音データ
	std::shared_ptr<KdSoundInstance>m_frogSfxInst[m_frogSfxNum];//サウンドインスタンス

	//ゴースト
	static const int m_ghostSfxNum = 1;
	std::shared_ptr<KdSoundEffect>  m_ghostSfxData[m_ghostSfxNum]; //音データ
	std::shared_ptr<KdSoundInstance>m_ghostSfxInst[m_ghostSfxNum];//サウンドインスタンス

	//グレムリン
	static const int m_gremlinSfxNum = 1;
	std::shared_ptr<KdSoundEffect>  m_gremlinSfxData[m_gremlinSfxNum]; //音データ
	std::shared_ptr<KdSoundInstance>m_gremlinSfxInst[m_gremlinSfxNum];//サウンドインスタンス
	
	//センチネル
	static const int m_sentinelSfxNum = 1;
	std::shared_ptr<KdSoundEffect>  m_sentinelSfxData[m_sentinelSfxNum]; //音データ
	std::shared_ptr<KdSoundInstance>m_sentinelSfxInst[m_sentinelSfxNum];//サウンドインスタンス

	//ボスロボット
	static const int m_bossRobotSfxNum = 3;
	std::shared_ptr<KdSoundEffect>  m_bossRobotSfxData[m_bossRobotSfxNum]; //音データ
	std::shared_ptr<KdSoundInstance>m_bossRobotSfxInst[m_bossRobotSfxNum];//サウンドインスタンス

	//スカル
	static const int m_skullSfxNum = 6;
	std::shared_ptr<KdSoundEffect>  m_skullSfxData[m_skullSfxNum]; //音データ
	std::shared_ptr<KdSoundInstance>m_skullSfxInst[m_skullSfxNum];//サウンドインスタンス
};

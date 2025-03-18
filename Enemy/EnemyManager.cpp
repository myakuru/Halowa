#include "EnemyManager.h"
#include "../Scene.h"

C_EnemyMgr::C_EnemyMgr() :m_mOwner(nullptr), m_robotTex(), m_robot(), m_bossRobot(), m_coin(), m_littleWitch(nullptr)
{
	m_frameCnt = 0;
}

//初期化
void C_EnemyMgr::Init()
{
	m_mOwner->GetEnemyAtkHit()->SetEnemyMgr(this);
	SetSoundVolume(1.0f);

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// ボスステータス設定
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	//魔法少女が召喚するボス
	m_bossRobotStatus[Weak] = new C_BossRobot(
		10,//最大体力
		0, //攻撃力
		0, //当たったときのダメージ
		0, //所持コインの最大
		1, //感電限界値
		0  //煙のダメージ
	);
	m_skullStatus[Weak] = new C_Skull(
		10,//最大体力
		0, //攻撃力
		0, //当たったときのダメージ
		0, //所持コインの最大
		1, //感電限界値
		0, //火の玉のダメージ
		0  //焚火のダメージ
	);

	//通常時のボス
	m_bossRobotStatus[Normal] = new C_BossRobot(
		200, //最大体力
		400, //攻撃力
		200, //当たったときのダメージ
		30,  //所持コインの最大
		100, //感電限界値
		500  //煙のダメージ
	);
	m_skullStatus[Normal] = new C_Skull(
		400,//最大体力
		400,//攻撃力
		200,//当たったときのダメージ
		50, //所持コインの最大
		250,//感電限界値
		300,//火の玉のダメージ
		200 //焚火のダメージ
	);
}

//動作
void C_EnemyMgr::Action()
{
	//プレイヤーの座標を取得
	Math::Vector2 playerPos = m_mOwner->GetChara()->GetPos();

	//コインの動作
	for (size_t i = 0; i < m_coin.size(); i++)
	{
		m_coin[i]->Action(playerPos);
	}
	//全ての敵の動作
	for (size_t i = 0; i < m_allEnemies.size(); i++)
	{
		m_allEnemies[i]->Action(playerPos);
	}
}

//更新
void C_EnemyMgr::Update()
{
	//フレームカウントアップ
	m_frameCnt++;

	//コイン削除処理
	for (size_t i = 0; i < m_coin.size(); i++)
	{
		if (m_coin[i]->GetAlive()) continue;

		delete m_coin[i];

		auto cItr = m_coin.begin();

		m_coin.erase(cItr + i);
	}
	//ロボット死亡時処理
	for (size_t i = 0; i < m_robot.size(); i++)
	{
		//生存フラグがONならコンティニュー
		if (m_robot[i]->GetAlive())continue;

		//配列の最初をイテレータに入れて
		auto eItr = m_robot.begin();

		//指定の配列を削除
		m_robot.erase(eItr + i);
	}
	//カエル死亡時処理
	for (size_t i = 0; i < m_frog.size(); i++)
	{
		//生存フラグがONならコンティニュー
		if (m_frog[i]->GetAlive())continue;

		//配列の最初をイテレータに入れて
		auto eItr = m_frog.begin();

		//指定の配列を削除
		m_frog.erase(eItr + i);
	}
	//ゴースト死亡時処理
	for (size_t i = 0; i < m_ghost.size(); i++)
	{
		//生存フラグがONならコンティニュー
		if (m_ghost[i]->GetAlive())continue;

		//配列の最初をイテレータに入れて
		auto eItr = m_ghost.begin();

		//指定の配列を削除
		m_ghost.erase(eItr + i);
	}
	//グレムリン死亡時処理
	for (size_t i = 0; i < m_gremlin.size(); i++)
	{
		//生存フラグがONならコンティニュー
		if (m_gremlin[i]->GetAlive())continue;

		//配列の最初をイテレータに入れて
		auto eItr = m_gremlin.begin();

		//指定の配列を削除
		m_gremlin.erase(eItr + i);
	}
	//センチネル死亡時処理
	for (size_t i = 0; i < m_sentinel.size(); i++)
	{
		//生存フラグがONならコンティニュー
		if (m_sentinel[i]->GetAlive())continue;

		//配列の最初をイテレータに入れて
		auto eItr = m_sentinel.begin();

		//指定の配列を削除
		m_sentinel.erase(eItr + i);
	}
	//ボスロボット死亡時処理
	for (size_t i = 0; i < m_bossRobot.size(); i++)
	{
		//生存フラグがONならコンティニュー
		if (m_bossRobot[i]->GetAlive())continue;

		//配列の最初をイテレータに入れて
		auto eItr = m_bossRobot.begin();

		//指定の配列を削除
		m_bossRobot.erase(eItr + i);
	}
	//スカル死亡時処理
	for (size_t i = 0; i < m_skull.size(); i++)
	{
		//生存フラグがONならコンティニュー
		if (m_skull[i]->GetAlive())continue;

		//配列の最初をイテレータに入れて
		auto eItr = m_skull.begin();

		//指定の配列を削除
		m_skull.erase(eItr + i);
	}
	//全ての敵の死亡時処理
	for (size_t i = 0; i < m_allEnemies.size(); i++)
	{
		//生存フラグがONならコンティニュー
		if (m_allEnemies[i]->GetAlive())continue;

		//所持コイン枚数がまだあれば
		if (m_allEnemies[i]->GetCoinDropCount() > 0)
		{
			//コイン生成のフレームレートに合わせて
			if (m_frameCnt % m_createCoinFrameRate == 0)
			{
				//敵の死亡座標取得
				const Math::Vector2 enemyPos = m_allEnemies[i]->GetPos();

				//コインを生成
				CreateCoin(enemyPos.x, enemyPos.y);

				//所持コイン枚数を1枚減らす
				m_allEnemies[i]->SetCoinDropCount(m_allEnemies[i]->GetCoinDropCount() - 1);
			}
			continue;
		}

		//魔法少女なら
		if (m_allEnemies[i]->GetEnemyType() == EnemyType::LittleWitch)
		{
			//インスタンスの解放
			delete m_allEnemies[i];

			//nullptrで初期化
			m_littleWitch = nullptr;
		}
		else
		{		
			//インスタンスの解放
			delete m_allEnemies[i];
		}

		//配列の最初をイテレータに入れて
		auto eItr = m_allEnemies.begin();

		//指定の配列を削除
		m_allEnemies.erase(eItr + i);
	}

	//スクロールの値を取得
	const float scrollX = m_mOwner->GetMap()->GetScrollX();
	const float scrollY = m_mOwner->GetMap()->GetScrollY();

	//コインの更新
	for (size_t i = 0; i < m_coin.size(); i++)
	{
		m_coin[i]->Update(scrollX, scrollY);
	}
	//全ての敵の更新
	for (size_t i = 0; i < m_allEnemies.size(); i++)
	{
		m_allEnemies[i]->Update(scrollX, scrollY);
	}

}

//描画
void C_EnemyMgr::Draw()
{
	//全ての敵の描画
	for (size_t i = 0; i < m_allEnemies.size(); i++)
	{
		m_allEnemies[i]->Draw();
	}
	//コインの描画
	for (size_t i = 0; i < m_coin.size(); i++)
	{
		m_coin[i]->Draw();
	}
}

//読み込み
void C_EnemyMgr::Load()
{
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 画像読み込み
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	//コイン
	m_coinTex.Load("Texture/Enemy/Coin.png");

	//感電
	m_elecShockTex.Load("Texture/Enemy/Shock_Flash.png");

	//煙
	m_smokeTex.Load("Texture/Enemy/Boss/BossRobot/Smoke.png");

	//魔法
	m_spellTex.Load("Texture/Enemy/Standard/Frog/Spell.png");

	//砂埃
	m_dustTex.Load("Texture/Enemy/Standard/Gremlin/Dust.png");

	//火のベール
	m_fireVeilTex.Load("Texture/Enemy/Boss/Skull/FireVeil.png");

	//焚火
	m_bonfireTex.Load("Texture/Enemy/Boss/Skull/Bonfire.png");

	//混乱画像
	m_confusedTex.Load("Texture/Enemy/Boss/Skull/Confused.png");

	//火の玉
	m_fireballTex.Load("Texture/Enemy/Boss/Skull/Fireball.png");

	//敵スポナー
	m_enemySpawnerTex.Load("Texture/Enemy/Boss/LittleWitch/EnemySpawner.png");

	//敵スポナーのひび割れ
	m_enemySpawnerCrackTex.Load("Texture/Enemy/Boss/LittleWitch/EnemySpawnerCrack.png");

	//シールド
	m_shieldTex[0].Load("Texture/Enemy/Boss/LittleWitch/Shield_Off.png");
	m_shieldTex[1].Load("Texture/Enemy/Boss/LittleWitch/Shield_On.png");
	m_shieldTex[2].Load("Texture/Enemy/Boss/LittleWitch/Shield.png");

	//ロボット
	m_robotTex[0].Load("Texture/Enemy/Standard/Robot/walking.png");
	m_robotTex[1].Load("Texture/Enemy/Standard/Robot/attack.png");
	m_robotTex[2].Load("Texture/Enemy/Standard/Robot/death.png");

	//カエル
	m_frogTex[0].Load("Texture/Enemy/Standard/Frog/Idle.png");
	m_frogTex[1].Load("Texture/Enemy/Standard/Frog/Attack.png");
	m_frogTex[2].Load("Texture/Enemy/Standard/Frog/Death.png");

	//ゴースト
	m_ghostTex[0].Load("Texture/Enemy/Standard/Ghost/Float.png");
	m_ghostTex[1].Load("Texture/Enemy/Standard/Ghost/Death.png");

	//グレムリン
	m_gremlinTex[0].Load("Texture/Enemy/Standard/Gremlin/Idle.png");
	m_gremlinTex[1].Load("Texture/Enemy/Standard/Gremlin/Walk.png");
	m_gremlinTex[2].Load("Texture/Enemy/Standard/Gremlin/Attack.png");
	m_gremlinTex[3].Load("Texture/Enemy/Standard/Gremlin/Death.png");

	//センチネル
	m_sentinelTex[0].Load("Texture/Enemy/Standard/Sentinel/Idle.png");
	m_sentinelTex[1].Load("Texture/Enemy/Standard/Sentinel/Walk.png");
	m_sentinelTex[2].Load("Texture/Enemy/Standard/Sentinel/Attack1.png");
	m_sentinelTex[3].Load("Texture/Enemy/Standard/Sentinel/Attack2.png");
	m_sentinelTex[4].Load("Texture/Enemy/Standard/Sentinel/Death.png");

	//ボスロボット
	m_bossRobotTex[0].Load("Texture/Enemy/Boss/BossRobot/Idle.png");
	m_bossRobotTex[1].Load("Texture/Enemy/Boss/BossRobot/Walk.png");
	m_bossRobotTex[2].Load("Texture/Enemy/Boss/BossRobot/Attack.png");
	m_bossRobotTex[3].Load("Texture/Enemy/Boss/BossRobot/Death.png");
	m_bossRobotTex[4].Load("Texture/Enemy/Boss/BossRobot/Hello.png");

	//スカル
	m_skullTex[0].Load("Texture/Enemy/Boss/Skull/Float.png");
	m_skullTex[1].Load("Texture/Enemy/Boss/Skull/Death.png");

	//魔法少女
	m_littleWitchTex[0].Load("Texture/Enemy/Boss/LittleWitch/Idle.png");
	m_littleWitchTex[1].Load("Texture/Enemy/Boss/LittleWitch/Walk.png");
	m_littleWitchTex[2].Load("Texture/Enemy/Boss/LittleWitch/Jump.png");
	m_littleWitchTex[3].Load("Texture/Enemy/Boss/LittleWitch/Fall.png");
	m_littleWitchTex[4].Load("Texture/Enemy/Boss/LittleWitch/Land.png");
	m_littleWitchTex[5].Load("Texture/Enemy/Boss/LittleWitch/Attack.png");
	m_littleWitchTex[6].Load("Texture/Enemy/Boss/LittleWitch/CastSpell.png");
	m_littleWitchTex[7].Load("Texture/Enemy/Boss/LittleWitch/Surprised.png");
	m_littleWitchTex[8].Load("Texture/Enemy/Boss/LittleWitch/Death.png");

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// サウンドエフェクト読み込み
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	//コイン
	m_coinSfxData = std::make_shared<KdSoundEffect>();
	m_coinSfxData->Load("Sound/Enemy/GetCoin.wav");
	m_coinSfxInst = m_coinSfxData->CreateInstance(false);

	//感電
	m_elecShockSfxData = std::make_shared<KdSoundEffect>();
	m_elecShockSfxData->Load("Sound/Enemy/Electric_Shock.wav");
	m_elecShockSfxInst = m_elecShockSfxData->CreateInstance(false);

	//ロボット
	for (int i = 0; i < m_robotSfxNum; i++)
	{
		m_robotSfxData[i] = std::make_shared<KdSoundEffect>();
	}
	m_robotSfxData[0]->Load("Sound/Enemy/Robot/Explosion.wav");
	for (int i = 0; i < m_robotSfxNum; i++)
	{
		m_robotSfxInst[i] = m_robotSfxData[i]->CreateInstance(false);
	}

	//カエル
	for (int i = 0; i < m_frogSfxNum; i++)
	{
		m_frogSfxData[i] = std::make_shared<KdSoundEffect>();
	}
	m_frogSfxData[0]->Load("Sound/Enemy/Frog/Shot.wav");
	m_frogSfxData[1]->Load("Sound/Enemy/Frog/Death.wav");
	for (int i = 0; i < m_frogSfxNum; i++)
	{
		m_frogSfxInst[i] = m_frogSfxData[i]->CreateInstance(false);
	}

	//ボスロボット
	for (int i = 0; i < m_bossRobotSfxNum; i++)
	{
		m_bossRobotSfxData[i] = std::make_shared<KdSoundEffect>();
	}
	m_bossRobotSfxData [0]->Load("Sound/Enemy/BossRobot/Landing.wav");
	m_bossRobotSfxData [1]->Load("Sound/Enemy/BossRobot/Walk.wav");
	m_bossRobotSfxData [2]->Load("Sound/Enemy/BossRobot/Death.wav");	
	for (int i = 0; i < m_bossRobotSfxNum; i++)
	{
		m_bossRobotSfxInst[i] = m_bossRobotSfxData[i]->CreateInstance(false);
	}

	//スカル
	for (int i = 0; i < m_skullSfxNum; i++)
	{
		m_skullSfxData[i] = std::make_shared<KdSoundEffect>();
	}
	m_skullSfxData[0]->Load("Sound/Enemy/Skull/Collision.wav");
	m_skullSfxData[1]->Load("Sound/Enemy/Skull/Confused.wav");
	m_skullSfxData[2]->Load("Sound/Enemy/Skull/Ignition.wav");
	m_skullSfxData[3]->Load("Sound/Enemy/Skull/Shot.wav");
	m_skullSfxData[4]->Load("Sound/Enemy/Skull/Rolling.wav");
	m_skullSfxData[5]->Load("Sound/Enemy/Skull/Explosion.wav");
	for (int i = 0; i < m_skullSfxNum; i++)
	{
		m_skullSfxInst[i] = m_skullSfxData[i]->CreateInstance(false);
	}
}

//解放
void C_EnemyMgr::Release()
{
	//画像解放
	m_coinTex.Release();
	m_elecShockTex.Release();
	m_smokeTex.Release();
	m_spellTex.Release();
	m_dustTex.Release();
	m_fireVeilTex.Release();
	m_bonfireTex.Release();
	m_confusedTex.Release();
	m_fireballTex.Release();
	m_enemySpawnerTex.Release();
	m_enemySpawnerCrackTex.Release();
	for (int i = 0; i < m_shieldTexNum; i++)
	{
		m_shieldTex[i].Release();
	}

	for (int i = 0; i < m_robotTexNum; i++)
	{
		m_robotTex[i].Release();
	}
	for (int i = 0; i < m_frogTexNum; i++)
	{
		m_frogTex[i].Release();
	}
	for (int i = 0; i < m_ghostTexNum; i++)
	{
		m_ghostTex[i].Release();
	}
	for (int i = 0; i < m_gremlinTexNum; i++)
	{
		m_gremlinTex[i].Release();
	}
	for (int i = 0; i < m_sentinelTexNum; i++)
	{
		m_sentinelTex[i].Release();
	}
	for (int i = 0; i < m_bossRobotTexNum; i++)
	{
		m_bossRobotTex[i].Release();
	}
	for (int i = 0; i < m_skullTexNum; i++)
	{
		m_skullTex[i].Release();
	}
	for (int i = 0; i < m_littleWitchTexNum; i++)
	{
		m_littleWitchTex[i].Release();
	}
	//敵のインスタンスを全消去
	DestroyAllEnemies();
}

//サウンドエフェクトの音量セット
void C_EnemyMgr::SetSoundVolume(float a_multiplier)
{
	m_coinSfxInst->SetVolume(a_multiplier);
	m_elecShockSfxInst->SetVolume(a_multiplier);
	for (int i = 0; i < m_robotSfxNum; i++)
	{
		m_robotSfxInst[i]->SetVolume(a_multiplier);
	}
	for (int i = 0; i < m_frogSfxNum; i++)
	{
		m_frogSfxInst[i]->SetVolume(a_multiplier);
	}
	for (int i = 0; i < m_bossRobotSfxNum; i++)
	{
		m_bossRobotSfxInst[i]->SetVolume(a_multiplier);
	}
	for (int i = 0; i < m_skullSfxNum; i++)
	{
		m_skullSfxInst[i]->SetVolume(a_multiplier);
	}
}

//インスタンスが存在するか確認
bool C_EnemyMgr::IsInstanceActive(C_EnemyBase* a_enemy)
{
	//全ての敵を検索
	for (size_t i = 0; i < m_allEnemies.size(); i++)
	{
		//同じアドレスが存在したらtrue
		if (m_allEnemies[i] == a_enemy)return true;
	}
	//存在しないアドレスならfalse
	return false;
}

//敵のインスタンスと配列を全消去
void C_EnemyMgr::DestroyAllEnemies()
{
	for (size_t i = 0; i < m_coin.size(); i++)
	{
		delete m_coin[i];
	}
	for (size_t i = 0; i < m_allEnemies.size(); i++)
	{
		delete m_allEnemies[i];
	}

	m_coin.clear();
	m_robot.clear();
	m_frog.clear();
	m_ghost.clear();
	m_gremlin.clear();
	m_sentinel.clear();
	m_bossRobot.clear();
	m_skull.clear();
	m_littleWitch = nullptr;
	m_allEnemies.clear();
}

//コインの生成
void C_EnemyMgr::CreateCoin(float a_posX, float a_posY)
{
	//メモリを確保しインスタンスの生成
	m_coin.push_back(new C_Coin({ a_posX,a_posY }));

	//生成されたインスタンスに画像をセット
	m_coin.back()->SetTex(&m_coinTex);
}

//ロボット生成
C_Robot* C_EnemyMgr::SpawnRobot(float a_posX,float a_posY)
{
	//メモリを確保しインスタンスの生成
	m_robot.push_back(new C_Robot({ a_posX,a_posY }));

	//生成されたインスタンスに敵画像をセット
	m_robot.back()->SetEnemyTex(m_robotTex);

	//生成されたインスタンスに音声データをセット
	m_robot.back()->SetEnemySfx(m_robotSfxInst);

	//全ての敵インスタンス管理用配列に格納
	m_allEnemies.push_back(m_robot.back());

	//敵共通スポーン初期化
	SpawnInit();

	//戻り値で生成したインスタンスを返す
	return m_robot.back();
}

//カエル生成
C_Frog* C_EnemyMgr::SpawnFrog(float a_posX, float a_posY)
{
	//メモリを確保しインスタンスの生成
	m_frog.push_back(new C_Frog({ a_posX,a_posY }));

	//生成されたインスタンスに敵画像をセット
	m_frog.back()->SetEnemyTex(m_frogTex);

	//生成されたインスタンスに魔法画像をセット
	m_frog.back()->SetSpellTex(&m_spellTex);

	//生成されたインスタンスに音声データをセット
	m_frog.back()->SetEnemySfx(m_frogSfxInst);

	//全ての敵インスタンス管理用配列に格納
	m_allEnemies.push_back(m_frog.back());

	//敵共通スポーン初期化
	SpawnInit();

	//戻り値で生成したインスタンスを返す
	return m_frog.back();
}

//ゴーストの生成
C_Ghost* C_EnemyMgr::SpawnGhost(float a_posX, float a_posY)
{
	//メモリを確保しインスタンスの生成
	m_ghost.push_back(new C_Ghost({ a_posX,a_posY }));

	//生成されたインスタンスに敵画像をセット
	m_ghost.back()->SetEnemyTex(m_ghostTex);

	//生成されたインスタンスに音声データをセット
	m_ghost.back()->SetEnemySfx(m_ghostSfxInst);

	//全ての敵インスタンス管理用配列に格納
	m_allEnemies.push_back(m_ghost.back());

	//敵共通スポーン初期化
	SpawnInit();

	//戻り値で生成したインスタンスを返す
	return m_ghost.back();
}

//グレムリンの生成
C_Gremlin* C_EnemyMgr::SpawnGremlin(float a_posX, float a_posY)
{
	//メモリを確保しインスタンスの生成
	m_gremlin.push_back(new C_Gremlin({ a_posX,a_posY }));

	//生成されたインスタンスに敵画像をセット
	m_gremlin.back()->SetEnemyTex(m_gremlinTex);

	//生成されたインスタンスに砂埃画像をセット
	m_gremlin.back()->SetDustTex(&m_dustTex);

	//生成されたインスタンスに音声データをセット
	m_gremlin.back()->SetEnemySfx(m_gremlinSfxInst);

	//全ての敵インスタンス管理用配列に格納
	m_allEnemies.push_back(m_gremlin.back());

	//敵共通スポーン初期化
	SpawnInit();

	//戻り値で生成したインスタンスを返す
	return m_gremlin.back();
}

//センチネルの生成
C_Sentinel* C_EnemyMgr::SpawnSentinel(float a_posX, float a_posY)
{
	//メモリを確保しインスタンスの生成
	m_sentinel.push_back(new C_Sentinel({ a_posX,a_posY }));

	//生成されたインスタンスに敵画像をセット
	m_sentinel.back()->SetEnemyTex(m_sentinelTex);

	//生成されたインスタンスに音声データをセット
	m_sentinel.back()->SetEnemySfx(m_sentinelSfxInst);

	//全ての敵インスタンス管理用配列に格納
	m_allEnemies.push_back(m_sentinel.back());

	//敵共通スポーン初期化
	SpawnInit();

	//戻り値で生成したインスタンスを返す
	return m_sentinel.back();
}

//ボスロボット生成
C_BossRobot* C_EnemyMgr::SpawnBossRobot(float a_posX, float a_posY, bool a_isLittleWitchSummoned)
{
	//魔法少女が召喚していたら
	if (a_isLittleWitchSummoned)
	{
		//弱めのステータスで
		//メモリを確保しインスタンスの生成
		m_bossRobot.push_back(new C_BossRobot({ a_posX,a_posY }, *m_bossRobotStatus[Weak]));
	}
	//魔法少女で無い場合
	else
	{
		//普通のステータスで
		//メモリを確保しインスタンスの生成
		m_bossRobot.push_back(new C_BossRobot({ a_posX,a_posY }, *m_bossRobotStatus[Normal]));
	}

	//生成されたインスタンスに敵画像をセット
	m_bossRobot.back()->SetEnemyTex(m_bossRobotTex);

	//生成されたインスタンスに煙画像をセット
	m_bossRobot.back()->SetSmokeTex(&m_smokeTex);

	//生成されたインスタンスに音声データをセット
	m_bossRobot.back()->SetEnemySfx(m_bossRobotSfxInst);

	//全ての敵インスタンス管理用配列に格納
	m_allEnemies.push_back(m_bossRobot.back());

	//敵共通スポーン初期化
	SpawnInit();

	//戻り値で生成したインスタンスを返す
	return m_bossRobot.back();
}

//スカルの生成
C_Skull* C_EnemyMgr::SpawnSkull(float a_posX, float a_posY, bool a_isLittleWitchSummoned)
{
	//魔法少女が召喚していたら
	if (a_isLittleWitchSummoned)
	{
		//弱めのステータスで
		//メモリを確保しインスタンスの生成
		m_skull.push_back(new C_Skull({ a_posX,a_posY }, *m_skullStatus[Weak]));
	}
	//魔法少女で無い場合
	else
	{
		//普通のステータスで
		//メモリを確保しインスタンスの生成
		m_skull.push_back(new C_Skull({ a_posX,a_posY }, *m_skullStatus[Normal]));
	}

	//生成されたインスタンスに敵画像をセット
	m_skull.back()->SetEnemyTex(m_skullTex);

	//生成されたインスタンスに火のベール画像をセット
	m_skull.back()->SetFireVeilTex(&m_fireVeilTex);

	//生成されたインスタンスに焚火画像をセット
	m_skull.back()->SetBonfireTex(&m_bonfireTex);

	//生成されたインスタンスに混乱画像をセット
	m_skull.back()->SetConfusedTex(&m_confusedTex);

	//生成されたインスタンスに火の玉画像をセット
	m_skull.back()->SetFireballTex(&m_fireballTex);

	//生成されたインスタンスに音声データをセット
	m_skull.back()->SetEnemySfx(m_skullSfxInst);

	//全ての敵インスタンス管理用配列に格納
	m_allEnemies.push_back(m_skull.back());

	//敵共通スポーン初期化
	SpawnInit();

	//戻り値で生成したインスタンスを返す
	return m_skull.back();
}

//魔法少女の生成
C_LittleWitch* C_EnemyMgr::SpawnLittleWitch(float a_posX, float a_posY)
{
	//魔法少女が既にいたらリターン
	if (m_littleWitch != nullptr)
	{
		return nullptr;
	}

	//メモリを確保しインスタンスの生成
	m_littleWitch = new C_LittleWitch({ a_posX,a_posY });

	//生成されたインスタンスに敵画像をセット
	m_littleWitch->SetEnemyTex(m_littleWitchTex);

	//生成されたインスタンスにシールド画像をセット
	m_littleWitch->SetShieldTex(m_shieldTex);

	//生成されたインスタンスに敵スポナー画像をセット
	m_littleWitch->SetEnemySpawnerTex(&m_enemySpawnerTex);

	//生成されたインスタンスに敵スポナーのひび割れ画像をセット
	m_littleWitch->SetEnemySpawnerCrackTex(&m_enemySpawnerCrackTex);

	//全ての敵インスタンス管理用配列に格納
	m_allEnemies.push_back(m_littleWitch);

	//敵共通スポーン初期化
	SpawnInit();

	//戻り値で生成したインスタンスを返す
	return m_littleWitch;
}

//敵共通スポーン初期化
void C_EnemyMgr::SpawnInit()
{
	//生成されたインスタンスに感電エフェクト画像をセット
	m_allEnemies[m_allEnemies.size() - 1]->SetElecShockTex(&m_elecShockTex);

	//生成されたインスタンスに感電サウンドをセット
	m_allEnemies[m_allEnemies.size() - 1]->SetElecShockSfx(&m_elecShockSfxInst);

	//生成されたインスタンスにオーナーをセット
	m_allEnemies[m_allEnemies.size() - 1]->SetOwner(m_mOwner);

	//生成されたインスタンスを初期化
	m_allEnemies[m_allEnemies.size() - 1]->Init();
}

//コインのサウンドを鳴らす
void C_EnemyMgr::PlayCoinSound()
{
	m_coinSfxInst->Play();
}

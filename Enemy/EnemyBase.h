#pragma once
class Scene;
//敵の種類列挙
enum class EnemyType
{
	Robot,
	Frog,
	Ghost,
	Gremlin,
	Sentinel,
	BossRobot,
	Skull,
	LittleWitch
};

//敵の基底クラス
class C_EnemyBase
{
public:

	C_EnemyBase(
		EnemyType a_enemyType,
		int   a_texWidth,
		int   a_texHeight,
		int   a_frameRate,
		int   a_hpMax,
		int   a_attackDamage,
		int   a_hitDamage,
		int   a_attackTexIndex,
		int   a_coinMax,
		int   a_elecShockLimit,
		float a_moveSpeed,
		float a_gravity,
		float a_jumpPower,
		float a_scaleSize,
		float a_attackDis,
		float a_attackHitDis,
		float a_attackRadius,
		float a_trackDist,
		float a_noTrackDist,
		float a_hitWidth,
		float a_hitHeight,
		Math::Color a_defaultColor,
		Math::Color a_damageColor
	);
	C_EnemyBase(const C_EnemyBase& a_enemyData);
	virtual ~C_EnemyBase() = default;
	
	
	virtual void Init() = 0;  //初期化
	virtual void Action(const Math::Vector2 a_playerPos) = 0;//動作
	virtual void Update(const float a_scrollX,const float a_scrollY) = 0;//更新
	virtual void Draw();//描画

	void MapHitX(float a_posX, float a_moveX);			           //マップ当たり判定用 X調整
	virtual void MapHitY(float a_posY, float a_moveY, bool a_jump);//マップ当たり判定用 Y調整


	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 敵共通セッター
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	//オーナーのインスタンスをセット
	void SetOwner(Scene* a_eOwner)             { m_eOwner = a_eOwner; }
	//敵画像セット						   	   
	void SetEnemyTex(KdTexture* a_eTex)        { m_enemyTex = a_eTex; }
	//感電エフェクト画像					      
	void SetElecShockTex(KdTexture* a_sTex)    { m_elecShockTex = a_sTex; }
	//感電音データ								              
	void SetElecShockSfx(std::shared_ptr<KdSoundInstance>* a_eSfx) { m_elecShockSfx = a_eSfx; }
	//敵の音データ
	void SetEnemySfx(std::shared_ptr<KdSoundInstance>* a_eSfx)     { m_enemySfx = a_eSfx; }
	//感電蓄積値のセット					        
	virtual bool SetElecShockGauge(int a_elecShockGauge)
	{
		m_elecShockGauge += a_elecShockGauge;
		return true;
	}
	//感電ヒットフラグ						
	void SetElecShockHit(bool a_isElecShockHit) { m_isElecShockHit = a_isElecShockHit; }
	//コイン
	void SetCoinDropCount(int a_coinDropCount)  { m_coinDropCount = a_coinDropCount; }
	//ダメージのセット						        
	virtual bool SetDamage(int a_damage)
	{
		m_hp -= a_damage;
		m_isDamage = true;
		return true;
	}
	
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 敵共通ゲッター
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	//敵の種類
	const EnemyType GetEnemyType()     const { return m_enemyType; }
	//座標
	const Math::Vector2 GetPos()       const { return m_pos; }
	//未来座標
	const Math::Vector2 GetNextPos()   const { return m_pos + m_move; }
	//攻撃座標
	const Math::Vector2 GetAttackPos() const { return m_attackPos; }
	//存在フラグ
	const bool GetAlive()              const { return m_isAlive; }
	//死亡フラグ
	const bool GetDead()               const { return m_isDead; }
	//感電フラグ						  
	const bool GetElecShock()          const { return m_isElecShock; }
	//感電ヒットフラグ				   
	const bool GetElecShockHit()       const { return m_isElecShockHit; }
	//攻撃判定フラグ				    
	const bool GetAttackHit()          const { return m_isAttackHit; }
	//体力						       
	const int GetHp()                  const { return m_hp; }
	//最大体力						   
	const int GetHpMax()               const { return m_hpMax; }
	//当たったときのダメージ		    
	const int GetHitDamage()           const { return m_hitDamage; }
	//攻撃ダメージ
	const int GetAttackDamage()        const { return m_attackDamage; }
	//感電蓄積値						  
	const int GetElecShockGauge()      const { return m_elecShockGauge; }
	//感電限界値						  
	const int GetElecShockLimit()      const { return m_elecShockLimit; }
	//コイン						    
	const int GetCoinDropCount()       const { return m_coinDropCount; }
	//当たり判定横サイズ				  
	const float GetHitWidth()          const { return m_hitWidth; }
	//当たり判定縦サイズ				  
	const float GetHitHeight()         const { return m_hitHeight; }
	//攻撃範囲
	const float GetAttackRadius()      const { return m_attackRadius; }
	//当たったときの衝撃				  
	const float GetHitKnockForce()     const { return m_hitKnockForce; }

protected://子クラスに継承
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// エフェクト
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	//エフェクト用構造体(横スプライト用)
	struct Effect1
	{
		const int texWidth;   //画像横サイズ
		const int texHeight;  //画像縦サイズ
		const int texNumMax;  //画像枚数
		const int frameRate;  //フレームレート
		int texIndex;         //画像指標
	};
	//エフェクト用構造体(縦横スプライト用)
	struct Effect2
	{
		const int texWidth; //画像横サイズ
		const int texHeight;//画像縦サイズ
		const int rowMax;   //行最大枚数
		const int columnMax;//列最大枚数
		const int texNumMax;//画像枚数
		const int frameRate;//フレームレート
		int row;            //現在の行
		int column;         //現在の列
		int texIndex;       //画像指標
	};

	void EffectUpdate(Effect1* a_effect);
	void EffectUpdate(Effect2* a_effect);

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 敵共通関数
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	//ジャンプ
	bool Jump(float a_jumpPower);

	//ダメージ
	bool Damage();

	//確率チェック
	bool CheckProbability(float a_probability);

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 敵共通ポインタ
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	Scene* m_eOwner;//オーナー用インスタンス
	
	KdTexture* m_nowEnemyTex; //現在の敵画像
	KdTexture* m_enemyTex;    //敵画像保管用
	KdTexture* m_elecShockTex;//感電エフェクト画像
	std::shared_ptr<KdSoundInstance>* m_elecShockSfx;//感電効果音
	std::shared_ptr<KdSoundInstance>* m_enemySfx;//敵の効果音

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 敵共通変数
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	bool  m_isAlive;       //存在フラグ
	bool  m_isDead;        //死亡フラグ
	bool  m_isActive;      //アクティブフラグ
	bool  m_isDamage;      //ダメージフラグ
	bool  m_isElecShock;   //感電フラグ
	bool  m_isElecShockHit;//感電ヒットフラグ
	bool  m_isHitWall;     //壁衝突フラグ
	bool  m_isJump;	       //ジャンプフラグ
	bool  m_isAttack;      //攻撃中フラグ
	bool  m_isAttackHit;   //攻撃判定フラグ
	bool  m_isTracking;    //追跡フラグ
	int   m_hp;		       //体力
	int   m_coinDropCount; //所持コイン枚数
	int   m_elecShockGauge;//感電蓄積値
	int   m_elecShockTime; //感電継続時間
	int   m_texIndex;      //現在スプライトの何枚目の画像か
	int   m_frameCnt;      //フレームカウント用
	float m_texAngle;      //画像の角度(degree)
	float m_shakeX;        //感電による震え

	Math::Vector2 m_pos;        //座標
	Math::Vector2 m_move;       //移動量
	Math::Vector2 m_scale;      //拡大率
	Math::Vector2 m_attackPos;  //攻撃座標
	Math::Color   m_color;      //色

	Math::Matrix m_scaleMat;   //拡大行列
	Math::Matrix m_rotationMat;//回転行列
	Math::Matrix m_transMat;   //移動行列
	Math::Matrix m_mat;		   //合成行列


	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 敵共通定数
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	const EnemyType m_enemyType;     //敵の種類
	const int   m_texWidth;		     //画像1枚横サイズ
	const int   m_texHeight;         //画像1枚縦サイズ
	const int   m_frameRate;         //アニメーションの更新頻度
	const int   m_hpMax;             //最大体力
	const int   m_attackDamage;      //攻撃力
	const int   m_hitDamage;         //当たったときのダメージ
	const int   m_attackTexIndex;    //攻撃判定をする画像
	const int   m_coinMax;           //所持コインの最大
	const int   m_elecShockLimit;    //感電限界値
	const float	m_moveSpeed;         //移動速度
	const float	m_gravity;	         //重力
	const float m_jumpPower;         //ジャンプ力
	const float m_scaleSize;         //拡大率
	const float m_attackDis;         //攻撃可能射程
	const float m_attackHitDis;      //攻撃射程
	const float m_attackRadius;      //攻撃範囲
	const float m_trackDist;         //追跡をする距離
	const float m_noTrackDist;       //追跡をしない距離
	const float m_hitWidth;          //当たり判定横サイズ
	const float m_hitHeight;         //当たり判定縦サイズ
	const Math::Color m_defaultColor;//通常時の色
	const Math::Color m_damageColor; //ダメージをくらったときの色

	const int   m_elecShockTimeMax = 60 * 3;//最大感電時間(3秒)
	const float m_hitKnockForce    = 15.0f; //当たったときの衝撃
	const float m_shakePower       = 2.0f;  //感電による震えの強さ
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 感電画像関連
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	//感電状態の変更
	bool ChangeElecShockState();

	//感電の状態更新
	void UpdateElecShock();
	//感電エフェクト描画
	void DrawElecShock() const;  

	//感電エフェクト構造体
	Effect1 m_elecShock{ 
		512,//画像横サイズ
		512,//画像縦サイズ
		14,	//画像枚数
		2	//フレームレート
	};

	Math::Vector2 m_elecShockScale;   //拡大率
	Math::Matrix  m_elecShockScaleMat;//拡大行列
	Math::Matrix  m_elecShockTransMat;//移動行列
	Math::Matrix  m_elecShockMat;	  //合成行列
};


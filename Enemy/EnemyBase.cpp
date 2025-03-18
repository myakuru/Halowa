#include"EnemyBase.h"
#include "../Scene.h"
#include "../Constants.h"

C_EnemyBase::C_EnemyBase(
	//敵共通定数セット用の引数
	EnemyType a_enemyType,     //m_enemyType     ...敵の種類
	int   a_texWidth, 	       //m_texWidth      ...画像1枚横サイズ
	int   a_texHeight,	       //m_texHeight     ...画像1枚縦サイズ
	int   a_frameRate,         //m_frameRate     ...アニメーションの更新頻度
	int   a_hpMax,             //m_hpMax         ...最大体力
	int   a_attackDamage,      //m_attackDamage  ...攻撃力
	int   a_hitDamage,         //m_hitDamage     ...当たったときのダメージ
	int   a_attackTexIndex,    //m_attackTexIndex...攻撃判定をする画像
	int   a_coinMax,           //m_coinMax       ...所持コインの最大
	int   a_elecShockLimit,    //m_elecShockLimit...感電限界値
	float a_moveSpeed,	       //m_moveSpeed     ...移動速度
	float a_gravity,	       //m_gravity       ...重力
	float a_jumpPower,	       //m_jumpPower     ...ジャンプ力
	float a_scaleSize,	       //m_scaleSize     ...拡大率
	float a_attackDis,	       //m_attackDis     ...攻撃可能射程
	float a_attackHitDis,      //m_attackHitDis  ...攻撃射程
	float a_attackRadius,      //m_attackRadius  ...攻撃範囲
	float a_trackDist,	       //m_trackDist     ...追跡をする距離
	float a_noTrackDist,       //m_noTrackDist   ...追跡をしない距離
	float a_hitWidth,          //m_hitWidth      ...当たり判定横サイズ
	float a_hitHeight,         //m_hitHeight     ...当たり判定縦サイズ
	Math::Color a_defaultColor,//m_defaultColor  ...通常時の色
	Math::Color a_damageColor  //m_damageColor   ...ダメージをくらったときの色
) : 
	//ポインター初期化
	m_eOwner(nullptr),
	m_nowEnemyTex(nullptr),
	m_enemyTex(nullptr),
	m_elecShockTex(nullptr),
	m_elecShockSfx(nullptr),
	m_enemySfx(nullptr),
	//敵共通定数セット
	m_enemyType(a_enemyType),          //敵の種類
	m_texWidth(a_texWidth),		       //画像1枚横サイズ
	m_texHeight(a_texHeight),	       //画像1枚縦サイズ
	m_frameRate(a_frameRate),          //アニメーションの更新頻度
	m_hpMax(a_hpMax),                  //最大体力
	m_attackDamage(a_attackDamage),    //攻撃力
	m_hitDamage(a_hitDamage),          //当たったときのダメージ
	m_attackTexIndex(a_attackTexIndex),//攻撃判定をする画像
	m_coinMax(a_coinMax),              //所持コインの最大
	m_elecShockLimit(a_elecShockLimit),//感電限界値
	m_moveSpeed(a_moveSpeed),	       //移動速度
	m_gravity(a_gravity),		       //重力
	m_jumpPower(a_jumpPower),	       //ジャンプ力
	m_scaleSize(a_scaleSize),	       //拡大率
	m_attackDis(a_attackDis),          //攻撃可能射程
	m_attackHitDis(a_attackHitDis),    //攻撃射程
	m_attackRadius(a_attackRadius),    //攻撃範囲
	m_trackDist(a_trackDist),	       //追跡をする距離
	m_noTrackDist(a_noTrackDist),      //追跡をしない距離
	m_hitWidth(a_hitWidth),            //当たり判定横サイズ
	m_hitHeight(a_hitHeight),          //当たり判定縦サイズ
	m_defaultColor(a_defaultColor),    //通常時の色
	m_damageColor(a_damageColor)       //ダメージをくらったときの色
{
	//敵共通変数の初期化
	m_isAlive        = true;     //存在フラグ
	m_isDead         = false;    //死亡フラグ
	m_isActive       = false;    //アクティブフラグ
	m_isDamage       = false;    //ダメージフラグ
	m_isElecShock    = false;    //感電フラグ
	m_isElecShockHit = false;    //感電ヒットフラグ
	m_isHitWall      = false;    //ジャンプフラグ
	m_isJump         = false;    //行き止まりフラグ
	m_isAttack       = false;    //攻撃中フラグ
	m_isAttackHit    = false;    //攻撃判定フラグ
	m_isTracking     = false;    //追跡フラグ
	m_hp             = m_hpMax;  //体力
	m_coinDropCount  = m_coinMax;//所持コイン枚数
	m_elecShockGauge = 0;	     //感電蓄積値
	m_elecShockTime  = 0;        //感電継続時間
	m_texIndex       = 0;	     //現在スプライトの何枚目の画像か
	m_frameCnt       = 0;	     //アニメーションフレームカウント用
	m_texAngle       = 0.0f;     //画像の角度(degree)
	m_shakeX         = 0.0f;     //感電による震え
	m_move  = { 0,0 };					  //移動量
	m_scale = { m_scaleSize,m_scaleSize };//拡大率
	m_color = m_defaultColor;    //色

	//感電エフェクト用変数初期化
	m_elecShock.texIndex = 0;//現在スプライトの何枚目の画像か

	//敵のサイズに合わせて拡大率計算し、それに補正値をプラス
	const float scaleX = (m_texWidth * m_scale.x) / m_elecShock.texWidth + 0.5f;
	const float scaleY = (m_texHeight * m_scale.y) / m_elecShock.texHeight + 0.5f;
	m_elecShockScale = { scaleX,scaleY };//拡大率
}

C_EnemyBase::C_EnemyBase(const C_EnemyBase& a_enemyData) : 
	//ポインター初期化
	m_eOwner(nullptr),
	m_nowEnemyTex(nullptr),
	m_enemyTex(nullptr),
	m_elecShockTex(nullptr),
	m_elecShockSfx(nullptr),
	m_enemySfx(nullptr),
	//敵共通定数セット
	m_enemyType(a_enemyData.m_enemyType),          //敵の種類
	m_texWidth(a_enemyData.m_texWidth),		       //画像1枚横サイズ
	m_texHeight(a_enemyData.m_texHeight),	       //画像1枚縦サイズ
	m_frameRate(a_enemyData.m_frameRate),          //アニメーションの更新頻度
	m_hpMax(a_enemyData.m_hpMax),                  //最大体力
	m_attackDamage(a_enemyData.m_attackDamage),    //攻撃力
	m_hitDamage(a_enemyData.m_hitDamage),          //当たったときのダメージ
	m_attackTexIndex(a_enemyData.m_attackTexIndex),//攻撃判定をする画像
	m_coinMax(a_enemyData.m_coinMax),              //所持コインの最大
	m_elecShockLimit(a_enemyData.m_elecShockLimit),//感電限界値
	m_moveSpeed(a_enemyData.m_moveSpeed),	       //移動速度
	m_gravity(a_enemyData.m_gravity),		       //重力
	m_jumpPower(a_enemyData.m_jumpPower),	       //ジャンプ力
	m_scaleSize(a_enemyData.m_scaleSize),	       //拡大率
	m_attackDis(a_enemyData.m_attackDis),          //攻撃可能射程
	m_attackHitDis(a_enemyData.m_attackHitDis),    //攻撃射程
	m_attackRadius(a_enemyData.m_attackRadius),    //攻撃範囲
	m_trackDist(a_enemyData.m_trackDist),	       //追跡をする距離
	m_noTrackDist(a_enemyData.m_noTrackDist),      //追跡をしない距離
	m_hitWidth(a_enemyData.m_hitWidth),            //当たり判定横サイズ
	m_hitHeight(a_enemyData.m_hitHeight),          //当たり判定縦サイズ
	m_defaultColor(a_enemyData.m_defaultColor),    //通常時の色
	m_damageColor(a_enemyData.m_damageColor)       //ダメージをくらったときの色
{
	//敵共通変数の初期化
	m_isAlive = true;     //存在フラグ
	m_isDead = false;    //死亡フラグ
	m_isActive = false;    //アクティブフラグ
	m_isDamage = false;    //ダメージフラグ
	m_isElecShock = false;    //感電フラグ
	m_isElecShockHit = false;    //感電ヒットフラグ
	m_isHitWall = false;    //ジャンプフラグ
	m_isJump = false;    //行き止まりフラグ
	m_isAttack = false;    //攻撃中フラグ
	m_isAttackHit = false;    //攻撃判定フラグ
	m_isTracking = false;    //追跡フラグ
	m_hp = m_hpMax;  //体力
	m_coinDropCount = m_coinMax;//所持コイン枚数
	m_elecShockGauge = 0;	     //感電蓄積値
	m_elecShockTime = 0;        //感電継続時間
	m_texIndex = 0;	     //現在スプライトの何枚目の画像か
	m_frameCnt = 0;	     //アニメーションフレームカウント用
	m_texAngle = 0.0f;     //画像の角度(degree)
	m_shakeX = 0.0f;     //感電による震え
	m_move = { 0,0 };					  //移動量
	m_scale = { m_scaleSize,m_scaleSize };//拡大率
	m_color = m_defaultColor;    //色

	//感電エフェクト用変数初期化
	m_elecShock.texIndex = 0;//現在スプライトの何枚目の画像か

	//敵のサイズに合わせて拡大率計算し、それに補正値をプラス
	const float scaleX = (m_texWidth * m_scale.x) / m_elecShock.texWidth + 0.5f;
	const float scaleY = (m_texHeight * m_scale.y) / m_elecShock.texHeight + 0.5f;
	m_elecShockScale = { scaleX,scaleY };//拡大率
}

//感電状態の変更
bool C_EnemyBase::ChangeElecShockState()
{
	//感電蓄積値が感電限界値を以上なら
	//感電フラグがOFFなら
	if (m_elecShockGauge >= m_elecShockLimit && !m_isElecShock)
	{
		//画像を初期位置に戻す
		m_elecShock.texIndex = 0;

		//感電最大時間を感電継続時間にセット
		m_elecShockTime = m_elecShockTimeMax;

		//感電フラグをON
		m_isElecShock = true;

		return true;
	}

	//感電フラグがONかつ感電継続時間が0以下になったら
	if (m_elecShockTime <= 0 && m_isElecShock)
	{
		//感電蓄積値をリセット
		m_elecShockGauge = 0;

		//感電音を止める
		(*m_elecShockSfx)->Stop();

		//感電フラグをOFF
		m_isElecShock = false;
	}
	return false;
}

//感電状態の更新
void C_EnemyBase::UpdateElecShock()
{
	//感電継続時間を減らす
	if (m_elecShockTime > 0)
	{
		m_elecShockTime--;
	}

	//感電状態であれば
	if (m_isElecShock)
	{
		//感電効果音がなっていなかったら
		if ((*m_elecShockSfx)->IsPlay() == false)
		{
			//感電音再生
			(*m_elecShockSfx)->Play();
		}
		
		//感電エフェクトの更新
		EffectUpdate(&m_elecShock);
	}

	//感電状態であれば敵を震えさせる
	if (m_isElecShock)
	{
		m_shakeX = m_shakeX < 0 ? m_shakePower : -m_shakePower;
	}
	else
	{
		m_shakeX = 0;
	}

	//スクロールの値を取得
	const float scrollX = m_eOwner->GetMap()->GetScrollX();
	const float scrollY = m_eOwner->GetMap()->GetScrollY();

	m_elecShockScaleMat = Math::Matrix::CreateScale(m_elecShockScale.x, m_elecShockScale.y, 0);//拡大行列の作成
	m_elecShockTransMat = Math::Matrix::CreateTranslation(m_pos.x - scrollX, m_pos.y - scrollY, 0);//移動行列の作成
	m_elecShockMat = m_elecShockScaleMat * m_elecShockTransMat;//敵の移動行列を使用した行列合成
}

//感電エフェクト描画
void C_EnemyBase::DrawElecShock() const
{
	//感電状態でなければリターン
	if (!m_isElecShock)return;

	//m_elecShock.texIndexで指定された位置を切取
	const Math::Rectangle shockRect = { m_elecShock.texWidth * m_elecShock.texIndex,0,m_elecShock.texWidth,m_elecShock.texHeight };

	//行列をセット
	SHADER.m_spriteShader.SetMatrix(m_elecShockMat);

	//描画
	SHADER.m_spriteShader.DrawTex(m_elecShockTex, 0, 0, &shockRect, &Math::Color{ 1,1,1,1 });
}

//描画
void C_EnemyBase::Draw()
{
	//生きていなかったらリターン
	if (!m_isAlive) return;

	//m_texIndexで指定された位置を切取
	const Math::Rectangle enemyRect = { m_texWidth * m_texIndex,0,m_texWidth,m_texHeight };

	//行列をセット
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//描画
	SHADER.m_spriteShader.DrawTex(m_nowEnemyTex, 0, 0, &enemyRect, &m_color);

	//体力が無かったら感電画像を描画しない
	if (m_hp <= 0)return;

	//感電エフェクト描画
	DrawElecShock();
	


	//仮
	//スクロールの値を取得
	//const float scrollX = m_eOwner->GetMap()->GetScrollX();
	//const float scrollY = m_eOwner->GetMap()->GetScrollY();
	//Math::Matrix mat = Math::Matrix::CreateTranslation(m_pos.x - scrollX, m_pos.y - scrollY, 0);
	//SHADER.m_spriteShader.SetMatrix(mat);
	//SHADER.m_spriteShader.DrawCircle(0, 0, (int)m_hitWidth, &Math::Color{ 1,0,0,0.5f });
	//SHADER.m_spriteShader.DrawCircle(0, 0, 5, &Math::Color{ 0,0,1,0.5f });
}

//マップ当たり判定用 X調整
void C_EnemyBase::MapHitX(float a_posX, float a_moveX)
{
	m_pos.x     = a_posX;
	m_move.x    = a_moveX;
	m_isHitWall = true;
}

//マップ当たり判定用 Y調整
void C_EnemyBase::MapHitY(float a_posY, float a_moveY, bool a_jump)
{
	m_pos.y  = a_posY;
	m_move.y = a_moveY;
	m_isJump = a_jump;
}

//Effect1構造体の更新
void C_EnemyBase::EffectUpdate(Effect1* a_effect)
{
	//フレームレートに合わせてアニメーションを更新
	if (m_frameCnt % a_effect->frameRate == 0)
	{
		//画像を進める
		a_effect->texIndex++;

		//最後の画像まで行ったら初期値に戻す
		if (a_effect->texIndex >= a_effect->texNumMax)
		{
			a_effect->texIndex = 0;
		}
	}
}

//Effect2構造体の更新
void C_EnemyBase::EffectUpdate(Effect2* a_effect)
{
	//フレームレートに合わせてアニメーションを更新
	if (m_frameCnt % a_effect->frameRate == 0)
	{
		//画像を進める
		a_effect->texIndex++;

		//画像が最後までいったら
		if (a_effect->texIndex >= a_effect->texNumMax)
		{
			//画像を初期画像に戻す
			a_effect->texIndex = 0;
		}
		a_effect->row = a_effect->texIndex / a_effect->rowMax;//行数を取得
		a_effect->column = a_effect->texIndex % a_effect->columnMax;//列数を取得
	}
}

//ジャンプ処理
bool C_EnemyBase::Jump(float a_jumpPower)
{
	//ジャンプをしていなかったら
	if (!m_isJump)
	{
		//ジャンプ前の攻撃フラグをOFF
		//m_isAttack = false;

		//ジャンプ
		m_move.y = a_jumpPower;
		m_isJump = true;

		return true;
	}
	return false;
}

//ダメージ処理
bool C_EnemyBase::Damage()
{
	//ダメージフラグがONなら
	if (m_isDamage)
	{
		//敵画像を赤色にする
		m_color = m_damageColor;
		m_isDamage = false;
		return true;
	}
	else
	{
		//元の色に戻していく
		if (m_color.R() < m_defaultColor.R())
		{
			m_color.R(m_color.R() + 0.05f);
		}
		if (m_color.G() < m_defaultColor.G())
		{
			m_color.G(m_color.G() + 0.05f);
		}
		if (m_color.B() < m_defaultColor.B())
		{
			m_color.B(m_color.B() + 0.05f);
		}
		if (m_color.A() < m_defaultColor.A())
		{
			m_color.A(m_color.A() + 0.05f);
		}
		return false;
	}
}

//確率チェック
bool C_EnemyBase::CheckProbability(float a_probability)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	//1～100の乱数
	static std::uniform_real_distribution<> dist(0.0f, 100.0f);

	//指定された確率が生成した乱数よりも大きかったら
	if (a_probability > dist(gen))
	{
		return true;
	}
	return false;
}

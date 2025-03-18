#include "Frog.h"
#include "../../../Scene.h"
#include "../../../Constants.h"

C_Frog::C_Frog(Math::Vector2 a_pos) :
	C_EnemyBase(
		//定数初期値セット
		EnemyType::Frog, //m_enemyType      ...敵の種類
		283,   //m_texWidth      ...画像1枚横サイズ
		192,   //m_texHeight     ...画像1枚縦サイズ
		7,     //m_frameRate     ...アニメーションの更新頻度
		25,    //m_hpMax         ...最大体力
		0,     //m_attackDamage  ...攻撃力
		100,   //m_hitDamage     ...当たったときのダメージ
		3,     //m_attackTexIndex...攻撃判定をする画像
		5,     //m_coinMax       ...所持コインの最大
		30,     //m_elecShockLimit...感電限界値
		1.5f,  //m_moveSpeed     ...移動速度
		1.0f,  //m_gravity       ...重力
		12.0f, //m_jumpPower     ...ジャンプ力
		0.5f,  //m_scaleSize     ...拡大率
		500.0f,//m_attackRange   ...攻撃可能射程
		0,     //m_attackHitDis  ...攻撃射程
		0,     //m_attackRadius  ...攻撃範囲
		50.0f, //m_trackDist     ...追跡をする距離
		20.0f, //m_noTrackDist   ...追跡をしない距離
		192.0f * 0.5f / 2,//m_hitWidth   ...当たり判定横サイズ
		183.0f * 0.5f / 2,//m_hitHeight  ...当たり判定縦サイズ
		{ 1,1,1,1 },//m_defaultColor...通常時の色
		{ 1, 0, 0, 0.5f }    //m_damageColor...ダメージをくらったときの色
	)
{
	//固有変数の初期化
	m_pos = a_pos;  //座標
	m_nowAnim = IdleAnim;//現在のアニメーション
	m_spell = nullptr;
	m_spellTex = nullptr;
	m_isSpellActive = false;
}

C_Frog::~C_Frog()
{
	//メモリを解放
	if (m_spell != nullptr)
	{
		delete m_spell;
	}
}

//初期化
void C_Frog::Init()
{
	//画像セット
	m_nowEnemyTex = m_enemyTex + m_nowAnim;
}

//動作
void C_Frog::Action(const Math::Vector2 a_playerPos)
{
	//存在していなかったらリターン
	if (!m_isAlive) return;

	//魔法の動作
	if (m_spell != nullptr)
	{
		m_spell->Action(a_playerPos);
	}

	//移動量初期化
	m_move.x = 0;

	//重力
	m_move.y -= m_gravity;

	//1フレームを進める
	if (m_frameCnt < INT_MAX)
	{
		m_frameCnt++;
	}
	else
	{
		m_frameCnt = 0;
	}

	//体力が0以下なら死亡フラグをON
	if (m_hp <= 0)
	{
		m_eOwner->GetEffectManager()->SetBurstFlogEffect(m_pos.x, m_pos.y, true);
		m_isDead = true;
	}

	//死亡フラグがONなら
	if (m_isDead)
	{
		//死亡音
		(*(m_enemySfx + DeathSfx))->Play();

		//死亡アニメーション
		AnimationUpdate(DeathAnim);
		return;
	}

	//ダメージ処理
	Damage();

	//感電状態のセット
	ChangeElecShockState();

	//感電状態の更新
	UpdateElecShock();

	//感電状態であればリターン
	if (m_isElecShock)return;

	//スクロールの値を取得
	const float scrollX = m_eOwner->GetMap()->GetScrollX();
	const float scrollY = m_eOwner->GetMap()->GetScrollY();

	//画面内にいる場合はアクションフラグをON
	if (m_pos.x - m_hitWidth - scrollX < SCREEN_RIGHT &&
		m_pos.x + m_hitWidth - scrollX > SCREEN_LEFT &&
		m_pos.y - m_hitHeight - scrollY < SCREEN_TOP &&
		m_pos.y + m_hitHeight - scrollY > SCREEN_BOTTOM)
	{
		m_isActive = true;
	}

	//アクションフラグがOFF
	//または攻撃フラグがOFFの時に魔法アクティブフラグがONならリターン
	if (!m_isActive || !m_isAttack && m_isSpellActive)
	{
		m_scale.x = m_pos.x > a_playerPos.x ? m_scaleSize : -m_scaleSize;//プレイヤーの方向を向かせる
		AnimationUpdate(IdleAnim);
		return;
	}

	//ロボットとプレイヤーの距離の計算
	const float a = m_pos.x - a_playerPos.x;//底辺a
	const float b = m_pos.y - a_playerPos.y;//高さb
	const float c = sqrt(a * a + b * b);  //斜辺(距離)c

	//攻撃可能射程に入った又は攻撃フラグが立っている時
	if (c <= m_attackDis || m_isAttack)
	{
		m_isAttack = true;//攻撃フラグをON
		AnimationUpdate(AttackAnim);//攻撃アニメーション

		//攻撃をする画像になったら
		if (m_texIndex == m_attackTexIndex)
		{
			//魔法発生
			EmitSpell(a_playerPos);
		}
		return;
	}

	

	//立ち姿
	AnimationUpdate(IdleAnim);
}

//更新
void C_Frog::Update(const float a_scrollX, const float a_scrollY)
{
	//存在していなかったらリターン
	if (!m_isAlive) return;

	//魔法の更新
	if (m_spell != nullptr)
	{
		m_spell->Update(a_scrollX, a_scrollY);

		//魔法が消えたら
		if (!m_spell->GetAlive())
		{
			//メモリを解放
			delete m_spell;

			//ポインタの中のアドレスを消去
			m_spell = nullptr;

			//魔法アクティブフラグをOFF
			m_isSpellActive = false;
		}
	}

	//座標確定
	m_pos += m_move;

	//行列作成
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);     //拡大行列の作成
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x + m_shakeX - a_scrollX, m_pos.y - a_scrollY, 0);//移動行列の作成
	m_mat = m_scaleMat * m_transMat;//行列の合成
}

//描画
void C_Frog::Draw()
{
	//魔法の描画
	if (m_spell != nullptr)
	{
		m_spell->Draw();
	}

	//敵の描画
	C_EnemyBase::Draw();
}

//アニメーション更新
void C_Frog::AnimationUpdate(AnimationType a_animation)
{
	//別のアニメーションを行おうとしている場合
	if (m_nowAnim != a_animation)
	{
		//画像の切取位置を初期値に戻す
		m_texIndex = 0;

		//指定されたアニメーションを設定
		m_nowAnim = a_animation;

		//画像をセット
		m_nowEnemyTex = m_enemyTex + m_nowAnim;
		return;
	}

	//2フレームに1回アニメーションを更新
	if (m_frameCnt % m_frameRate == 0)
	{
		m_texIndex++;//画像の切取位置を進める
		switch (m_nowAnim)
		{
		case IdleAnim:
			//アニメーションをループ
			if (m_texIndex >= m_idleMax)m_texIndex = 0;
			break;
		case AttackAnim:
			//最後の画像まで行ったら
			if (m_texIndex >= m_attackMax)
			{
				m_texIndex = 0;//画像の切取位置を初期値に戻す
				m_isAttack = false;//攻撃フラグをOFF
			}
			break;
		case DeathAnim:
			//最後の画像まで行ったら存在フラグをOFFにする
			if (m_texIndex >= m_deathMax)m_isAlive = false;
			break;
		default:
			break;
		}
	}
}

void C_Frog::EmitSpell(Math::Vector2 a_targetPos)
{
	//ポインタにまだデータが入っていたらリターン
	if (m_spell != nullptr) return;

	//発射音
	(*(m_enemySfx + ShotSfx))->Play();

	//魔法アクティブフラグをON
	m_isSpellActive = true;

	//メモリを確保しインスタンスの生成
	m_spell = new C_Spell(m_pos, a_targetPos);

	//生成されたインスタンスに煙画像をセット
	m_spell->SetTex(m_spellTex);
}
#include "EnemySpawner.h"
#include "../../EnemyBase.h"
#include "../../../Scene.h"

C_EnemySpawner::C_EnemySpawner(EnemyType a_enemyType, Math::Vector2 a_pos) : m_tex(nullptr), m_crackTex(nullptr), m_eOwner(nullptr)
{
	m_pos = a_pos;
	m_texIndex = 0;
	m_frameCnt = 0;
	m_spawnEnemyType = a_enemyType;
	m_isSpawnCompleted = false;
	m_isAlive = true;
	m_durability = m_durabilityMax;
	m_summonWaitTime = m_summonWaitTimeMax;
	m_color = { 1,1,1,1 };
}

void C_EnemySpawner::Update(const float a_scrollX, const float a_scrollY)
{
	//耐久力がなければ
	if (m_durability <= 0)
	{
		m_isAlive = false;

		//死亡エフェクト
		m_eOwner->GetEffectManager()->SetBossDeathEffect(m_pos.x, m_pos.y, true);
	}

	//存在フラグがなければリターン
	if (!m_isAlive)return;

	//1フレームを進める
	if (m_frameCnt < INT_MAX)
	{
		m_frameCnt++;
	}
	else
	{
		m_frameCnt = 0;
	}

	//召喚までの時間が残っていたら
	if (m_summonWaitTime > 0)
	{
		m_summonWaitTime--;
	}

	//召喚までの時間が無くなったら
	if (m_summonWaitTime <= 0)
	{
		C_EnemyMgr* enemyMgr = m_eOwner->GetEnemyMgr();

		//指定された敵を召喚
		switch (m_spawnEnemyType)
		{
		case EnemyType::Robot:
			enemyMgr->SpawnRobot(m_pos.x, m_pos.y);
			break;
		case EnemyType::Frog:
			enemyMgr->SpawnFrog(m_pos.x, m_pos.y);
			break;
		case EnemyType::Ghost:
			enemyMgr->SpawnGhost(m_pos.x, m_pos.y);
			break;
		case EnemyType::Gremlin:
			enemyMgr->SpawnGremlin(m_pos.x, m_pos.y);
			break;
		case EnemyType::BossRobot:
			enemyMgr->SpawnBossRobot(m_pos.x, m_pos.y + 50, true);
			break;
		case EnemyType::Skull:
			enemyMgr->SpawnSkull(m_pos.x, m_pos.y + 50, true);
			break;
		default:
			break;
		}

		//存在フラグをOFF
		m_isAlive = false;

		//死亡エフェクト
		m_eOwner->GetEffectManager()->SetExplosionEffect(m_pos.x, m_pos.y, true);
		return;
	}
	
	//アニメーション更新
	//アニメーション更新頻度に合わせて
	if (m_frameCnt % m_animFrameRate == 0)
	{
		//画像を進める
		m_texIndex++;
		if (m_texIndex >= m_texNumMax)
		{
			m_texIndex = 0;
		}
	}

	//sinカーブ
	static int sinAngle = 0;
	int angleStep;
	float sinValue;

	//召喚までの時間が短ければ点滅を早める
	angleStep = ((float)m_summonWaitTimeMax / m_summonWaitTime) * 10;

	sinAngle += angleStep;
	if (sinAngle >= 360)
	{
		sinAngle -= 360;
	}

	//sin値を代入
	sinValue = fabsf(sin(ToRadians(sinAngle)));

	sinValue += 0.1f;

	//値をセット
	m_color.R(sinValue);
	m_color.B(sinValue);

	////赤色
	//if (m_frameCnt % m_summonWaitTime == 0)//÷0でエラー
	//{
	//	m_color.G(0);
	//	m_color.B(0);
	//}
	//
	////色を戻していく
	//if (m_color.G() < 1.0f)
	//{
	//	m_color.G(m_color.G() + 0.05f);
	//}
	//if (m_color.B() < 1.0f)
	//{
	//	m_color.B(m_color.B() + 0.05f);
	//}


	//行列作成
	m_scaleMat = Math::Matrix::CreateScale(m_scaleSize, m_scaleSize, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - a_scrollX, m_pos.y - a_scrollY, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_EnemySpawner::Draw()
{
	//存在フラグがなければリターン
	if (!m_isAlive)return;

	Math::Rectangle rect = { m_texWidth * m_texIndex,0,m_texWidth, m_texHeight };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, 0, 0, &rect, &m_color);

	int crackTexIndex = m_durabilityMax - m_durability;
	Math::Rectangle crackRect = { m_texWidth * crackTexIndex,m_texHeight,m_texWidth, m_texHeight };
	SHADER.m_spriteShader.DrawTex(m_crackTex, crackRect);
}

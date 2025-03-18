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
	//�ϋv�͂��Ȃ����
	if (m_durability <= 0)
	{
		m_isAlive = false;

		//���S�G�t�F�N�g
		m_eOwner->GetEffectManager()->SetBossDeathEffect(m_pos.x, m_pos.y, true);
	}

	//���݃t���O���Ȃ���΃��^�[��
	if (!m_isAlive)return;

	//1�t���[����i�߂�
	if (m_frameCnt < INT_MAX)
	{
		m_frameCnt++;
	}
	else
	{
		m_frameCnt = 0;
	}

	//�����܂ł̎��Ԃ��c���Ă�����
	if (m_summonWaitTime > 0)
	{
		m_summonWaitTime--;
	}

	//�����܂ł̎��Ԃ������Ȃ�����
	if (m_summonWaitTime <= 0)
	{
		C_EnemyMgr* enemyMgr = m_eOwner->GetEnemyMgr();

		//�w�肳�ꂽ�G������
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

		//���݃t���O��OFF
		m_isAlive = false;

		//���S�G�t�F�N�g
		m_eOwner->GetEffectManager()->SetExplosionEffect(m_pos.x, m_pos.y, true);
		return;
	}
	
	//�A�j���[�V�����X�V
	//�A�j���[�V�����X�V�p�x�ɍ��킹��
	if (m_frameCnt % m_animFrameRate == 0)
	{
		//�摜��i�߂�
		m_texIndex++;
		if (m_texIndex >= m_texNumMax)
		{
			m_texIndex = 0;
		}
	}

	//sin�J�[�u
	static int sinAngle = 0;
	int angleStep;
	float sinValue;

	//�����܂ł̎��Ԃ��Z����Γ_�ł𑁂߂�
	angleStep = ((float)m_summonWaitTimeMax / m_summonWaitTime) * 10;

	sinAngle += angleStep;
	if (sinAngle >= 360)
	{
		sinAngle -= 360;
	}

	//sin�l����
	sinValue = fabsf(sin(ToRadians(sinAngle)));

	sinValue += 0.1f;

	//�l���Z�b�g
	m_color.R(sinValue);
	m_color.B(sinValue);

	////�ԐF
	//if (m_frameCnt % m_summonWaitTime == 0)//��0�ŃG���[
	//{
	//	m_color.G(0);
	//	m_color.B(0);
	//}
	//
	////�F��߂��Ă���
	//if (m_color.G() < 1.0f)
	//{
	//	m_color.G(m_color.G() + 0.05f);
	//}
	//if (m_color.B() < 1.0f)
	//{
	//	m_color.B(m_color.B() + 0.05f);
	//}


	//�s��쐬
	m_scaleMat = Math::Matrix::CreateScale(m_scaleSize, m_scaleSize, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - a_scrollX, m_pos.y - a_scrollY, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_EnemySpawner::Draw()
{
	//���݃t���O���Ȃ���΃��^�[��
	if (!m_isAlive)return;

	Math::Rectangle rect = { m_texWidth * m_texIndex,0,m_texWidth, m_texHeight };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, 0, 0, &rect, &m_color);

	int crackTexIndex = m_durabilityMax - m_durability;
	Math::Rectangle crackRect = { m_texWidth * crackTexIndex,m_texHeight,m_texWidth, m_texHeight };
	SHADER.m_spriteShader.DrawTex(m_crackTex, crackRect);
}

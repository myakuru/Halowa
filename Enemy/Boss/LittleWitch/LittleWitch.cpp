#include "LittleWitch.h"
#include "../../../Scene.h"
#include "../../../Constants.h"

C_LittleWitch::C_LittleWitch(Math::Vector2 a_pos) : m_shieldTex(nullptr),
	C_EnemyBase(
		//�萔�����l�Z�b�g
		EnemyType::LittleWitch,//m_enemyType     ...�G�̎��
		258,     //m_texWidth      ...�摜1�����T�C�Y
		260,     //m_texHeight     ...�摜1���c�T�C�Y
		7,//10,       //m_frameRate     ...�A�j���[�V�����̍X�V�p�x
		20,      //m_hpMax         ...�ő�̗�
		200,     //m_attackDamage  ...�U����
		100,     //m_hitDamage     ...���������Ƃ��̃_���[�W
		2,       //m_attackTexIndex...�U�����������摜
		5,       //m_coinMax       ...�����R�C���̍ő�
		30,      //m_elecShockLimit...���d���E�l
		1.5f,    //m_moveSpeed     ...�ړ����x
		0.4f,    //m_gravity       ...�d��
		16.0f,   //m_jumpPower     ...�W�����v��
		0.5f,    //m_scaleSize     ...�g�嗦
		100.0f,  //m_attackDis     ...�U���\�˒�
		60,      //m_attackHitDis  ...�U���˒�
		60,      //m_attackRadius  ...�U���͈�
		50.0f,   //m_trackDist     ...�ǐՂ����鋗��
		20.0f,   //m_noTrackDist   ...�ǐՂ����Ȃ�����
		55.0f,   //m_hitWidth      ...�����蔻�艡�T�C�Y
		55.0f,   //m_hitHeight     ...�����蔻��c�T�C�Y
		{ 1,1,1,1 },//m_defaultColor...�ʏ펞�̐F
		{ 1,0,0,1 } //m_damageColor ...�_���[�W����������Ƃ��̐F
	)
{
	//�ŗL�ϐ��̏�����
	m_pos = a_pos;  //���W
	m_scale.x = -m_scaleSize;
	m_nowAnim = WalkAnim;//���݂̃A�j���[�V����
	m_isCastingSpell = true;
	m_isShieldActive = true;
	m_isShieldDamaged = false;
	m_isSurprised = false;
	m_isLanded = false;
	m_nowShieldState = ShieldState::ON;
	m_shieldDurability = m_shieldDurabilityMax;
	m_enemySpawner = nullptr;
	m_enemySpawnerTex = nullptr;
	m_enemySpawnerCrackTex = nullptr;
	m_shieldColor = { 1,1,1,1 };
	m_isHitWall = true;
}

C_LittleWitch::~C_LittleWitch()
{
	if (m_enemySpawner != nullptr)
	{
		delete m_enemySpawner;
	}
}

//������
void C_LittleWitch::Init()
{
	//�摜�Z�b�g
	m_nowEnemyTex = m_enemyTex + m_nowAnim;
}

//����
void C_LittleWitch::Action(const Math::Vector2 a_playerPos)
{
	//���݂��Ă��Ȃ������烊�^�[��
	if (!m_isAlive) return;


	//�ړ��ʏ�����
	m_move.x = 0;

	//�d��
	m_move.y -= m_gravity;

	//1�t���[����i�߂�
	if (m_frameCnt < INT_MAX)
	{
		m_frameCnt++;
	}
	else
	{
		m_frameCnt = 0;
	}

	//�̗͂�0�ȉ��Ȃ玀�S�t���O��ON�ɂ��Ĕ���
	if (m_hp <= 0 && !m_isDead)
	{
		m_isShieldActive = false;
		m_isDead = true;

		//���S�G�t�F�N�g
		m_eOwner->GetEffectManager()->SetBossDeathEffect(m_pos.x, m_pos.y, true);
	}

	//���S�t���O��ON�Ȃ�
	if (m_isDead)
	{
		AnimationUpdate(DeathAnim);//���S�A�j���[�V����
		return;
	}

	//�_���[�W����
	Damage();

	//���d��Ԃ̃Z�b�g
	ChangeElecShockState();

	//���d��Ԃ̍X�V
	UpdateElecShock();

	//���d��Ԃł���΃��^�[��
	if (m_isElecShock)return;

	////�X�N���[���̒l���擾
	//const float scrollX = m_eOwner->GetMap()->GetScrollX();
	//const float scrollY = m_eOwner->GetMap()->GetScrollY();

	////��ʓ��ɂ���ꍇ�̓A�N�V�����t���O��ON
	//if (m_pos.x - m_hitWidth - scrollX < SCREEN_RIGHT &&
	//	m_pos.x + m_hitWidth - scrollX > SCREEN_LEFT &&
	//	m_pos.y - m_hitHeight - scrollY < SCREEN_TOP &&
	//	m_pos.y + m_hitHeight - scrollY > SCREEN_BOTTOM)
	//{
	//	//m_isActive = true;
	//}

	//�����t���O��ON�Ȃ�
	if (m_isSurprised)
	{
		//�����A�j���[�V����
		AnimationUpdate(SurprisedAnim);
		return;
	}

	//�A�N�e�B�u�t���O��OFF�Ȃ烊�^�[��
	if (!m_isActive)
	{
		AnimationUpdate(IdleAnim);
		return;
	}

	//�ǂɂԂ����Ă�����W�����v
	if (m_isHitWall)
	{
		//�W�����v
		Jump(m_jumpPower);
		m_isHitWall = false;
	}

	//�G�X�|�i�[�����݂��Ă��Ȃ�������
	if (m_enemySpawner == nullptr)
	{
		//���@�r���t���OON
		m_isCastingSpell = true;
	}

	//���n�t���O��ON�Ȃ�
	if (m_isLanded)
	{
		AnimationUpdate(LandAnim);
		return;
	}

	//�W�����v�t���O��ON�Ȃ�
	if (m_isJump)
	{
		//Y�̈ړ��ʂ����̒l�Ȃ�
		if (m_move.y > 0)
		{
			//�W�����v
			AnimationUpdate(JumpAnim);
		}
		//Y�̈ړ��ʂ����̒l�Ȃ�
		else
		{
			//�~��
			AnimationUpdate(FallAnim);
		}
		return;
	}

	//���@�r���t���O��ON�Ȃ�
	if (m_isCastingSpell)
	{
		//���@��������
		AnimationUpdate(CastSpellAnim);
		return;
	}

	/*
	{
		//���{�b�g�ƃv���C���[�̋����̌v�Z
		const float a = m_pos.x - a_playerPos.x;//���a
		const float b = m_pos.y - a_playerPos.y;//����b
		const float c = sqrt(a * a + b * b);  //�Ε�(����)c

		//�U������t���O��OFF
		m_isAttackHit = false;

		//�W�����v���Ă��Ȃ�������
		if (!m_isJump)
		{
			//�U���\�˒��ɓ��������͍U���t���O�������Ă��鎞
			if (c <= m_attackDis || m_isAttack)
			{
				m_isAttack = true;//�U���t���O��ON
				AnimationUpdate(Attack);//�U���A�j���[�V����

				//�U�����������摜�ɂȂ�����
				if (m_texIndex == m_attackTexIndex)
				{
					//�U������t���O��ON
					m_isAttackHit = true;

					//�U�����W�̐ݒ�
					m_attackPos.x = m_scale.x > 0 ? m_pos.x - m_attackHitDis : m_pos.x + m_attackHitDis;
					m_attackPos.y = m_pos.y;
				}
				return;
			}
		}

		if (fabsf(a) < m_noTrackDist)//x���W�̍����߂�����ƒǐՂ��Ȃ�
		{
			m_isTracking = false;
		}
		else if (fabsf(a) > m_trackDist)//x���W�̍��������Ȃ�ƒǐՂ���
		{
			m_isTracking = true;
		}

		//�ǐՃt���O��ON�Ȃ�
		if (m_isTracking)
		{
			//�v���C���[����������Ɍ�����
			m_move.x = a_playerPos.x < m_pos.x ? -m_moveSpeed : m_moveSpeed;
		}
		else
		{
			//�����Ă�������ɍ��킹�ăX���[
			m_move.x = m_scale.x > 0 ? m_moveSpeed : -m_moveSpeed;
		}
	}
	*/

	//����
	AnimationUpdate(WalkAnim);
}

//�X�V
void C_LittleWitch::Update(const float a_scrollX, const float a_scrollY)
{
	//�V�[���h�̍X�V
	ShieldUpdate();

	//�G�X�|�i�[�̍X�V
	if (m_enemySpawner != nullptr)
	{
		m_enemySpawner->Update(a_scrollX, a_scrollY);

		//���݂��Ă��Ȃ�������
		if (!m_enemySpawner->GetAlive())
		{
			//delete����
			delete m_enemySpawner;

			//nullptr�ŏ�����
			m_enemySpawner = nullptr;
		}
	}

	//���݂��Ă��Ȃ������烊�^�[��
	if (!m_isAlive) return;

	//�ړ���������ɍ��킹�Č����Ă������ς���
	if (m_move.x > 0)
	{
		m_scale.x = m_scaleSize;
	}
	else if (m_move.x < 0)
	{
		m_scale.x = -m_scaleSize;
	}


	//���W�m��
	m_pos += m_move;

	//�s��쐬
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);     //�g��s��̍쐬
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x + m_shakeX - a_scrollX, m_pos.y - a_scrollY, 0);//�ړ��s��̍쐬
	m_mat = m_scaleMat * m_transMat;//�s��̍���

	//�V�[���h�̍s��쐬
	m_shieldScaleMat = Math::Matrix::CreateScale(m_shieldScaleSize, m_shieldScaleSize, 0);
	m_shieldMat = m_shieldScaleMat * m_transMat;
}

//�`��
void C_LittleWitch::Draw()
{
	//�G�X�|�i�[�̕`��
	if (m_enemySpawner != nullptr)
	{
		m_enemySpawner->Draw();
	}

	//���@�����̕`��
	C_EnemyBase::Draw();

	//�V�[���h�̕`��
	Math::Rectangle sRect = { m_shield.column * m_shield.texWidth,m_shield.row * m_shield.texHeight,
							m_shield.texWidth,m_shield.texHeight };

	//�V�[���h�̃G�t�F�N�g���̐F
	static Math::Color shieldEffectColor = { 1,1,1,0.5f };

	SHADER.m_spriteShader.SetMatrix(m_shieldMat);
	if (m_isShieldActive)
	{
		switch (m_nowShieldState)
		{
		case ShieldState::ON:
			SHADER.m_spriteShader.DrawTex(m_shieldTex + (int)m_nowShieldState, 0, 0, &sRect, &shieldEffectColor);
			break;
		case ShieldState::ACTIVE:
			SHADER.m_spriteShader.DrawTex(m_shieldTex + (int)m_nowShieldState, 0, 0, &sRect, &m_shieldColor);
			break;
		default:
			break;
		}
	}

	//�V�[���h���_���[�W���󂯂���
	if (m_isShieldDamaged)
	{
		SHADER.m_spriteShader.DrawTex(m_shieldTex + (int)ShieldState::OFF, 0, 0, &sRect, &shieldEffectColor);
	}
}

//�}�b�v�����蔻��p Y����
void C_LittleWitch::MapHitY(float a_posY, float a_moveY, bool a_jump)
{
	m_pos.y = a_posY;
	m_move.y = a_moveY;

	//�W�����v����
	if (m_isJump && !a_jump)
	{
		//���n�t���O��ON
		m_isLanded = true;
	}
	m_isJump = a_jump;
}

//�A�j���[�V�����X�V
void C_LittleWitch::AnimationUpdate(AnimationType a_animation)
{
	//�ʂ̃A�j���[�V�������s�����Ƃ��Ă���ꍇ
	if (m_nowAnim != a_animation)
	{
		//�摜�̐؎�ʒu�������l�ɖ߂�
		m_texIndex = 0;

		//�w�肳�ꂽ�A�j���[�V������ݒ�
		m_nowAnim = a_animation;

		//�摜���Z�b�g
		m_nowEnemyTex = m_enemyTex + m_nowAnim;
		return;
	}

	//2�t���[����1��A�j���[�V�������X�V
	if (m_frameCnt % m_frameRate == 0)
	{
		m_texIndex++;//�摜�̐؎�ʒu��i�߂�
		switch (m_nowAnim)
		{
		case IdleAnim:
			//�A�j���[�V���������[�v
			if (m_texIndex >= m_idleMax)m_texIndex = 0;
			break;
		case WalkAnim:
			//�A�j���[�V���������[�v
			if (m_texIndex >= m_walkMax)m_texIndex = 0;
			break;
		case JumpAnim:
			//�Ō�̉摜�܂ł�������
			if (m_texIndex >= m_jumpMax)
			{
				//�Ō�̉摜�Ɉێ�
				m_texIndex = m_jumpMax - 1;
			}
			break;
		case FallAnim:
			//�Ō�̉摜�܂ł�������
			if (m_texIndex >= m_fallMax)
			{
				//�Ō�̉摜���ێ�
				m_texIndex = m_fallMax - 1;
			}
			break;
		case LandAnim:
			//�Ō�̉摜�܂ł�������
			if (m_texIndex >= m_landMax)
			{
				m_isLanded = false;
			}
			break;
		case AttackAnim:
			//�Ō�̉摜�܂ł�������
			if (m_texIndex >= m_attackMax)
			{
				const float playerX = m_eOwner->GetChara()->GetPos().x;
				m_scale.x = m_pos.x > playerX ? -m_scaleSize : m_scaleSize;//�v���C���[�̕�������������
				m_texIndex = 0;//�摜�̐؎�ʒu�������l�ɖ߂�
				m_isAttack = false;//�U���t���O��OFF
			}
			break;
		case CastSpellAnim:
			//�Ō�̉摜�܂ł�������
			if (m_texIndex >= m_castSpellMax)
			{
				m_texIndex = 0;
				m_isCastingSpell = false;
				CreateEnemySpawner();
			}
			break;
		case SurprisedAnim:
			//�Ō�̉摜�܂ł�������
			if (m_texIndex >= m_surprisedMax)
			{
				m_isSurprised = false;
			}
			break;
		case DeathAnim:
			//�Ō�̉摜�܂ōs�����瑶�݃t���O��OFF�ɂ���
			if (m_texIndex >= m_deathMax && m_isAlive)
			{
				m_isAlive = false;
			}
			break;
		default:
			break;
		}
	}
}

//�V�[���h�̍X�V
void C_LittleWitch::ShieldUpdate()
{
	//sin�J�[�u
	static int sinAngle = 0;
	int angleStep;
	float sinValue;

	//�V�[���h�̑ϋv�͂��Ⴂ�قǓ_�ł𑁂߂�
	angleStep = m_shieldDurabilityMax - m_shieldDurability + 1;

	sinAngle += angleStep;
	if (sinAngle >= 360)
	{
		sinAngle -= 360;
	}

	//sin�l����
	sinValue = fabsf(sin(ToRadians(sinAngle)));

	//�Œ�ۏ�
	sinValue += 0.1f;

	//�V�[���h�̃A���t�@�l���Z�b�g
	m_shieldColor.A(sinValue);

	//�V�[���h�̑ϋv�͂�0�ȉ��Ȃ�
	if (m_shieldDurability <= 0)
	{
		//�V�[���h�A�N�e�B�u�t���O��ON�Ȃ�
		if (m_isShieldActive)
		{
			//����
			m_isSurprised = true;
		}

		//�V�[���h������
		m_isShieldActive = false;
	}

	//�t���[���J�E���g���t���[�����[�g�Ŋ���؂��Ƃ�
	if (m_frameCnt % m_shield.frameRate == 0)
	{
		//�摜��i�߂�
		m_shield.texIndex++;

		//�摜���Ō�܂ł�������
		if (m_shield.texIndex >= m_shield.texNumMax)
		{
			//�摜�������摜�ɖ߂�
			m_shield.texIndex = 0;

			//�V�[���h�_���[�W�t���O��OFF
			m_isShieldDamaged = false;

			switch (m_nowShieldState)
			{
			case ShieldState::ON:
				m_nowShieldState = ShieldState::ACTIVE;
				break;
			case ShieldState::ACTIVE:
				break;
			default:
				break;
			}
		}
		m_shield.row = m_shield.texIndex / m_shield.rowMax;//�s�����擾
		m_shield.column = m_shield.texIndex % m_shield.columnMax;//�񐔂��擾
	}
}

//�G�X�|�i�[�̐���
void C_LittleWitch::CreateEnemySpawner()
{
	//�G�X�|�i�[����������Ă�����
	if (m_enemySpawner != nullptr)return;

	static std::random_device rd;
	static std::mt19937 gen(rd());
	EnemyType enemyType;

	//�m���Ń{�X����
	if (CheckProbability(m_bossSummonProbability))
	{
		static std::uniform_int_distribution<int> dist((int)EnemyType::BossRobot,(int)EnemyType::Skull);

		//�{�X�̒��Ń����_��
		enemyType = (EnemyType)dist(gen);
	}
	//�{�X�����̊m����������Ȃ����
	else
	{
		static std::uniform_int_distribution<int> dist((int)EnemyType::Robot, (int)EnemyType::Gremlin);

		//�{�X�ȊO�̓G�Ń����_��
		enemyType = (EnemyType)dist(gen);
	}

	const float setPosX = (float)(rand() % 700 - 300);
	const float setPosY = -1000;
	m_enemySpawner = new C_EnemySpawner(enemyType, { setPosX,setPosY });
	m_enemySpawner->SetTex(m_enemySpawnerTex);
	m_enemySpawner->SetCrackTex(m_enemySpawnerCrackTex);
	m_enemySpawner->SetOwner(m_eOwner);
	
	//���S�G�t�F�N�g
	m_eOwner->GetEffectManager()->SetBakuhatuEffect(setPosX, setPosY, true);
}

//��s
void C_LittleWitch::Fly()
{
	m_move.x = m_flyMoveX;
	m_move.y = m_flyMoveY;
}

//���d�~�ϒl�̃Z�b�g
bool C_LittleWitch::SetElecShockGauge(int a_elecShockGauge)
{
	//�V�[���h���A�N�e�B�u�Ȃ�
	if (m_isShieldActive)
	{
		//���d������ł���΃V�[���h�A�N�e�B�u�t���O��OFF
		if (m_eOwner->GetChara()->GetNowAvoidType() == OverAvoid)
		{
			//�V�[���h�̑ϋv�͂�0��
			m_shieldDurability = 0;

			//�V�[���h�̃A�j���[�V�����������摜��
			m_shield.texIndex = 0;
		}

		//���^�[��
		return false;
	}

	//���d�~�ϒl���Z�b�g
	m_elecShockGauge += a_elecShockGauge;
	return true;
}

//�_���[�W�̃Z�b�g
bool C_LittleWitch::SetDamage(int a_damage)
{
	//�_���[�W��0�ȉ��Ȃ烊�^�[��
	if (a_damage <= 0)return false;

	//�V�[���h���A�N�e�B�u����
	if (m_isShieldActive)
	{
		//�V�[���h�̑ϋv�͂�����Ȃ�
		if (m_shieldDurability > 0)
		{
			//�V�[���h�̑ϋv�͂����炷
			m_shieldDurability--;

			//�V�[���h�̃A�j���[�V�����������摜��
			m_shield.texIndex = 0;

			//�V�[���h�̑ϋv�͂��܂�����Ȃ�
			if (m_shieldDurability > 0)
			{
				//�V�[���h�_���[�W�t���O��ON
				m_isShieldDamaged = true;
			}
		}
		return false;
	}

	m_hp -= a_damage;
	m_isDamage = true;
	return true;
}

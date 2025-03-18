#include "BossRobot.h"
#include "../../../Scene.h"
#include "../../../Constants.h"

//C_BossRobot::C_BossRobot(Math::Vector2 a_pos) :
//	C_EnemyBase(
//		//�萔�����l�Z�b�g
//		EnemyType::BossRobot, //m_enemyType     ...�G�̎��
//		300,       //m_texWidth      ...�摜1�����T�C�Y
//		300,       //m_texHeight     ...�摜1���c�T�C�Y
//		2,         //m_frameRate     ...�A�j���[�V�����̍X�V�p�x
//		200,       //m_hpMax         ...�ő�̗�
//		400,       //m_attackDamage  ...�U����
//		200,       //m_hitDamage     ...���������Ƃ��̃_���[�W
//		8,         //m_attackTexIndex...�U�����������摜
//		30,        //m_coinMax       ...�����R�C���̍ő�
//		100,       //m_elecShockLimit...���d���E�l
//		9.0f,      //m_moveSpeed     ...�ړ����x
//		0.9f,      //m_gravity       ...�d��
//		15.0f,     //m_jumpPower     ...�W�����v��
//		1.5f,      //m_scaleSize     ...�g�嗦
//		190.0f,    //m_attackRange   ...�U���\�˒�
//		120,       //m_attackHitDis  ...�U���˒�
//		120,       //m_attackRadius  ...�U���͈�
//		150.0f,    //m_trackDist     ...�ǐՂ����鋗��
//		120.0f,    //m_noTrackDist   ...�ǐՂ����Ȃ�����
//		120.0f,    //m_hitWidth      ...�����蔻�艡�T�C�Y
//		150.0f,     //m_hitHeight     ...�����蔻��c�T�C�Y
//		{ 1,1,1,1 },//m_defaultColor...�ʏ펞�̐F
//		{ 1, 0, 0, 1 }//m_damageColor   ...�_���[�W����������Ƃ��̐F
//	)
//{
//	//�ŗL�ϐ�������
//	m_nowAnim = IdleAnim;
//	m_animHallo = false;
//	m_isHighJump = true;
//	m_highJumpInterval = m_highJumpIntervalMax;
//	m_landingPosX = 0;
//	m_cooldownTime = 0;
//	m_smoke = nullptr;
//	m_smokeTex = nullptr;
//
//
//	//���W��private�ϐ��̃Z�b�g
//	m_pos = a_pos;  //���W
//	m_scale.x = -m_scaleSize;//������������
//}

C_BossRobot::C_BossRobot(
	//�G���ʒ萔�Z�b�g�p�̈���
	int   a_hpMax,         //m_hpMax         ...�ő�̗�
	int   a_attackDamage,  //m_attackDamage  ...�U����
	int   a_hitDamage,     //m_hitDamage     ...���������Ƃ��̃_���[�W
	int   a_coinMax,       //m_coinMax       ...�����R�C���̍ő�
	int   a_elecShockLimit,//m_elecShockLimit...���d���E�l
	int   a_smokeDamage    //m_smokeDamage   ...���̃_���[�W
) :
	C_EnemyBase(
		//�萔�����l�Z�b�g
		EnemyType::BossRobot, //m_enemyType     ...�G�̎��
		300,             //m_texWidth      ...�摜1�����T�C�Y
		300,             //m_texHeight     ...�摜1���c�T�C�Y
		2,               //m_frameRate     ...�A�j���[�V�����̍X�V�p�x
		a_hpMax,         //m_hpMax         ...�ő�̗�
		a_attackDamage,  //m_attackDamage  ...�U����
		a_hitDamage,     //m_hitDamage     ...���������Ƃ��̃_���[�W
		8,               //m_attackTexIndex...�U�����������摜
		a_coinMax,       //m_coinMax       ...�����R�C���̍ő�
		a_elecShockLimit,//m_elecShockLimit...���d���E�l
		9.0f,            //m_moveSpeed     ...�ړ����x
		0.9f,            //m_gravity       ...�d��
		15.0f,           //m_jumpPower     ...�W�����v��
		1.5f,            //m_scaleSize     ...�g�嗦
		190.0f,          //m_attackRange   ...�U���\�˒�
		120,             //m_attackHitDis  ...�U���˒�
		120,             //m_attackRadius  ...�U���͈�
		150.0f,          //m_trackDist     ...�ǐՂ����鋗��
		120.0f,          //m_noTrackDist   ...�ǐՂ����Ȃ�����
		120.0f,          //m_hitWidth      ...�����蔻�艡�T�C�Y
		150.0f,          //m_hitHeight     ...�����蔻��c�T�C�Y
		{ 1, 1, 1, 1 },  //m_defaultColor  ...�ʏ펞�̐F
		{ 1, 0, 0, 1 }   //m_damageColor   ...�_���[�W����������Ƃ��̐F
	),
	m_smokeDamage(a_smokeDamage)
{
	m_isAlive = false;
}

C_BossRobot::C_BossRobot(Math::Vector2 a_pos, const C_BossRobot& a_enemyData) :
	C_EnemyBase(a_enemyData),
	m_smokeDamage(a_enemyData.m_smokeDamage)
{
	//�ŗL�ϐ�������
	m_nowAnim = IdleAnim;
	m_animHallo = false;
	m_isHighJump = true;
	m_highJumpInterval = m_highJumpIntervalMax;
	m_landingPosX = 0;
	m_cooldownTime = 0;
	m_smoke = nullptr;
	m_smokeTex = nullptr;


	//���W��private�ϐ��̃Z�b�g
	m_pos = a_pos;  //���W
	m_scale.x = -m_scaleSize;//������������
}

C_BossRobot::~C_BossRobot()
{
	//�����������
	if (m_smoke != nullptr)
	{
		delete m_smoke;
	}
}

//������
void C_BossRobot::Init()
{
	m_nowEnemyTex = m_enemyTex + m_nowAnim;
}

//����
void C_BossRobot::Action(const Math::Vector2 a_playerPos)
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

	//�̗͂�0�ȉ��Ȃ玀�S�t���O��ON
	if (m_hp <= 0)m_isDead = true;

	//���S�t���O��ON�Ȃ�
	if (m_isDead)
	{
		m_texAngle += 10;//�摜����]
		m_scale *= {0.97f, 0.97f};//�摜�̃T�C�Y��������
		m_color.A(m_color.A() - 0.02f);//�����ɂ��Ă���
		//���S�������Đ����Ă��Ȃ�������
		if ((*(m_enemySfx + DeathSfx))->IsPlay() == false)
		{
			//���S�������Đ�
			(*(m_enemySfx + DeathSfx))->Play();
		}
		AnimationUpdate(DeathAnim);
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


	//�N�[���_�E���^�C�����I����Ă��Ȃ�������
	if (m_cooldownTime > 0)
	{
		//�n�ʂ̐k���̃t���[���Ԋu�ɍ��킹��
		if (m_frameCnt % m_seismicFrameRate == 0)
		{
			//�}�b�v�̃C���X�^���X���擾
			C_MapBase* map = m_eOwner->GetMap();

			//�n�k�̒l������
			float seismicShakeX = rand() % 2 == 0 ? m_seismicShakePower : -m_seismicShakePower;
			float seismicShakeY = rand() % 2 == 0 ? m_seismicShakePower : -m_seismicShakePower;

			//�n�ʂ�h�炷
			map->SetScrollX(map->GetScrollX() + seismicShakeX);
			map->SetScrollY(map->GetScrollY() + seismicShakeY);
		}

		//�N�[���_�E���^�C�������炷
		m_cooldownTime--;
	}

	//���A�t���O��ON�Ȃ�
	if (m_animHallo)
	{
		AnimationUpdate(HelloAnim);
		return;
	}

	//�A�N�e�B�u�t���OOFF
	//�܂��̓N�[���_�E���^�C�����c���Ă�����
	if (!m_isActive || m_cooldownTime > 0)
	{
		//�����p�̃A�j���[�V�������s�����^�[��
		AnimationUpdate(IdleAnim);
		return;
	}

	//�C���^�[�o�����I����
	if (m_highJumpInterval <= 0)
	{
		//�n�C�W�����v�����Ă��Ȃ��Ƃ�
		if (!m_isHighJump)
		{
			//�W�����v�ł�����
			if (Jump(m_highJumpPower))
			{
				//�v���C���[�̌��݈ʒu���擾����
				//���n�ꏊ�ɐݒ�
				m_landingPosX = a_playerPos.x;

				//�ǐՂ�OFF
				m_isTracking = false;

				//�n�C�W�����v�t���O��ON
				m_isHighJump = true;
			}
		}
	}

	//�C���^�[�o�����f�N�������g
	if (m_highJumpInterval > 0)
	{
		m_highJumpInterval--;
	}

	//�ǂɂԂ����Ă�����
	if (m_isHitWall)
	{
		//�W�����v
		Jump(m_jumpPower);
		m_isHitWall = false;
	}


	//���{�b�g�ƃv���C���[�̋����̌v�Z
	const float a = m_pos.x - a_playerPos.x;//���a
	const float b = m_pos.y - a_playerPos.y;//����b
	const float c = sqrt(a * a + b * b);  //�Ε�(����)c
	
	//�U������t���O��OFF
	m_isAttackHit = false;

	//�W�����v���Ă��Ȃ��Ƃ�
	if (!m_isJump)
	{
		//�U���\�˒��ɓ��������͍U���t���O�������Ă��鎞
		if (c <= m_attackDis || m_isAttack)
		{
			m_isAttack = true;//�U���t���O��ON
			AnimationUpdate(AttackAnim);//�U���A�j���[�V����

			//�U�����������摜�ɂȂ�����
			if (m_texIndex == m_attackTexIndex)
			{
				//�U������t���O��ON
				m_isAttackHit = true;

				//�U�����W�̐ݒ�
				m_attackPos.x = m_scale.x > 0 ? m_pos.x + m_attackHitDis : m_pos.x - m_attackHitDis;
				m_attackPos.y = m_pos.y;
			}
			return;
		}
	}


	//x���W�̍����߂�����ƒǐՂ��Ȃ�
	if (fabsf(a) < m_noTrackDist)
	{
		m_isTracking = false;
	}
	//x���W�̍��������Ȃ�ƒǐ�
	else if (fabsf(a) > m_trackDist)
	{
		m_isTracking = true;
	}

	//�n�C�W�����v�����Ă�����
	if (m_isHighJump)
	{
		const float dis = fabsf(m_pos.x - m_landingPosX);
		if (dis > m_highJumpNoTrackDist)
		{
			//�w�肳�ꂽ���n�ꏊ�Ɍ������Ēǐ�
			m_move.x = m_landingPosX < m_pos.x ? -m_moveSpeed : m_moveSpeed;
		}
	}
	//�ǐՃt���O��ON�Ȃ�
	else if (m_isTracking)
	{
		//�v���C���[�Ɍ������Ēǐ�
		m_move.x = a_playerPos.x < m_pos.x ? -m_moveSpeed : m_moveSpeed;
	}
	//�ǐՃt���O��OFF�Ȃ�
	else
	{
		//�����Ă�������ɍ��킹�ăX���[
		m_move.x = m_scale.x < 0 ? -m_moveSpeed : m_moveSpeed;
	}
	//����
	AnimationUpdate(WalkAnim);

	//�W�����v���Ă��Ȃ�������
	if (!m_isJump)
	{
		//�����������Đ����Ă��Ȃ�������
		if ((*(m_enemySfx + WalkSfx))->IsPlay() == false)
		{
			//�����������Đ�
			(*(m_enemySfx + WalkSfx))->Play();
		}
	}
}

//�X�V
void C_BossRobot::Update(const float a_scrollX, const float a_scrollY)
{
	//���݂��Ă��Ȃ������烊�^�[��
	if (!m_isAlive) return;

	//���̍X�V
	if (m_smoke != nullptr)
	{
		m_smoke->Update(a_scrollX,a_scrollY);
		
		//������������
		if (!m_smoke->GetAlive())
		{
			//�����������
			delete m_smoke;

			//�|�C���^�̒��̃A�h���X������
			m_smoke = nullptr;
		}
	}

	//�E�Ɉړ����悤�Ƃ��Ă�����
	if (m_move.x > 0)
	{
		//�E����������
		m_scale.x = m_scaleSize;
	}
	//���Ɉړ����悤�Ƃ��Ă�����
	else if (m_move.x < 0)
	{
		//������������
		m_scale.x = -m_scaleSize;
	}
	
	//�̗͂���������
	if (m_hp > 0)
	{
		//���W�m��
		m_pos += m_move;
	}

	//�s��쐬
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);     //�g��s��̍쐬
	m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(m_texAngle));//��]�s��̍쐬
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x + m_shakeX - a_scrollX, m_pos.y + m_drawCorrY - a_scrollY, 0);//�ړ��s��̍쐬
	m_mat = m_scaleMat * m_rotationMat * m_transMat;//�s��̍���
}

//�`��
void C_BossRobot::Draw()
{
	//���̕`��
	if (m_smoke != nullptr)
	{
		m_smoke->Draw();
	}

	//�G�̕`��
	C_EnemyBase::Draw();
}

//�A�j���[�V�����X�V
void C_BossRobot::AnimationUpdate(AnimationType a_animation)
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

	//�A�j���[�V�������X�V
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
			if (m_texIndex >= m_walkingMax)m_texIndex = 0;
			break;
		case AttackAnim:
			//�Ō�̉摜�܂ōs������
			if (m_texIndex >= m_attackMax)
			{
				const float playerX = m_eOwner->GetChara()->GetPos().x;
				m_scale.x = m_pos.x > playerX ? -m_scaleSize : m_scaleSize;//�v���C���[�̕�������������
				m_texIndex = 0;//�摜�̐؎�ʒu�������l�ɖ߂�
				m_isAttack = false;//�U���t���O��OFF
			}
			break;
		case DeathAnim:
			//�Ō�̉摜�܂ōs�����瑶�݃t���O��OFF�ɂ���
			if (m_texIndex >= m_deathMax)m_isAlive = false;
			break;
		case HelloAnim:
			if (m_texIndex >= m_helloMax)
			{
				m_texIndex = 0;//�摜�̐؎�ʒu�������l�ɖ߂�
				m_animHallo = false;//���A�t���O��OFF
			}
			break;
		default:
			break;
		}
	}
}

//�}�b�v�����蔻��p Y����
void C_BossRobot::MapHitY(float a_posY, float a_moveY, bool a_jump)
{
	C_EnemyBase::MapHitY(a_posY, a_moveY, a_jump);

	//�n�C�W�����v��̒��n�����Ă��Ȃ���΃��^�[��
	if (!m_isHighJump || a_jump)return;

	//�n�C�W�����v�t���O��OFF
	m_isHighJump = a_jump;

	//�n�C�W�����v��̒��n
	HighJumpLand();
}

//�n�C�W�����v��̒��n
void C_BossRobot::HighJumpLand()
{
	//�C���^�[�o�����Z�b�g
	m_highJumpInterval = m_highJumpIntervalMax;

	//���d��Ԃ܂��̗͑͂�0�ȉ��Ȃ烊�^�[��
	if (m_isElecShock || m_hp <= 0)return;

	//�d�����Ԃ̃Z�b�g
	m_cooldownTime = m_cooldownTimeMax;

	//������
	EmitSmoke();

	//���n���Đ�
	(*(m_enemySfx + LandingSfx))->Play();
}

//������
void C_BossRobot::EmitSmoke()
{
	//�|�C���^�ɂ܂��f�[�^�������Ă����烊�^�[��
	if (m_smoke != nullptr) return;

	//���������m�ۂ��C���X�^���X�̐���
	m_smoke = new C_Smoke(m_pos, m_smokeDamage);

	//�������ꂽ�C���X�^���X�ɉ��摜���Z�b�g
	m_smoke->SetTex(m_smokeTex);
}

#include "Frog.h"
#include "../../../Scene.h"
#include "../../../Constants.h"

C_Frog::C_Frog(Math::Vector2 a_pos) :
	C_EnemyBase(
		//�萔�����l�Z�b�g
		EnemyType::Frog, //m_enemyType      ...�G�̎��
		283,   //m_texWidth      ...�摜1�����T�C�Y
		192,   //m_texHeight     ...�摜1���c�T�C�Y
		7,     //m_frameRate     ...�A�j���[�V�����̍X�V�p�x
		25,    //m_hpMax         ...�ő�̗�
		0,     //m_attackDamage  ...�U����
		100,   //m_hitDamage     ...���������Ƃ��̃_���[�W
		3,     //m_attackTexIndex...�U�����������摜
		5,     //m_coinMax       ...�����R�C���̍ő�
		30,     //m_elecShockLimit...���d���E�l
		1.5f,  //m_moveSpeed     ...�ړ����x
		1.0f,  //m_gravity       ...�d��
		12.0f, //m_jumpPower     ...�W�����v��
		0.5f,  //m_scaleSize     ...�g�嗦
		500.0f,//m_attackRange   ...�U���\�˒�
		0,     //m_attackHitDis  ...�U���˒�
		0,     //m_attackRadius  ...�U���͈�
		50.0f, //m_trackDist     ...�ǐՂ����鋗��
		20.0f, //m_noTrackDist   ...�ǐՂ����Ȃ�����
		192.0f * 0.5f / 2,//m_hitWidth   ...�����蔻�艡�T�C�Y
		183.0f * 0.5f / 2,//m_hitHeight  ...�����蔻��c�T�C�Y
		{ 1,1,1,1 },//m_defaultColor...�ʏ펞�̐F
		{ 1, 0, 0, 0.5f }    //m_damageColor...�_���[�W����������Ƃ��̐F
	)
{
	//�ŗL�ϐ��̏�����
	m_pos = a_pos;  //���W
	m_nowAnim = IdleAnim;//���݂̃A�j���[�V����
	m_spell = nullptr;
	m_spellTex = nullptr;
	m_isSpellActive = false;
}

C_Frog::~C_Frog()
{
	//�����������
	if (m_spell != nullptr)
	{
		delete m_spell;
	}
}

//������
void C_Frog::Init()
{
	//�摜�Z�b�g
	m_nowEnemyTex = m_enemyTex + m_nowAnim;
}

//����
void C_Frog::Action(const Math::Vector2 a_playerPos)
{
	//���݂��Ă��Ȃ������烊�^�[��
	if (!m_isAlive) return;

	//���@�̓���
	if (m_spell != nullptr)
	{
		m_spell->Action(a_playerPos);
	}

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
	if (m_hp <= 0)
	{
		m_eOwner->GetEffectManager()->SetBurstFlogEffect(m_pos.x, m_pos.y, true);
		m_isDead = true;
	}

	//���S�t���O��ON�Ȃ�
	if (m_isDead)
	{
		//���S��
		(*(m_enemySfx + DeathSfx))->Play();

		//���S�A�j���[�V����
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

	//�X�N���[���̒l���擾
	const float scrollX = m_eOwner->GetMap()->GetScrollX();
	const float scrollY = m_eOwner->GetMap()->GetScrollY();

	//��ʓ��ɂ���ꍇ�̓A�N�V�����t���O��ON
	if (m_pos.x - m_hitWidth - scrollX < SCREEN_RIGHT &&
		m_pos.x + m_hitWidth - scrollX > SCREEN_LEFT &&
		m_pos.y - m_hitHeight - scrollY < SCREEN_TOP &&
		m_pos.y + m_hitHeight - scrollY > SCREEN_BOTTOM)
	{
		m_isActive = true;
	}

	//�A�N�V�����t���O��OFF
	//�܂��͍U���t���O��OFF�̎��ɖ��@�A�N�e�B�u�t���O��ON�Ȃ烊�^�[��
	if (!m_isActive || !m_isAttack && m_isSpellActive)
	{
		m_scale.x = m_pos.x > a_playerPos.x ? m_scaleSize : -m_scaleSize;//�v���C���[�̕�������������
		AnimationUpdate(IdleAnim);
		return;
	}

	//���{�b�g�ƃv���C���[�̋����̌v�Z
	const float a = m_pos.x - a_playerPos.x;//���a
	const float b = m_pos.y - a_playerPos.y;//����b
	const float c = sqrt(a * a + b * b);  //�Ε�(����)c

	//�U���\�˒��ɓ��������͍U���t���O�������Ă��鎞
	if (c <= m_attackDis || m_isAttack)
	{
		m_isAttack = true;//�U���t���O��ON
		AnimationUpdate(AttackAnim);//�U���A�j���[�V����

		//�U��������摜�ɂȂ�����
		if (m_texIndex == m_attackTexIndex)
		{
			//���@����
			EmitSpell(a_playerPos);
		}
		return;
	}

	

	//�����p
	AnimationUpdate(IdleAnim);
}

//�X�V
void C_Frog::Update(const float a_scrollX, const float a_scrollY)
{
	//���݂��Ă��Ȃ������烊�^�[��
	if (!m_isAlive) return;

	//���@�̍X�V
	if (m_spell != nullptr)
	{
		m_spell->Update(a_scrollX, a_scrollY);

		//���@����������
		if (!m_spell->GetAlive())
		{
			//�����������
			delete m_spell;

			//�|�C���^�̒��̃A�h���X������
			m_spell = nullptr;

			//���@�A�N�e�B�u�t���O��OFF
			m_isSpellActive = false;
		}
	}

	//���W�m��
	m_pos += m_move;

	//�s��쐬
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);     //�g��s��̍쐬
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x + m_shakeX - a_scrollX, m_pos.y - a_scrollY, 0);//�ړ��s��̍쐬
	m_mat = m_scaleMat * m_transMat;//�s��̍���
}

//�`��
void C_Frog::Draw()
{
	//���@�̕`��
	if (m_spell != nullptr)
	{
		m_spell->Draw();
	}

	//�G�̕`��
	C_EnemyBase::Draw();
}

//�A�j���[�V�����X�V
void C_Frog::AnimationUpdate(AnimationType a_animation)
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
		case AttackAnim:
			//�Ō�̉摜�܂ōs������
			if (m_texIndex >= m_attackMax)
			{
				m_texIndex = 0;//�摜�̐؎�ʒu�������l�ɖ߂�
				m_isAttack = false;//�U���t���O��OFF
			}
			break;
		case DeathAnim:
			//�Ō�̉摜�܂ōs�����瑶�݃t���O��OFF�ɂ���
			if (m_texIndex >= m_deathMax)m_isAlive = false;
			break;
		default:
			break;
		}
	}
}

void C_Frog::EmitSpell(Math::Vector2 a_targetPos)
{
	//�|�C���^�ɂ܂��f�[�^�������Ă����烊�^�[��
	if (m_spell != nullptr) return;

	//���ˉ�
	(*(m_enemySfx + ShotSfx))->Play();

	//���@�A�N�e�B�u�t���O��ON
	m_isSpellActive = true;

	//���������m�ۂ��C���X�^���X�̐���
	m_spell = new C_Spell(m_pos, a_targetPos);

	//�������ꂽ�C���X�^���X�ɉ��摜���Z�b�g
	m_spell->SetTex(m_spellTex);
}
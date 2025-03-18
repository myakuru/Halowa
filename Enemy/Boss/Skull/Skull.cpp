#include "Skull.h"
#include "../../../Scene.h"
#include "../../../Constants.h"

//C_Skull::C_Skull(Math::Vector2 a_pos) :
//	C_EnemyBase(
//		//�萔�����l�Z�b�g
//		EnemyType::Skull, //m_enemyType     ...�G�̎��
//		147,   //m_texWidth      ...�摜1�����T�C�Y
//		146,   //m_texHeight     ...�摜1���c�T�C�Y
//		10,    //m_frameRate     ...�A�j���[�V�����̍X�V�p�x
//		400,   //m_hpMax         ...�ő�̗�
//		400,   //m_attackDamage  ...�U����
//		200,   //m_hitDamage     ...���������Ƃ��̃_���[�W
//		0,     //m_attackTexIndex...�U�����������摜
//		50,    //m_coinMax       ...�����R�C���̍ő�
//		250,   //m_elecShockLimit...���d���E�l
//		8.0f,  //m_moveSpeed     ...�ړ����x
//		2.0f,  //m_gravity       ...�d��
//		20.0f, //m_jumpPower     ...�W�����v��
//		2.0f,  //m_scaleSize     ...�g�嗦
//		100.0f,//m_attackDis     ...�U���\�˒�
//		60,    //m_attackHitDis  ...�U���˒�
//		110,    //m_attackRadius  ...�U���͈�
//		150.0f,//m_trackDist     ...�ǐՂ����鋗��
//		120.0f,//m_noTrackDist   ...�ǐՂ����Ȃ�����
//		110.0f,//m_hitWidth      ...�����蔻�艡�T�C�Y
//		110.0f,//m_hitHeight     ...�����蔻��c�T�C�Y
//		{ 1,1,1,1 },//m_defaultColor...�ʏ펞�̐F
//		{ 0, 0, 1, 0.5f } //m_damageColor   ...�_���[�W����������Ƃ��̐F
//	),
//	m_bonfire()
//{
//	//�ŗL�ϐ��̏�����
//	m_fireVeilTex = nullptr;
//	m_fireballTex = nullptr;
//	m_bonfireTex = nullptr;
//	m_confusedTex = nullptr;
//	m_pos = a_pos;  //���W
//	m_nowAnim = FloatAnim;//���݂̃A�j���[�V����
//	m_fireVeil.texIndex = 0;
//	m_fireVeil.row = 0;
//	m_fireVeil.column = 0;
//	m_rotationCount = 0;
//	m_rollingCount = 0;
//	m_waitTime = 60;
//	m_isRolling = false;
//	m_isConfused = false;
//	m_setMoveX = 0;
//	m_seismicTime = 0;
//	m_isFireVeilActive = false;
//	m_isAwakened = false;
//	m_isErupting = false;
//	m_fireballCount = 0;
//}

C_Skull::C_Skull(
	//�G���ʒ萔�Z�b�g�p�̈���
	int   a_hpMax,         //m_hpMax         ...�ő�̗�
	int   a_attackDamage,  //m_attackDamage  ...�U����
	int   a_hitDamage,     //m_hitDamage     ...���������Ƃ��̃_���[�W
	int   a_coinMax,       //m_coinMax       ...�����R�C���̍ő�
	int   a_elecShockLimit,//m_elecShockLimit...���d���E�l
	int   a_fireballDamage,//m_fireballDamage...�΂̋ʂ̃_���[�W
	int   a_bonfireDamage  //m_bonfireDamage ...���΂̃_���[�W
) :
	C_EnemyBase(
		//�萔�����l�Z�b�g
		EnemyType::Skull,//m_enemyType     ...�G�̎��
		147,             //m_texWidth      ...�摜1�����T�C�Y
		146,             //m_texHeight     ...�摜1���c�T�C�Y
		10,              //m_frameRate     ...�A�j���[�V�����̍X�V�p�x
		a_hpMax,         //m_hpMax         ...�ő�̗�
		a_attackDamage,  //m_attackDamage  ...�U����
		a_hitDamage,     //m_hitDamage     ...���������Ƃ��̃_���[�W
		0,               //m_attackTexIndex...�U�����������摜
		a_coinMax,       //m_coinMax       ...�����R�C���̍ő�
		a_elecShockLimit,//m_elecShockLimit...���d���E�l
		8.0f,            //m_moveSpeed     ...�ړ����x
		2.0f,            //m_gravity       ...�d��
		20.0f,           //m_jumpPower     ...�W�����v��
		2.0f,            //m_scaleSize     ...�g�嗦
		100.0f,          //m_attackDis     ...�U���\�˒�
		60,              //m_attackHitDis  ...�U���˒�
		110,             //m_attackRadius  ...�U���͈�
		150.0f,          //m_trackDist     ...�ǐՂ����鋗��
		120.0f,          //m_noTrackDist   ...�ǐՂ����Ȃ�����
		110.0f,          //m_hitWidth      ...�����蔻�艡�T�C�Y
		110.0f,          //m_hitHeight     ...�����蔻��c�T�C�Y
		{ 1,1,1,1 },     //m_defaultColor  ...�ʏ펞�̐F
		{ 0, 0, 1, 0.5f }//m_damageColor   ...�_���[�W����������Ƃ��̐F
	),
	m_fireballDamage(a_fireballDamage),
	m_bonfireDamage(a_bonfireDamage)
{
	m_isAlive = false;
}

C_Skull::C_Skull(Math::Vector2 a_pos, const C_Skull& a_enemyData) :
	C_EnemyBase(a_enemyData),
	m_fireballDamage(a_enemyData.m_fireballDamage),
	m_bonfireDamage(a_enemyData.m_bonfireDamage)
{
	//�ŗL�ϐ��̏�����
	m_fireVeilTex = nullptr;
	m_fireballTex = nullptr;
	m_bonfireTex = nullptr;
	m_confusedTex = nullptr;
	m_pos = a_pos;  //���W
	m_nowAnim = FloatAnim;//���݂̃A�j���[�V����
	m_fireVeil.texIndex = 0;
	m_fireVeil.row = 0;
	m_fireVeil.column = 0;
	m_rotationCount = 0;
	m_rollingCount = 0;
	m_waitTime = 60;
	m_isRolling = false;
	m_isConfused = false;
	m_setMoveX = 0;
	m_seismicTime = 0;
	m_isFireVeilActive = false;
	m_isAwakened = false;
	m_isErupting = false;
	m_fireballCount = 0;
}

C_Skull::~C_Skull()
{
	for (size_t i = 0; i < m_fireball.size(); i++)
	{
		delete m_fireball[i];
	}
	m_fireball.clear();
	for (size_t i = 0; i < m_bonfire.size(); i++)
	{
		delete m_bonfire[i];
	}
	m_bonfire.clear();
}

//������
void C_Skull::Init()
{
	//�摜�Z�b�g
	m_nowEnemyTex = m_enemyTex + m_nowAnim;
}

//����
void C_Skull::Action(const Math::Vector2 a_playerPos)
{
	//�΂̋ʓ���
	for (size_t i = 0; i < m_fireball.size(); i++)
	{
		m_fireball[i]->Action();
	}
	//���Γ���
	for (size_t i = 0; i < m_bonfire.size(); i++)
	{
		m_bonfire[i]->Action();
	}

	//���݂��Ă��Ȃ������烊�^�[��
	if (!m_isAlive)
	{
		//�]���鉹�����~
		(*(m_enemySfx + RollingSfx))->Stop();
		return;
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

	//�̗͂������ȉ��ɂȂ�����
	if (m_hp < m_hpMax / 2)
	{
		//�]����t���O��OFF�Ȃ�
		if (!m_isRolling)
		{
			//�o���t���O��ON
			m_isAwakened = true;
		}
	}
	//�̗͂�0�ȉ��Ȃ�
	if (m_hp <= 0 && !m_isDead)
	{
		//���S�G�t�F�N�g
		m_eOwner->GetEffectManager()->SetBossDeathEffect(m_pos.x, m_pos.y, true);
		
		//�����������Đ�
		(*(m_enemySfx + ExplosionSfx))->Play();
		
		//���S�t���O��ON
		m_isDead = true;

		//�����t���O��OFF
		m_isConfused = false;
	}

	//���S�t���O��ON�Ȃ�
	if (m_isDead)
	{
		//�]���鉹�����~
		(*(m_enemySfx + RollingSfx))->Stop();

		//���S�A�j���[�V����
		AnimationUpdate(DeathAnim);
		return;
	}

	//�_���[�W����
	Damage();

	//���d��Ԃ̕ύX
	ChangeElecShockState();

	//���d��Ԃ̍X�V
	UpdateElecShock();

	//���d��Ԃł���΃��^�[��
	if (m_isElecShock)
	{
		//�t�@�C�A�x�[���A�N�e�B�u�t���O��OFF
		m_isFireVeilActive = false;

		//�]���鉹�����~
		(*(m_enemySfx + RollingSfx))->Stop();
		return;
	}

	//�ǂɂԂ����Ă�����
	if (m_isHitWall)
	{
		//�]����񐔃J�E���g��������
		m_rollingCount = 0;

		//��]�񐔂�������
		m_rotationCount = 0;

		//�]����t���O��OFF
		m_isRolling = false;

		//�U������t���O��OFF
		m_isAttackHit = false;

		//�ǏՓ˃t���O��OFF
		m_isHitWall = false;
		
		//�������Ă�����
		if (m_isConfused)
		{
			//�Փˉ������Đ�
			(*(m_enemySfx + CollisionSfx))->Play();

			//���˂�
			Jump(m_jumpPower);

			//�������Ԃ�ݒ�
			m_waitTime = m_confusionTimeMax;

			//�n�k�̎��Ԃ��Z�b�g
			m_seismicTime = m_seismicTimeMax;
		}
		else
		{
			m_texAngle = 0;

			//�o���t���O��ON�Ȃ�
			if (m_isAwakened)
			{
				//���΃t���O��OFF�Ȃ�
				if (!m_isErupting)
				{
					//���Δ����m��
					if (CheckProbability(m_eruptingProb))
					{
						//���΃t���OON
						m_isErupting = true;

						//�΂̋ʂ̌��̐ݒ�
						m_fireballCount = m_fireballCountMax;
					}
				}
			}
		}
	}

	//�n�k�̎c�莞�Ԃ���������
	if (m_seismicTime > 0)
	{
		//�n�k�̎��Ԃ����炷
		m_seismicTime--;

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
	}

	//���΃t���O��ON���]����t���O��OFF�Ȃ�
	if (m_isErupting && !m_isRolling)
	{
		//�t�@�C�A�{�[���̔����Ԋu�ɍ��킹��
		if (m_frameCnt % m_fireballEmitRate == 0)
		{
			//�t�@�C�A�{�[���̌��J�E���g��0���傫�����
			if (m_fireballCount > 0)
			{
				//�t�@�C�A�{�[���̌��J�E���g�����炷
				m_fireballCount--;

				//�΂̋ʔ���
				EmitFireball();

				//�t�@�C�A�x�[���A�N�e�B�u�t���O��OFF
				m_isFireVeilActive = false;

				//�]���鉹�����~
				(*(m_enemySfx + RollingSfx))->Stop();

				//���^�[��
				return;
			}
			else
			{
				//���΃t���O��OFF
				m_isErupting = false;
			}
		}
	}

	//�A�N�e�B�u�t���O��OFF�܂���
	//�ҋ@���ԂȂ�
	if (!m_isActive || m_waitTime > 0)
	{
		//�ҋ@���Ԃ����炷
		if (m_waitTime > 0)
		{
			m_waitTime--;
		}

		//�]���鉹�����~
		(*(m_enemySfx + RollingSfx))->Stop();

		//�������Ă���Ȃ�
		if (m_isConfused)
		{
			//�t�@�C�A�x�[���A�N�e�B�u�t���O��OFF
			m_isFireVeilActive = false;

			//�Đ�����ĂȂ�������
			if (!(*(m_enemySfx + ConfusedSfx))->IsPlay())
			{
				//�����������Đ�
				(*(m_enemySfx + ConfusedSfx))->Play();
			}
			return;
		}

		//���̏�ŕ��V
		AnimationUpdate(FloatAnim);
		return;
	}

	//�]�����Ă��Ȃ�������
	if (!m_isRolling)
	{
		//�����t���O��OFF
		m_isConfused = false;

		//�{�^������
		m_eOwner->GetGimicMgr()->GetButton()->SetButton();

		//�����������~
		(*(m_enemySfx + ConfusedSfx))->Stop();

		//�]�����Ă��鎞�̉��ړ��ʂ�ݒ�
		m_setMoveX = m_pos.x < a_playerPos.x ? m_moveSpeed : -m_moveSpeed;

		//�摜�̊p�x��0�x
		m_texAngle = 0;

		//�]����t���O��ON
		m_isRolling = true;

		//�U������t���O��ON
		m_isAttackHit = true;
	}

	//�]�����Ă�����
	if (m_isRolling)
	{
		//�o���t���O��ON�Ȃ�
		if (m_isAwakened)
		{
			//�t�@�C�A�x�[���A�N�e�B�u�t���O��ON
			m_isFireVeilActive = true;
		}

		//�]���鉹�����Đ�
		if (!(*(m_enemySfx + RollingSfx))->IsPlay())
		{
			(*(m_enemySfx + RollingSfx))->Play();
		}

		//�v���C���[�̕����Ɉړ��ʂ�����
		m_move.x = m_setMoveX;
		
		//�m���ŉ΂�����
		if (CheckProbability(m_bonfireProb))
		{
			EmitBonfire(m_pos);
		}
	}

	//�E�Ɉړ�����Ȃ�
	if (m_move.x > 0)
	{
		//����]
		m_texAngle -= m_rotationAngle;

		//�p�x��0�`359�ɕ␳
		if (m_texAngle < 0)
		{
			m_texAngle += 360;
		}

		//1��]������
		if (m_texAngle == 0)
		{
			//��]�񐔂��J�E���g
			m_rotationCount++;
		}

	}
	//���Ɉړ�����Ȃ�
	else if (m_move.x < 0)
	{
		//�E��]
		m_texAngle += m_rotationAngle;

		//�p�x��0�`359�ɕ␳
		if (m_texAngle >= 360)
		{
			m_texAngle -= 360;
		}

		//1��]������
		if (m_texAngle == 0)
		{
			//��]�񐔂��J�E���g
			m_rotationCount++;
		}
	}

	//��]�񐔃J�E���g����]�񐔂̍ő�ȉ��Ȃ�
	if (m_rotationCount >= m_rotationCountMax)
	{
		//�摜�̎w�W��߂�
		m_texIndex = 0;

		//�摜�̊p�x��0�x
		m_texAngle = 0;

		//��]�񐔂�������
		m_rotationCount = 0;

		//�]����񐔂��J�E���g
		m_rollingCount++;

		//�]����񐔃J�E���g���]����񐔂̍ő喢���Ȃ�
		if (m_rollingCount < m_rollingCountMax)
		{
			//�x�e���Ԃ�ݒ�
			m_waitTime = m_restTimeMax;

			//�]����t���O��OFF
			m_isRolling = false;

			//�U������t���O��OFF
			m_isAttackHit = false;

			//�o���t���O��ON�Ȃ�
			if (m_isAwakened)
			{
				//���΃t���O��OFF�Ȃ�
				if (!m_isErupting)
				{
					//���Δ����m��
					if (CheckProbability(m_eruptingProb))
					{
						//���΃t���OON
						m_isErupting = true;

						//�΂̋ʂ̌��̐ݒ�
						m_fireballCount = m_fireballCountMax;
					}
				}
			}
		}
	}
}

//�X�V
void C_Skull::Update(const float a_scrollX, const float a_scrollY)
{
	//�΂̋ʍX�V
	for (size_t i = 0; i < m_fireball.size(); i++)
	{
		m_fireball[i]->Update(a_scrollX, a_scrollY);

		if (!m_fireball[i]->GetGroundHit())continue;

		//���e���W�̎擾
		Math::Vector2 fireballPos = m_fireball[i]->GetPos();

		//���e���W�ɕ��΂𔭐�
		EmitBonfire(fireballPos);

		//�폜����
		delete m_fireball[i];

		auto itr = m_fireball.begin();

		m_fireball.erase(itr + i);
	}

	//���΂̍X�V
	for (size_t i = 0; i < m_bonfire.size(); i++)
	{
		m_bonfire[i]->Update(a_scrollX, a_scrollY);

		//�폜����
		if (m_bonfire[i]->GetAlive())continue;

		delete m_bonfire[i];

		auto itr = m_bonfire.begin();

		m_bonfire.erase(itr + i);
	}
	
	//�t�@�C�A�x�[���G�t�F�N�g�̍X�V
	EffectUpdate(&m_fireVeil);
	
	//���݂��Ă��Ȃ������烊�^�[��
	if (!m_isAlive) return;

	//������Ԃ�������
	if (m_isConfused)
	{
		//�����G�t�F�N�g�̍X�V
		EffectUpdate(&m_confused);
	}

	//�ړ���������ɍ��킹�Č����Ă������ς���
	if (m_move.x > 0)
	{
		m_scale.x = -m_scaleSize;
	}
	else if (m_move.x < 0)
	{
		m_scale.x = m_scaleSize;
	}


	//���W�m��
	m_pos += m_move;

	//�s��쐬
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);     //�g��s��̍쐬
	m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(m_texAngle));//��]�s��̍쐬
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x + m_shakeX - a_scrollX, m_pos.y - a_scrollY, 0);//�ړ��s��̍쐬
	m_mat = m_scaleMat * m_rotationMat * m_transMat;//�s��̍���

	//�΂̃x�[���̍s��쐬
	m_fireVeilScaleMat = Math::Matrix::CreateScale(m_fireVeilScaleSize, m_fireVeilScaleSize, 0);//�g��s��̍쐬
	m_fireVeilMat = m_fireVeilScaleMat * m_transMat;
}

void C_Skull::Draw()
{
	//�΂̋ʂ̕`��
	for (size_t i = 0; i < m_fireball.size(); i++)
	{
		m_fireball[i]->Draw();
	}

	//�t�@�C�A�x�[���̕`��
	Math::Rectangle fRect = { m_fireVeil.column * m_fireVeil.texWidth,m_fireVeil.row * m_fireVeil.texHeight,
								m_fireVeil.texWidth,m_fireVeil.texHeight };
	Math::Color fColor = { 1,1,1,0.5f };
	if (m_isFireVeilActive)
	{
		D3D.SetBlendState(BlendMode::Add);
		SHADER.m_spriteShader.SetMatrix(m_fireVeilMat);
		SHADER.m_spriteShader.DrawTex(m_fireVeilTex, 0, 0, &fRect, &fColor);
		D3D.SetBlendState(BlendMode::Alpha);
	}

	//�G�̕`��
	C_EnemyBase::Draw();

	//�t�@�C�A�x�[���̕`��
	if (m_isFireVeilActive)
	{
		D3D.SetBlendState(BlendMode::Add);
		SHADER.m_spriteShader.SetMatrix(m_fireVeilMat);
		SHADER.m_spriteShader.DrawTex(m_fireVeilTex, 0, 0, &fRect, &fColor);
		D3D.SetBlendState(BlendMode::Alpha);
	}

	//���Ε`��
	for (size_t i = 0; i < m_bonfire.size(); i++)
	{
		m_bonfire[i]->Draw();
	}

	//�������Ă��Ȃ���΃��^�[��
	if (m_isConfused)
	{
		//�����摜
		Math::Rectangle cRect = { m_confused.texIndex * m_confused.texWidth,0,
								  m_confused.texWidth,m_confused.texHeight };
		Math::Color cColor = { 1,1,1,1 };
		SHADER.m_spriteShader.SetMatrix(m_transMat);
		SHADER.m_spriteShader.DrawTex(m_confusedTex, 0, 0, &cRect, &cColor);
	}
}

//�΂̋ʔ����֐�
void C_Skull::EmitFireball()
{
	//���ˉ�
	(*(m_enemySfx + ShotSfx))->Play();
	m_fireball.push_back(new C_Fireball(m_pos, m_fireballDamage));
	m_fireball.back()->SetTex(m_fireballTex);
}

//���Δ����֐�
void C_Skull::EmitBonfire(Math::Vector2 a_pos)
{
	//���Ή������Đ�
	(*(m_enemySfx + IgnitionSfx))->Play();
	m_bonfire.push_back(new C_Bonfire(a_pos, m_bonfireDamage));
	m_bonfire.back()->SetTex(m_bonfireTex);
}

//�A�j���[�V�����X�V
void C_Skull::AnimationUpdate(AnimationType a_animation)
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
		case FloatAnim:
			//�A�j���[�V���������[�v
			if (m_texIndex >= m_floatMax)m_texIndex = 0;
			break;
		case DeathAnim:
			//�Ō�̉摜�܂ōs�����瑶�݃t���O��OFF�ɂ���
			if (m_texIndex >= m_deathMax && m_isAlive)m_isAlive = false;
			break;
		default:
			break;
		}
	}
}

void C_Skull::MapHitX(float a_posX, float a_moveX, char a_mapData)
{
	C_EnemyBase::MapHitX(a_posX, a_moveX);

	//�����u���b�N�ɂԂ����Ă����ꍇ
	if (a_mapData == '!')
	{
		//�x�e���Ԃ��Z�b�g
		m_waitTime = m_restTimeMax;
	}
	//�����u���b�N�ȊO�Ȃ�
	else
	{
		//�����t���O��ON
		m_isConfused = true;
	}
}
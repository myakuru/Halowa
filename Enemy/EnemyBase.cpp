#include"EnemyBase.h"
#include "../Scene.h"
#include "../Constants.h"

C_EnemyBase::C_EnemyBase(
	//�G���ʒ萔�Z�b�g�p�̈���
	EnemyType a_enemyType,     //m_enemyType     ...�G�̎��
	int   a_texWidth, 	       //m_texWidth      ...�摜1�����T�C�Y
	int   a_texHeight,	       //m_texHeight     ...�摜1���c�T�C�Y
	int   a_frameRate,         //m_frameRate     ...�A�j���[�V�����̍X�V�p�x
	int   a_hpMax,             //m_hpMax         ...�ő�̗�
	int   a_attackDamage,      //m_attackDamage  ...�U����
	int   a_hitDamage,         //m_hitDamage     ...���������Ƃ��̃_���[�W
	int   a_attackTexIndex,    //m_attackTexIndex...�U�����������摜
	int   a_coinMax,           //m_coinMax       ...�����R�C���̍ő�
	int   a_elecShockLimit,    //m_elecShockLimit...���d���E�l
	float a_moveSpeed,	       //m_moveSpeed     ...�ړ����x
	float a_gravity,	       //m_gravity       ...�d��
	float a_jumpPower,	       //m_jumpPower     ...�W�����v��
	float a_scaleSize,	       //m_scaleSize     ...�g�嗦
	float a_attackDis,	       //m_attackDis     ...�U���\�˒�
	float a_attackHitDis,      //m_attackHitDis  ...�U���˒�
	float a_attackRadius,      //m_attackRadius  ...�U���͈�
	float a_trackDist,	       //m_trackDist     ...�ǐՂ����鋗��
	float a_noTrackDist,       //m_noTrackDist   ...�ǐՂ����Ȃ�����
	float a_hitWidth,          //m_hitWidth      ...�����蔻�艡�T�C�Y
	float a_hitHeight,         //m_hitHeight     ...�����蔻��c�T�C�Y
	Math::Color a_defaultColor,//m_defaultColor  ...�ʏ펞�̐F
	Math::Color a_damageColor  //m_damageColor   ...�_���[�W����������Ƃ��̐F
) : 
	//�|�C���^�[������
	m_eOwner(nullptr),
	m_nowEnemyTex(nullptr),
	m_enemyTex(nullptr),
	m_elecShockTex(nullptr),
	m_elecShockSfx(nullptr),
	m_enemySfx(nullptr),
	//�G���ʒ萔�Z�b�g
	m_enemyType(a_enemyType),          //�G�̎��
	m_texWidth(a_texWidth),		       //�摜1�����T�C�Y
	m_texHeight(a_texHeight),	       //�摜1���c�T�C�Y
	m_frameRate(a_frameRate),          //�A�j���[�V�����̍X�V�p�x
	m_hpMax(a_hpMax),                  //�ő�̗�
	m_attackDamage(a_attackDamage),    //�U����
	m_hitDamage(a_hitDamage),          //���������Ƃ��̃_���[�W
	m_attackTexIndex(a_attackTexIndex),//�U�����������摜
	m_coinMax(a_coinMax),              //�����R�C���̍ő�
	m_elecShockLimit(a_elecShockLimit),//���d���E�l
	m_moveSpeed(a_moveSpeed),	       //�ړ����x
	m_gravity(a_gravity),		       //�d��
	m_jumpPower(a_jumpPower),	       //�W�����v��
	m_scaleSize(a_scaleSize),	       //�g�嗦
	m_attackDis(a_attackDis),          //�U���\�˒�
	m_attackHitDis(a_attackHitDis),    //�U���˒�
	m_attackRadius(a_attackRadius),    //�U���͈�
	m_trackDist(a_trackDist),	       //�ǐՂ����鋗��
	m_noTrackDist(a_noTrackDist),      //�ǐՂ����Ȃ�����
	m_hitWidth(a_hitWidth),            //�����蔻�艡�T�C�Y
	m_hitHeight(a_hitHeight),          //�����蔻��c�T�C�Y
	m_defaultColor(a_defaultColor),    //�ʏ펞�̐F
	m_damageColor(a_damageColor)       //�_���[�W����������Ƃ��̐F
{
	//�G���ʕϐ��̏�����
	m_isAlive        = true;     //���݃t���O
	m_isDead         = false;    //���S�t���O
	m_isActive       = false;    //�A�N�e�B�u�t���O
	m_isDamage       = false;    //�_���[�W�t���O
	m_isElecShock    = false;    //���d�t���O
	m_isElecShockHit = false;    //���d�q�b�g�t���O
	m_isHitWall      = false;    //�W�����v�t���O
	m_isJump         = false;    //�s���~�܂�t���O
	m_isAttack       = false;    //�U�����t���O
	m_isAttackHit    = false;    //�U������t���O
	m_isTracking     = false;    //�ǐՃt���O
	m_hp             = m_hpMax;  //�̗�
	m_coinDropCount  = m_coinMax;//�����R�C������
	m_elecShockGauge = 0;	     //���d�~�ϒl
	m_elecShockTime  = 0;        //���d�p������
	m_texIndex       = 0;	     //���݃X�v���C�g�̉����ڂ̉摜��
	m_frameCnt       = 0;	     //�A�j���[�V�����t���[���J�E���g�p
	m_texAngle       = 0.0f;     //�摜�̊p�x(degree)
	m_shakeX         = 0.0f;     //���d�ɂ��k��
	m_move  = { 0,0 };					  //�ړ���
	m_scale = { m_scaleSize,m_scaleSize };//�g�嗦
	m_color = m_defaultColor;    //�F

	//���d�G�t�F�N�g�p�ϐ�������
	m_elecShock.texIndex = 0;//���݃X�v���C�g�̉����ڂ̉摜��

	//�G�̃T�C�Y�ɍ��킹�Ċg�嗦�v�Z���A����ɕ␳�l���v���X
	const float scaleX = (m_texWidth * m_scale.x) / m_elecShock.texWidth + 0.5f;
	const float scaleY = (m_texHeight * m_scale.y) / m_elecShock.texHeight + 0.5f;
	m_elecShockScale = { scaleX,scaleY };//�g�嗦
}

C_EnemyBase::C_EnemyBase(const C_EnemyBase& a_enemyData) : 
	//�|�C���^�[������
	m_eOwner(nullptr),
	m_nowEnemyTex(nullptr),
	m_enemyTex(nullptr),
	m_elecShockTex(nullptr),
	m_elecShockSfx(nullptr),
	m_enemySfx(nullptr),
	//�G���ʒ萔�Z�b�g
	m_enemyType(a_enemyData.m_enemyType),          //�G�̎��
	m_texWidth(a_enemyData.m_texWidth),		       //�摜1�����T�C�Y
	m_texHeight(a_enemyData.m_texHeight),	       //�摜1���c�T�C�Y
	m_frameRate(a_enemyData.m_frameRate),          //�A�j���[�V�����̍X�V�p�x
	m_hpMax(a_enemyData.m_hpMax),                  //�ő�̗�
	m_attackDamage(a_enemyData.m_attackDamage),    //�U����
	m_hitDamage(a_enemyData.m_hitDamage),          //���������Ƃ��̃_���[�W
	m_attackTexIndex(a_enemyData.m_attackTexIndex),//�U�����������摜
	m_coinMax(a_enemyData.m_coinMax),              //�����R�C���̍ő�
	m_elecShockLimit(a_enemyData.m_elecShockLimit),//���d���E�l
	m_moveSpeed(a_enemyData.m_moveSpeed),	       //�ړ����x
	m_gravity(a_enemyData.m_gravity),		       //�d��
	m_jumpPower(a_enemyData.m_jumpPower),	       //�W�����v��
	m_scaleSize(a_enemyData.m_scaleSize),	       //�g�嗦
	m_attackDis(a_enemyData.m_attackDis),          //�U���\�˒�
	m_attackHitDis(a_enemyData.m_attackHitDis),    //�U���˒�
	m_attackRadius(a_enemyData.m_attackRadius),    //�U���͈�
	m_trackDist(a_enemyData.m_trackDist),	       //�ǐՂ����鋗��
	m_noTrackDist(a_enemyData.m_noTrackDist),      //�ǐՂ����Ȃ�����
	m_hitWidth(a_enemyData.m_hitWidth),            //�����蔻�艡�T�C�Y
	m_hitHeight(a_enemyData.m_hitHeight),          //�����蔻��c�T�C�Y
	m_defaultColor(a_enemyData.m_defaultColor),    //�ʏ펞�̐F
	m_damageColor(a_enemyData.m_damageColor)       //�_���[�W����������Ƃ��̐F
{
	//�G���ʕϐ��̏�����
	m_isAlive = true;     //���݃t���O
	m_isDead = false;    //���S�t���O
	m_isActive = false;    //�A�N�e�B�u�t���O
	m_isDamage = false;    //�_���[�W�t���O
	m_isElecShock = false;    //���d�t���O
	m_isElecShockHit = false;    //���d�q�b�g�t���O
	m_isHitWall = false;    //�W�����v�t���O
	m_isJump = false;    //�s���~�܂�t���O
	m_isAttack = false;    //�U�����t���O
	m_isAttackHit = false;    //�U������t���O
	m_isTracking = false;    //�ǐՃt���O
	m_hp = m_hpMax;  //�̗�
	m_coinDropCount = m_coinMax;//�����R�C������
	m_elecShockGauge = 0;	     //���d�~�ϒl
	m_elecShockTime = 0;        //���d�p������
	m_texIndex = 0;	     //���݃X�v���C�g�̉����ڂ̉摜��
	m_frameCnt = 0;	     //�A�j���[�V�����t���[���J�E���g�p
	m_texAngle = 0.0f;     //�摜�̊p�x(degree)
	m_shakeX = 0.0f;     //���d�ɂ��k��
	m_move = { 0,0 };					  //�ړ���
	m_scale = { m_scaleSize,m_scaleSize };//�g�嗦
	m_color = m_defaultColor;    //�F

	//���d�G�t�F�N�g�p�ϐ�������
	m_elecShock.texIndex = 0;//���݃X�v���C�g�̉����ڂ̉摜��

	//�G�̃T�C�Y�ɍ��킹�Ċg�嗦�v�Z���A����ɕ␳�l���v���X
	const float scaleX = (m_texWidth * m_scale.x) / m_elecShock.texWidth + 0.5f;
	const float scaleY = (m_texHeight * m_scale.y) / m_elecShock.texHeight + 0.5f;
	m_elecShockScale = { scaleX,scaleY };//�g�嗦
}

//���d��Ԃ̕ύX
bool C_EnemyBase::ChangeElecShockState()
{
	//���d�~�ϒl�����d���E�l���ȏ�Ȃ�
	//���d�t���O��OFF�Ȃ�
	if (m_elecShockGauge >= m_elecShockLimit && !m_isElecShock)
	{
		//�摜�������ʒu�ɖ߂�
		m_elecShock.texIndex = 0;

		//���d�ő厞�Ԃ����d�p�����ԂɃZ�b�g
		m_elecShockTime = m_elecShockTimeMax;

		//���d�t���O��ON
		m_isElecShock = true;

		return true;
	}

	//���d�t���O��ON�����d�p�����Ԃ�0�ȉ��ɂȂ�����
	if (m_elecShockTime <= 0 && m_isElecShock)
	{
		//���d�~�ϒl�����Z�b�g
		m_elecShockGauge = 0;

		//���d�����~�߂�
		(*m_elecShockSfx)->Stop();

		//���d�t���O��OFF
		m_isElecShock = false;
	}
	return false;
}

//���d��Ԃ̍X�V
void C_EnemyBase::UpdateElecShock()
{
	//���d�p�����Ԃ����炷
	if (m_elecShockTime > 0)
	{
		m_elecShockTime--;
	}

	//���d��Ԃł����
	if (m_isElecShock)
	{
		//���d���ʉ����Ȃ��Ă��Ȃ�������
		if ((*m_elecShockSfx)->IsPlay() == false)
		{
			//���d���Đ�
			(*m_elecShockSfx)->Play();
		}
		
		//���d�G�t�F�N�g�̍X�V
		EffectUpdate(&m_elecShock);
	}

	//���d��Ԃł���ΓG��k��������
	if (m_isElecShock)
	{
		m_shakeX = m_shakeX < 0 ? m_shakePower : -m_shakePower;
	}
	else
	{
		m_shakeX = 0;
	}

	//�X�N���[���̒l���擾
	const float scrollX = m_eOwner->GetMap()->GetScrollX();
	const float scrollY = m_eOwner->GetMap()->GetScrollY();

	m_elecShockScaleMat = Math::Matrix::CreateScale(m_elecShockScale.x, m_elecShockScale.y, 0);//�g��s��̍쐬
	m_elecShockTransMat = Math::Matrix::CreateTranslation(m_pos.x - scrollX, m_pos.y - scrollY, 0);//�ړ��s��̍쐬
	m_elecShockMat = m_elecShockScaleMat * m_elecShockTransMat;//�G�̈ړ��s����g�p�����s�񍇐�
}

//���d�G�t�F�N�g�`��
void C_EnemyBase::DrawElecShock() const
{
	//���d��ԂłȂ���΃��^�[��
	if (!m_isElecShock)return;

	//m_elecShock.texIndex�Ŏw�肳�ꂽ�ʒu��؎�
	const Math::Rectangle shockRect = { m_elecShock.texWidth * m_elecShock.texIndex,0,m_elecShock.texWidth,m_elecShock.texHeight };

	//�s����Z�b�g
	SHADER.m_spriteShader.SetMatrix(m_elecShockMat);

	//�`��
	SHADER.m_spriteShader.DrawTex(m_elecShockTex, 0, 0, &shockRect, &Math::Color{ 1,1,1,1 });
}

//�`��
void C_EnemyBase::Draw()
{
	//�����Ă��Ȃ������烊�^�[��
	if (!m_isAlive) return;

	//m_texIndex�Ŏw�肳�ꂽ�ʒu��؎�
	const Math::Rectangle enemyRect = { m_texWidth * m_texIndex,0,m_texWidth,m_texHeight };

	//�s����Z�b�g
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//�`��
	SHADER.m_spriteShader.DrawTex(m_nowEnemyTex, 0, 0, &enemyRect, &m_color);

	//�̗͂����������犴�d�摜��`�悵�Ȃ�
	if (m_hp <= 0)return;

	//���d�G�t�F�N�g�`��
	DrawElecShock();
	


	//��
	//�X�N���[���̒l���擾
	//const float scrollX = m_eOwner->GetMap()->GetScrollX();
	//const float scrollY = m_eOwner->GetMap()->GetScrollY();
	//Math::Matrix mat = Math::Matrix::CreateTranslation(m_pos.x - scrollX, m_pos.y - scrollY, 0);
	//SHADER.m_spriteShader.SetMatrix(mat);
	//SHADER.m_spriteShader.DrawCircle(0, 0, (int)m_hitWidth, &Math::Color{ 1,0,0,0.5f });
	//SHADER.m_spriteShader.DrawCircle(0, 0, 5, &Math::Color{ 0,0,1,0.5f });
}

//�}�b�v�����蔻��p X����
void C_EnemyBase::MapHitX(float a_posX, float a_moveX)
{
	m_pos.x     = a_posX;
	m_move.x    = a_moveX;
	m_isHitWall = true;
}

//�}�b�v�����蔻��p Y����
void C_EnemyBase::MapHitY(float a_posY, float a_moveY, bool a_jump)
{
	m_pos.y  = a_posY;
	m_move.y = a_moveY;
	m_isJump = a_jump;
}

//Effect1�\���̂̍X�V
void C_EnemyBase::EffectUpdate(Effect1* a_effect)
{
	//�t���[�����[�g�ɍ��킹�ăA�j���[�V�������X�V
	if (m_frameCnt % a_effect->frameRate == 0)
	{
		//�摜��i�߂�
		a_effect->texIndex++;

		//�Ō�̉摜�܂ōs�����珉���l�ɖ߂�
		if (a_effect->texIndex >= a_effect->texNumMax)
		{
			a_effect->texIndex = 0;
		}
	}
}

//Effect2�\���̂̍X�V
void C_EnemyBase::EffectUpdate(Effect2* a_effect)
{
	//�t���[�����[�g�ɍ��킹�ăA�j���[�V�������X�V
	if (m_frameCnt % a_effect->frameRate == 0)
	{
		//�摜��i�߂�
		a_effect->texIndex++;

		//�摜���Ō�܂ł�������
		if (a_effect->texIndex >= a_effect->texNumMax)
		{
			//�摜�������摜�ɖ߂�
			a_effect->texIndex = 0;
		}
		a_effect->row = a_effect->texIndex / a_effect->rowMax;//�s�����擾
		a_effect->column = a_effect->texIndex % a_effect->columnMax;//�񐔂��擾
	}
}

//�W�����v����
bool C_EnemyBase::Jump(float a_jumpPower)
{
	//�W�����v�����Ă��Ȃ�������
	if (!m_isJump)
	{
		//�W�����v�O�̍U���t���O��OFF
		//m_isAttack = false;

		//�W�����v
		m_move.y = a_jumpPower;
		m_isJump = true;

		return true;
	}
	return false;
}

//�_���[�W����
bool C_EnemyBase::Damage()
{
	//�_���[�W�t���O��ON�Ȃ�
	if (m_isDamage)
	{
		//�G�摜��ԐF�ɂ���
		m_color = m_damageColor;
		m_isDamage = false;
		return true;
	}
	else
	{
		//���̐F�ɖ߂��Ă���
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

//�m���`�F�b�N
bool C_EnemyBase::CheckProbability(float a_probability)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	//1�`100�̗���
	static std::uniform_real_distribution<> dist(0.0f, 100.0f);

	//�w�肳�ꂽ�m���������������������傫��������
	if (a_probability > dist(gen))
	{
		return true;
	}
	return false;
}

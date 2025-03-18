#pragma once
#include "../../EnemyBase.h"
#include "Smoke.h"


//�{�X���{�b�g�N���X
class C_BossRobot : public C_EnemyBase
{
public:
	//C_BossRobot(Math::Vector2 a_pos);
	C_BossRobot(
		int   a_hpMax,
		int   a_attackDamage,
		int   a_hitDamage,
		int   a_coinMax,
		int   a_elecShockLimit,
		int   a_smokeDamage
	);
	~C_BossRobot();

	C_BossRobot(Math::Vector2 a_pos, const C_BossRobot& a_enemyData);

	//������
	void Init()override;
	//����
	void Action(const Math::Vector2 playerPos)override;
	//�X�V
	void Update(const float a_scrollX, const float a_scrollY)override;

	//�`��
	void Draw()override;

	//�}�b�v�����蔻��p Y����
	void MapHitY(float a_posY, float a_moveY, bool a_jump) override;

	//���A�A�j���[�V�����̎��s
	void ExecuteHello() { m_animHallo = true; }

	//������������������������������������������������������������
	// �Z�b�^�[
	//������������������������������������������������������������

	//�A�N�e�B�u�t���O
	void SetActive(bool a_isActive) { m_isActive = a_isActive; }

	//���摜
	void SetSmokeTex(KdTexture* a_smokeTex) { m_smokeTex = a_smokeTex; }

	//������������������������������������������������������������
	// �Q�b�^�[
	//������������������������������������������������������������
	
	//���̃C���X�^���X�擾
	const C_Smoke* GetSmoke() { return m_smoke; }

	//�U���̃m�b�N�o�b�N�p�x
	const float GetAttackAngle() { return m_attackAngle; }


private:

	//�n�C�W�����v��̒��n
	void HighJumpLand();

	//�������֐�
	void EmitSmoke();

	//���p�[�e�B�N���p�̃|�C���^
	C_Smoke* m_smoke;

	//���摜
	KdTexture* m_smokeTex;

	//�A�j���[�V�����̎��
	enum AnimationType
	{
		IdleAnim,  //�����p
		WalkAnim,  //����
		AttackAnim,//�U��
		DeathAnim, //���S
		HelloAnim  //���A
	};
	//�T�E���h�̎��
	enum SoundEffectType
	{
		LandingSfx,//���n
		WalkSfx,   //����
		DeathSfx   //���S
	};

	//�A�j���[�V�����X�V
	void AnimationUpdate(AnimationType a_animation);

	//�A�j���[�V�����ő吔
	static const int m_idleMax    = 21;//�����p
	static const int m_walkingMax = 25;//����
	static const int m_runMax     = 25;//����
	static const int m_attackMax  = 21;//�U��
	static const int m_deathMax   = 27;//���S
	static const int m_helloMax   = 41;//���A

	static const int m_highJumpIntervalMax = 60 * 2;//�n�C�W�����v�̃C���^�[�o���̃Z�b�g����
	static const int m_cooldownTimeMax = 60;//�n�C�W�����v��̍d�����Ԃ̍ő�
	static const int m_seismicFrameRate = 5;//�n�ʂ̐k���̃t���[���Ԋu

	const int m_smokeDamage;
	const float m_highJumpPower = 30.0f;    //�n�C�W�����v�̃W�����v��
	const float m_highJumpNoTrackDist = 20; //�n�C�W�����v��̒��n�ꏊ�܂ł̋���
	const float m_drawCorrY = 70;           //Y���W�̕`�悸��␳�l
	const float m_seismicShakePower = 10.0f;//���n�ɂ��n�ʂ̐k���̗�
	const float m_attackAngle = 60.0f;//�U���̃m�b�N�o�b�N�p�x
	
	AnimationType m_nowAnim; //���݂̃A�j���[�V����
	bool  m_animHallo;       //���A�t���O
	bool  m_isHighJump;      //�n�C�W�����v�t���O
	int   m_highJumpInterval;//�n�C�W�����v�̃C���^�[�o��
	int   m_cooldownTime;    //�n�C�W�����v��̍d������
	float m_landingPosX;     //�n�C�W�����v��̒��n�ꏊ
};
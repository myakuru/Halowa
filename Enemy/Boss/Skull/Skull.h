#pragma once
#include "../../EnemyBase.h"
#include "Bonfire.h"
#include "Fireball.h"
#include <vector>
#include <random>

//���{�b�g�N���X
class C_Skull : public C_EnemyBase
{
public:
	//C_Skull(Math::Vector2 a_pos);
	C_Skull(
		int   a_hpMax,
		int   a_attackDamage,
		int   a_hitDamage,
		int   a_coinMax,
		int   a_elecShockLimit,
		int   a_fireballDamage,
		int   a_bonfireDamage
	);
	~C_Skull();

	C_Skull(Math::Vector2 a_pos, const C_Skull& a_enemyData);

	//������
	void Init()override;
	//����
	void Action(const Math::Vector2 a_playerPos)override;
	//�X�V
	void Update(const float a_scrollX, const float a_scrollY)override;

	//�`��
	void Draw()override;

	//�A�N�e�B�u�t���O
	void SetActive(bool a_isActive) { m_isActive = a_isActive; }

	//�΂̃x�[���摜
	void SetFireVeilTex(KdTexture* a_fTex) { m_fireVeilTex = a_fTex; }

	//���΂̉摜
	void SetBonfireTex(KdTexture* a_bTex) { m_bonfireTex = a_bTex; }

	//�����摜
	void SetConfusedTex(KdTexture* a_cTex) { m_confusedTex = a_cTex; }

	//�΂̋ʉ摜
	void SetFireballTex(KdTexture* a_fTex) { m_fireballTex = a_fTex; }

	//�_���[�W�̃Z�b�g
	bool SetDamage(int a_damage)override
	{
		if (m_isFireVeilActive)return false;
		m_hp -= a_damage;
		m_isDamage = true;
		return true;
	}

	//�΂̋ʂ̃C���X�^���X�擾
	const std::vector<C_Fireball*> GetFireball() { return m_fireball; }

	//���΂̃C���X�^���X�擾
	const std::vector<C_Bonfire*> GetBonfire() { return m_bonfire; }

	//�}�b�v�����蔻��p X����
	void MapHitX(float a_posX, float a_moveX, char a_mapData);

private:
	//�A�j���[�V�����̎��
	enum AnimationType
	{
		FloatAnim,      //���V
		DeathAnim       //���S
	};

	//�T�E���h�̎��
	enum SoundEffectType
	{
		CollisionSfx,//�Փ�
		ConfusedSfx, //����
		IgnitionSfx, //����
		ShotSfx,     //����
		RollingSfx,  //�]����
		ExplosionSfx//����
	};

	//�A�j���[�V�����X�V
	void AnimationUpdate(AnimationType a_animation);

	//���݂̃A�j���[�V����
	AnimationType m_nowAnim;

	//�A�j���[�V�����ő吔
	static const int m_floatMax = 5;//���V
	static const int m_deathMax = 2;//���S

	const float m_rotationAngle = 360.0f / 60.0f;//��]���Ă����p�x

	static const int m_rotationCountMax = 3;//��]�񐔂̍ő�
	int m_rotationCount;//��]�񐔃J�E���g

	static const int m_rollingCountMax = 3;//�]����񐔂̍ő�
	int m_rollingCount;//�]����񐔃J�E���g

	static const int m_restTimeMax = 60 * 2;//�x�e���Ԃ̍ő�
	static const int m_confusionTimeMax = 60 * 5;//�������Ԃ̍ő�
	int m_waitTime;//�ҋ@����

	static const int m_seismicTimeMax = 60 * 2;//�n�k�̍ő厞��
	static const int m_seismicFrameRate = 5;//�n�ʂ̐k���̃t���[���Ԋu
	const float m_seismicShakePower = 10.0f;//���n�ɂ��n�ʂ̐k���̗�
	int m_seismicTime;//�n�k�̎���


	bool m_isRolling; //�]����t���O
	bool m_isConfused;//�����t���O
	bool m_isAwakened;//�o���t���O

	float m_setMoveX;//�]�����Ă��鎞�̉��ړ��ʂ̐ݒ�

	//������������������������������������������������������������
	// �t�@�C�A�x�[��
	//������������������������������������������������������������

	//�t�@�C�A�x�[���摜
	KdTexture* m_fireVeilTex;

	//�t�@�C�A�x�[���G�t�F�N�g�p�\����
	Effect2 m_fireVeil = {
		512,//�摜���T�C�Y
		512,//�摜�c�T�C�Y
		8,  //�s�ő喇��
		8,  //��ő喇��
		64, //�摜����
		2   //�t���[�����[�g
	};
	const float m_fireVeilScaleSize = 1.0f;//�t�@�C�A�x�[���T�C�Y
	bool m_isFireVeilActive;//�t�@�C�A�x�[���A�N�e�B�u�t���O

	Math::Matrix m_fireVeilScaleMat;//�t�@�C�A�x�[���g��s��
	Math::Matrix m_fireVeilMat;     //�t�@�C�A�x�[�������s��
	
	//������������������������������������������������������������
	// �΂̋�
	//������������������������������������������������������������
	
	//�΂̋ʉ摜
	KdTexture* m_fireballTex;

	//�΂̋ʃC���X�^���X
	std::vector<C_Fireball*> m_fireball;

	//�΂̋ʔ����֐�
	void EmitFireball();

	//�΂̋ʃ_���[�W
	const int m_fireballDamage;

	//������������������������������������������������������������
	// ����
	//������������������������������������������������������������

	//���΃t���O
	bool m_isErupting;

	//���Δ����m��
	const float m_eruptingProb = 100.0f;

	//���΂̍ۂɔ�������t�@�C�A�{�[���̌��ő�
	static const int m_fireballCountMax = 5;

	//���΂̍ۂɔ�������t�@�C�A�{�[���̌��J�E���g
	int m_fireballCount;

	//���΂̍ۂɔ�������΂̋ʂ̔����Ԋu
	static const int m_fireballEmitRate = 10;
	
	//������������������������������������������������������������
	// ����
	//������������������������������������������������������������
	
	//���Ή摜
	KdTexture* m_bonfireTex;

	//���΃C���X�^���X
	std::vector<C_Bonfire*> m_bonfire;
	
	//���Δ����֐�
	void EmitBonfire(Math::Vector2 a_pos);

	//���Δ����m��
	const float m_bonfireProb = 1.0f;//0.7f;//%

	//���΃_���[�W
	const int m_bonfireDamage;

	//������������������������������������������������������������
	// ����
	//������������������������������������������������������������

	//�����摜
	KdTexture* m_confusedTex;

	//�����G�t�F�N�g�p�\����
	Effect1 m_confused = { 
		300,//�摜���T�C�Y
		300,//�摜�c�T�C�Y
		13,	//�摜����
		4	//�t���[�����[�g
	};
};
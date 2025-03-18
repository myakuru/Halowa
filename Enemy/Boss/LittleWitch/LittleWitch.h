#pragma once
#include "../../EnemyBase.h"
#include "EnemySpawner.h"

//���@�����N���X
class C_LittleWitch : public C_EnemyBase
{
public:
	C_LittleWitch(Math::Vector2 a_pos);
	~C_LittleWitch();

	//������
	void Init()override;
	//����
	void Action(const Math::Vector2 a_playerPos)override;
	//�X�V
	void Update(const float a_scrollX, const float a_scrollY)override;
	//�`��
	void Draw()override;

	//�}�b�v�����蔻��p Y����
	void MapHitY(float a_posY, float a_moveY, bool a_jump) override;

	//�A�N�e�B�u�t���O
	void SetActive(bool a_isActive) { m_isActive = a_isActive; }
	//���d�~�ϒl�̃Z�b�g					        
	bool SetElecShockGauge(int a_elecShockGauge) override;
	//�_���[�W�̃Z�b�g
	bool SetDamage(int a_damage)override;
	//�V�[���h�摜
	void SetShieldTex(KdTexture* a_sTex) { m_shieldTex = a_sTex; }
	//�G�X�|�i�[�摜�̃Z�b�g
	void SetEnemySpawnerTex(KdTexture* a_eTex) { m_enemySpawnerTex = a_eTex; }
	//�G�X�|�i�[�̂Ђъ���摜�̃Z�b�g
	void SetEnemySpawnerCrackTex(KdTexture* a_eTex) { m_enemySpawnerCrackTex = a_eTex; }
	
	//�V�[���h�̑ϋv��
	int GetShieldDurability() { return m_shieldDurability; }
	//�G�X�|�i�[
	C_EnemySpawner* GetEnemySpawner() { return m_enemySpawner; }

private:
	//�A�j���[�V�����̎��
	enum AnimationType
	{
		IdleAnim,     //�����p
		WalkAnim,     //����
		JumpAnim,     //�W�����v
		FallAnim,     //�~��
		LandAnim,     //���n
		AttackAnim,   //�U��
		CastSpellAnim,//���@��������
		SurprisedAnim,//����
		DeathAnim,    //���S
	};

	//�A�j���[�V�����X�V
	void AnimationUpdate(AnimationType a_animation);

	//���݂̃A�j���[�V����
	AnimationType m_nowAnim;

	//�A�j���[�V�����ő吔
	static const int m_idleMax      = 8; //�����p
	static const int m_walkMax      = 8; //����
	static const int m_jumpMax      = 3; //�W�����v
	static const int m_fallMax      = 2; //�~��
	static const int m_landMax      = 2; //���n
	static const int m_attackMax    = 2; //�U��
	static const int m_castSpellMax = 11;//���@��������
	static const int m_surprisedMax = 6; //����
	static const int m_deathMax     = 12;//���S

	//������������������������������������������������������������
	// �V�[���h
	//������������������������������������������������������������
	
	//�V�[���h�̏��
	enum class ShieldState {
		OFF,    // �V�[���h��OFF
		ON,     // �V�[���h��ON
		ACTIVE  // �V�[���h���A�N�e�B�u
	};

	//�V�[���h�摜
	KdTexture* m_shieldTex;

	//���݂̃V�[���h�̏��
	ShieldState m_nowShieldState;


	//�V�[���h�G�t�F�N�g�p�\����
	Effect2 m_shield = {
		512,//�摜���T�C�Y
		512,//�摜�c�T�C�Y
		8,  //�s�ő喇��
		8,  //��ő喇��
		64, //�摜����
		3   //�t���[�����[�g
	};
	const float m_shieldScaleSize = 0.7f;//�V�[���h�T�C�Y
	bool m_isShieldActive;//�V�[���h�A�N�e�B�u�t���O

	Math::Matrix m_shieldScaleMat;//�V�[���h�g��s��
	Math::Matrix m_shieldMat;     //�V�[���h�����s��
	Math::Color  m_shieldColor;   //�V�[���h�̐F

	//�V�[���h�̍X�V
	void ShieldUpdate();

	static const int m_shieldDurabilityMax = 5;//�V�[���h�̑ϋv�͂̍ő�
	int m_shieldDurability;//�V�[���h�̑ϋv��
	bool m_isShieldDamaged;//�V�[���h�_���[�W�t���O

	//������������������������������������������������������������
	// �G�X�|�i�[
	//������������������������������������������������������������

	//�G�X�|�i�[�C���X�^���X
	C_EnemySpawner* m_enemySpawner;

	//�G�X�|�i�[�摜
	KdTexture* m_enemySpawnerTex;

	//�G�X�|�i�[�̂Ђъ���摜
	KdTexture* m_enemySpawnerCrackTex;

	//�{�X�����m��
	static const int m_bossSummonProbability = 20;

	//�G�X�|�i�[����
	void CreateEnemySpawner();

	//������������������������������������������������������������
	// ��s
	//������������������������������������������������������������
	
	//��s
	void Fly();

	const float m_flyMoveX = 3;//��s���̈ړ���X
	const float m_flyMoveY = 3;//��s���̈ړ���Y

	bool m_isFlying;//��s�t���O

	//������������������������������������������������������������

	bool m_isCastingSpell;//���@�r���t���O
	bool m_isSurprised;   //�����t���O
	bool m_isLanded;      //���n�t���O
};
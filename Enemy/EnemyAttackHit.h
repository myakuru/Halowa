#pragma once
class Scene;
class C_EnemyMgr;
class C_Chara;

//�G�U������N���X
class C_EnemyAtkHit
{
public:
	C_EnemyAtkHit();
	~C_EnemyAtkHit() = default;

	//�v���C���[�ƓG�̓����蔻��
	void Player_EnemyHit();

	//�S�Ă̓G�̍U��
	void AllEnemiesAttack();

	//�G�Ǘ��N���X�̃C���X�^���X�Z�b�g
	void SetEnemyMgr(C_EnemyMgr* a_enemyMgr) { m_hEnemyMgr = a_enemyMgr; }

	//�v���C���[�N���X�̃C���X�^���X�Z�b�g
	void SetPlayer(C_Chara* a_player) { m_hPlayer = a_player; }

	// �I�[�i�[�̐ݒ�
	void SetOwner(Scene* owner) { m_hOwner = owner; };

private:
	//���{�b�g�̍U������
	void RobotAttackHit();

	//�O���������̍U������
	void GremlinAttackHit();

	//�{�X���{�b�g�̍U������
	void BossRobotAttackHit();

	//�X�J���̍U������
	void SkullAttackHit();

	//���̓����蔻��
	void SmokeHit();

	//���@�̓����蔻��
	void SpellHit();
	
	//�΂̋ʂ̓����蔻��
	void FireballHit();

	//���΂Ƃ̓����蔻��
	void BonfireHit();

	//�v���C���[�Ɖ~�̓����蔻��
	bool PlayerHitCircle(float circleX, float circleY, float circleRadius);

	//�m�b�N�o�b�N�v�Z
	void Knockback(Math::Vector2 a_srcPos, float a_knockForce);
	void Knockback(Math::Vector2 a_srcPos, float a_knockForce, float a_knockAngle);

	// �����o�ϐ�
	Scene* m_hOwner;
	C_EnemyMgr* m_hEnemyMgr;
	C_Chara* m_hPlayer;
};
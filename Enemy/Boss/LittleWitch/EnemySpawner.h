#pragma once
enum class EnemyType;
class Scene;

//�G�X�|�i�[�N���X
class C_EnemySpawner
{
public:
	C_EnemySpawner(EnemyType a_enemyType, Math::Vector2 a_pos);
	~C_EnemySpawner() {};

	void Update(const float a_scrollX, const float a_scrollY);
	void Draw();

	//�G�X�|�i�[�摜
	void SetTex(KdTexture* a_tex) { m_tex = a_tex; }
	//�Ђъ���摜
	void SetCrackTex(KdTexture* a_tex) { m_crackTex = a_tex; }
	//�I�[�i�[�̃C���X�^���X���Z�b�g
	void SetOwner(Scene* a_eOwner) { m_eOwner = a_eOwner; }
	//�_���[�W
	void SetDamage(int a_damage) { m_durability -= a_damage; }

	//���݃t���O
	bool GetAlive() { return m_isAlive; }
	//�����蔻��c�T�C�Y
	float GetHitHeight() { return m_hitHeight; }
	//�����蔻�艡�T�C�Y
	float GetHitWidth() { return m_hitWidth; }
	//���݂̍��W
	Math::Vector2 GetPos() { return m_pos; }


private:

	Scene* m_eOwner;      
	KdTexture* m_tex;     //�G�X�|�i�[�摜
	KdTexture* m_crackTex;//�Ђъ���摜

	EnemyType m_spawnEnemyType;//��������G�̎��

	static const int m_texNumMax = 11;   //�摜����
	static const int m_texHeight = 140;  //�摜�c�T�C�Y
	static const int m_texWidth = 100;   //�摜���T�C�Y
	static const int m_animFrameRate = 5;//�A�j���[�V�����X�V�p�x
	static const int m_durabilityMax = 5;//�ϋv�͂̍ő�
	static const int m_summonWaitTimeMax = 60 * 8;//�����܂ł̎��Ԃ̍ő�
	const float m_scaleSize = 1.5f;      //�g�嗦
	const float m_hitHeight = m_texHeight / 2 * m_scaleSize;//�����蔻��c�T�C�Y
	const float m_hitWidth  = m_texWidth / 2 * m_scaleSize; //�����蔻�艡�T�C�Y


	int  m_summonWaitTime;//�����܂ł̎���
	int  m_texIndex;
	int  m_frameCnt;
	int  m_durability;//�ϋv��
	bool m_isAlive;        //���݃t���O
	bool m_isSpawnCompleted;

	Math::Vector2 m_pos;

	Math::Matrix m_scaleMat;
	Math::Matrix m_transMat;
	Math::Matrix m_mat;
	Math::Color  m_color;
};
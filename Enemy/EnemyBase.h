#pragma once
class Scene;
//�G�̎�ޗ�
enum class EnemyType
{
	Robot,
	Frog,
	Ghost,
	Gremlin,
	Sentinel,
	BossRobot,
	Skull,
	LittleWitch
};

//�G�̊��N���X
class C_EnemyBase
{
public:

	C_EnemyBase(
		EnemyType a_enemyType,
		int   a_texWidth,
		int   a_texHeight,
		int   a_frameRate,
		int   a_hpMax,
		int   a_attackDamage,
		int   a_hitDamage,
		int   a_attackTexIndex,
		int   a_coinMax,
		int   a_elecShockLimit,
		float a_moveSpeed,
		float a_gravity,
		float a_jumpPower,
		float a_scaleSize,
		float a_attackDis,
		float a_attackHitDis,
		float a_attackRadius,
		float a_trackDist,
		float a_noTrackDist,
		float a_hitWidth,
		float a_hitHeight,
		Math::Color a_defaultColor,
		Math::Color a_damageColor
	);
	C_EnemyBase(const C_EnemyBase& a_enemyData);
	virtual ~C_EnemyBase() = default;
	
	
	virtual void Init() = 0;  //������
	virtual void Action(const Math::Vector2 a_playerPos) = 0;//����
	virtual void Update(const float a_scrollX,const float a_scrollY) = 0;//�X�V
	virtual void Draw();//�`��

	void MapHitX(float a_posX, float a_moveX);			           //�}�b�v�����蔻��p X����
	virtual void MapHitY(float a_posY, float a_moveY, bool a_jump);//�}�b�v�����蔻��p Y����


	//������������������������������������������������������������������������������������������
	// �G���ʃZ�b�^�[
	//������������������������������������������������������������������������������������������
	
	//�I�[�i�[�̃C���X�^���X���Z�b�g
	void SetOwner(Scene* a_eOwner)             { m_eOwner = a_eOwner; }
	//�G�摜�Z�b�g						   	   
	void SetEnemyTex(KdTexture* a_eTex)        { m_enemyTex = a_eTex; }
	//���d�G�t�F�N�g�摜					      
	void SetElecShockTex(KdTexture* a_sTex)    { m_elecShockTex = a_sTex; }
	//���d���f�[�^								              
	void SetElecShockSfx(std::shared_ptr<KdSoundInstance>* a_eSfx) { m_elecShockSfx = a_eSfx; }
	//�G�̉��f�[�^
	void SetEnemySfx(std::shared_ptr<KdSoundInstance>* a_eSfx)     { m_enemySfx = a_eSfx; }
	//���d�~�ϒl�̃Z�b�g					        
	virtual bool SetElecShockGauge(int a_elecShockGauge)
	{
		m_elecShockGauge += a_elecShockGauge;
		return true;
	}
	//���d�q�b�g�t���O						
	void SetElecShockHit(bool a_isElecShockHit) { m_isElecShockHit = a_isElecShockHit; }
	//�R�C��
	void SetCoinDropCount(int a_coinDropCount)  { m_coinDropCount = a_coinDropCount; }
	//�_���[�W�̃Z�b�g						        
	virtual bool SetDamage(int a_damage)
	{
		m_hp -= a_damage;
		m_isDamage = true;
		return true;
	}
	
	//������������������������������������������������������������������������������������������
	// �G���ʃQ�b�^�[
	//������������������������������������������������������������������������������������������
	
	//�G�̎��
	const EnemyType GetEnemyType()     const { return m_enemyType; }
	//���W
	const Math::Vector2 GetPos()       const { return m_pos; }
	//�������W
	const Math::Vector2 GetNextPos()   const { return m_pos + m_move; }
	//�U�����W
	const Math::Vector2 GetAttackPos() const { return m_attackPos; }
	//���݃t���O
	const bool GetAlive()              const { return m_isAlive; }
	//���S�t���O
	const bool GetDead()               const { return m_isDead; }
	//���d�t���O						  
	const bool GetElecShock()          const { return m_isElecShock; }
	//���d�q�b�g�t���O				   
	const bool GetElecShockHit()       const { return m_isElecShockHit; }
	//�U������t���O				    
	const bool GetAttackHit()          const { return m_isAttackHit; }
	//�̗�						       
	const int GetHp()                  const { return m_hp; }
	//�ő�̗�						   
	const int GetHpMax()               const { return m_hpMax; }
	//���������Ƃ��̃_���[�W		    
	const int GetHitDamage()           const { return m_hitDamage; }
	//�U���_���[�W
	const int GetAttackDamage()        const { return m_attackDamage; }
	//���d�~�ϒl						  
	const int GetElecShockGauge()      const { return m_elecShockGauge; }
	//���d���E�l						  
	const int GetElecShockLimit()      const { return m_elecShockLimit; }
	//�R�C��						    
	const int GetCoinDropCount()       const { return m_coinDropCount; }
	//�����蔻�艡�T�C�Y				  
	const float GetHitWidth()          const { return m_hitWidth; }
	//�����蔻��c�T�C�Y				  
	const float GetHitHeight()         const { return m_hitHeight; }
	//�U���͈�
	const float GetAttackRadius()      const { return m_attackRadius; }
	//���������Ƃ��̏Ռ�				  
	const float GetHitKnockForce()     const { return m_hitKnockForce; }

protected://�q�N���X�Ɍp��
	//������������������������������������������������������������
	// �G�t�F�N�g
	//������������������������������������������������������������
	
	//�G�t�F�N�g�p�\����(���X�v���C�g�p)
	struct Effect1
	{
		const int texWidth;   //�摜���T�C�Y
		const int texHeight;  //�摜�c�T�C�Y
		const int texNumMax;  //�摜����
		const int frameRate;  //�t���[�����[�g
		int texIndex;         //�摜�w�W
	};
	//�G�t�F�N�g�p�\����(�c���X�v���C�g�p)
	struct Effect2
	{
		const int texWidth; //�摜���T�C�Y
		const int texHeight;//�摜�c�T�C�Y
		const int rowMax;   //�s�ő喇��
		const int columnMax;//��ő喇��
		const int texNumMax;//�摜����
		const int frameRate;//�t���[�����[�g
		int row;            //���݂̍s
		int column;         //���݂̗�
		int texIndex;       //�摜�w�W
	};

	void EffectUpdate(Effect1* a_effect);
	void EffectUpdate(Effect2* a_effect);

	//������������������������������������������������������������
	// �G���ʊ֐�
	//������������������������������������������������������������

	//�W�����v
	bool Jump(float a_jumpPower);

	//�_���[�W
	bool Damage();

	//�m���`�F�b�N
	bool CheckProbability(float a_probability);

	//������������������������������������������������������������
	// �G���ʃ|�C���^
	//������������������������������������������������������������
	Scene* m_eOwner;//�I�[�i�[�p�C���X�^���X
	
	KdTexture* m_nowEnemyTex; //���݂̓G�摜
	KdTexture* m_enemyTex;    //�G�摜�ۊǗp
	KdTexture* m_elecShockTex;//���d�G�t�F�N�g�摜
	std::shared_ptr<KdSoundInstance>* m_elecShockSfx;//���d���ʉ�
	std::shared_ptr<KdSoundInstance>* m_enemySfx;//�G�̌��ʉ�

	//������������������������������������������������������������
	// �G���ʕϐ�
	//������������������������������������������������������������
	bool  m_isAlive;       //���݃t���O
	bool  m_isDead;        //���S�t���O
	bool  m_isActive;      //�A�N�e�B�u�t���O
	bool  m_isDamage;      //�_���[�W�t���O
	bool  m_isElecShock;   //���d�t���O
	bool  m_isElecShockHit;//���d�q�b�g�t���O
	bool  m_isHitWall;     //�ǏՓ˃t���O
	bool  m_isJump;	       //�W�����v�t���O
	bool  m_isAttack;      //�U�����t���O
	bool  m_isAttackHit;   //�U������t���O
	bool  m_isTracking;    //�ǐՃt���O
	int   m_hp;		       //�̗�
	int   m_coinDropCount; //�����R�C������
	int   m_elecShockGauge;//���d�~�ϒl
	int   m_elecShockTime; //���d�p������
	int   m_texIndex;      //���݃X�v���C�g�̉����ڂ̉摜��
	int   m_frameCnt;      //�t���[���J�E���g�p
	float m_texAngle;      //�摜�̊p�x(degree)
	float m_shakeX;        //���d�ɂ��k��

	Math::Vector2 m_pos;        //���W
	Math::Vector2 m_move;       //�ړ���
	Math::Vector2 m_scale;      //�g�嗦
	Math::Vector2 m_attackPos;  //�U�����W
	Math::Color   m_color;      //�F

	Math::Matrix m_scaleMat;   //�g��s��
	Math::Matrix m_rotationMat;//��]�s��
	Math::Matrix m_transMat;   //�ړ��s��
	Math::Matrix m_mat;		   //�����s��


	//������������������������������������������������������������
	// �G���ʒ萔
	//������������������������������������������������������������
	const EnemyType m_enemyType;     //�G�̎��
	const int   m_texWidth;		     //�摜1�����T�C�Y
	const int   m_texHeight;         //�摜1���c�T�C�Y
	const int   m_frameRate;         //�A�j���[�V�����̍X�V�p�x
	const int   m_hpMax;             //�ő�̗�
	const int   m_attackDamage;      //�U����
	const int   m_hitDamage;         //���������Ƃ��̃_���[�W
	const int   m_attackTexIndex;    //�U�����������摜
	const int   m_coinMax;           //�����R�C���̍ő�
	const int   m_elecShockLimit;    //���d���E�l
	const float	m_moveSpeed;         //�ړ����x
	const float	m_gravity;	         //�d��
	const float m_jumpPower;         //�W�����v��
	const float m_scaleSize;         //�g�嗦
	const float m_attackDis;         //�U���\�˒�
	const float m_attackHitDis;      //�U���˒�
	const float m_attackRadius;      //�U���͈�
	const float m_trackDist;         //�ǐՂ����鋗��
	const float m_noTrackDist;       //�ǐՂ����Ȃ�����
	const float m_hitWidth;          //�����蔻�艡�T�C�Y
	const float m_hitHeight;         //�����蔻��c�T�C�Y
	const Math::Color m_defaultColor;//�ʏ펞�̐F
	const Math::Color m_damageColor; //�_���[�W����������Ƃ��̐F

	const int   m_elecShockTimeMax = 60 * 3;//�ő労�d����(3�b)
	const float m_hitKnockForce    = 15.0f; //���������Ƃ��̏Ռ�
	const float m_shakePower       = 2.0f;  //���d�ɂ��k���̋���
	//������������������������������������������������������������
	// ���d�摜�֘A
	//������������������������������������������������������������
	
	//���d��Ԃ̕ύX
	bool ChangeElecShockState();

	//���d�̏�ԍX�V
	void UpdateElecShock();
	//���d�G�t�F�N�g�`��
	void DrawElecShock() const;  

	//���d�G�t�F�N�g�\����
	Effect1 m_elecShock{ 
		512,//�摜���T�C�Y
		512,//�摜�c�T�C�Y
		14,	//�摜����
		2	//�t���[�����[�g
	};

	Math::Vector2 m_elecShockScale;   //�g�嗦
	Math::Matrix  m_elecShockScaleMat;//�g��s��
	Math::Matrix  m_elecShockTransMat;//�ړ��s��
	Math::Matrix  m_elecShockMat;	  //�����s��
};


#pragma once
#include <vector>
#include "EnemyBase.h"
#include "Standard/Robot/Robot.h"
#include "Standard/Frog/Frog.h"
#include "Standard/Ghost/Ghost.h"
#include "Standard/Gremlin/Gremlin.h"
#include "Standard/Sentinel/Sentinel.h"
#include "Boss/BossRobot/BossRobot.h"
#include "Boss/Skull/Skull.h"
#include "Boss/LittleWitch/LittleWitch.h"
#include "Coin.h"

class Scene;
/// �u���̃N���X�̎g�����v
/// ���C���X�^���X�̍쐬
/// C_EnemyMgr* enemyMgr = [�I�[�i�[]->GetEnemyMgr();
/// 
/// ���֐��̌Ăяo����
/// for (int i = 0; i < m_enemyMgr.Get[�G�̎��]().size(); i++)
/// {
/// 	m_enemyMgr->Get[�G�̎��]()[i]->[�Ăяo�������֐�]();
/// }

//�G�Ǘ��N���X
class C_EnemyMgr
{
public:
	C_EnemyMgr();
	~C_EnemyMgr(){}

	//������
	void Init();
	//����
	void Action();
	//�X�V
	void Update();
	//�`��
	void Draw();

	//�ǂݍ���
	void Load();
	//���
	void Release();

	//�T�E���h�G�t�F�N�g�̉��ʃZ�b�g
	void SetSoundVolume(float a_multiplier);

	//�C���X�^���X�����݂��邩�m�F
	bool IsInstanceActive(C_EnemyBase* a_enemy);

	//�G�̃C���X�^���X�Ɣz���S����
	void DestroyAllEnemies();

	//�R�C���̐���
	void CreateCoin(float a_posX, float a_posY);

	//�R�C���̃T�E���h��炷
	void PlayCoinSound();

	//�X�|�[���֐�...�߂�l�Ő��������G�̃C���X�^���X�Ԃ�
	
	//���{�b�g�̐���
	C_Robot* SpawnRobot(float a_posX, float a_posY);

	//�J�G���̐���
	C_Frog* SpawnFrog(float a_posX, float a_posY);

	//�S�[�X�g�̐���
	C_Ghost* SpawnGhost(float a_posX, float a_posY);
	
	//�O���������̐���
	C_Gremlin* SpawnGremlin(float a_posX, float a_posY);

	//�Z���`�l������
	C_Sentinel* SpawnSentinel(float a_posX, float a_posY);

	//�{�X���{�b�g�̐���
	C_BossRobot* SpawnBossRobot(float a_posX, float a_posY, bool a_isLittleWitchSummoned = false);

	//�X�J���̐���
	C_Skull* SpawnSkull(float a_posX, float a_posY, bool a_isLittleWitchSummoned = false);

	//���@�����̐���
	C_LittleWitch* SpawnLittleWitch(float a_posX, float a_posY);

	//////////////�Z�b�^�[///////////////////////////////////////////////

	//�I�[�i�[�̃C���X�^���X�擾
	void SetOwner(Scene* a_eOwner) { m_mOwner = a_eOwner; }
	/////////////////////////////////////////////////////////////////////


	//////////////�Q�b�^�[///////////////////////////////////////////////
	
	//�R�C���̃C���X�^���X���擾
	const std::vector<C_Coin*>GetCoin() { return m_coin; }

	//���{�b�g�̃C���X�^���X�擾
	const std::vector<C_Robot*>GetRobot() { return m_robot; }

	//�J�G���̃C���X�^���X�擾
	const std::vector<C_Frog*>GetFrog() { return m_frog; }

	//�S�[�X�g�̃C���X�^���X�擾
	const std::vector<C_Ghost*>GetGhost() { return m_ghost; }

	//�O���������̃C���X�^���X�擾
	const std::vector<C_Gremlin*>GetGremlin() { return m_gremlin; }

	//�Z���`�l���̃C���X�^���X�擾
	const std::vector<C_Sentinel*>GetSentinel() { return m_sentinel; }

	//�{�X���{�b�g�̃C���X�^���X�擾
	const std::vector<C_BossRobot*>GetBossRobot() { return m_bossRobot; }
	
	//�X�J���̃C���X�^���X�擾
	const std::vector<C_Skull*>GetSkull() { return m_skull; }
	
	//���@�����̃C���X�^���X�擾
	C_LittleWitch* GetLittleWitch() { return m_littleWitch; }

	//�S�Ă̓G�̃C���X�^���X���擾
	const std::vector<C_EnemyBase*>GetAllEnemies() { return m_allEnemies; }
	/////////////////////////////////////////////////////////////////////

private:

	//�{�X�G�̃X�e�[�^�X�̋���
	enum BossEnemyStrength {
		Weak,        // ���...���@���������p
		Normal,      // ����
		StrengthCount// �X�e�[�^�X�̎�ނ̐�
	};

	//�G���ʃX�|�[��������
	void SpawnInit();

	//�I�[�i�[
	Scene* m_mOwner;

	//�t���[���J�E���g�p
	int   m_frameCnt;

	//�R�C�������t���[�����[�g
	static const int m_createCoinFrameRate = 3;

	//������������������������������������������������������������������������������
	// �C���X�^���X
	//������������������������������������������������������������������������������
	
	std::vector<C_Coin*>m_coin;//�R�C��

	//�{�X�X�e�[�^�X�ۊ�
	C_BossRobot* m_bossRobotStatus[StrengthCount];
	C_Skull*     m_skullStatus[StrengthCount];

	std::vector<C_Robot*>m_robot;            //���{�b�g
	std::vector<C_Frog*> m_frog;             //�J�G��
	std::vector<C_Ghost*>m_ghost;	         //�S�[�X�g
	std::vector<C_Gremlin*>m_gremlin;	     //�O��������
	std::vector<C_Sentinel*>m_sentinel;	     //�Z���`�l��
	std::vector<C_BossRobot*>m_bossRobot;    //�{�X���{�b�g
	std::vector<C_Skull*>m_skull;            //�X�J��
	C_LittleWitch* m_littleWitch;            //���@����
	std::vector<C_EnemyBase*>m_allEnemies;   //�S�Ă̓G�C���X�^���X�Ǘ��p

	//������������������������������������������������������������������������������
	// �摜
	//������������������������������������������������������������������������������
	
	//�R�C��
	KdTexture m_coinTex;

	KdTexture m_elecShockTex;//���d
	KdTexture m_smokeTex;    //��
	KdTexture m_spellTex;    //���@
	KdTexture m_dustTex;     //����
	KdTexture m_fireVeilTex; //�΂̃x�[��
	KdTexture m_bonfireTex;  //����
	KdTexture m_confusedTex; //����
	KdTexture m_fireballTex; //�΂̋�
	KdTexture m_enemySpawnerTex;     //�G�X�|�i�[
	KdTexture m_enemySpawnerCrackTex;//�G�X�|�i�[�̂Ђъ���

	//�V�[���h
	static const int m_shieldTexNum = 3;
	KdTexture m_shieldTex[m_shieldTexNum];

	//���{�b�g
	static const int m_robotTexNum = 3;
	KdTexture m_robotTex[m_robotTexNum];

	//�J�G��
	static const int m_frogTexNum = 3;
	KdTexture m_frogTex[m_frogTexNum];

	//�S�[�X�g
	static const int m_ghostTexNum = 2;
	KdTexture m_ghostTex[m_ghostTexNum];

	//�O��������
	static const int m_gremlinTexNum = 4;
	KdTexture m_gremlinTex[m_gremlinTexNum];
	
	//�Z���`�l��
	static const int m_sentinelTexNum = 5;
	KdTexture m_sentinelTex[m_sentinelTexNum];

	//�{�X���{�b�g
	static const int m_bossRobotTexNum = 5;     
	KdTexture m_bossRobotTex[m_bossRobotTexNum];

	//�X�J��
	static const int m_skullTexNum = 2; 
	KdTexture m_skullTex[m_skullTexNum];

	//���@����
	static const int m_littleWitchTexNum = 9;
	KdTexture m_littleWitchTex[m_littleWitchTexNum];


	//������������������������������������������������������������������������������
	// �T�E���h
	//������������������������������������������������������������������������������

	//�R�C��
	std::shared_ptr<KdSoundEffect>  m_coinSfxData;//���f�[�^
	std::shared_ptr<KdSoundInstance>m_coinSfxInst;//�T�E���h�C���X�^���X

	//���d
	std::shared_ptr<KdSoundEffect>  m_elecShockSfxData;//���f�[�^
	std::shared_ptr<KdSoundInstance>m_elecShockSfxInst;//�T�E���h�C���X�^���X
	
	//���{�b�g
	static const int m_robotSfxNum = 1;
	std::shared_ptr<KdSoundEffect>  m_robotSfxData[m_robotSfxNum]; //���f�[�^
	std::shared_ptr<KdSoundInstance>m_robotSfxInst[m_robotSfxNum];//�T�E���h�C���X�^���X

	//�J�G��
	static const int m_frogSfxNum = 2;
	std::shared_ptr<KdSoundEffect>  m_frogSfxData[m_frogSfxNum]; //���f�[�^
	std::shared_ptr<KdSoundInstance>m_frogSfxInst[m_frogSfxNum];//�T�E���h�C���X�^���X

	//�S�[�X�g
	static const int m_ghostSfxNum = 1;
	std::shared_ptr<KdSoundEffect>  m_ghostSfxData[m_ghostSfxNum]; //���f�[�^
	std::shared_ptr<KdSoundInstance>m_ghostSfxInst[m_ghostSfxNum];//�T�E���h�C���X�^���X

	//�O��������
	static const int m_gremlinSfxNum = 1;
	std::shared_ptr<KdSoundEffect>  m_gremlinSfxData[m_gremlinSfxNum]; //���f�[�^
	std::shared_ptr<KdSoundInstance>m_gremlinSfxInst[m_gremlinSfxNum];//�T�E���h�C���X�^���X
	
	//�Z���`�l��
	static const int m_sentinelSfxNum = 1;
	std::shared_ptr<KdSoundEffect>  m_sentinelSfxData[m_sentinelSfxNum]; //���f�[�^
	std::shared_ptr<KdSoundInstance>m_sentinelSfxInst[m_sentinelSfxNum];//�T�E���h�C���X�^���X

	//�{�X���{�b�g
	static const int m_bossRobotSfxNum = 3;
	std::shared_ptr<KdSoundEffect>  m_bossRobotSfxData[m_bossRobotSfxNum]; //���f�[�^
	std::shared_ptr<KdSoundInstance>m_bossRobotSfxInst[m_bossRobotSfxNum];//�T�E���h�C���X�^���X

	//�X�J��
	static const int m_skullSfxNum = 6;
	std::shared_ptr<KdSoundEffect>  m_skullSfxData[m_skullSfxNum]; //���f�[�^
	std::shared_ptr<KdSoundInstance>m_skullSfxInst[m_skullSfxNum];//�T�E���h�C���X�^���X
};

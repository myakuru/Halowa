#include "EnemyManager.h"
#include "../Scene.h"

C_EnemyMgr::C_EnemyMgr() :m_mOwner(nullptr), m_robotTex(), m_robot(), m_bossRobot(), m_coin(), m_littleWitch(nullptr)
{
	m_frameCnt = 0;
}

//������
void C_EnemyMgr::Init()
{
	m_mOwner->GetEnemyAtkHit()->SetEnemyMgr(this);
	SetSoundVolume(1.0f);

	//������������������������������������������������������������������������������
	// �{�X�X�e�[�^�X�ݒ�
	//������������������������������������������������������������������������������

	//���@��������������{�X
	m_bossRobotStatus[Weak] = new C_BossRobot(
		10,//�ő�̗�
		0, //�U����
		0, //���������Ƃ��̃_���[�W
		0, //�����R�C���̍ő�
		1, //���d���E�l
		0  //���̃_���[�W
	);
	m_skullStatus[Weak] = new C_Skull(
		10,//�ő�̗�
		0, //�U����
		0, //���������Ƃ��̃_���[�W
		0, //�����R�C���̍ő�
		1, //���d���E�l
		0, //�΂̋ʂ̃_���[�W
		0  //���΂̃_���[�W
	);

	//�ʏ펞�̃{�X
	m_bossRobotStatus[Normal] = new C_BossRobot(
		200, //�ő�̗�
		400, //�U����
		200, //���������Ƃ��̃_���[�W
		30,  //�����R�C���̍ő�
		100, //���d���E�l
		500  //���̃_���[�W
	);
	m_skullStatus[Normal] = new C_Skull(
		400,//�ő�̗�
		400,//�U����
		200,//���������Ƃ��̃_���[�W
		50, //�����R�C���̍ő�
		250,//���d���E�l
		300,//�΂̋ʂ̃_���[�W
		200 //���΂̃_���[�W
	);
}

//����
void C_EnemyMgr::Action()
{
	//�v���C���[�̍��W���擾
	Math::Vector2 playerPos = m_mOwner->GetChara()->GetPos();

	//�R�C���̓���
	for (size_t i = 0; i < m_coin.size(); i++)
	{
		m_coin[i]->Action(playerPos);
	}
	//�S�Ă̓G�̓���
	for (size_t i = 0; i < m_allEnemies.size(); i++)
	{
		m_allEnemies[i]->Action(playerPos);
	}
}

//�X�V
void C_EnemyMgr::Update()
{
	//�t���[���J�E���g�A�b�v
	m_frameCnt++;

	//�R�C���폜����
	for (size_t i = 0; i < m_coin.size(); i++)
	{
		if (m_coin[i]->GetAlive()) continue;

		delete m_coin[i];

		auto cItr = m_coin.begin();

		m_coin.erase(cItr + i);
	}
	//���{�b�g���S������
	for (size_t i = 0; i < m_robot.size(); i++)
	{
		//�����t���O��ON�Ȃ�R���e�B�j���[
		if (m_robot[i]->GetAlive())continue;

		//�z��̍ŏ����C�e���[�^�ɓ����
		auto eItr = m_robot.begin();

		//�w��̔z����폜
		m_robot.erase(eItr + i);
	}
	//�J�G�����S������
	for (size_t i = 0; i < m_frog.size(); i++)
	{
		//�����t���O��ON�Ȃ�R���e�B�j���[
		if (m_frog[i]->GetAlive())continue;

		//�z��̍ŏ����C�e���[�^�ɓ����
		auto eItr = m_frog.begin();

		//�w��̔z����폜
		m_frog.erase(eItr + i);
	}
	//�S�[�X�g���S������
	for (size_t i = 0; i < m_ghost.size(); i++)
	{
		//�����t���O��ON�Ȃ�R���e�B�j���[
		if (m_ghost[i]->GetAlive())continue;

		//�z��̍ŏ����C�e���[�^�ɓ����
		auto eItr = m_ghost.begin();

		//�w��̔z����폜
		m_ghost.erase(eItr + i);
	}
	//�O�����������S������
	for (size_t i = 0; i < m_gremlin.size(); i++)
	{
		//�����t���O��ON�Ȃ�R���e�B�j���[
		if (m_gremlin[i]->GetAlive())continue;

		//�z��̍ŏ����C�e���[�^�ɓ����
		auto eItr = m_gremlin.begin();

		//�w��̔z����폜
		m_gremlin.erase(eItr + i);
	}
	//�Z���`�l�����S������
	for (size_t i = 0; i < m_sentinel.size(); i++)
	{
		//�����t���O��ON�Ȃ�R���e�B�j���[
		if (m_sentinel[i]->GetAlive())continue;

		//�z��̍ŏ����C�e���[�^�ɓ����
		auto eItr = m_sentinel.begin();

		//�w��̔z����폜
		m_sentinel.erase(eItr + i);
	}
	//�{�X���{�b�g���S������
	for (size_t i = 0; i < m_bossRobot.size(); i++)
	{
		//�����t���O��ON�Ȃ�R���e�B�j���[
		if (m_bossRobot[i]->GetAlive())continue;

		//�z��̍ŏ����C�e���[�^�ɓ����
		auto eItr = m_bossRobot.begin();

		//�w��̔z����폜
		m_bossRobot.erase(eItr + i);
	}
	//�X�J�����S������
	for (size_t i = 0; i < m_skull.size(); i++)
	{
		//�����t���O��ON�Ȃ�R���e�B�j���[
		if (m_skull[i]->GetAlive())continue;

		//�z��̍ŏ����C�e���[�^�ɓ����
		auto eItr = m_skull.begin();

		//�w��̔z����폜
		m_skull.erase(eItr + i);
	}
	//�S�Ă̓G�̎��S������
	for (size_t i = 0; i < m_allEnemies.size(); i++)
	{
		//�����t���O��ON�Ȃ�R���e�B�j���[
		if (m_allEnemies[i]->GetAlive())continue;

		//�����R�C���������܂������
		if (m_allEnemies[i]->GetCoinDropCount() > 0)
		{
			//�R�C�������̃t���[�����[�g�ɍ��킹��
			if (m_frameCnt % m_createCoinFrameRate == 0)
			{
				//�G�̎��S���W�擾
				const Math::Vector2 enemyPos = m_allEnemies[i]->GetPos();

				//�R�C���𐶐�
				CreateCoin(enemyPos.x, enemyPos.y);

				//�����R�C��������1�����炷
				m_allEnemies[i]->SetCoinDropCount(m_allEnemies[i]->GetCoinDropCount() - 1);
			}
			continue;
		}

		//���@�����Ȃ�
		if (m_allEnemies[i]->GetEnemyType() == EnemyType::LittleWitch)
		{
			//�C���X�^���X�̉��
			delete m_allEnemies[i];

			//nullptr�ŏ�����
			m_littleWitch = nullptr;
		}
		else
		{		
			//�C���X�^���X�̉��
			delete m_allEnemies[i];
		}

		//�z��̍ŏ����C�e���[�^�ɓ����
		auto eItr = m_allEnemies.begin();

		//�w��̔z����폜
		m_allEnemies.erase(eItr + i);
	}

	//�X�N���[���̒l���擾
	const float scrollX = m_mOwner->GetMap()->GetScrollX();
	const float scrollY = m_mOwner->GetMap()->GetScrollY();

	//�R�C���̍X�V
	for (size_t i = 0; i < m_coin.size(); i++)
	{
		m_coin[i]->Update(scrollX, scrollY);
	}
	//�S�Ă̓G�̍X�V
	for (size_t i = 0; i < m_allEnemies.size(); i++)
	{
		m_allEnemies[i]->Update(scrollX, scrollY);
	}

}

//�`��
void C_EnemyMgr::Draw()
{
	//�S�Ă̓G�̕`��
	for (size_t i = 0; i < m_allEnemies.size(); i++)
	{
		m_allEnemies[i]->Draw();
	}
	//�R�C���̕`��
	for (size_t i = 0; i < m_coin.size(); i++)
	{
		m_coin[i]->Draw();
	}
}

//�ǂݍ���
void C_EnemyMgr::Load()
{
	//������������������������������������������������������������������������������
	// �摜�ǂݍ���
	//������������������������������������������������������������������������������
	//�R�C��
	m_coinTex.Load("Texture/Enemy/Coin.png");

	//���d
	m_elecShockTex.Load("Texture/Enemy/Shock_Flash.png");

	//��
	m_smokeTex.Load("Texture/Enemy/Boss/BossRobot/Smoke.png");

	//���@
	m_spellTex.Load("Texture/Enemy/Standard/Frog/Spell.png");

	//����
	m_dustTex.Load("Texture/Enemy/Standard/Gremlin/Dust.png");

	//�΂̃x�[��
	m_fireVeilTex.Load("Texture/Enemy/Boss/Skull/FireVeil.png");

	//����
	m_bonfireTex.Load("Texture/Enemy/Boss/Skull/Bonfire.png");

	//�����摜
	m_confusedTex.Load("Texture/Enemy/Boss/Skull/Confused.png");

	//�΂̋�
	m_fireballTex.Load("Texture/Enemy/Boss/Skull/Fireball.png");

	//�G�X�|�i�[
	m_enemySpawnerTex.Load("Texture/Enemy/Boss/LittleWitch/EnemySpawner.png");

	//�G�X�|�i�[�̂Ђъ���
	m_enemySpawnerCrackTex.Load("Texture/Enemy/Boss/LittleWitch/EnemySpawnerCrack.png");

	//�V�[���h
	m_shieldTex[0].Load("Texture/Enemy/Boss/LittleWitch/Shield_Off.png");
	m_shieldTex[1].Load("Texture/Enemy/Boss/LittleWitch/Shield_On.png");
	m_shieldTex[2].Load("Texture/Enemy/Boss/LittleWitch/Shield.png");

	//���{�b�g
	m_robotTex[0].Load("Texture/Enemy/Standard/Robot/walking.png");
	m_robotTex[1].Load("Texture/Enemy/Standard/Robot/attack.png");
	m_robotTex[2].Load("Texture/Enemy/Standard/Robot/death.png");

	//�J�G��
	m_frogTex[0].Load("Texture/Enemy/Standard/Frog/Idle.png");
	m_frogTex[1].Load("Texture/Enemy/Standard/Frog/Attack.png");
	m_frogTex[2].Load("Texture/Enemy/Standard/Frog/Death.png");

	//�S�[�X�g
	m_ghostTex[0].Load("Texture/Enemy/Standard/Ghost/Float.png");
	m_ghostTex[1].Load("Texture/Enemy/Standard/Ghost/Death.png");

	//�O��������
	m_gremlinTex[0].Load("Texture/Enemy/Standard/Gremlin/Idle.png");
	m_gremlinTex[1].Load("Texture/Enemy/Standard/Gremlin/Walk.png");
	m_gremlinTex[2].Load("Texture/Enemy/Standard/Gremlin/Attack.png");
	m_gremlinTex[3].Load("Texture/Enemy/Standard/Gremlin/Death.png");

	//�Z���`�l��
	m_sentinelTex[0].Load("Texture/Enemy/Standard/Sentinel/Idle.png");
	m_sentinelTex[1].Load("Texture/Enemy/Standard/Sentinel/Walk.png");
	m_sentinelTex[2].Load("Texture/Enemy/Standard/Sentinel/Attack1.png");
	m_sentinelTex[3].Load("Texture/Enemy/Standard/Sentinel/Attack2.png");
	m_sentinelTex[4].Load("Texture/Enemy/Standard/Sentinel/Death.png");

	//�{�X���{�b�g
	m_bossRobotTex[0].Load("Texture/Enemy/Boss/BossRobot/Idle.png");
	m_bossRobotTex[1].Load("Texture/Enemy/Boss/BossRobot/Walk.png");
	m_bossRobotTex[2].Load("Texture/Enemy/Boss/BossRobot/Attack.png");
	m_bossRobotTex[3].Load("Texture/Enemy/Boss/BossRobot/Death.png");
	m_bossRobotTex[4].Load("Texture/Enemy/Boss/BossRobot/Hello.png");

	//�X�J��
	m_skullTex[0].Load("Texture/Enemy/Boss/Skull/Float.png");
	m_skullTex[1].Load("Texture/Enemy/Boss/Skull/Death.png");

	//���@����
	m_littleWitchTex[0].Load("Texture/Enemy/Boss/LittleWitch/Idle.png");
	m_littleWitchTex[1].Load("Texture/Enemy/Boss/LittleWitch/Walk.png");
	m_littleWitchTex[2].Load("Texture/Enemy/Boss/LittleWitch/Jump.png");
	m_littleWitchTex[3].Load("Texture/Enemy/Boss/LittleWitch/Fall.png");
	m_littleWitchTex[4].Load("Texture/Enemy/Boss/LittleWitch/Land.png");
	m_littleWitchTex[5].Load("Texture/Enemy/Boss/LittleWitch/Attack.png");
	m_littleWitchTex[6].Load("Texture/Enemy/Boss/LittleWitch/CastSpell.png");
	m_littleWitchTex[7].Load("Texture/Enemy/Boss/LittleWitch/Surprised.png");
	m_littleWitchTex[8].Load("Texture/Enemy/Boss/LittleWitch/Death.png");

	//������������������������������������������������������������������������������
	// �T�E���h�G�t�F�N�g�ǂݍ���
	//������������������������������������������������������������������������������
	
	//�R�C��
	m_coinSfxData = std::make_shared<KdSoundEffect>();
	m_coinSfxData->Load("Sound/Enemy/GetCoin.wav");
	m_coinSfxInst = m_coinSfxData->CreateInstance(false);

	//���d
	m_elecShockSfxData = std::make_shared<KdSoundEffect>();
	m_elecShockSfxData->Load("Sound/Enemy/Electric_Shock.wav");
	m_elecShockSfxInst = m_elecShockSfxData->CreateInstance(false);

	//���{�b�g
	for (int i = 0; i < m_robotSfxNum; i++)
	{
		m_robotSfxData[i] = std::make_shared<KdSoundEffect>();
	}
	m_robotSfxData[0]->Load("Sound/Enemy/Robot/Explosion.wav");
	for (int i = 0; i < m_robotSfxNum; i++)
	{
		m_robotSfxInst[i] = m_robotSfxData[i]->CreateInstance(false);
	}

	//�J�G��
	for (int i = 0; i < m_frogSfxNum; i++)
	{
		m_frogSfxData[i] = std::make_shared<KdSoundEffect>();
	}
	m_frogSfxData[0]->Load("Sound/Enemy/Frog/Shot.wav");
	m_frogSfxData[1]->Load("Sound/Enemy/Frog/Death.wav");
	for (int i = 0; i < m_frogSfxNum; i++)
	{
		m_frogSfxInst[i] = m_frogSfxData[i]->CreateInstance(false);
	}

	//�{�X���{�b�g
	for (int i = 0; i < m_bossRobotSfxNum; i++)
	{
		m_bossRobotSfxData[i] = std::make_shared<KdSoundEffect>();
	}
	m_bossRobotSfxData [0]->Load("Sound/Enemy/BossRobot/Landing.wav");
	m_bossRobotSfxData [1]->Load("Sound/Enemy/BossRobot/Walk.wav");
	m_bossRobotSfxData [2]->Load("Sound/Enemy/BossRobot/Death.wav");	
	for (int i = 0; i < m_bossRobotSfxNum; i++)
	{
		m_bossRobotSfxInst[i] = m_bossRobotSfxData[i]->CreateInstance(false);
	}

	//�X�J��
	for (int i = 0; i < m_skullSfxNum; i++)
	{
		m_skullSfxData[i] = std::make_shared<KdSoundEffect>();
	}
	m_skullSfxData[0]->Load("Sound/Enemy/Skull/Collision.wav");
	m_skullSfxData[1]->Load("Sound/Enemy/Skull/Confused.wav");
	m_skullSfxData[2]->Load("Sound/Enemy/Skull/Ignition.wav");
	m_skullSfxData[3]->Load("Sound/Enemy/Skull/Shot.wav");
	m_skullSfxData[4]->Load("Sound/Enemy/Skull/Rolling.wav");
	m_skullSfxData[5]->Load("Sound/Enemy/Skull/Explosion.wav");
	for (int i = 0; i < m_skullSfxNum; i++)
	{
		m_skullSfxInst[i] = m_skullSfxData[i]->CreateInstance(false);
	}
}

//���
void C_EnemyMgr::Release()
{
	//�摜���
	m_coinTex.Release();
	m_elecShockTex.Release();
	m_smokeTex.Release();
	m_spellTex.Release();
	m_dustTex.Release();
	m_fireVeilTex.Release();
	m_bonfireTex.Release();
	m_confusedTex.Release();
	m_fireballTex.Release();
	m_enemySpawnerTex.Release();
	m_enemySpawnerCrackTex.Release();
	for (int i = 0; i < m_shieldTexNum; i++)
	{
		m_shieldTex[i].Release();
	}

	for (int i = 0; i < m_robotTexNum; i++)
	{
		m_robotTex[i].Release();
	}
	for (int i = 0; i < m_frogTexNum; i++)
	{
		m_frogTex[i].Release();
	}
	for (int i = 0; i < m_ghostTexNum; i++)
	{
		m_ghostTex[i].Release();
	}
	for (int i = 0; i < m_gremlinTexNum; i++)
	{
		m_gremlinTex[i].Release();
	}
	for (int i = 0; i < m_sentinelTexNum; i++)
	{
		m_sentinelTex[i].Release();
	}
	for (int i = 0; i < m_bossRobotTexNum; i++)
	{
		m_bossRobotTex[i].Release();
	}
	for (int i = 0; i < m_skullTexNum; i++)
	{
		m_skullTex[i].Release();
	}
	for (int i = 0; i < m_littleWitchTexNum; i++)
	{
		m_littleWitchTex[i].Release();
	}
	//�G�̃C���X�^���X��S����
	DestroyAllEnemies();
}

//�T�E���h�G�t�F�N�g�̉��ʃZ�b�g
void C_EnemyMgr::SetSoundVolume(float a_multiplier)
{
	m_coinSfxInst->SetVolume(a_multiplier);
	m_elecShockSfxInst->SetVolume(a_multiplier);
	for (int i = 0; i < m_robotSfxNum; i++)
	{
		m_robotSfxInst[i]->SetVolume(a_multiplier);
	}
	for (int i = 0; i < m_frogSfxNum; i++)
	{
		m_frogSfxInst[i]->SetVolume(a_multiplier);
	}
	for (int i = 0; i < m_bossRobotSfxNum; i++)
	{
		m_bossRobotSfxInst[i]->SetVolume(a_multiplier);
	}
	for (int i = 0; i < m_skullSfxNum; i++)
	{
		m_skullSfxInst[i]->SetVolume(a_multiplier);
	}
}

//�C���X�^���X�����݂��邩�m�F
bool C_EnemyMgr::IsInstanceActive(C_EnemyBase* a_enemy)
{
	//�S�Ă̓G������
	for (size_t i = 0; i < m_allEnemies.size(); i++)
	{
		//�����A�h���X�����݂�����true
		if (m_allEnemies[i] == a_enemy)return true;
	}
	//���݂��Ȃ��A�h���X�Ȃ�false
	return false;
}

//�G�̃C���X�^���X�Ɣz���S����
void C_EnemyMgr::DestroyAllEnemies()
{
	for (size_t i = 0; i < m_coin.size(); i++)
	{
		delete m_coin[i];
	}
	for (size_t i = 0; i < m_allEnemies.size(); i++)
	{
		delete m_allEnemies[i];
	}

	m_coin.clear();
	m_robot.clear();
	m_frog.clear();
	m_ghost.clear();
	m_gremlin.clear();
	m_sentinel.clear();
	m_bossRobot.clear();
	m_skull.clear();
	m_littleWitch = nullptr;
	m_allEnemies.clear();
}

//�R�C���̐���
void C_EnemyMgr::CreateCoin(float a_posX, float a_posY)
{
	//���������m�ۂ��C���X�^���X�̐���
	m_coin.push_back(new C_Coin({ a_posX,a_posY }));

	//�������ꂽ�C���X�^���X�ɉ摜���Z�b�g
	m_coin.back()->SetTex(&m_coinTex);
}

//���{�b�g����
C_Robot* C_EnemyMgr::SpawnRobot(float a_posX,float a_posY)
{
	//���������m�ۂ��C���X�^���X�̐���
	m_robot.push_back(new C_Robot({ a_posX,a_posY }));

	//�������ꂽ�C���X�^���X�ɓG�摜���Z�b�g
	m_robot.back()->SetEnemyTex(m_robotTex);

	//�������ꂽ�C���X�^���X�ɉ����f�[�^���Z�b�g
	m_robot.back()->SetEnemySfx(m_robotSfxInst);

	//�S�Ă̓G�C���X�^���X�Ǘ��p�z��Ɋi�[
	m_allEnemies.push_back(m_robot.back());

	//�G���ʃX�|�[��������
	SpawnInit();

	//�߂�l�Ő��������C���X�^���X��Ԃ�
	return m_robot.back();
}

//�J�G������
C_Frog* C_EnemyMgr::SpawnFrog(float a_posX, float a_posY)
{
	//���������m�ۂ��C���X�^���X�̐���
	m_frog.push_back(new C_Frog({ a_posX,a_posY }));

	//�������ꂽ�C���X�^���X�ɓG�摜���Z�b�g
	m_frog.back()->SetEnemyTex(m_frogTex);

	//�������ꂽ�C���X�^���X�ɖ��@�摜���Z�b�g
	m_frog.back()->SetSpellTex(&m_spellTex);

	//�������ꂽ�C���X�^���X�ɉ����f�[�^���Z�b�g
	m_frog.back()->SetEnemySfx(m_frogSfxInst);

	//�S�Ă̓G�C���X�^���X�Ǘ��p�z��Ɋi�[
	m_allEnemies.push_back(m_frog.back());

	//�G���ʃX�|�[��������
	SpawnInit();

	//�߂�l�Ő��������C���X�^���X��Ԃ�
	return m_frog.back();
}

//�S�[�X�g�̐���
C_Ghost* C_EnemyMgr::SpawnGhost(float a_posX, float a_posY)
{
	//���������m�ۂ��C���X�^���X�̐���
	m_ghost.push_back(new C_Ghost({ a_posX,a_posY }));

	//�������ꂽ�C���X�^���X�ɓG�摜���Z�b�g
	m_ghost.back()->SetEnemyTex(m_ghostTex);

	//�������ꂽ�C���X�^���X�ɉ����f�[�^���Z�b�g
	m_ghost.back()->SetEnemySfx(m_ghostSfxInst);

	//�S�Ă̓G�C���X�^���X�Ǘ��p�z��Ɋi�[
	m_allEnemies.push_back(m_ghost.back());

	//�G���ʃX�|�[��������
	SpawnInit();

	//�߂�l�Ő��������C���X�^���X��Ԃ�
	return m_ghost.back();
}

//�O���������̐���
C_Gremlin* C_EnemyMgr::SpawnGremlin(float a_posX, float a_posY)
{
	//���������m�ۂ��C���X�^���X�̐���
	m_gremlin.push_back(new C_Gremlin({ a_posX,a_posY }));

	//�������ꂽ�C���X�^���X�ɓG�摜���Z�b�g
	m_gremlin.back()->SetEnemyTex(m_gremlinTex);

	//�������ꂽ�C���X�^���X�ɍ����摜���Z�b�g
	m_gremlin.back()->SetDustTex(&m_dustTex);

	//�������ꂽ�C���X�^���X�ɉ����f�[�^���Z�b�g
	m_gremlin.back()->SetEnemySfx(m_gremlinSfxInst);

	//�S�Ă̓G�C���X�^���X�Ǘ��p�z��Ɋi�[
	m_allEnemies.push_back(m_gremlin.back());

	//�G���ʃX�|�[��������
	SpawnInit();

	//�߂�l�Ő��������C���X�^���X��Ԃ�
	return m_gremlin.back();
}

//�Z���`�l���̐���
C_Sentinel* C_EnemyMgr::SpawnSentinel(float a_posX, float a_posY)
{
	//���������m�ۂ��C���X�^���X�̐���
	m_sentinel.push_back(new C_Sentinel({ a_posX,a_posY }));

	//�������ꂽ�C���X�^���X�ɓG�摜���Z�b�g
	m_sentinel.back()->SetEnemyTex(m_sentinelTex);

	//�������ꂽ�C���X�^���X�ɉ����f�[�^���Z�b�g
	m_sentinel.back()->SetEnemySfx(m_sentinelSfxInst);

	//�S�Ă̓G�C���X�^���X�Ǘ��p�z��Ɋi�[
	m_allEnemies.push_back(m_sentinel.back());

	//�G���ʃX�|�[��������
	SpawnInit();

	//�߂�l�Ő��������C���X�^���X��Ԃ�
	return m_sentinel.back();
}

//�{�X���{�b�g����
C_BossRobot* C_EnemyMgr::SpawnBossRobot(float a_posX, float a_posY, bool a_isLittleWitchSummoned)
{
	//���@�������������Ă�����
	if (a_isLittleWitchSummoned)
	{
		//��߂̃X�e�[�^�X��
		//���������m�ۂ��C���X�^���X�̐���
		m_bossRobot.push_back(new C_BossRobot({ a_posX,a_posY }, *m_bossRobotStatus[Weak]));
	}
	//���@�����Ŗ����ꍇ
	else
	{
		//���ʂ̃X�e�[�^�X��
		//���������m�ۂ��C���X�^���X�̐���
		m_bossRobot.push_back(new C_BossRobot({ a_posX,a_posY }, *m_bossRobotStatus[Normal]));
	}

	//�������ꂽ�C���X�^���X�ɓG�摜���Z�b�g
	m_bossRobot.back()->SetEnemyTex(m_bossRobotTex);

	//�������ꂽ�C���X�^���X�ɉ��摜���Z�b�g
	m_bossRobot.back()->SetSmokeTex(&m_smokeTex);

	//�������ꂽ�C���X�^���X�ɉ����f�[�^���Z�b�g
	m_bossRobot.back()->SetEnemySfx(m_bossRobotSfxInst);

	//�S�Ă̓G�C���X�^���X�Ǘ��p�z��Ɋi�[
	m_allEnemies.push_back(m_bossRobot.back());

	//�G���ʃX�|�[��������
	SpawnInit();

	//�߂�l�Ő��������C���X�^���X��Ԃ�
	return m_bossRobot.back();
}

//�X�J���̐���
C_Skull* C_EnemyMgr::SpawnSkull(float a_posX, float a_posY, bool a_isLittleWitchSummoned)
{
	//���@�������������Ă�����
	if (a_isLittleWitchSummoned)
	{
		//��߂̃X�e�[�^�X��
		//���������m�ۂ��C���X�^���X�̐���
		m_skull.push_back(new C_Skull({ a_posX,a_posY }, *m_skullStatus[Weak]));
	}
	//���@�����Ŗ����ꍇ
	else
	{
		//���ʂ̃X�e�[�^�X��
		//���������m�ۂ��C���X�^���X�̐���
		m_skull.push_back(new C_Skull({ a_posX,a_posY }, *m_skullStatus[Normal]));
	}

	//�������ꂽ�C���X�^���X�ɓG�摜���Z�b�g
	m_skull.back()->SetEnemyTex(m_skullTex);

	//�������ꂽ�C���X�^���X�ɉ΂̃x�[���摜���Z�b�g
	m_skull.back()->SetFireVeilTex(&m_fireVeilTex);

	//�������ꂽ�C���X�^���X�ɕ��Ή摜���Z�b�g
	m_skull.back()->SetBonfireTex(&m_bonfireTex);

	//�������ꂽ�C���X�^���X�ɍ����摜���Z�b�g
	m_skull.back()->SetConfusedTex(&m_confusedTex);

	//�������ꂽ�C���X�^���X�ɉ΂̋ʉ摜���Z�b�g
	m_skull.back()->SetFireballTex(&m_fireballTex);

	//�������ꂽ�C���X�^���X�ɉ����f�[�^���Z�b�g
	m_skull.back()->SetEnemySfx(m_skullSfxInst);

	//�S�Ă̓G�C���X�^���X�Ǘ��p�z��Ɋi�[
	m_allEnemies.push_back(m_skull.back());

	//�G���ʃX�|�[��������
	SpawnInit();

	//�߂�l�Ő��������C���X�^���X��Ԃ�
	return m_skull.back();
}

//���@�����̐���
C_LittleWitch* C_EnemyMgr::SpawnLittleWitch(float a_posX, float a_posY)
{
	//���@���������ɂ����烊�^�[��
	if (m_littleWitch != nullptr)
	{
		return nullptr;
	}

	//���������m�ۂ��C���X�^���X�̐���
	m_littleWitch = new C_LittleWitch({ a_posX,a_posY });

	//�������ꂽ�C���X�^���X�ɓG�摜���Z�b�g
	m_littleWitch->SetEnemyTex(m_littleWitchTex);

	//�������ꂽ�C���X�^���X�ɃV�[���h�摜���Z�b�g
	m_littleWitch->SetShieldTex(m_shieldTex);

	//�������ꂽ�C���X�^���X�ɓG�X�|�i�[�摜���Z�b�g
	m_littleWitch->SetEnemySpawnerTex(&m_enemySpawnerTex);

	//�������ꂽ�C���X�^���X�ɓG�X�|�i�[�̂Ђъ���摜���Z�b�g
	m_littleWitch->SetEnemySpawnerCrackTex(&m_enemySpawnerCrackTex);

	//�S�Ă̓G�C���X�^���X�Ǘ��p�z��Ɋi�[
	m_allEnemies.push_back(m_littleWitch);

	//�G���ʃX�|�[��������
	SpawnInit();

	//�߂�l�Ő��������C���X�^���X��Ԃ�
	return m_littleWitch;
}

//�G���ʃX�|�[��������
void C_EnemyMgr::SpawnInit()
{
	//�������ꂽ�C���X�^���X�Ɋ��d�G�t�F�N�g�摜���Z�b�g
	m_allEnemies[m_allEnemies.size() - 1]->SetElecShockTex(&m_elecShockTex);

	//�������ꂽ�C���X�^���X�Ɋ��d�T�E���h���Z�b�g
	m_allEnemies[m_allEnemies.size() - 1]->SetElecShockSfx(&m_elecShockSfxInst);

	//�������ꂽ�C���X�^���X�ɃI�[�i�[���Z�b�g
	m_allEnemies[m_allEnemies.size() - 1]->SetOwner(m_mOwner);

	//�������ꂽ�C���X�^���X��������
	m_allEnemies[m_allEnemies.size() - 1]->Init();
}

//�R�C���̃T�E���h��炷
void C_EnemyMgr::PlayCoinSound()
{
	m_coinSfxInst->Play();
}

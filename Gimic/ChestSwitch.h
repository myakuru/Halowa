#pragma once
class Scene;

enum CollectItemsNum;

class C_Chest {
public:
	C_Chest(Math::Vector2 pos, CollectItemsNum type);
	~C_Chest();

	//�𗋐j�M�~�b�N
	void Init();   //�����l
	void Update(); //�X�V
	void UpdateHit();
	void Draw();   //�`��

	//�Z�b�^�[
	//void SetRange(bool Range); //�߂��ɂ���
	//void SetUsed(bool Used); //�L�[����
	//void SetChest(int chest) { m_chestNum = chest; }
	void SetOwner(Scene* owner) { m_owner = owner; }
	void PlaySE();

	//�Q�b�^�[
	//Math::Vector2 GetPos() { return chest.m_pos; }

	void SetVol(float a_Vol) {
		seInst->SetVolume(a_Vol);
	}

private:

	struct Chest {
		Math::Vector2 m_pos;
		Math::Vector2 m_move;
		float m_scale;
		float m_rotate;
		Math::Matrix m_mat;
		Math::Matrix m_scaleMat;
		Math::Matrix m_transMat;
		Math::Matrix m_rotateMat;
		float m_alpha;
		float m_angle;
	}chest, item , itemAni;


	int m_chestNum;
	bool chestFlg = false;
	bool itemFlg = false;
	bool itemBounceFlg = false;
	bool itemAniAlphaFlg = false;

	bool Once = false;
 
	float frameTimer;

	Scene* m_owner;

	KdTexture m_chestTex;
	KdTexture m_itemTex;
	KdTexture m_itemAniTex;

	int m_currentFrame;
	int m_frameCount;
	int m_frameTime;     
	int m_elapsedFrames;

	int m_currentColumn;;
	int m_currentRow;

	CollectItemsNum reward;

	//SE�p
	std::shared_ptr<KdSoundEffect>   se; //���f�[�^�̐݌v�}
	std::shared_ptr<KdSoundInstance> seInst; //�X�s�[�J�[�̐݌v�}

	//float vol;
};
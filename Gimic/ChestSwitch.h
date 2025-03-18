#pragma once
class Scene;

enum CollectItemsNum;

class C_Chest {
public:
	C_Chest(Math::Vector2 pos, CollectItemsNum type);
	~C_Chest();

	//避雷針ギミック
	void Init();   //初期値
	void Update(); //更新
	void UpdateHit();
	void Draw();   //描画

	//セッター
	//void SetRange(bool Range); //近くにいる
	//void SetUsed(bool Used); //キー入力
	//void SetChest(int chest) { m_chestNum = chest; }
	void SetOwner(Scene* owner) { m_owner = owner; }
	void PlaySE();

	//ゲッター
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

	//SE用
	std::shared_ptr<KdSoundEffect>   se; //音データの設計図
	std::shared_ptr<KdSoundInstance> seInst; //スピーカーの設計図

	//float vol;
};
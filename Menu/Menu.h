#pragma once
#include<string>
#include<fstream>
#include"../main.h"
#include"../Enum/AvoidTypeEnum.h"
#include"../Enum/ItemAndCollectEnum.h"


class Scene;

//メニューベース==========================================================================================
class C_MenuBase {
public:
	C_MenuBase(){}
	~C_MenuBase(){}

	float vol = 0.5;

	struct Object {
		Math::Vector2 m_pos = { 0,0 };
		Math::Vector2 m_move = { 0,0 };
		Math::Vector2 m_scale = {1,1};
		bool m_Alive = false;

		Math::Color m_color = {1,1,1,1};

		Math::Matrix m_mat;
		Math::Matrix m_scaleMat;
		Math::Matrix m_transMat;

		KdTexture m_Tex;

	};

	struct S_Number {
		Math::Vector2 m_pos = { 0,0 };
		Math::Vector2 m_scale = { 1,1 };
		bool m_Alive = true;

		Math::Color m_color = { 0,0,0,1 };

		Math::Matrix m_mat;
		Math::Matrix m_scaleMat;
		Math::Matrix m_transMat;

		int m_value=0;
	};

	KdTexture m_NumTex;

	POINT m_MousePos;

	void GetMousePos(POINT* a_MousePos) {
		//ディスプレイ上のマウス座標を取得(ディスプレイの左上が(0,0))
		GetCursorPos(a_MousePos);

		//指定のウィンドウ基準のマウス座標に変換(ウィンドウの左上が(0,0))
		ScreenToClient(APP.m_window.GetWndHandle(), a_MousePos);

		//マウスの座標系を実行ウィンドウの座標系(中心が(0,0)に補正)
		a_MousePos->x -= 1280 / 2;
		a_MousePos->y -= 720 / 2;
		a_MousePos->y *= -1;
	}

	bool m_KeyFlg = false;

	Scene* m_mOwner = nullptr;

	

	void ObjectMatrix(Object& a_object) {
		a_object.m_pos += a_object.m_move;
		a_object.m_transMat = Math::Matrix::CreateTranslation(a_object.m_pos.x, a_object.m_pos.y, 0);
		a_object.m_scaleMat = Math::Matrix::CreateScale(a_object.m_scale.x, a_object.m_scale.y, 1);
		a_object.m_mat = a_object.m_scaleMat * a_object.m_transMat;
		a_object.m_move = { 0,0 };
	}

	void DrawObject(Object& a_object, Math::Rectangle a_rect) {
		SHADER.m_spriteShader.SetMatrix(a_object.m_mat);
		SHADER.m_spriteShader.DrawTex(&a_object.m_Tex, 0, 0, &a_rect, &a_object.m_color);
	}

	void NumberMatrix(S_Number& a_number) {
		if (!a_number.m_Alive) return;
		a_number.m_scaleMat = Math::Matrix::CreateScale(a_number.m_scale.x, a_number.m_scale.y, 1);
		a_number.m_transMat = Math::Matrix::CreateTranslation(a_number.m_pos.x, a_number.m_pos.y, 0);
		a_number.m_mat = a_number.m_scaleMat * a_number.m_transMat;
	}

	void DrawNumber(S_Number& a_number) {
		if (!a_number.m_Alive)return;
		SHADER.m_spriteShader.SetMatrix(a_number.m_mat);
		Math::Rectangle rect = { a_number.m_value * 27,0,27,40 };
		SHADER.m_spriteShader.DrawTex(&m_NumTex, 0, 0, &rect, &a_number.m_color);
	}


};



//状態メニュー==========================================================================================
class C_StatusMenu:public C_MenuBase {
private:

	bool m_Active;
	bool m_AutoUpdate;
	bool SEOneFlg = false;

	bool m_Shake = false;
	int m_ShakeMove = 0;
	int m_ShakeCnt = 0;

	enum StatusMenuSE {
		StatusSelectSE,
		UnLockSE,
		StatusMenuSEMAX
	};

	std::shared_ptr<KdSoundEffect> se[StatusMenuSEMAX];
	std::shared_ptr<KdSoundInstance> seInst[StatusMenuSEMAX];

	

	AvoidType m_MenuAvoidNum=NormalAvoid;
	int m_NowSelect = 0;

	Object AllFrame,SelectFrame,UnderLine;
	S_Number NowHP[3], MaxHP[3], MaxMP[3], BoostAtkLv,Money[3], MpCost[3],ElectricPow[3],OverDamage[3];

	struct Skill {
		Math::Vector2 m_pos = { 0,0 };
		Math::Vector2 m_Move = { 0,0 };
		int m_Left;
		int m_Right;
		int m_Bottom;
		int m_Top;
		bool m_Hit;

		Math::Vector2 m_scale = { 1,1 };

		bool m_Alive;
		bool m_UnLock;

		int m_Num=0;
		AvoidType m_AvoidType;

		Math::Color m_color = { 1,1,1,1 };

		Math::Matrix m_mat;
		Math::Matrix m_scaleMat;
		Math::Matrix m_transMat;

		KdTexture m_tex;

		Math::Vector2 m_InfoPos = {322,0};
		bool m_InfoAlive;
		Math::Color m_InfoColor = { 1,1,1,1 };
		Math::Matrix m_InfoMat;
		KdTexture m_InfoTex;
		KdTexture m_LockInfoTex;


	};

	Skill SkillType[AvoidMax];

	KdTexture m_LockTex;
	KdTexture m_UnLockTex;

public:
	C_StatusMenu(){}
	~C_StatusMenu(){}

	void Update();
	void Draw();
	void Init();
	void ImGuiUpdate();

	void SkillMatrix(Skill& a_Skill);
	void SkillSetRange(Skill& a_Skill) {
		a_Skill.m_Left = a_Skill.m_pos.x - 50;
		a_Skill.m_Right = a_Skill.m_pos.x + 50;
		a_Skill.m_Bottom = a_Skill.m_pos.y - 50;
		a_Skill.m_Top = a_Skill.m_pos.y + 50;
	}
	void SkillHit(Skill& a_Skill) {
		if (a_Skill.m_Left<m_MousePos.x && a_Skill.m_Right>m_MousePos.x &&
			a_Skill.m_Bottom<m_MousePos.y && a_Skill.m_Top>m_MousePos.y) {
			a_Skill.m_Hit = true;
		}
		else {
			a_Skill.m_Hit = false;
		}
	}
	void DrawSkill(Skill& a_Skill);

	void LoadTex();
	void ReleaseTex();
	void LoadSE();

	void SetActive(bool a_Active, Scene* a_Owner);
	void SetAutoUpdate(AvoidType a_AvoidType) {
		m_AutoUpdate = true;
		m_NowSelect = SkillType[a_AvoidType].m_Num;
		m_ShakeMove = 10;
	}

	void SetAlive(bool a_Active) { m_Active = a_Active; }

	void SetVol(float a_Vol) {
		for (int i = 0; i < StatusMenuSEMAX; i++) {
			seInst[i]->SetVolume(a_Vol);
		}
	}
};



//アイテムメニュー==========================================================================================
class C_ItemMenu :public C_MenuBase {
private:

	enum ItemMenuSE {
		ItemSelectSE,
		EquipmentSE,
		ItemMenuSEMAX
	};

	std::shared_ptr<KdSoundEffect> se[ItemMenuSEMAX];
	std::shared_ptr<KdSoundInstance> seInst[ItemMenuSEMAX];

	bool m_Active;
	bool SEOneFlg = false;

	Object SelectFrame,AllFrame,CharacterE,UnderLine;

	int m_HaveItemCnt;
	int m_NowSelect;

	

	struct Items {
		Math::Vector2 m_pos = { 0,0 };
		int m_Left;
		int m_Right;
		int m_Bottom;
		int m_Top;
		bool m_Hit;
		Math::Vector2 m_scale = { 1,1 };
		bool m_Alive=false;
		int m_Num=0;

		Math::Color m_color = {1,1,1,1};

		Math::Matrix m_mat;
		Math::Matrix m_scaleMat;
		Math::Matrix m_transMat;

		KdTexture m_tex;

		Math::Vector2 m_InfoPos = { 270,100 };
		bool m_InfoAlive;
		Math::Color m_InfoColor = { 1,1,1,1 };
		Math::Matrix m_InfoMat;
		KdTexture m_InfoTex;

		S_Number ItemCnt;

	};

	Items HPPotion, MPPotion;


public:

	C_ItemMenu(){}
	~C_ItemMenu(){}

	void Update();
	void Draw();
	void Init();

	void ItemMatrix(Items& a_Items,ItemsNum a_ItemsNum);
	void ItemSetRange(Items& a_Items) {
		a_Items.m_Left = a_Items.m_pos.x - 50;
		a_Items.m_Right = a_Items.m_pos.x + 50;
		a_Items.m_Bottom = a_Items.m_pos.y - 50;
		a_Items.m_Top = a_Items.m_pos.y + 50;
	}
	void ItemHit(Items& a_Items) {
		if (a_Items.m_Left<(float)m_MousePos.x && a_Items.m_Right>(float)m_MousePos.x &&
			a_Items.m_Bottom<(float)m_MousePos.y && a_Items.m_Top>(float)m_MousePos.y) {
			a_Items.m_Hit = true;
		}
		else {
			a_Items.m_Hit = false;
		}
	}
	void DrawItems(Items& a_Items);

	void LoadTex();
	void ReleaseTex();
	void LoadSE();

	void SetActive(bool a_Active, Scene* a_Owner);
	void SetAlive(bool a_Active) { m_Active = a_Active; }
	void SetCharacterE(bool a_Alive) { CharacterE.m_Alive = a_Alive; }
	void SetVol(float a_Vol) {
		for (int i = 0; i < ItemMenuSEMAX; i++) {
			seInst[i]->SetVolume(a_Vol);
		}
	}

	void ImGuiUpdate();

};

//コレクションメニュー==========================================================================================
class C_CollectItemMenu:public C_MenuBase {
private:
	enum CollectMenuSE {
		CollectSelectSEA,
		CollectSelectSEB,
		CollectMenuSEMAX
	};

	std::shared_ptr<KdSoundEffect> se[CollectMenuSEMAX];
	std::shared_ptr<KdSoundInstance> seInst[CollectMenuSEMAX];

	int m_CollectItemCnt=0;
	int m_NowSelect=1;
	int m_NowRow, m_NowCol;

	bool m_KeyFlg;

	bool m_Active;

	Object AllFrame, SelectFrame,UnderLine;

	S_Number AllCollectItem[2], HaveCollectItem[2];

	struct S_CollectItem {
		Math::Vector2 m_Pos;

		int m_Left, m_Right, m_Bottom, m_Top;
		bool m_Hit;

		bool m_Alive;
		bool m_FirstGetFlg;
		int m_Num=0;
		int m_row=0, m_col=0;

		Math::Matrix m_Mat;

		Math::Color m_Color = { 1,1,1,1 };
		KdTexture m_Tex;

		Math::Vector2 m_InfoPos = {320,-90};
		bool m_InfoAlive;
		Math::Matrix m_InfoMat;
		KdTexture m_InfoTex;

	};

	S_CollectItem CollectItem[CollectItemsMax];



public:

	C_CollectItemMenu(){}
	~C_CollectItemMenu(){}

	void Update();
	void Draw();
	void Init();
	void LoadTex();
	void ReleaseTex();
	void LoadSE();
	void ImGuiUpdate();

	void SetActive(bool a_Active, Scene* a_Owner);

	void SetFActive() { m_Active = false; }

	void SetVol(float a_Vol) {
		for (int i = 0; i < CollectMenuSEMAX; i++) {
			seInst[i]->SetVolume(a_Vol);
		}
	}

	void CollectMatrix(S_CollectItem& a_CollectItem);
	void DrawCollect(S_CollectItem& a_CollectItem);

	bool GetCollectItemAlive(CollectItemsNum a_CollectItemsNum) {
		return CollectItem[a_CollectItemsNum].m_Alive;
	}
	bool GetFirstGetFlg(CollectItemsNum a_CollectItemsNum) {
		return CollectItem[a_CollectItemsNum].m_FirstGetFlg;
	}

	void CollectSetRange(S_CollectItem& a_Collect) {
		a_Collect.m_Left = a_Collect.m_Pos.x - 50;
		a_Collect.m_Right = a_Collect.m_Pos.x + 50;
		a_Collect.m_Bottom = a_Collect.m_Pos.y - 50;
		a_Collect.m_Top = a_Collect.m_Pos.y + 50;
	}

	void CollectHit(S_CollectItem& a_Collect) {
		if (a_Collect.m_Left<(float)m_MousePos.x && a_Collect.m_Right>(float)m_MousePos.x &&
			a_Collect.m_Bottom<(float)m_MousePos.y && a_Collect.m_Top>(float)m_MousePos.y) {
			a_Collect.m_Hit = true;
		}
		else {
			a_Collect.m_Hit = false;
		}
	}

	void SetCollectItem(CollectItemsNum a_CollectItemNum) {
		if (!CollectItem[a_CollectItemNum].m_Alive) {
			m_CollectItemCnt++;
			CollectItem[a_CollectItemNum].m_Num = m_CollectItemCnt;
			CollectItem[a_CollectItemNum].m_row = (CollectItem[a_CollectItemNum].m_Num-1) / 5;
			CollectItem[a_CollectItemNum].m_col = (CollectItem[a_CollectItemNum].m_Num-1) % 5;
			CollectItem[a_CollectItemNum].m_Alive = true;
			
		}
	}

	void MenuDatSave();
	void MenuDatLoad();
	void MenuDatDelete();
	std::string BoolToString(bool a_Bool) {
		if (a_Bool) return "TRUE";
		else return "FALSE";
	}
	bool ParseBool(const std::string& str) {
		if (str == "true" || str == "TRUE") return true;
		else return false;
	}


};

//マップメニュー==========================================================================================
class C_MapMenu:public C_MenuBase {
private:
	Object AllFrame;

public:

	C_MapMenu(){}
	~C_MapMenu(){}

	void Update();
	void Draw();

	void LoadTex();
	void ReleaseTex();
	void SetOwner(Scene* a_Owner) { m_mOwner = a_Owner; }

};

//メニュー==========================================================================================
class C_Menu :public C_MenuBase {
private:

	bool m_Active;
	bool m_AutoUpdate;
	bool SEOneFlg = false;

	enum MenuSE {
		MenuTabSelectSE,
		MenuTabMouseHitSE,
		OpenMenuSE,
		ExitMenuSE,
		LiberationSE,
		MenuSEMAX
	};

	std::shared_ptr<KdSoundEffect> se[MenuSEMAX];
	std::shared_ptr<KdSoundInstance> seInst[MenuSEMAX];

	C_ItemMenu m_ItemMenu;
	C_StatusMenu m_StatusMenu;
	C_CollectItemMenu m_CollectItemMenu;
	C_MapMenu m_MapMenu;

	bool m_TabKeyFlg = false;

	enum MenuNum {
		MenuMin,
		Status,
		Item,
		Collect,
		Map,
		MenuMax
	};

	MenuNum m_MenuNum;

	Object UnderLine, OverLine,OverSelectFrame, BackGround;

	struct S_Tab {
		Math::Vector2 m_Pos;
		Math::Vector2 m_scale = { 1,1 };
		int m_Left;
		int m_Right;
		int m_Bottom;
		int m_Top;
		bool m_Hit;

		MenuNum m_Num;

		Math::Matrix m_scaleMat;
		Math::Matrix m_transMat;
		Math::Matrix m_mat;

		Math::Color m_color = { 1,1,1,1 };
		KdTexture m_Tex;

	};

	S_Tab StatusTab, ItemTab, CollectTab, MapTab;

public:
	C_Menu(){}
	~C_Menu(){}

	void Update();
	void Draw();
	void Init();

	void LoadTex();
	void ReleaseTex();
	void LoadSE();

	void SetActive(bool a_Active) {
		m_Active = a_Active;
		seInst[OpenMenuSE]->Play();
		m_MenuNum = Status;
		UnderLine.m_pos = { 0,-330 };
		OverLine.m_pos = { 0,330 };
		OverSelectFrame.m_pos = { -297,335 };
		//OverSelectFrame.m_pos = { -102,335 };
		//OverSelectFrame.m_pos = { 97,335 };
		//OverSelectFrame.m_pos = { 277,335 };
		BackGround.m_color = { 1,1,1,0.8 };
	}

	void SetActive(AvoidType a_AvoidType) {
		seInst[LiberationSE]->Play();
		UnderLine.m_pos = { 0,-330 };
		OverLine.m_pos = { 0,330 };
		OverSelectFrame.m_pos = { -297,335 };
		BackGround.m_color = { 1,1,1,0.8 };
		m_Active = true;
		m_AutoUpdate = true;
		m_MenuNum = Status;
		m_StatusMenu.SetAutoUpdate(a_AvoidType);
	}

	void SetOwner(Scene* a_Owner) { m_mOwner = a_Owner; }
	void SetTabKeyFlg(bool a_TabKeyFlg) { m_TabKeyFlg = a_TabKeyFlg; }
	void SetAutoUpdate() { m_AutoUpdate = false; }
	void SetVol(float a_Vol){
		for (int i = 0; i < MenuSEMAX; i++) {
			seInst[i]->SetVolume(0.5 * a_Vol);
		}
		m_CollectItemMenu.SetVol(0.5 * a_Vol);
		m_ItemMenu.SetVol(0.5 * a_Vol);
		m_StatusMenu.SetVol(0.5 * a_Vol);
		
	}

	C_ItemMenu* GetItemMenu() { return &m_ItemMenu; }
	C_CollectItemMenu* GetCollectMenu() { return &m_CollectItemMenu; }
	C_StatusMenu* GetStatusMenu() { return &m_StatusMenu; }
	bool GetTabKeyFlg() { return m_TabKeyFlg; }
	bool GetActive() { return m_Active; }

	void ImGuiUpdate();

	void DrawTab(S_Tab& a_Tab) {
		SHADER.m_spriteShader.SetMatrix(a_Tab.m_mat);
		Math::Rectangle rect = { 0,0,150,70 };
		SHADER.m_spriteShader.DrawTex(&a_Tab.m_Tex, 0, 0, &rect, &a_Tab.m_color);
	}
	void TabMatrix(S_Tab& a_Tab) {
		a_Tab.m_scaleMat = Math::Matrix::CreateScale(a_Tab.m_scale.x, a_Tab.m_scale.y, 1);
		a_Tab.m_transMat = Math::Matrix::CreateTranslation(a_Tab.m_Pos.x, a_Tab.m_Pos.y, 0);
		a_Tab.m_mat = a_Tab.m_scaleMat * a_Tab.m_transMat;
	}
	void TabSetRange(S_Tab& a_Tab) {
		a_Tab.m_Left = a_Tab.m_Pos.x - 75;
		a_Tab.m_Right = a_Tab.m_Pos.x + 75;
		a_Tab.m_Bottom = a_Tab.m_Pos.y - 35;
		a_Tab.m_Top = a_Tab.m_Pos.y + 35;
	}
	void TabHit(S_Tab& a_Tab) {

		if (a_Tab.m_Left<(float)m_MousePos.x && a_Tab.m_Right>(float)m_MousePos.x &&
			a_Tab.m_Bottom<(float)m_MousePos.y && a_Tab.m_Top>(float)m_MousePos.y) {
			a_Tab.m_Hit = true;
			a_Tab.m_scale = { 1.1,1.1 };
			if (!seInst[MenuTabMouseHitSE]->IsPlay()) {
				if (!seInst[MenuTabSelectSE]->IsPlay()) {
					if (!SEOneFlg) {
						if (m_MenuNum != a_Tab.m_Num) {
							seInst[MenuTabMouseHitSE]->Play();
							SEOneFlg = true;
						}
					}
				}
			}
		}
		else {
			a_Tab.m_Hit = false;
		}
	}


};
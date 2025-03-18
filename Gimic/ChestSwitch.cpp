#include "ChestSwitch.h"
#include "../Scene.h"
#include"../Enum/ItemAndCollectEnum.h"

//C_Chest::C_Chest(Math::Vector2 pos) :m_owner(nullptr)
//{
//	m_chestTex.Load("Texture/Gimic/Chest.png");
//	chest.m_pos = pos;
//
//	m_itemTex.Load("Texture/Gimic/item.png");
//	m_itemAniTex.Load("Texture/Gimic/itemstarloop.png");
//}

C_Chest::C_Chest(Math::Vector2 pos, CollectItemsNum type) :m_owner(nullptr) {

	m_chestTex.Load("Texture/Gimic/Chest.png");
	m_itemTex.Load("Texture/Gimic/Items.png");
	m_itemAniTex.Load("Texture/Gimic/itemstarloop.png");

	chest.m_pos = pos;
	item.m_pos = chest.m_pos;
	itemAni.m_pos = { chest.m_pos.x, chest.m_pos.y + 200 };
	reward = type;

	Init();
}

C_Chest::~C_Chest()
{
	m_chestTex.Release();
	m_itemTex.Release();
	m_itemAniTex.Release();
}

void C_Chest::Init()
{
	chestFlg = false;
	itemFlg = false;
	itemBounceFlg = false;
	itemAniAlphaFlg = false;

	Once = false;

	chest.m_scale = 0.6;
	m_chestNum = 0;
	chest.m_alpha = 1.0f;

	m_currentFrame = -1;
	m_frameTime = 3;
	m_elapsedFrames = 0;

	item.m_move = { 0.0f,0.0f };
	item.m_angle = 0;
	item.m_scale = 0.0f;
	item.m_alpha = 1.0f;

	itemAni.m_scale = 1.0f;
	itemAni.m_alpha = 0;

	frameTimer = 0;

	//音量初期値
	//vol = 0.3f; //MAXは1.0f

	//SE
	//①メモリ領域の確保
	se = std::make_shared<KdSoundEffect>();

	//②音データの読み込み
	se->Load("Sound/Gimic/544015__mr_fritz__item-pick-up.WAV");

	//③スピーカーのメモリ確保＆音データを渡す
	seInst = se->CreateInstance(false);
	//seInst->SetVolume(vol); //ボリューム調整(セッターで音を流す)
}

void C_Chest::Update()
{
	C_Chara* player = m_owner->GetChara();
	C_MapBase* map = m_owner->GetMap();
	GimicManager* instance = m_owner->GetGimicMgr();
	C_CollectItemMenu* menu = m_owner->GetMenu()->GetCollectMenu();

	if (chestFlg) {
		frameTimer++;

		item.m_scale += 0.01f;
		if (item.m_scale > 1.0f) {
			item.m_scale = 1.0f;
		}

		item.m_move.y += 0.09f;
		if (item.m_pos.y + item.m_move.y > chest.m_pos.y + 210) {
			item.m_move.y = 0;
			item.m_pos.y = chest.m_pos.y + 210;
			itemBounceFlg = true;
			itemAniAlphaFlg = true;
		}

		if (itemAniAlphaFlg) {
			itemAni.m_alpha += 0.02f;
			if (itemAni.m_alpha > 1.0f) {
				itemAni.m_alpha = 1.0f;
				itemAniAlphaFlg = false;
			}
		}

		if (frameTimer >= 3 * 60) {
			m_chestNum = 0;

			switch (reward) {
			case FirstKey:          menu->SetCollectItem(FirstKey); break;
			case SecondKey:         menu->SetCollectItem(SecondKey); break;
			case ThirdKey:          menu->SetCollectItem(ThirdKey); break;
			case SunBook:           menu->SetCollectItem(SunBook); break;
			case SuperLuckCrystal:  menu->SetCollectItem(SuperLuckCrystal); break;
			case PocketWatch:       menu->SetCollectItem(PocketWatch); break;
			case AncientBook:       menu->SetCollectItem(AncientBook); break;
			case Horn:              menu->SetCollectItem(Horn); break;
			default:                break;
			}
		}

		if (frameTimer >= 4 * 60) {
			chest.m_alpha -= 0.01f;
			item.m_alpha -= 0.01f;
			itemAni.m_alpha -= 0.02f;

			if (chest.m_alpha < 0.0f) chest.m_alpha = 0.0f;
			if (item.m_alpha < 0.0f) item.m_alpha = 0.0f;
			if (itemAni.m_alpha < 0.0f) itemAni.m_alpha = 0.0f;

			if (chest.m_alpha == 0.0f && item.m_alpha == 0.0f) {
				chestFlg = false;
				itemFlg = false;
				itemBounceFlg = false;
				frameTimer = 0;
				instance->RemoveChest();
			}
		}
	}

	const int spriteSheetColumns = 8;
	const int spriteSheetRows = 8;
	const int totalFrames = spriteSheetColumns * spriteSheetRows;

	if (itemFlg) {
		m_elapsedFrames++;
		if (m_elapsedFrames >= m_frameTime) {
			m_currentFrame++;
			if (m_currentFrame >= totalFrames) {
				m_currentFrame = 0;  // Loop back to the first frame
			}
			m_elapsedFrames = 0;

			m_currentRow = m_currentFrame % spriteSheetRows;
			m_currentColumn = m_currentFrame / spriteSheetColumns;
		}

		if (itemBounceFlg) {
			item.m_angle += 5;
			if (item.m_angle >= 360) {
				item.m_angle = 0;
			}
			//sinから-1～1が返る?
			item.m_move.y = sin(DirectX::XMConvertToRadians(item.m_angle)) * 1;

		}
	}

	item.m_pos.y += item.m_move.y;

	item.m_scaleMat = Math::Matrix::CreateScale(item.m_scale, item.m_scale, 1.0f);
	item.m_transMat = Math::Matrix::CreateTranslation(item.m_pos.x - map->GetScrollX(), item.m_pos.y - map->GetScrollY(), 0);
	item.m_mat = item.m_scaleMat * item.m_transMat;

	itemAni.m_scaleMat = Math::Matrix::CreateScale(itemAni.m_scale, itemAni.m_scale, 1.0f);
	itemAni.m_transMat = Math::Matrix::CreateTranslation(itemAni.m_pos.x - map->GetScrollX(), itemAni.m_pos.y - map->GetScrollY(), 0);
	itemAni.m_mat = itemAni.m_scaleMat * itemAni.m_transMat;

	chest.m_scaleMat = Math::Matrix::CreateScale(chest.m_scale, chest.m_scale, 1.0f);
	chest.m_transMat = Math::Matrix::CreateTranslation(chest.m_pos.x - map->GetScrollX(), chest.m_pos.y - map->GetScrollY(), 0);
	chest.m_mat = chest.m_scaleMat * chest.m_transMat;
}

void C_Chest::UpdateHit()
{
	C_Chara* player = m_owner->GetChara();
	GimicManager* key = m_owner->GetGimicMgr();

	float a = chest.m_pos.x - player->GetPos().x;  //底辺a
	float b = chest.m_pos.y - player->GetPos().y;  //高さb
	float c = sqrt(a * a + b * b); //斜辺(距離)c
	if (c < 200) {
		if (!Once) {
			key->SetKey({ chest.m_pos.x,chest.m_pos.y + 100 });
			Once = true;
		}
		if (GetAsyncKeyState('F') & 0x8000) {
			if (!chestFlg && !itemFlg) {
				key->ClearKey();
				m_chestNum = 3;
				PlaySE();
				chestFlg = true;
				itemFlg = true;
			}
		}
	}
	else if (!chestFlg && !itemFlg && Once) {
		Once = false;
		key->ClearKey();
		//key->RemoveLastKey();
		//key->RemoveKeyAt({ chest.m_pos.x,chest.m_pos.y + 100 });
	}
}

void C_Chest::Draw()
{
	//描画
	Math::Rectangle srcChestRect; //テクスチャ座標
	switch (m_chestNum) {
	case 0:
		srcChestRect = { 0, 0, 133, 128 };
		break;
	case 3:
		srcChestRect = { 399, 0, 133, 128 };
		break;
	default:
		break;
	}
	SHADER.m_spriteShader.SetMatrix(chest.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_chestTex, 0, 0, &srcChestRect, &Math::Color(1.0f, 1.0f, 1.0f, chest.m_alpha));


	Math::Rectangle srcItemRect; //テクスチャ座標

	if (itemFlg) {
		SHADER.m_spriteShader.SetMatrix(itemAni.m_mat);
		SHADER.m_spriteShader.DrawTex(&m_itemAniTex, Math::Rectangle{ 512 * m_currentRow, 512 * m_currentColumn, 512, 512 }, itemAni.m_alpha);
		;
		//描画
		switch (reward) {
		case FirstKey:
			srcItemRect = { 400, 0, 100, 100 };
			break;
		case SecondKey:
			srcItemRect = { 300, 0, 100, 100 };
			break;
		case ThirdKey:
			srcItemRect = { 500, 0, 100, 100 };
			break;
		case AncientBook:
			srcItemRect = { 0, 0, 100, 100 };
			break;
		case SunBook:
			srcItemRect = { 700, 0, 100, 100 };
			break;
		case PocketWatch:
			srcItemRect = { 600, 0, 100, 100 };
			break;
		case SuperLuckCrystal:
			srcItemRect = { 100, 0, 100, 100 };
			break;
		case Horn:
			srcItemRect = { 200, 0, 100, 100 };
			break;
		default:
			break;
		}
		SHADER.m_spriteShader.SetMatrix(item.m_mat);
		SHADER.m_spriteShader.DrawTex(&m_itemTex, 0, 0, &srcItemRect, &Math::Color(1.0f, 1.0f, 1.0f, item.m_alpha));
		//SHADER.m_spriteShader.DrawTex(&m_itemTex, Math::Rectangle{ 0, 0, 1000, 1000 }, 1.0f);
	}
}

void C_Chest::PlaySE()
{
	//音再生
	seInst->Play(); //ループ再生オフ
}


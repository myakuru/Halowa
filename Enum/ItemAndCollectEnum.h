#pragma once

//アイテム管理
enum HaveItems {
	ItemEmpty,
	HaveHPPotion,
	HaveMPPotion
};

//アイテムの種類
enum ItemsNum {
	ItemsMin,
	HPPotionNum,
	MPPotionNum,
	ItemsMax,

	BoostMin,
	AtkBoostNum,
	HPBoostNum,
	MPBoostNum,
	BoostMax
};

//宝物の種類
enum CollectItemsNum {
	FirstKey,
	SecondKey,
	ThirdKey,
	AncientBook,
	SunBook,
	PocketWatch,
	SuperLuckCrystal,
	Horn,
	CollectItemsMax
};

//なんかアイテムのEnum==========================================================================================
enum SetHaveItem {
	SetHaveHPPotion,
	SetHaveMPPotion
};
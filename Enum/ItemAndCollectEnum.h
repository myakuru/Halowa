#pragma once

//�A�C�e���Ǘ�
enum HaveItems {
	ItemEmpty,
	HaveHPPotion,
	HaveMPPotion
};

//�A�C�e���̎��
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

//�󕨂̎��
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

//�Ȃ񂩃A�C�e����Enum==========================================================================================
enum SetHaveItem {
	SetHaveHPPotion,
	SetHaveMPPotion
};
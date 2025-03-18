#pragma once
#include"../MapBase.h"
class C_EnemyBase;

class C_map005 :public C_MapBase
{
public:
	C_map005();
	~C_map005();

	void InitMap() override;

	void DrawMap() override;

	void ScrollUpdate() override;

	void DrawBackGround() const override;

	void UpdateBackGround() override;

	void StageMove()override;

	void StageGimmickUpdate()override;

	//MAPフラグのゲッター
	bool GetMapFlg() override { return m_mapFlg; }
	//MAPフラグのセッター
	void SetMapFlg(bool flg) override { C_MapBase::SetMapFlg(flg); }
	//一つ前のステージに行くフラグのゲッター
	bool GetMapBeforeFlg()override { return m_mapBeforeFlg; }

private:

	bool trapTrigger = false;

	C_EnemyBase* enemyNum[6];
};
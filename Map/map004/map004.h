#pragma once
#include"../MapBase.h"
class C_map004	:public C_MapBase
{
public:
	C_map004();
	~C_map004();

	void InitMap() override;

	void DrawMap() override;

	void ScrollUpdate() override;

	void DrawBackGround() const override;

	void UpdateBackGround() override;

	void StageMove()override;

	void EnemyPos1() override;

	//MAPフラグのゲッター
	bool GetMapFlg() override { return m_mapFlg; }
	//MAPフラグのセッター
	void SetMapFlg(bool flg) override { C_MapBase::SetMapFlg(flg); }
	//一つ前のステージに行くフラグのゲッター
	bool GetMapBeforeFlg()override { return m_mapBeforeFlg; }

private:

};

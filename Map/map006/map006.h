#pragma once
#include"../MapBase.h"
class C_map006 :public C_MapBase
{
public:
	C_map006();
	~C_map006();

	void InitMap() override;

	void DrawMap() override;

	void ScrollUpdate() override;

	void DrawBackGround() const override;

	void UpdateBackGround() override;

	void EnemyPos1() override;

	void StageMove()override;

	//MAPフラグのゲッター
	bool GetMapFlg() override { return m_mapFlg; }
	//MAPフラグのセッター
	void SetMapFlg(bool flg) override { C_MapBase::SetMapFlg(flg); }
	//一つ前のステージに行くフラグのゲッター
	bool GetMapBeforeFlg()override { return m_mapBeforeFlg; }
	//次のステージに行くフラグのゲッター
	bool GetMapNextFlg() { return m_mapNextFlg; }

private:

};
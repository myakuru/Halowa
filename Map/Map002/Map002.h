#pragma once
#include "../MapBase.h"

class C_Map002 :public C_MapBase
{

public:
	C_Map002 ();
	~C_Map002 ();

	void InitMap() override;

	void DrawMap() override;

	void  UpdateMap() override;

	void ScrollUpdate() override;

	void DrawBackGround() const override;

	void UpdateBackGround() override;

	void StageMove()override;

	void StageGimmickUpdate() override;

	//MAPフラグのゲッター
	bool GetMapFlg() override { return m_mapFlg; }
	//MAPフラグのセッター
	void SetMapFlg(bool flg) override { C_MapBase::SetMapFlg(flg); }

	//一つ前のステージに行くフラグのゲッター
	bool GetMapBeforeFlg()override { return m_mapBeforeFlg; }

private:

	bool EnterFlg = false;

};

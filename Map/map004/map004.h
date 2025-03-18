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

	//MAP�t���O�̃Q�b�^�[
	bool GetMapFlg() override { return m_mapFlg; }
	//MAP�t���O�̃Z�b�^�[
	void SetMapFlg(bool flg) override { C_MapBase::SetMapFlg(flg); }
	//��O�̃X�e�[�W�ɍs���t���O�̃Q�b�^�[
	bool GetMapBeforeFlg()override { return m_mapBeforeFlg; }

private:

};

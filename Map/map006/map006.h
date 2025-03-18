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

	//MAP�t���O�̃Q�b�^�[
	bool GetMapFlg() override { return m_mapFlg; }
	//MAP�t���O�̃Z�b�^�[
	void SetMapFlg(bool flg) override { C_MapBase::SetMapFlg(flg); }
	//��O�̃X�e�[�W�ɍs���t���O�̃Q�b�^�[
	bool GetMapBeforeFlg()override { return m_mapBeforeFlg; }
	//���̃X�e�[�W�ɍs���t���O�̃Q�b�^�[
	bool GetMapNextFlg() { return m_mapNextFlg; }

private:

};
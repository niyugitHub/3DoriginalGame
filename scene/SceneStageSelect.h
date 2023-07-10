#pragma once
#include "SceneBase.h"
#include<memory>
#include<array>

class FieldBase;

class SceneStageSelect : public SceneBase
{
public:
	SceneStageSelect();
	virtual ~SceneStageSelect();

	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;
	virtual void draw() override;

	//ステージ番号によってステージを変える関数
	void SelectStage(int stageNum);

	virtual void normalUpdate() override;

private:
	int m_stageNum; // ステージ番号
	int m_stageX;
	int m_stageY;
	int m_coinHandle;

	void ChangeStage();

	std::shared_ptr<FieldBase> m_Field;

	std::array<UI, 11> m_UI;//UI情報

	Vec2 m_coinPos[10][3];

	SceneBase* m_nextScene;
};


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

	//�X�e�[�W�ԍ��ɂ���ăX�e�[�W��ς���֐�
	void SelectStage(int stageNum);

	virtual void normalUpdate() override;

private:
	int m_stageNum; // �X�e�[�W�ԍ�
	int m_stageX;
	int m_stageY;
	int m_coinHandle;

	void ChangeStage();

	std::shared_ptr<FieldBase> m_Field;

	std::array<UI, 11> m_UI;//UI���

	Vec2 m_coinPos[10][3];

	SceneBase* m_nextScene;
};


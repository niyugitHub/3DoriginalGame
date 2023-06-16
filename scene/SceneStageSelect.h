#pragma once
#include "SceneBase.h"
#include<memory>

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

private:
	int m_stageNum;

	std::shared_ptr<FieldBase> m_Field;
};


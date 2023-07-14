#pragma once
#include "SceneBase.h"
#include <array>
#include "../util/Vec2.h"

class SceneMainMenu : public SceneBase
{
public:
	SceneMainMenu();
	virtual ~SceneMainMenu();

	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;
	virtual void draw() override;

	virtual void normalUpdate() override;

private:

	enum SelectAction
	{
		StageSelect,	//�X�e�[�W�Z���N�g
		Option,		//�I�v�V����
		Title			//�^�C�g��
	};

	void DecisionNum(int& selectNum);	//����\

	int m_selectScreen;	//����I�����邩
	std::array<UI, 3> m_UI;//UI���

	SceneBase* m_nextScene;
};


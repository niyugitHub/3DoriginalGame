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
		StageSelect,	//ステージセレクト
		Option,		//オプション
		Title			//タイトル
	};

	void DecisionNum(int& selectNum);	//決定表

	int m_selectScreen;	//何を選択するか
	std::array<UI, 3> m_UI;//UI情報

	SceneBase* m_nextScene;
};



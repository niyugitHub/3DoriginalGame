#pragma once
#include "SceneBase.h"

class SceneSelectScreen : public SceneBase
{
public:
	SceneSelectScreen();
	virtual ~SceneSelectScreen();

	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;
	virtual void draw() override;

private:

	enum
	{
		kStageSelect,	//ステージセレクト
		kOption,		//オプション
		kTitle			//タイトル
	};

	void DecisionNum(int& selectNum);	//決定表

	int m_selectScreen;	//何を選択するか
};



#pragma once
#include "SceneBase.h"
#include<array>
#include <DxLib.h>

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;
	virtual void draw() override;

private:
	//UIのアップデート
	void UiUpdate();

	void DecisionNum(int& selectNum);	//決定表

	struct Data
	{
		int handle = -1;
		VECTOR pos;
		float speed;
		bool isModelUp;//モデルの移動が上昇中かどうか
	};

	enum
	{
		kStart = 0,
		kExit = 1
	};

	//ブロックモデルのハンドル
	std::array<Data, 4>m_data;

	//画像UIの配列
	std::array<UI, 2> m_UI;

	//選んだ番号
	int m_selectNum;
};


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
		VECTOR pos = {0.0f,0.0f};
		float speed = 0.0f;
		bool isModelUp = false;//モデルの移動が上昇中かどうか
	};

	struct stringData
	{
		int handle = -1;
		Vec2 pos = {0,0};
		float jumpPower = 0.0f;
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

	//文字画像UIの配列
	std::array<stringData, 11> m_stringUI;

	//選んだ番号
	int m_selectNum;
};


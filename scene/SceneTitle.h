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
	struct Data
	{
		int handle = -1;
		VECTOR pos;
		float speed;
		bool isModelUp;//モデルの移動が上昇中かどうか
	};
	//ブロックモデルのハンドル
	std::array<Data, 4>m_data;
};


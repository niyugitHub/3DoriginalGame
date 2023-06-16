#include "SceneStageSelect.h"
#include"Pad.h"
#include"SceneMain.h"
#include"SceneOption.h"
#include <DxLib.h>
#include "field/Field1.h"
#include "field/Field2.h"
#include "field/Field3.h"
#include "field/Field4.h"

namespace
{
	constexpr int kStageNumY = 2;//Y方向のステージ数
	constexpr int kStageNumX = 5;//X方向のステージ数

	//ステージ決定表
	constexpr int kStage[kStageNumY][kStageNumX] =
	{
		{1,2,3,4,5},
		{6,7,8,9,10}
	};
}

SceneStageSelect::SceneStageSelect() : 
	m_stageNum(1),
	m_Field(nullptr)
{
}

SceneStageSelect::~SceneStageSelect()
{
}

void SceneStageSelect::init()
{
}

void SceneStageSelect::end()
{
}

SceneBase* SceneStageSelect::update()
{
	ChangeStage();

	if (Pad::isTrigger(PAD_INPUT_1) && m_stageNum != 0)
	{
		SelectStage(m_stageNum);
		return new SceneMain(m_Field);
	}
	return this;
}

void SceneStageSelect::draw()
{
	DrawString(300, 300, "SceneStageSelect", 0xffffff);
	DrawFormatString(300, 400, 0xffffff, "%d", m_stageNum);
}

void SceneStageSelect::SelectStage(int stageNum)
{
	switch (stageNum)
	{
	case 1:
		m_Field = std::make_shared<Field1>();
		break;
	case 2:
		m_Field = std::make_shared<Field2>();
		break;
	case 3:
		m_Field = std::make_shared<Field3>();
		break;
	case 4:
		m_Field = std::make_shared<Field4>();
		break;
			/*case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:*/

	};
}

void SceneStageSelect::ChangeStage()
{
	//ステージX番号
	static int stageX = 0;
	//ステージY番号
	static int stageY = 0;

	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		stageX--;
		if (stageX < 0) //範囲外アクセス防止
		{
			stageX = kStageNumX - 1;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		stageX++;
		if (stageX > kStageNumX - 1) //範囲外アクセス防止
		{
			stageX = 0;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		stageY--;
		if (stageY < 0) //範囲外アクセス防止
		{
			stageY = kStageNumY - 1;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		stageY++;
		if (stageY > kStageNumY - 1) //範囲外アクセス防止
		{
			stageY = 0;
		}
	}

	//m_stageNumに決定表代入
	m_stageNum = kStage[stageY][stageX];
}

#include "SceneStageSelect.h"
#include"Pad.h"
#include"SceneMain.h"
#include"SceneOption.h"
#include"SceneSelectScreen.h"
#include <DxLib.h>
#include "field/Field1.h"
#include "field/Field2.h"
#include "field/Field3.h"
#include "field/Field4.h"
#include"game.h"

namespace
{
	constexpr int kStageNumY = 2;//Y方向のステージ数
	constexpr int kStageNumX = 5;//X方向のステージ数

	//ステージ決定表
	constexpr int kStage[kStageNumY][kStageNumX] =
	{
		{0,1,2,3,4},
		{5,6,7,8,9}
	};
}

SceneStageSelect::SceneStageSelect() : 
	m_stageNum(0),
	m_Field(nullptr)
{
	float X = 300;
	float Y = 300;
	int count = 0;
	for (auto& UI : m_UI)
	{
		UI.pos = { X,Y };
		UI.size = { UI.pos.x + 200.0f,UI.pos.y + 200 };

		X += 280;
		count++;

		if (count == 5)
		{
			X = 300;
			Y = 600;
		}
	}

	m_UI[10].pos = { 0,Game::kScreenHeight - 200 };
	m_UI[10].size = { 300 ,Game::kScreenHeight };
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

	if (Pad::isTrigger(PAD_INPUT_1) && m_stageNum != 10)
	{
		SelectStage(m_stageNum);
		return new SceneMain(m_Field);
	}
	else if (Pad::isTrigger(PAD_INPUT_1) && m_stageNum == 10)
	{
		return new SceneSelectScreen;
	}
	return this;
}

void SceneStageSelect::draw()
{
	DrawString(300, 300, "SceneStageSelect", 0xffffff);
	DrawFormatString(300, 400, 0xffffff, "%d", m_stageNum);

	for (int i = 0; i < m_UI.size(); i++)
	{
		if (m_stageNum == i)
		{
			DrawBox(m_UI[i].pos.x - 20, m_UI[i].pos.y - 20,
				m_UI[i].size.x + 20, m_UI[i].size.y + 20,
				0xffffff, true);
		}
		DrawBox(m_UI[i].pos.x, m_UI[i].pos.y,
			m_UI[i].size.x, m_UI[i].size.y,
			0x0000ff, true);
	}
}

void SceneStageSelect::SelectStage(int stageNum)
{
	switch (stageNum)
	{
	case 0:
		m_Field = std::make_shared<Field1>();
		break;
	case 1:
		m_Field = std::make_shared<Field2>();
		break;
	case 2:
		m_Field = std::make_shared<Field3>();
		break;
	case 3:
		m_Field = std::make_shared<Field4>();
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	};
}

void SceneStageSelect::ChangeStage()
{
	//ステージX番号
	static int stageX = 0;
	//ステージY番号
	static int stageY = 0;

	if (Pad::isTrigger(PAD_INPUT_LEFT) && m_stageNum != 10)
	{
		stageX--;
		if (stageX < 0) //範囲外アクセス防止
		{
			stageX = kStageNumX - 1;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_RIGHT) && m_stageNum != 10)
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
			stageY = kStageNumY;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		stageY++;
		if (stageY > kStageNumY) //範囲外アクセス防止
		{
			stageY = 0;
		}
	}

	if (stageY == kStageNumY)
	{
		m_stageNum = 10;
		return;
	}
	//m_stageNumに決定表代入
	m_stageNum = kStage[stageY][stageX];
}

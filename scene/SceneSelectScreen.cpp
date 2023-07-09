#include "SceneSelectScreen.h"
#include "SceneStageSelect.h"
#include "SceneTitle.h"
#include "SceneOption.h"
#include "../util/Pad.h"
#include <DxLib.h>
#include "../util/ImageUI.h"

namespace
{
	//ファイル名
	const char* const kEnemyModelFileName[3] =
	{
		"data/image/SceneSelectPlay.png",
		"data/image/SceneSelectOption.png",
		"data/image/SceneSelectTitle.png"
	};
}

SceneSelectScreen::SceneSelectScreen() : 
	m_selectScreen(kStageSelect)
{
	int sizeX,sizeY;
	m_UI[0].pos = { 450.0f,540.0f };
	m_UI[1].pos = { 1350,340 };
	m_UI[2].pos = { 1350.0f,760.0f };

	for (int i = 0; i < static_cast<int>(m_UI.size()); i++)
	{
		m_UI[i].handle = LoadGraph(kEnemyModelFileName[i]);
		GetGraphSize(m_UI[i].handle, &sizeX, &sizeY);
		m_UI[i].size = { static_cast<float>(sizeX / 2),static_cast<float>(sizeY / 2) };
	}

	m_pImageUI = std::make_shared<ImageUI>();

	for (int i = 0; i < static_cast<int>(m_UI.size()); i++)
	{
		m_pImageUI->AddUI(m_UI[i].pos, m_UI[i].size, m_UI[i].handle);
	}
}

SceneSelectScreen::~SceneSelectScreen()
{
}

void SceneSelectScreen::init()
{
}

void SceneSelectScreen::end()
{
}

SceneBase* SceneSelectScreen::update()
{
	DecisionNum(m_selectScreen);

	SelectSE();

	if (Pad::isTrigger(PAD_INPUT_1) && m_selectScreen == kStageSelect)
	{
		return new SceneStageSelect;
	}
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectScreen == kOption)
	{
		//自身のポインター、ゲーム中のオプション画面かのフラグを引数に持つ
		return new SceneOption(this,false);
	}
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectScreen == kTitle)
	{
		return new SceneTitle;
	}

	return this;
}

void SceneSelectScreen::draw()
{
	DrawFormatString(300, 0, 0xffffff, "%d", m_selectScreen);

	m_pImageUI->Draw(m_selectScreen,0);
	/*for (int i = 0; i < m_UI.size(); i++)
	{
		if (m_selectScreen == i)
		{
			DrawBox(static_cast<int>(m_UI[i].pos.x - 20), 
				static_cast<int>(m_UI[i].pos.y - 20),
				static_cast<int>(m_UI[i].size.x + 20), 
				static_cast<int>(m_UI[i].size.y + 20),
				0xffffff, true);
		}
		DrawBox(static_cast<int>(m_UI[i].pos.x), static_cast<int>(m_UI[i].pos.y),
			static_cast<int>(m_UI[i].size.x), static_cast<int>(m_UI[i].size.y),
			0x0000ff,true);
	}*/
}

void SceneSelectScreen::DecisionNum(int& selectNum)
{
	switch (selectNum)
	{
	case kStageSelect:
		if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			selectNum = kOption;
		}
		break;

	case kOption:
		if (Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_UP))
		{
			selectNum = kTitle;
		}
		if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			selectNum = kStageSelect;
		}
		break;

	case kTitle:
		if (Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_UP))
		{
			selectNum = kOption;
		}
		if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			selectNum = kStageSelect;
		}
		break;
	default:
		break;
	}
}

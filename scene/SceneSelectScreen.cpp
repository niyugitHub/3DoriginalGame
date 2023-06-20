#include "SceneSelectScreen.h"
#include "SceneStageSelect.h"
#include "SceneTitle.h"
#include "SceneOption.h"
#include "Pad.h"
#include <DxLib.h>

SceneSelectScreen::SceneSelectScreen() : 
	m_selectScreen(kStageSelect)
{
	m_UI[0].pos = { 200.0f,200.0f };
	m_UI[0].size = { m_UI[0].pos.x + 300.0f,m_UI[0].pos.y + 500.0f };
	m_UI[1].pos = { 800,200 };
	m_UI[1].size = { m_UI[1].pos.x + 500.0f,m_UI[1].pos.y + 200.0f };
	m_UI[2].pos = { 800.0f,500.0f };
	m_UI[2].size = { m_UI[2].pos.x + 500.0f,m_UI[2].pos.y + 200.0f };
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

	for (int i = 0; i < m_UI.size(); i++)
	{
		if (m_selectScreen == i)
		{
			DrawBox(static_cast<int>(m_UI[i].pos.x - 20), 
				static_cast<int>(m_UI[i].pos.y - 20),
				static_cast<int>(m_UI[i].size.x + 20), 
				static_cast<int>(m_UI[i].size.y + 20),
				0xffffff, true);
		}
		DrawBox(m_UI[i].pos.x, m_UI[i].pos.y,
			m_UI[i].size.x, m_UI[i].size.y,
			0x0000ff,true);
	}
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

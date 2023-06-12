#include "SceneSelectScreen.h"
#include "SceneStageSelect.h"
#include "SceneTitle.h"
#include "SceneOption.h"
#include "Pad.h"
#include <DxLib.h>

SceneSelectScreen::SceneSelectScreen() : 
	m_selectScreen(kStageSelect)
{
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
		return new SceneOption(this);
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
}

void SceneSelectScreen::DecisionNum(int& selectNum)
{
	switch (selectNum)
	{
	case kStageSelect:
		if (Pad::isTrigger(PAD_INPUT_DOWN))
		{
			selectNum = kOption;
		}
		if (Pad::isTrigger(PAD_INPUT_UP))
		{
			selectNum = kTitle;
		}
		break;

	case kOption:
		if (Pad::isTrigger(PAD_INPUT_DOWN))
		{
			selectNum = kTitle;
		}
		if (Pad::isTrigger(PAD_INPUT_UP))
		{
			selectNum = kStageSelect;
		}
		break;

	case kTitle:
		if (Pad::isTrigger(PAD_INPUT_DOWN))
		{
			selectNum = kStageSelect;
		}
		if (Pad::isTrigger(PAD_INPUT_UP))
		{
			selectNum = kOption;
		}
		break;
	default:
		break;
	}
}

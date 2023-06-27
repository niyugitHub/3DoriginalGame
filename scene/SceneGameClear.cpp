#include "SceneGameClear.h"
#include "SceneMain.h"
#include "SceneStageSelect.h"
#include "SceneTitle.h"
#include"DxLib.h"
#include "../util/Pad.h"
#include"../object/Player.h"
#include"../object/field/FieldBase.h"

SceneGameClear::SceneGameClear(std::shared_ptr<Player> pPlayer, std::shared_ptr<FieldBase> pField) : 
	m_selectNum(kStageSelect)
{
	m_pPlayer = pPlayer;
	m_pField = pField;
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::init()
{
}

SceneBase* SceneGameClear::update()
{
	m_pPlayer->ClearUpdate();

	DecisionNum(m_selectNum);

	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kStageSelect)
	{
		return new SceneStageSelect;
	}
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kRestart)
	{
		return new SceneMain(m_pField);
	}
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kTitle)
	{
		return new SceneTitle;
	}

	return this;
}

void SceneGameClear::draw()
{
	m_pField->Draw();
	m_pPlayer->Draw();
	/*DrawString(0, 0,
		"ゲームクリア！", 0xffffff);
	DrawString(0, 100,
		"Zボタンで戻る", 0xffffff);*/
	DrawFormatString(300, 0, 0xffffff, "%d", m_selectNum);
}

void SceneGameClear::DecisionNum(int& selectNum)
{
	switch (selectNum)
	{
	case kStageSelect:
		if (Pad::isTrigger(PAD_INPUT_DOWN))
		{
			selectNum = kRestart;
		}
		if (Pad::isTrigger(PAD_INPUT_UP))
		{
			selectNum = kTitle;
		}
		break;

	case kRestart:
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
			selectNum = kRestart;
		}
		break;
	default:
		break;
	}
}

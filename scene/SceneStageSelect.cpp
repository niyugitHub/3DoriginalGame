#include "SceneStageSelect.h"
#include"Pad.h"
#include"SceneMain.h"
#include"SceneOption.h"
#include <DxLib.h>
#include "field/Field1.h"
#include "field/Field2.h"
#include "field/Field3.h"

SceneStageSelect::SceneStageSelect() : 
	m_stageNum(0),
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
	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		m_stageNum--;
	}

	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		m_stageNum++;
	}
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
		/*case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:*/

	};
}

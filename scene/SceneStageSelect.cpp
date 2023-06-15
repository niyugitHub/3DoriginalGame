#include "SceneStageSelect.h"
#include"Pad.h"
#include"SceneMain.h"
#include"SceneOption.h"
#include <DxLib.h>
#include "field/Field1.h"
#include "field/Field2.h"

SceneStageSelect::SceneStageSelect() : 
	m_stageNum(0)
{
	m_Field = std::make_shared<Field1>();
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
	if (Pad::isTrigger(PAD_INPUT_1) && m_stageNum == 0)
	{
		return new SceneMain(m_Field);
	}
	if (Pad::isTrigger(PAD_INPUT_1) && m_stageNum == 1)
	{
		return new SceneOption(this);
	}
	return this;
}

void SceneStageSelect::draw()
{
	DrawString(300, 300, "SceneStageSelect", 0xffffff);
	DrawFormatString(300, 400, 0xffffff, "%d", m_stageNum);
}

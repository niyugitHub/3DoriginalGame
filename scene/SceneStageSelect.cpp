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
	constexpr int kStageNumY = 2;//Y�����̃X�e�[�W��
	constexpr int kStageNumX = 5;//X�����̃X�e�[�W��

	//�X�e�[�W����\
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
	//�X�e�[�WX�ԍ�
	static int stageX = 0;
	//�X�e�[�WY�ԍ�
	static int stageY = 0;

	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		stageX--;
		if (stageX < 0) //�͈͊O�A�N�Z�X�h�~
		{
			stageX = kStageNumX - 1;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		stageX++;
		if (stageX > kStageNumX - 1) //�͈͊O�A�N�Z�X�h�~
		{
			stageX = 0;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		stageY--;
		if (stageY < 0) //�͈͊O�A�N�Z�X�h�~
		{
			stageY = kStageNumY - 1;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		stageY++;
		if (stageY > kStageNumY - 1) //�͈͊O�A�N�Z�X�h�~
		{
			stageY = 0;
		}
	}

	//m_stageNum�Ɍ���\���
	m_stageNum = kStage[stageY][stageX];
}

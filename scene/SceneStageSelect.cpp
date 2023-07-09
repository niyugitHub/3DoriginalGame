#include "SceneStageSelect.h"
#include "../util/Pad.h"
#include"SceneMain.h"
#include"SceneOption.h"
#include"SceneSelectScreen.h"
#include <DxLib.h>
#include "../object/field/Field1.h"
#include "../object/field/Field2.h"
#include "../object/field/Field3.h"
#include "../object/field/Field4.h"
#include "../object/field/Field5.h"
#include "../object/field/Field6.h"
#include "../object/field/Field7.h"
#include "../object/field/Field8.h"
#include "../object/field/Field9.h"
#include "../object/field/Field10.h"
#include"../game.h"
#include"../SaveData.h"
#include "../util/ImageUI.h"
#include "../SoundManager.h"

namespace
{
	constexpr int kStageNumY = 2;//Y�����̃X�e�[�W��
	constexpr int kStageNumX = 5;//X�����̃X�e�[�W��

	//�X�e�[�W����\
	constexpr int kStage[kStageNumY][kStageNumX] =
	{
		{0,1,2,3,4},
		{5,6,7,8,9}
	};

	constexpr int kCoinWidth = 60; //�R�C���̕�
	constexpr int kCoinHeight = 120; //�R�C���̕�
	
	//�t�@�C����
	const char* const kFileName[11] =
	{
		"data/image/stage1.png",
		"data/image/stage2.png",
		"data/image/stage3.png",
		"data/image/stage4.png",
		"data/image/stage5.png",
		"data/image/stage6.png",
		"data/image/stage7.png",
		"data/image/stage8.png",
		"data/image/stage9.png",
		"data/image/stage10.png",
		"data/image/back.png",
	};

	const char* const kCoinName = "data/image/Coin.png";
}

SceneStageSelect::SceneStageSelect() : 
	m_stageNum(0),
	m_stageX(0),
	m_stageY(0),
	m_coinHandle(-1),
	m_Field(nullptr)
{
	float X = 440;
	float Y = 440;

	int sizeX, sizeY;

	int count = 0;
	for (auto& UI : m_UI)
	{
		UI.pos = { X,Y };
		UI.handle = LoadGraph(kFileName[count]);
		GetGraphSize(UI.handle, &sizeX, &sizeY);
		UI.size = { static_cast<float>(sizeX / 2),static_cast<float>(sizeY / 2) };

		X += 280;
		count++;

		if (count == 5)
		{
			X = 440;
			Y = 740;
		}
	}

	m_coinHandle = LoadGraph(kCoinName);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_coinPos[i][j] = { m_UI[i].pos.x - 90,m_UI[i].pos.y - 80 };
			m_coinPos[i][j].x += kCoinWidth * j + 10;
			m_coinPos[i][j].y += kCoinHeight;
		}
	}

	m_UI[10].pos = { 150,Game::kScreenHeight - 100 };

	m_pImageUI = std::make_shared<ImageUI>();

	for (int i = 0; i < static_cast<int>(m_UI.size()); i++)
	{
		m_pImageUI->AddUI(m_UI[i].pos, m_UI[i].size, m_UI[i].handle);
	}
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

	SelectSE();

	if (Pad::isTrigger(PAD_INPUT_1) && m_stageNum != 10)
	{
		SoundManager::GetInstance().StopBGMAndSE();
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

	m_pImageUI->Draw(m_stageNum,0);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (SaveData::GetStar(i, j))
			{
				DrawGraph(static_cast<int>(m_coinPos[i][j].x), static_cast<int>(m_coinPos[i][j].y),
					m_coinHandle, true);
			}
		}
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
		m_Field = std::make_shared<Field5>();
		break;
	case 5:
		m_Field = std::make_shared<Field6>();
		break;
	case 6:
		m_Field = std::make_shared<Field7>();
		break;
	case 7:
		m_Field = std::make_shared<Field8>();
		break;
	case 8:
		m_Field = std::make_shared<Field9>();
		break;
	case 9:
		m_Field = std::make_shared<Field10>();
		break;
	};
}

void SceneStageSelect::ChangeStage()
{
	////�X�e�[�WX�ԍ�
	//static int m_stageX = 0;
	////�X�e�[�WY�ԍ�
	//static int m_stageY = 0;

	if (Pad::isTrigger(PAD_INPUT_LEFT) && m_stageNum != 10)
	{
		m_stageX--;
		if (m_stageX < 0) //�͈͊O�A�N�Z�X�h�~
		{
			m_stageX = kStageNumX - 1;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_RIGHT) && m_stageNum != 10)
	{
		m_stageX++;
		if (m_stageX > kStageNumX - 1) //�͈͊O�A�N�Z�X�h�~
		{
			m_stageX = 0;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_stageY--;
		if (m_stageY < 0) //�͈͊O�A�N�Z�X�h�~
		{
			m_stageY = kStageNumY;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_stageY++;
		if (m_stageY > kStageNumY) //�͈͊O�A�N�Z�X�h�~
		{
			m_stageY = 0;
		}
	}

	if (m_stageY == kStageNumY)
	{
		m_stageNum = 10;
		return;
	}
	//m_stageNum�Ɍ���\���
	m_stageNum = kStage[m_stageY][m_stageX];
}

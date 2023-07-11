#include "SceneGameClear.h"
#include "SceneMain.h"
#include "SceneStageSelect.h"
#include "SceneTitle.h"
#include"DxLib.h"
#include "../util/Pad.h"
#include"../object/Player.h"
#include"../object/Camera.h"
#include"../object/field/FieldBase.h"
#include"../SoundManager.h"
#include "../util/ImageUI.h"
#include"../object/Item.h"

namespace
{
	//�t�@�C����
	const char* const kGameClearFileName[3] =
	{
		"data/image/GameClear.png",
		"data/image/GameClearRetry.png",
		"data/image/GameClearStageSelect.png"
	};

	const char* const kCoinFileName = "data/image/co.png";

	//�X�N���[���I�����̒l
	constexpr int kStopScroll = 10;
}

//�V�[���ɓ����Ă���̃t���[�����𐔂���
static int frameCount = 0;
static int scroll = 1100;

SceneGameClear::SceneGameClear(std::shared_ptr<Player> pPlayer, std::shared_ptr<FieldBase> pField,
	std::shared_ptr<Camera>pCamera) :
	m_selectNum(kStageSelect)
{
	m_coinHandle = LoadGraph(kCoinFileName);
	int sizeX, sizeY;

	m_pPlayer = pPlayer;
	m_pField = pField;
	m_pCamera = pCamera;
	frameCount = 0;
	scroll = 1100;

	m_UI[0].pos = { 1300,500 };
	m_UI[1].pos = { 1100,800 };
	m_UI[2].pos = { 1500,800 };
	m_coinPos[0] = { 1055,510 };
	m_coinPos[1] = { 1290,510 };
	m_coinPos[2] = { 1528,510 };

	m_pImageUI = std::make_shared<ImageUI>();
	for (int i = 0; i < static_cast<int>(m_UI.size()); i++)
	{
		m_UI[i].handle = LoadGraph(kGameClearFileName[i]);
		GetGraphSize(m_UI[i].handle, &sizeX, &sizeY);
		m_UI[i].size = { static_cast<float>(sizeX / 2),static_cast<float>(sizeY / 2) };
		m_pImageUI->AddUI(m_UI[i].pos, m_UI[i].size, m_UI[i].handle);
	}
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::init()
{
}

SceneBase* SceneGameClear::update()
{
	frameCount++;
	//�N���A�����ۂ̃v���C���[�A�J�����̃A�b�v�f�[�g
	m_pPlayer->ClearUpdate();
	m_pCamera->ClearUpdate(m_pPlayer, frameCount > 150);

	if (frameCount > 150)
	{
		scroll = max(static_cast<int>(scroll - (scroll * 0.05f)), 0);
	}

	// m_selectNum�̐��l��ω������邽�߂̊֐�
	DecisionNum(m_selectNum);

	//PAD1���������Am_selectNum���e�l�̂Ƃ�(������Ă�BGM���~�߂āA�V����BGM���Đ�)
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kStageSelect && scroll < kStopScroll)
	{
		SoundManager::GetInstance().StopBGMAndSE();
		SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
		return new SceneStageSelect;
	}
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kRestart && scroll < kStopScroll)
	{
		m_pField->ResetTime();
		m_pField->GetItem()->SetExist(true);
		SoundManager::GetInstance().StopBGMAndSE();
		//SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
		return new SceneMain(m_pField);
	}

	return this;
}

void SceneGameClear::draw()
{
	m_pField->Draw();
	m_pPlayer->Draw();

	m_pImageUI->Draw(m_selectNum, scroll);

	for (int i = 0; i < static_cast<int>(m_coinPos.size()); i++)
	{
		if (m_pField->GetStar(i))
		{
			DrawExtendGraph(static_cast<int>(m_coinPos[i].x) + scroll - 125, static_cast<int>(m_coinPos[i].y) - 125,
				static_cast<int>(m_coinPos[i].x) + scroll + 125, static_cast<int>(m_coinPos[i].y) + 125,
				m_coinHandle, true);
		}
	}

	/*DrawString(0, 0,
		"�Q�[���N���A�I", 0xffffff);
	DrawString(0, 100,
		"Z�{�^���Ŗ߂�", 0xffffff);*/
	DrawFormatString(300, 0, 0xffffff, "%d", m_selectNum,0);
}

void SceneGameClear::DecisionNum(int& selectNum)
{
	if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		if (selectNum == kStageSelect)
		{
			selectNum = kRestart;
		}

		else if (selectNum == kRestart)
		{
			selectNum = kStageSelect;
		}
	}
}

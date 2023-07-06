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

namespace
{
	//ファイル名
	const char* const kGameClearFileName[3] =
	{
		"data/image/GameClear.png",
		"data/image/GameClearRetry.png",
		"data/image/GameClearStageSelect.png"
	};

	const char* const kCorsorFileName = "data/image/cursor.png";
}

//シーンに入ってからのフレーム数を数える
static int frameCount = 0;
static int scroll = 1100;

SceneGameClear::SceneGameClear(std::shared_ptr<Player> pPlayer, std::shared_ptr<FieldBase> pField,
	std::shared_ptr<Camera>pCamera) :
	m_selectNum(kStageSelect)
{
	int sizeX, sizeY;

	m_pPlayer = pPlayer;
	m_pField = pField;
	m_pCamera = pCamera;
	frameCount = 0;
	scroll = 1100;

	m_UI[0].pos = { 1300,500 };
	m_UI[1].pos = { 1100,800 };
	m_UI[2].pos = { 1500,800 };

	for (int i = 0; i < m_UI.size(); i++)
	{
		m_UI[i].handle = LoadGraph(kGameClearFileName[i]);
		GetGraphSize(m_UI[i].handle, &sizeX, &sizeY);
		m_UI[i].size = { static_cast<float>(sizeX / 2),static_cast<float>(sizeY / 2) };
	}

	m_pImageUI = std::make_shared<ImageUI>();

	for (int i = 0; i < m_UI.size(); i++)
	{
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
	//クリアした際のプレイヤー、カメラのアップデート
	m_pPlayer->ClearUpdate();
	m_pCamera->ClearUpdate(m_pPlayer, frameCount > 150);

	if (frameCount > 150)
	{
		scroll = max(scroll - (scroll * 0.05f), 0);
	}

	// m_selectNumの数値を変化させるための関数
	DecisionNum(m_selectNum);

	//PAD1を押した、m_selectNumが各値のとき(今流れてるBGMを止めて、新しいBGMを再生)
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kStageSelect)
	{
		SoundManager::GetInstance().StopBGMAndSE();
		SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
		return new SceneStageSelect;
	}
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kRestart)
	{
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

	/*DrawString(0, 0,
		"ゲームクリア！", 0xffffff);
	DrawString(0, 100,
		"Zボタンで戻る", 0xffffff);*/
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

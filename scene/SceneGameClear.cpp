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

SceneGameClear::SceneGameClear(std::shared_ptr<Player> pPlayer, std::shared_ptr<FieldBase> pField,
	std::shared_ptr<Camera>pCamera) :
	m_selectNum(kStageSelect)
{
	m_pPlayer = pPlayer;
	m_pField = pField;
	m_pCamera = pCamera;
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::init()
{
}

SceneBase* SceneGameClear::update()
{
	//シーンに入ってからのフレーム数を数える
	static int frameCount = 0;
	frameCount++;
	//クリアした際のプレイヤー、カメラのアップデート
	m_pPlayer->ClearUpdate();
	m_pCamera->ClearUpdate(m_pPlayer, frameCount > 150);

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
		SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
	}
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kTitle)
	{
		SoundManager::GetInstance().StopBGMAndSE();
		SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
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

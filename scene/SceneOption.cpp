#include "SceneOption.h"
#include"SceneBase.h"
#include"SceneTitle.h"
#include"SceneMain.h"
#include"SceneStageSelect.h"
#include<DxLib.h>
#include "../util/Pad.h"
#include"../game.h"
#include "../util/ImageUI.h"
#include"../SoundManager.h"

namespace
{
	//ファイル名
	const char* const kOptionFileName[4] =
	{
		"data/image/OptionSceneBGM.png",
		"data/image/OptionSceneSE.png",
		"data/image/Option_SelectStage.png",
		"data/image/back.png"
	};

	const char* const kCorsorFileName = "data/image/cursor.png";
}

SceneOption::SceneOption(SceneBase* pScene, bool isSceneMain) : 
	m_selectOption(0),
	m_nextScene(nullptr)
{
	int sizeX, sizeY;
	//前のシーン代入
	m_pScene = pScene;

	m_isSceneMain = isSceneMain;

	if (m_isSceneMain)
	{
		m_UI[0].pos = { 960.0f,200.0f };
		m_UI[1].pos = { 960.0f,500.0f };
		m_UI[2].pos = { 960.0f,800.0f };
		m_UI[3].pos = { 150,Game::kScreenHeight - 100 };
		m_corsorPosY[0] = 355;
		m_corsorPosY[1] = 700;
	}

	else
	{
		m_UI[0].pos = { 960.0f,350.0f };
		m_UI[1].pos = { 960.0f,700.0f };
		m_UI[2].pos = { 960.0f,10000.0f };//画面外表示
		m_UI[3].pos = { 150,Game::kScreenHeight - 100 };
		m_corsorPosY[0] = 255;
		m_corsorPosY[1] = 500;
	}

	for (int i = 0; i < static_cast<int>(m_UI.size()); i++)
	{
		m_UI[i].handle = LoadGraph(kOptionFileName[i]);
		GetGraphSize(m_UI[i].handle, &sizeX, &sizeY);
		m_UI[i].size = { static_cast<float>(sizeX / 2),static_cast<float>(sizeY / 2) };
	}

	m_pImageUI = std::make_shared<ImageUI>();

	for (int i = 0; i < static_cast<int>(m_UI.size()); i++)
	{
		m_pImageUI->AddUI(m_UI[i].pos, m_UI[i].size, m_UI[i].handle);
	}

	m_volumeBGM = SoundManager::GetInstance().GetBGMVolume() / 63;
	m_volumeSE = SoundManager::GetInstance().GetSEVolume() / 63;

	m_corsorHandle = LoadGraph(kCorsorFileName);
}

SceneOption::~SceneOption()
{
}

void SceneOption::init()
{
	m_updateFunc = &SceneBase::fadeinUpdate;
	m_pImageUI->Init();
	m_pImageUI->SetResetCount();
}

void SceneOption::end()
{
}

SceneBase* SceneOption::update()
{
	(this->*m_updateFunc)();

	if (m_pImageUI->GetFadeout())
	{
		m_nextScene->init();
		
		return m_nextScene;
	}

	return this;
}

void SceneOption::draw()
{
	if (m_isSceneMain)
	{
		m_pScene->draw();
	}

	DrawBox(0, 0, 100, 100, 0xffffff, true);

	DrawString(0, 400, "オプション画面", 0xffffff);

	m_pImageUI->Draw(m_selectOption,0);

	DrawGraph(505 + m_volumeBGM * 202 + m_pImageUI->GetScrollSize(0), m_corsorPosY[0], m_corsorHandle, true);

	DrawGraph(505 + m_volumeSE * 202 + m_pImageUI->GetScrollSize(1), m_corsorPosY[1], m_corsorHandle, true);
}

void SceneOption::normalUpdate()
{
	SelectUpdate();

	SelectSE();

	m_nextScene = nullptr;

	if (m_selectOption == Bgm)
	{
		AccelerateChangeBGMVoluem();
	}

	if (m_selectOption == Se)
	{
		AccelerateChangeSEVoluem();
	}

	if (Pad::isTrigger(PAD_INPUT_8))
	{
		SoundManager::GetInstance().SaveSoundConfig();
		m_nextScene = m_pScene;
	}

	if (Pad::isTrigger(PAD_INPUT_1) && m_selectOption == Back)
	{
		SoundManager::GetInstance().SaveSoundConfig();
		m_nextScene = m_pScene;
	}

	if (Pad::isTrigger(PAD_INPUT_1) && m_isSceneMain && m_selectOption == StageSelect)
	{
		SoundManager::GetInstance().SaveSoundConfig();
		SoundManager::GetInstance().StopBGMAndSE();
		SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
		m_nextScene = new SceneStageSelect;
	}

	if (m_nextScene != nullptr)
	{
		m_updateFunc = &SceneBase::fadeoutUpdate;
	}
	//オプションの番号を決定

}

void SceneOption::SelectUpdate()
{
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_selectOption++;
		if (m_selectOption == StageSelect && !m_isSceneMain)
		{
			m_selectOption++;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_selectOption--;
		if (m_selectOption == StageSelect && !m_isSceneMain)
		{
			m_selectOption--;
		}
	}

	if (m_selectOption > Back)
	{
		m_selectOption = Bgm;
	}

	if (m_selectOption < Bgm)
	{
		m_selectOption = Back;
	}
}

void SceneOption::AccelerateChangeBGMVoluem()
{
	auto& soundMgr = SoundManager::GetInstance();
	if (Pad::isTrigger(PAD_INPUT_LEFT) && m_volumeBGM > 0)
	{
		m_volumeBGM--;
	}

	if (Pad::isTrigger(PAD_INPUT_RIGHT) && m_volumeBGM < 4)
	{
		m_volumeBGM++;
	}

	soundMgr.SetBGMVolume(static_cast<unsigned short>(m_volumeBGM * 64));
}

void SceneOption::AccelerateChangeSEVoluem()
{
	auto& soundMgr = SoundManager::GetInstance();
	if (Pad::isTrigger(PAD_INPUT_LEFT) && m_volumeSE > 0)
	{
		m_volumeSE--;
	}

	if (Pad::isTrigger(PAD_INPUT_RIGHT) && m_volumeSE < 4)
	{
		m_volumeSE++;
	}

	soundMgr.SetSEVolume(static_cast<unsigned short>(m_volumeSE * 64));
}

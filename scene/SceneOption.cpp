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
	m_selectOption(0)
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
	}

	else
	{
		m_UI[0].pos = { 960.0f,350.0f };
		m_UI[1].pos = { 960.0f,700.0f };
		m_UI[2].pos = { 960.0f,10000.0f };
		m_UI[3].pos = { 150,Game::kScreenHeight - 100 };
	}

	for (int i = 0; i < m_UI.size(); i++)
	{
		m_UI[i].handle = LoadGraph(kOptionFileName[i]);
		GetGraphSize(m_UI[i].handle, &sizeX, &sizeY);
		m_UI[i].size = { static_cast<float>(sizeX / 2),static_cast<float>(sizeY / 2) };
	}

	m_pImageUI = std::make_shared<ImageUI>();

	for (int i = 0; i < m_UI.size(); i++)
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
}

void SceneOption::end()
{
}

SceneBase* SceneOption::update()
{
	SelectUpdate();

	SelectSE();

	if (m_selectOption == kBgm)
	{
		AccelerateChangeBGMVoluem();
	}

	if (m_selectOption == kSe)
	{
		AccelerateChangeSEVoluem();
	}

	if (Pad::isTrigger(PAD_INPUT_8))
	{
		SoundManager::GetInstance().SaveSoundConfig();
		return m_pScene;
	}

	if (Pad::isTrigger(PAD_INPUT_1) && m_selectOption == kBack)
	{
		SoundManager::GetInstance().SaveSoundConfig();
		return m_pScene;
	}

	if (Pad::isTrigger(PAD_INPUT_1) && m_isSceneMain && m_selectOption == kStageSelect)
	{
		SoundManager::GetInstance().SaveSoundConfig();
		SoundManager::GetInstance().StopBGMAndSE();
		SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");		return new SceneStageSelect;
	}

	//オプションの番号を決定


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

	DrawGraph(505 + m_volumeBGM * 202, 355, m_corsorHandle, true);

	DrawGraph(505 + m_volumeSE * 202, 700, m_corsorHandle, true);
}

void SceneOption::SelectUpdate()
{
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_selectOption++;
		if (m_selectOption == kStageSelect && !m_isSceneMain)
		{
			m_selectOption++;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_selectOption--;
		if (m_selectOption == kStageSelect && !m_isSceneMain)
		{
			m_selectOption--;
		}
	}

	if (m_selectOption > kBack)
	{
		m_selectOption = kBgm;
	}

	if (m_selectOption < kBgm)
	{
		m_selectOption = kBack;
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

	soundMgr.SetBGMVolume(m_volumeBGM * 64);
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

	soundMgr.SetSEVolume(m_volumeSE * 64);
}

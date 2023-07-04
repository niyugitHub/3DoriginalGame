#include "SceneOption.h"
#include"SceneBase.h"
#include"SceneTitle.h"
#include"SceneMain.h"
#include"SceneStageSelect.h"
#include<DxLib.h>
#include "../util/Pad.h"
#include"../game.h"
#include "../util/ImageUI.h"

namespace
{
	//ファイル名
	const char* const kEnemyModelFileName[3] =
	{
		"data/image/OptionSceneBGM.png",
		"data/image/OptionSceneSE.png",
		"data/image/back.png"
	};
}

SceneOption::SceneOption(SceneBase* pScene, bool isSceneMain) : 
	m_selectOption(0)
{
	int sizeX, sizeY;
	//前のシーン代入
	m_pScene = pScene;

	m_isSceneMain = isSceneMain;

	m_UI[0].pos = { 960.0f,350.0f };
	m_UI[1].pos = { 960.0f,700.0f };
	m_UI[2].pos = { 150,Game::kScreenHeight - 100 };

	for (int i = 0; i < m_UI.size(); i++)
	{
		m_UI[i].handle = LoadGraph(kEnemyModelFileName[i]);
		GetGraphSize(m_UI[i].handle, &sizeX, &sizeY);
		m_UI[i].size = { static_cast<float>(sizeX / 2),static_cast<float>(sizeY / 2) };
	}

	m_pImageUI = std::make_shared<ImageUI>();

	for (int i = 0; i < m_UI.size(); i++)
	{
		m_pImageUI->AddUI(m_UI[i].pos, m_UI[i].size, m_UI[i].handle);
	}
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

	if (Pad::isTrigger(PAD_INPUT_8))
	{
		return m_pScene;
	}

	if (Pad::isTrigger(PAD_INPUT_1) && m_selectOption == kBack)
	{
		return m_pScene;
	}

	if (Pad::isTrigger(PAD_INPUT_1) && m_isSceneMain)
	{
		return new SceneStageSelect;
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

	m_pImageUI->Draw(m_selectOption);
}

void SceneOption::SelectUpdate()
{
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_selectOption++;
	}

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_selectOption--;
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

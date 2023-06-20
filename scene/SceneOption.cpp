#include "SceneOption.h"
#include"SceneBase.h"
#include"SceneTitle.h"
#include"SceneMain.h"
#include"SceneStageSelect.h"
#include<DxLib.h>
#include"Pad.h"
#include"game.h"


SceneOption::SceneOption(SceneBase* pScene, bool isSceneMain) : 
	m_selectOption(0)
{
	//前のシーン代入
	m_pScene = pScene;

	m_isSceneMain = isSceneMain;

	m_UI[0].pos = { 400.0f,250.0f };
	m_UI[0].size = { m_UI[0].pos.x + 800.0f,m_UI[0].pos.y + 200.0f };
	m_UI[1].pos = { 800,600 };
	m_UI[1].size = { m_UI[1].pos.x + 800.0f,m_UI[1].pos.y + 200.0f };
	m_UI[2].pos = { 0,Game::kScreenHeight - 200 };
	m_UI[2].size = { 300 ,Game::kScreenHeight };
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
	if (Pad::isTrigger(PAD_INPUT_8))
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
	m_pScene->draw();

	DrawBox(0, 0, 100, 100, 0xffffff, true);

	DrawString(0, 400, "オプション画面", 0xffffff);

	for (int i = 0; i < m_UI.size(); i++)
	{
		if (m_selectOption == i)
		{
			DrawBox(m_UI[i].pos.x - 20, m_UI[i].pos.y - 20,
				m_UI[i].size.x + 20, m_UI[i].size.y + 20,
				0xffffff, true);
		}
		DrawBox(m_UI[i].pos.x, m_UI[i].pos.y,
			m_UI[i].size.x, m_UI[i].size.y,
			0x0000ff, true);
	}
}

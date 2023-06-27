#include "SceneManager.h"
#include <cassert>
#include "SceneBase.h"
#include "SceneDebug.h"
#include"SceneTitle.h"
#include"SceneStageSelect.h"
#include "../util/Pad.h"
#include<DxLib.h>
#include"../game.h"

namespace
{
	const char* kImageName1 = "data/image/Background_2.png";
	const char* kImageName2 = "data/image/Background_1.png";

	constexpr int kImageNum = 2; //”wŒi‚Ì”
	constexpr int kImageSpeed[kImageNum] = { 2,3 };
}

SceneManager::SceneManager() :
	m_pScene()
{
	m_backGraundHandle[0] = -1;
	m_backGraundHandle[1] = -1;

	m_backGraundPos[0] = 0;
	m_backGraundPos[1] = 0;
}
SceneManager::~SceneManager()
{

}

void SceneManager::init()
{
	m_pScene = new SceneTitle;
	m_pScene->init();

	m_backGraundHandle[0] = LoadGraph(kImageName1);
	m_backGraundHandle[1] = LoadGraph(kImageName2);
}

void SceneManager::end()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->end();
}

void SceneManager::update()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	Pad::update();
	SceneBase* pScene = m_pScene->update();
	if (pScene != m_pScene)
	{
		// ‘O‚ÌƒV[ƒ“‚ÌI—¹ˆ—
		m_pScene->end();

		m_pScene = pScene;
		m_pScene->init();
	}

	backGraundUpdate();
}

void SceneManager::draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	/*DrawGraph(0, 0, m_backGraundHandle[1], true);
	DrawGraph(0, 0, m_backGraundHandle[0], true);*/

	for (int i = 0; i < kImageNum; i++)
	{
		DrawModiGraph(m_backGraundPos[i], 0,
			m_backGraundPos[i] + Game::kScreenWidth, 0,
			m_backGraundPos[i] + 1920, 1080,
			m_backGraundPos[i], 1080,
			m_backGraundHandle[i], true);

		DrawModiGraph(m_backGraundPos[i] - Game::kScreenWidth, 0,
			m_backGraundPos[i], 0,
			m_backGraundPos[i], 1080,
			m_backGraundPos[i] - Game::kScreenWidth, 1080,
			m_backGraundHandle[i], true);
	}

	
	m_pScene->draw();
}

void SceneManager::backGraundUpdate()
{
	for (int i = 0; i < kImageNum; i++)
	{
		m_backGraundPos[i] += kImageSpeed[i];

		if (m_backGraundPos[i] > Game::kScreenWidth)
		{
			m_backGraundPos[i] = 0;
		}
	}
}

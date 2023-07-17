#include "SceneExplanation.h"
#include<DxLib.h>
#include"../util/Pad.h"
#include"../util/ImageUI.h"

namespace
{
	//ファイル名
	const char* const kExplanationFileName[4] =
	{
		"data/image/Explanation1.png",
		"data/image/Explanation2.png",
		"data/image/Explanation3.png",
		"data/image/Explanation4.png"
	};

	//ファイル名
	const char* const kUIFileName[2] =
	{
		"data/image/ExplanationNext.png",
		"data/image/ExplanationBack.png"
	};

	//動画ファイル名
	const char* const kMovieFile = "data/movie/movie1.mp4";

	//ページ数最大
	constexpr int kPageMax = 4;
}

SceneExplanation::SceneExplanation(SceneBase* scene) :
	m_pageNum(0),
	m_nextScene(scene)
{
	m_UI[0].pos = { 1300, 850 };
	m_UI[1].pos = { 500, 850 };

	int pageNum = m_pageHandle.size();

	int sizeX, sizeY;

	//m_movieHandle[0] = 

	m_pImageUI = std::make_shared<ImageUI>();

	for (int i = 0; i < static_cast<int>(m_UI.size()); i++)
	{
		m_UI[i].handle = LoadGraph(kUIFileName[i]);
		GetGraphSize(m_UI[i].handle, &sizeX, &sizeY);
		m_UI[i].size = { static_cast<float>(sizeX / 2),static_cast<float>(sizeY / 2) };
		m_pImageUI->AddUI(m_UI[i].pos, m_UI[i].size, m_UI[i].handle);
	}

	for (int i = 0; i < pageNum; i++)
	{
		m_pageHandle[i] = LoadGraph(kExplanationFileName[i]);
	}
}

SceneExplanation::~SceneExplanation()
{
}

void SceneExplanation::init()
{
}

SceneBase* SceneExplanation::update()
{
	SelectAction();

	if (SelectPage())
	{
		return m_nextScene;
	}

	return this;
}

void SceneExplanation::draw()
{
	//PlayMovie(kMovieFile, 1, DX_MOVIEPLAYTYPE_NORMAL);
	m_nextScene->draw();

	int pageNum = m_pageHandle.size();

	for (int i = 0; i < pageNum; i++)
	{
		if (i == m_pageNum)
		{
			DrawGraph(0,0,m_pageHandle[i],true);
		}
	}


	m_pImageUI->Draw(m_actionNum, 0);
}

void SceneExplanation::SelectAction()
{
	if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		if (m_actionNum == Next)
		{
			m_actionNum = Back;
		}

		else if (m_actionNum == Back)
		{
			m_actionNum = Next;
		}
	}
}

bool SceneExplanation::SelectPage()
{
	if (!Pad::isTrigger(PAD_INPUT_1)) return false;

	if (m_actionNum == Next)
	{
		m_pageNum++;
	}
	else
	{
		m_pageNum--;
	}

	if (m_pageNum < 0 || m_pageNum >= kPageMax)
	{
		return true;
	}

	return false;
}

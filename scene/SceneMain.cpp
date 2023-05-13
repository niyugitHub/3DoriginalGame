#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneDebug.h"
#include "Map.h"
#include "Player.h"
#include "SceneGameClear.h"

#include "Pad.h"

#include <cassert>

namespace
{
	
}

SceneMain::SceneMain() : 
	m_GameClear(false)
{
	m_Player = std::make_shared<Player>();
	m_Map = std::make_shared<Map>();
	m_SceneGameClear = std::make_shared<SceneGameClear>();
}

void SceneMain::init()
{
	m_Player->Init();
	m_Map->Init();
}

void SceneMain::end()
{
	
}

SceneBase* SceneMain::update()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
	}

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_GameClear = true;
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
	}

	m_Player->Update();
	
	if (m_GameClear)
	{
		m_SceneGameClear->Update();
	}

	updateFade();

	if (m_SceneGameClear->GetGameClear())
	{
		return new SceneDebug();
	}
	return this;
}

void SceneMain::draw()
{
	DrawString(64, 64,"ã“ü—Í‚ÅƒNƒŠƒA",0xffffff);

	m_Player->Draw();
	m_Map->Draw();

	if (m_GameClear)
	{
		m_SceneGameClear->Draw();
	}

	SceneBase::drawFade();
}


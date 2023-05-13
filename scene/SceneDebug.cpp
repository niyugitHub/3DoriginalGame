#include "DxLib.h"
#include "game.h"
#include "SceneDebug.h"
#include "SceneMain.h"

#include "Pad.h"

#include <cassert>

namespace
{
	
}

SceneDebug::SceneDebug()
{
}

void SceneDebug::init()
{
	
}

void SceneDebug::end()
{
	
}

SceneBase* SceneDebug::update()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return new SceneMain;
	}

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
	}

	updateFade();
	return this;
}

void SceneDebug::draw()
{
	DrawString(64, 64,"デバッグメニュー",0xffffff);
	DrawString(80, 96, "→テストシーン", 0x00ff00);

	SceneBase::drawFade();
}


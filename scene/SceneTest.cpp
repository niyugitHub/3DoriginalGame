#include "DxLib.h"
#include "game.h"
#include "SceneTest.h"

#include "Pad.h"

#include <cassert>

namespace
{
	
}

SceneTest::SceneTest()
{
}

void SceneTest::init()
{
	
}

void SceneTest::end()
{
	
}

SceneBase* SceneTest::update()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
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

void SceneTest::draw()
{
	DrawString(64, 64,"test",0xffffff);

	SceneBase::drawFade();
}


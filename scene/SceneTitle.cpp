#include "SceneTitle.h"
#include "../util/Pad.h"
#include <DxLib.h>
#include"SceneSelectScreen.h"
#include"SceneOption.h"
#include "../util/ImageUI.h"
#include"../SoundManager.h"


SceneTitle::SceneTitle()
{
	SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::init()
{
}

void SceneTitle::end()
{
}

SceneBase* SceneTitle::update()
{
	//SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return new SceneSelectScreen;
	}

	if (Pad::isTrigger(PAD_INPUT_8))
	{
		//自身のポインター、ゲーム中のオプション画面かのフラグを引数に持つ
		return new SceneOption(this,false);
	}

	return this;
}

void SceneTitle::draw()
{
	DrawString(300, 300, "SceneTitle"  , 0xffffff);
}

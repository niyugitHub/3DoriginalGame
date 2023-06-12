#include "SceneOption.h"
#include"SceneBase.h"
#include"SceneTitle.h"
#include<DxLib.h>
#include"Pad.h"


SceneOption::SceneOption(SceneBase* pScene)
{
	m_pScene = pScene;
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

	return this;
}

void SceneOption::draw()
{
	m_pScene->draw();

	DrawBox(0, 0, 100, 100, 0xffffff, true);

	DrawString(0, 400, "ƒIƒvƒVƒ‡ƒ“‰æ–Ê", 0xffffff);
}

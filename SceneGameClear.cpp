#include "SceneGameClear.h"
#include"DxLib.h"
#include "Pad.h"

SceneGameClear::SceneGameClear() : 
	m_GameClear(false)
{
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::Init()
{
}

void SceneGameClear::Update()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_GameClear = true;
	}
}

void SceneGameClear::Draw()
{
	DrawString(0, 0,
		"�Q�[���N���A�I", 0xffffff);
	DrawString(0, 100,
		"Z�{�^���Ŗ߂�", 0xffffff);
}

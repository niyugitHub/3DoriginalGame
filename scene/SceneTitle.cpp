#include "SceneTitle.h"
#include "Pad.h"
#include <DxLib.h>
#include"SceneSelectScreen.h"
#include"SceneOption.h"

SceneTitle::SceneTitle()
{
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
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return new SceneSelectScreen;
	}

	if (Pad::isTrigger(PAD_INPUT_8))
	{
		//���g�̃|�C���^�[�A�Q�[�����̃I�v�V������ʂ��̃t���O�������Ɏ���
		return new SceneOption(this,false);
	}

	return this;
}

void SceneTitle::draw()
{
	DrawString(300, 300, "SceneTitle"  , 0xffffff);
}

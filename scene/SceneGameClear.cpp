#include "SceneGameClear.h"
#include "SceneMain.h"
#include "SceneStageSelect.h"
#include "SceneTitle.h"
#include"DxLib.h"
#include "../util/Pad.h"
#include"../object/Player.h"
#include"../object/Camera.h"
#include"../object/field/FieldBase.h"
#include"../SoundManager.h"

SceneGameClear::SceneGameClear(std::shared_ptr<Player> pPlayer, std::shared_ptr<FieldBase> pField,
	std::shared_ptr<Camera>pCamera) :
	m_selectNum(kStageSelect)
{
	m_pPlayer = pPlayer;
	m_pField = pField;
	m_pCamera = pCamera;
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::init()
{
}

SceneBase* SceneGameClear::update()
{
	//�V�[���ɓ����Ă���̃t���[�����𐔂���
	static int frameCount = 0;
	frameCount++;
	//�N���A�����ۂ̃v���C���[�A�J�����̃A�b�v�f�[�g
	m_pPlayer->ClearUpdate();
	m_pCamera->ClearUpdate(m_pPlayer, frameCount > 150);

	// m_selectNum�̐��l��ω������邽�߂̊֐�
	DecisionNum(m_selectNum);

	//PAD1���������Am_selectNum���e�l�̂Ƃ�(������Ă�BGM���~�߂āA�V����BGM���Đ�)
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kStageSelect)
	{
		SoundManager::GetInstance().StopBGMAndSE();
		SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
		return new SceneStageSelect;
	}
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kRestart)
	{
		SoundManager::GetInstance().StopBGMAndSE();
		SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
	}
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kTitle)
	{
		SoundManager::GetInstance().StopBGMAndSE();
		SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
	}

	return this;
}

void SceneGameClear::draw()
{
	m_pField->Draw();
	m_pPlayer->Draw();
	/*DrawString(0, 0,
		"�Q�[���N���A�I", 0xffffff);
	DrawString(0, 100,
		"Z�{�^���Ŗ߂�", 0xffffff);*/
	DrawFormatString(300, 0, 0xffffff, "%d", m_selectNum);
}

void SceneGameClear::DecisionNum(int& selectNum)
{
	switch (selectNum)
	{
	case kStageSelect:
		if (Pad::isTrigger(PAD_INPUT_DOWN))
		{
			selectNum = kRestart;
		}
		if (Pad::isTrigger(PAD_INPUT_UP))
		{
			selectNum = kTitle;
		}
		break;

	case kRestart:
		if (Pad::isTrigger(PAD_INPUT_DOWN))
		{
			selectNum = kTitle;
		}
		if (Pad::isTrigger(PAD_INPUT_UP))
		{
			selectNum = kStageSelect;
		}
		break;

	case kTitle:
		if (Pad::isTrigger(PAD_INPUT_DOWN))
		{
			selectNum = kStageSelect;
		}
		if (Pad::isTrigger(PAD_INPUT_UP))
		{
			selectNum = kRestart;
		}
		break;
	default:
		break;
	}
}

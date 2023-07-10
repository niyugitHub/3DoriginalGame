#include "SceneTitle.h"
#include "../util/Pad.h"
#include"SceneSelectScreen.h"
#include"SceneOption.h"
#include "../util/ImageUI.h"
#include"../SoundManager.h"

namespace
{
	//�t�@�C����
	const char* const kFileName[4] =
	{
		"data/field.mv1",
		"data/fieldRed.mv1",
		"data/fieldBlue.mv1",
		"data/fieldGreen.mv1"
	};

	//���f���̈ړ�
	constexpr float kModelMaxPosY = 150.0f;
	constexpr float kModelMinPosY = -450.0f;
	constexpr float kModelMaxSpeed = 6.0f;
	constexpr float kModelAcc = 0.3f;
}


SceneTitle::SceneTitle()
{
	// �J�����̐ݒ�
	// �ǂ��܂ŕ\�����邩
	SetCameraNearFar(5.0f, 2800.0f);
	// �J�����̎���p(���W�A��)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// �J�����̈ʒu�A�ǂ�����ǂ������Ă��邩��ݒ�
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -800), VGet(0.0f, 0.0f, 0.0f));

	//�T�E���h�𗬂�
	SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");

	//���f�����[�h
	for (int i = 0; i < static_cast<int>(m_data.size()); i++)
	{
		m_data[i].handle = MV1LoadModel(kFileName[i]);
		m_data[i].pos = VGet(static_cast<float>( - 750 + (500 * i)), static_cast<float>(- 150 + (50 * i)), 1000.0f);
		m_data[i].speed = kModelMaxSpeed;
		m_data[i].isModelUp = false;
	}
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
		//���g�̃|�C���^�[�A�Q�[�����̃I�v�V������ʂ��̃t���O�������Ɏ���
		return new SceneOption(this,false);
	}

	//UI�̃A�b�v�f�[�g
	UiUpdate();

	return this;
}

void SceneTitle::draw()
{
	DrawString(300, 300, "SceneTitle"  , 0xffffff);

	//���f���`��
	for (int i = 0; i < static_cast<int>(m_data.size()); i++)
	{
		MV1DrawModel(m_data[i].handle);
	}
}

void SceneTitle::UiUpdate()
{
	//���f���̈ʒu�Z�b�g
	for (int i = 0; i < static_cast<int>(m_data.size()); i++)
	{
		if (m_data[i].pos.y > kModelMaxPosY)
		{
			m_data[i].isModelUp = false;
		}
		if (m_data[i].pos.y < kModelMinPosY)
		{
			m_data[i].isModelUp = true;
		}

		if (m_data[i].isModelUp)
		{
			m_data[i].speed += kModelAcc;
		}
		else
		{
			m_data[i].speed -= kModelAcc;
		}

		m_data[i].speed = min(max(m_data[i].speed, -kModelMaxSpeed), kModelMaxSpeed);

		m_data[i].pos.y += m_data[i].speed;

		MV1SetPosition(m_data[i].handle, m_data[i].pos);
	}
}

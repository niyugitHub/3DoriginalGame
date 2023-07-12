#include "SceneTitle.h"
#include "../util/Pad.h"
#include"SceneSelectScreen.h"
#include"SceneOption.h"
#include "../util/ImageUI.h"
#include"../SoundManager.h"

namespace
{
	//ファイル名
	const char* const kFileName[4] =
	{
		"data/field.mv1",
		"data/fieldRed.mv1",
		"data/fieldBlue.mv1",
		"data/fieldGreen.mv1"
	};

	const char* const kImageName[2] =
	{
		"data/image/Title_GameStart.png",
		"data/image/Title_Exit.png"
	};

	//モデルの移動
	constexpr float kModelMaxPosY = 150.0f;
	constexpr float kModelMinPosY = -450.0f;
	constexpr float kModelMaxSpeed = 6.0f;
	constexpr float kModelAcc = 0.3f;
}


SceneTitle::SceneTitle() : 
	m_selectNum(kStart)
{
	// カメラの設定
	// どこまで表示するか
	SetCameraNearFar(5.0f, 2800.0f);
	// カメラの視野角(ラジアン)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// カメラの位置、どこからどこを見ているかを設定
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -800), VGet(0.0f, 0.0f, 0.0f));

	//サウンドを流す
	SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");

	m_pImageUI = std::make_shared<ImageUI>();
	int sizeX, sizeY;

	m_UI[0].pos = { 550,850 };
	m_UI[1].pos = { 1370,850 };

	for (int i = 0; i < static_cast<int>(m_UI.size()); i++)
	{
		m_UI[i].handle = LoadGraph(kImageName[i]);
		GetGraphSize(m_UI[i].handle, &sizeX, &sizeY);
		m_UI[i].size = { static_cast<float>(sizeX / 2),static_cast<float>(sizeY / 2) };
		m_pImageUI->AddUI(m_UI[i].pos, m_UI[i].size, m_UI[i].handle);
	}

	//モデルロード
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
	// m_selectNumの数値を変化させるための関数
	DecisionNum(m_selectNum);

	//SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kStart)
	{
		return new SceneSelectScreen;
	}

	if (Pad::isTrigger(PAD_INPUT_1) && m_selectNum == kExit)
	{
		DxLib_End();
	}

	//UIのアップデート
	UiUpdate();

	return this;
}

void SceneTitle::draw()
{
	DrawString(300, 300, "SceneTitle"  , 0xffffff);

	//モデル描画
	for (int i = 0; i < static_cast<int>(m_data.size()); i++)
	{
		MV1DrawModel(m_data[i].handle);
	}

	m_pImageUI->Draw(m_selectNum, 0);
}

void SceneTitle::UiUpdate()
{
	//モデルの位置セット
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

void SceneTitle::DecisionNum(int& selectNum)
{
	if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		if (selectNum == kStart)
		{
			selectNum = kExit;
		}

		else if (selectNum == kExit)
		{
			selectNum = kStart;
		}
	}
}

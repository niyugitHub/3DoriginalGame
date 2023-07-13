#include "SceneTitle.h"
#include "../util/Pad.h"
#include"SceneSelectScreen.h"
#include"SceneOption.h"
#include "../util/ImageUI.h"
#include"../SoundManager.h"
#include"../game.h"

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

	const char* const kStringName = "data/image/Title_String.png";

	const char* const kUnderbarName = "data/image/Title_Underbar.png";

	//モデルの移動
	constexpr float kModelMaxPosY = 150.0f;
	constexpr float kModelMinPosY = -450.0f;
	constexpr float kModelMaxSpeed = 6.0f;
	constexpr float kModelAcc = 0.3f;

	//文字の動き
	constexpr float kJumpPower = -18.0f;
	constexpr float kGravity = 0.6f;

	//アンダーバーの座標
	constexpr int kPosX = 0;
	constexpr int kPosY = 300;
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

	//UI座標設定
	m_UI[0].pos = { 550,850 };
	m_UI[1].pos = { 1370,850 };

	//UIの画像ロード、サイズ取得
	for (int i = 0; i < static_cast<int>(m_UI.size()); i++)
	{
		m_UI[i].handle = LoadGraph(kImageName[i]);
		GetGraphSize(m_UI[i].handle, &sizeX, &sizeY);
		m_UI[i].size = { static_cast<float>(sizeX / 2),static_cast<float>(sizeY / 2) };
		m_pImageUI->AddUI(m_UI[i].pos, m_UI[i].size, m_UI[i].handle);
	}

	//文字画像UIの座標設定、画像ロード、サイズ取得
	int divHandle[12] = {};
	LoadDivGraph(kStringName, 12,
		12, 1,
		160, 220, divHandle);

	m_underbar.handle = LoadGraph(kUnderbarName);
	m_underbar.pos = { kPosX, kPosY };

	//文字のスペース
	int spaceNum = 0;

	for (int i = 0; i < static_cast<int>(m_stringUI.size()); i++)
	{
		if (i >= 5)
		{
			spaceNum = 120;
		}
		m_stringUI[i].pos.y = static_cast<float>(300 - (i * 15));
		m_stringUI[i].pos.x = static_cast<float>(150 + (i * 120)) + spaceNum;
		m_stringUI[i].handle = divHandle[i];
		m_stringUI[i].jumpPower = 0.0f;
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
	//フェードアップデート
	updateFade();

	//UIのアップデート
	UiUpdate();
	//SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		startFadeOut();
	}

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		startFadeOut();
	}

	if (isFading())
	{
		return this;
	}

	// m_selectNumの数値を変化させるための関数
	DecisionNum(m_selectNum);

	if (getFadeBright() == 255 && m_selectNum == kStart)
	{
		return new SceneSelectScreen;
	}

	else if (getFadeBright() == 255 && m_selectNum == kExit)
	{
		DxLib_End();
	}


	return this;
}

void SceneTitle::draw()
{
	DrawString(300, 300, "SceneTitle", 0xffffff);

	//モデル描画
	for (int i = 0; i < static_cast<int>(m_data.size()); i++)
	{
		MV1DrawModel(m_data[i].handle);
	}

	//アンダーバーの描画
	DrawGraph(static_cast<int>(m_underbar.pos.x) + 50, static_cast<int>(m_underbar.pos.y) + 100,
		m_underbar.handle, true);

	//文字の描画
	for (auto& stringUI : m_stringUI)
	{
		DrawGraph(static_cast<int>(stringUI.pos.x), static_cast<int>(stringUI.pos.y),
			stringUI.handle, true);
	}

	m_pImageUI->Draw(m_selectNum, 0);
	//フェード状態で画面を映す
	drawFade();
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

	//文字の位置アップデート
	for (int i = 0; i < static_cast<int>(m_stringUI.size()); i++)
	{
		m_stringUI[i].pos.y += m_stringUI[i].jumpPower;
		m_stringUI[i].jumpPower += kGravity;
		
		if (m_stringUI[i].pos.y > m_underbar.pos.y)
		{
			m_stringUI[i].jumpPower = kJumpPower;
		}
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

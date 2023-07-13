#include "SceneGameClear.h"
#include "SceneMain.h"
#include "SceneStageSelect.h"
#include "SceneTitle.h"
#include "../util/Pad.h"
#include"../object/Player.h"
#include"../object/Camera.h"
#include"../object/field/FieldBase.h"
#include"../SoundManager.h"
#include "../util/ImageUI.h"
#include"../object/Item.h"
#include"../game.h"

namespace
{
	//ファイル名
	const char* const kGameClearFileName[3] =
	{
		"data/image/GameClear.png",
		"data/image/GameClearRetry.png",
		"data/image/GameClearStageSelect.png"
	};

	// エフェクト名
	const char* const kEffectFileName = "data/effect/laser.efk";

	const char* const kCoinFileName = "data/image/co.png";

	//スクロール終了時の値
	constexpr int kStopScroll = 10;
}

//シーンに入ってからのフレーム数を数える
static int frameCount = 0;
static int scroll = 1100;

SceneGameClear::SceneGameClear(std::shared_ptr<Player> pPlayer, std::shared_ptr<FieldBase> pField,
	std::shared_ptr<Camera>pCamera) :
	m_selectNum(kStageSelect)
{
	m_coinHandle = LoadGraph(kCoinFileName);
	int sizeX, sizeY;

	m_pPlayer = pPlayer;
	m_pField = pField;
	m_pCamera = pCamera;
	frameCount = 0;
	scroll = 1100;

	m_UI[0].pos = { 1300,500 };
	m_UI[1].pos = { 1100,800 };
	m_UI[2].pos = { 1500,800 };
	m_coinPos[0] = { 1055,510 };
	m_coinPos[1] = { 1290,510 };
	m_coinPos[2] = { 1528,510 };

	m_pImageUI = std::make_shared<ImageUI>();
	for (int i = 0; i < static_cast<int>(m_UI.size()); i++)
	{
		m_UI[i].handle = LoadGraph(kGameClearFileName[i]);
		GetGraphSize(m_UI[i].handle, &sizeX, &sizeY);
		m_UI[i].size = { static_cast<float>(sizeX / 2),static_cast<float>(sizeY / 2) };
		m_pImageUI->AddUI(m_UI[i].pos, m_UI[i].size, m_UI[i].handle);
	}

	for (auto & effect : m_data)
	{
		effect.resourceHandle = LoadEffekseerEffect(kEffectFileName);
		effect.pos.x = static_cast<float>(GetRand(Game::kScreenWidth - 200) + 100);
		effect.pos.y = static_cast<float>(GetRand(Game::kScreenHeight));

		effect.playingEffectHandle = PlayEffekseer2DEffect(effect.resourceHandle);
		// エフェクトの拡大率を設定する。
		// Effekseerで作成したエフェクトは2D表示の場合、小さすぎることが殆どなので必ず拡大する。
		SetScalePlayingEffekseer2DEffect(effect.playingEffectHandle, 25.0f, 25.0f, 25.0f);
		SetSpeedPlayingEffekseer2DEffect(effect.resourceHandle, 0.2f);

		int ColorNum = GetRand(2);
		EffectColor(effect.color, ColorNum);

		SetColorPlayingEffekseer2DEffect(effect.playingEffectHandle,
			static_cast<int>(effect.color.x),
			static_cast<int>(effect.color.y),
			static_cast<int>(effect.color.z), 1000);
	}

	//フェードインはしないからシーンの始まりに0を代入
	setFadeBright(0);
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::init()
{
}

SceneBase* SceneGameClear::update()
{
	frameCount++;
	//クリアした際のプレイヤー、カメラのアップデート
	m_pPlayer->ClearUpdate();
	m_pCamera->ClearUpdate(m_pPlayer, frameCount > 150);

	updateFade();

	if (frameCount > 150)
	{
		scroll = max(static_cast<int>(scroll - (scroll * 0.05f)), 0);
	}

	for (auto& effect : m_data)
	{
		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer2DEffect(effect.playingEffectHandle, effect.pos.x, effect.pos.y, 0);
		effect.pos.y -= 15;

		if (effect.pos.y < 0)
		{
			effect.pos.y = Game::kScreenHeight;
			effect.pos.x = static_cast<float>(GetRand(Game::kScreenWidth - 200) + 100);

			effect.playingEffectHandle = PlayEffekseer2DEffect(effect.resourceHandle);
			// エフェクトの拡大率を設定する。
			// Effekseerで作成したエフェクトは2D表示の場合、小さすぎることが殆どなので必ず拡大する。
			SetScalePlayingEffekseer2DEffect(effect.playingEffectHandle, 25.0f, 25.0f, 25.0f);
			SetSpeedPlayingEffekseer2DEffect(effect.resourceHandle, 0.2f);

			int ColorNum = GetRand(2);
			EffectColor(effect.color, ColorNum);

			SetColorPlayingEffekseer2DEffect(effect.playingEffectHandle,
				static_cast<int>(effect.color.x),
				static_cast<int>(effect.color.y),
				static_cast<int>(effect.color.z), 1000);
		}
	}

	if (getFadeBright() >= 255)
	{
		if (m_selectNum == kStageSelect && getFadeBright() == 255)
		{
			SoundManager::GetInstance().StopBGMAndSE();
			SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
			return new SceneStageSelect;
		}
		if (m_selectNum == kRestart && getFadeBright() == 255)
		{
			m_pField->GetItem()->Spawn();
			m_pField->ResetTime();
			SoundManager::GetInstance().StopBGMAndSE();
			//SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
			return new SceneMain(m_pField);
		}
	}

	if (isFading()) return this;

	// m_selectNumの数値を変化させるための関数
	DecisionNum(m_selectNum);

	//PAD1を押した、m_selectNumが各値のとき(今流れてるBGMを止めて、新しいBGMを再生)
	if (Pad::isTrigger(PAD_INPUT_1) && scroll < kStopScroll)
	{
		startFadeOut();
		/*SoundManager::GetInstance().StopBGMAndSE();
		SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
		return new SceneStageSelect;*/
	}
	//if (Pad::isTrigger(PAD_INPUT_1) && scroll < kStopScroll)
	//{
	//	m_pField->ResetTime();
	//	m_pField->GetItem()->SetExist(true);
	//	SoundManager::GetInstance().StopBGMAndSE();
	//	//SoundManager::GetInstance().PlayMusic("sound/titleScene.mp3");
	//	return new SceneMain(m_pField);
	//}

	return this;
}

void SceneGameClear::draw()
{
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer2D();

	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer2D();

	m_pField->Draw();

	m_pPlayer->Draw();

	m_pImageUI->Draw(m_selectNum, scroll);

	for (int i = 0; i < static_cast<int>(m_coinPos.size()); i++)
	{
		if (m_pField->GetStar(i))
		{
			DrawExtendGraph(static_cast<int>(m_coinPos[i].x) + scroll - 125, static_cast<int>(m_coinPos[i].y) - 125,
				static_cast<int>(m_coinPos[i].x) + scroll + 125, static_cast<int>(m_coinPos[i].y) + 125,
				m_coinHandle, true);
		}
	}


	/*DrawString(0, 0,
		"ゲームクリア！", 0xffffff);
	DrawString(0, 100,
		"Zボタンで戻る", 0xffffff);*/
	DrawFormatString(300, 0, 0xffffff, "%d", m_selectNum,0);
	//フェード状態で画面を映す
	drawFade();
}

void SceneGameClear::DecisionNum(int& selectNum)
{
	if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		if (selectNum == kStageSelect)
		{
			selectNum = kRestart;
		}

		else if (selectNum == kRestart)
		{
			selectNum = kStageSelect;
		}
	}
}

void SceneGameClear::EffectColor(VECTOR& color, int colorNum)
{
	color.x = (colorNum == 0) ? 255.0f : 50.0f;
	color.y = (colorNum == 1) ? 255.0f : 50.0f;
	color.z = (colorNum == 2) ? 255.0f : 50.0f;
}

#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneDebug.h"
#include "Map.h"
#include "Player.h"
#include "SceneGameClear.h"

#include "Pad.h"

#include <cassert>

namespace
{
	
}

SceneMain::SceneMain() : 
	m_GameClear(false)
{
	m_Player = std::make_shared<Player>();
	m_Map = std::make_shared<Map>();
	m_SceneGameClear = std::make_shared<SceneGameClear>();
}

void SceneMain::init()
{
	//3D関連の設定

	//Zバッファを使用する
	SetUseZBuffer3D(true);
	//Zバッファへの書き込みを行う
	SetWriteZBuffer3D(true);

	//ポリゴンの裏面を描画しない
	SetUseBackCulling(true);


	// カメラの設定
	// どこまで表示するか
	SetCameraNearFar(5.0f, 2800.0f);
	// カメラの視野角(ラジアン)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// カメラの位置、どこからどこを見ているかを設定
	SetCameraPositionAndTarget_UpVecY(VGet(0, 300, -800), VGet(0.0f, 0.0f, 0.0f));

	m_Player->Init();
	m_Map->Init();
}

void SceneMain::end()
{
	
}

SceneBase* SceneMain::update()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
	}

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_GameClear = true;
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
	}

	m_Player->Update();
	
	if (m_GameClear)
	{
		m_SceneGameClear->Update();
	}

	updateFade();

	if (m_SceneGameClear->GetGameClear())
	{
		return new SceneDebug();
	}
	return this;
}

void SceneMain::draw()
{
	DrawString(64, 64,"上入力でクリア",0xffffff);

	m_Player->Draw();
	m_Map->Draw();

	if (m_GameClear)
	{
		m_SceneGameClear->Draw();
	}

	//-500~500の範囲にグリッドを表示
	for (float x = -500.0f; x <= 500.0f; x += 100)
	{
		VECTOR start = VGet(x, 0.0f, -500.0f);
		VECTOR end = VGet(x, 0.0f, 500.0f);
		DrawLine3D(start, end, 0xff00ff);
	}
	for (float z = -500.0f; z <= 500.0f; z += 100)
	{
		VECTOR start = VGet(-500.0f, 0.0f, z);
		VECTOR end = VGet(500.0f, 0.0f, z);
		DrawLine3D(start, end, 0xffff00);
	}

	SceneBase::drawFade();
}


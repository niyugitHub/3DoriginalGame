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
	//3D�֘A�̐ݒ�

	//Z�o�b�t�@���g�p����
	SetUseZBuffer3D(true);
	//Z�o�b�t�@�ւ̏������݂��s��
	SetWriteZBuffer3D(true);

	//�|���S���̗��ʂ�`�悵�Ȃ�
	SetUseBackCulling(true);


	// �J�����̐ݒ�
	// �ǂ��܂ŕ\�����邩
	SetCameraNearFar(5.0f, 2800.0f);
	// �J�����̎���p(���W�A��)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// �J�����̈ʒu�A�ǂ�����ǂ������Ă��邩��ݒ�
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
	DrawString(64, 64,"����͂ŃN���A",0xffffff);

	m_Player->Draw();
	m_Map->Draw();

	if (m_GameClear)
	{
		m_SceneGameClear->Draw();
	}

	//-500~500�͈̔͂ɃO���b�h��\��
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


#include "Player.h"
#include"Pad.h"
#include"Model.h"

namespace
{
	//ファイル名
	const char* const kEnemyModelFileName = "data/Character.mv1";

	// 旋回速度
	constexpr float kRotSpeed = 0.15f;
}

Player::Player() :
	m_modelHandle(-1),
	m_cameraPos(0.0f),
	m_animNo(3)
{
	m_Pos = VGet(0, 0, 0);
	//3Dモデルの生成
	m_pModel = std::make_shared<Model>(kEnemyModelFileName);
	m_pModel->setAnimation(m_animNo, true, true);
}

Player::~Player()
{
}

void Player::Init()
{
	m_modelHandle = MV1LoadModel(kEnemyModelFileName);
}

void Player::Update()
{
	//アニメーションを進める
	m_pModel->update();

	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_Pos.z += 5;
		if (m_angle <= DX_PI_F)
		{
			m_angle = m_angle + kRotSpeed;
		}
		if (m_angle > DX_PI_F)
		{
			m_angle = m_angle - kRotSpeed;
		}
	}

	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_Pos.z -= 5;
		if (m_angle <= DX_PI_F)
		{
			m_angle = m_angle - kRotSpeed;
		}
		if (m_angle > DX_PI_F)
		{
			m_angle = m_angle + kRotSpeed;
		}

		if (m_angle < 0)
		{
			m_angle = 0;
		}
	}

	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_Pos.x += 5;

		if (m_angle >= DX_PI_F / 2 && m_angle < (DX_PI_F / 2 * 3))
		{
			m_angle = m_angle + kRotSpeed;
		}
		if (m_angle >= (DX_PI_F / 2 * 3) || m_angle < DX_PI_F / 2)
		{
			m_angle = m_angle - kRotSpeed;
		}
		
	}

	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_Pos.x -= 5;

		if (m_angle >= DX_PI_F / 2 && m_angle < (DX_PI_F / 2 * 3))
		{
			m_angle = m_angle - kRotSpeed;
		}
		if (m_angle >= (DX_PI_F / 2 * 3)|| m_angle <= DX_PI_F / 2)
		{
			m_angle = m_angle + kRotSpeed;
		}
	}

	if (m_angle > DX_PI_F * 2)
	{
		m_angle = 0;
	}

	if (m_angle < 0)
	{
		m_angle = DX_PI_F * 2;
	}

	m_pModel->setPos(m_Pos);
	m_pModel->setRot(VGet(0.0f, m_angle, 0.0f));

	//カメラの位置、どこからどこを見ているかを設定
	m_cameraPos = (m_cameraPos * 0.8f) + (m_Pos.x * 0.2f);
	SetCameraPositionAndTarget_UpVecY(VGet(m_cameraPos, 300, -800 + m_Pos.z), VGet(m_cameraPos, 0, m_Pos.z));
}

void Player::Draw()
{
	m_pModel->draw();
}

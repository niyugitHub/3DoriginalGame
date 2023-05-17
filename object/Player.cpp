#include "Player.h"
#include"Pad.h"
#include"Model.h"
#include"Vec2.h"

namespace
{
	//ファイル名
	const char* const kEnemyModelFileName = "data/Character.mv1";

	// 旋回速度
	constexpr float kRotSpeed = 0.15f;

	// 最大移動速度
	constexpr float kMaxMoveSpeed = 5.0f;

	// 一フレームごとの移動速度上昇
	constexpr float kMoveSpeedUp = 0.5f;
}

Player::Player() :
	m_updateFunc(&Player::updateIdle),
	m_modelHandle(-1),
	m_cameraPos(0.0f),
	m_animNo(3),
	m_angle(0)
{
	m_Pos = VGet(0, 0, 0);
	m_Vec = VGet(0, 0, 0);
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
	(this->*m_updateFunc)();

	//現在の座標に移動ベクトルを足す
	m_Pos.x += m_Vec.x;
	m_Pos.y += m_Vec.y;
	m_Pos.z += m_Vec.z;
	//アニメーションを進める
	m_pModel->update();

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

void Player::updateIdle()
{
	if (Pad::isPress(PAD_INPUT_UP) || Pad::isPress(PAD_INPUT_DOWN) ||
		Pad::isPress(PAD_INPUT_LEFT) || Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_updateFunc = &Player::updateMove;
	}

	m_Vec.x = min(max(m_Vec.x - kMoveSpeedUp, 0), m_Vec.x + kMoveSpeedUp);
	m_Vec.z = min(max(m_Vec.z - kMoveSpeedUp, 0), m_Vec.z + kMoveSpeedUp);
}

void Player::updateMove()
{
	bool PressLeft = Pad::isPress(PAD_INPUT_LEFT);
	bool PressUp = Pad::isPress(PAD_INPUT_UP);
	bool PressRight = Pad::isPress(PAD_INPUT_RIGHT);
	bool PressBottom = Pad::isPress(PAD_INPUT_DOWN);

	if (PressUp)
	{
		m_Vec.z = min(m_Vec.z + kMoveSpeedUp,kMaxMoveSpeed);
		if (m_angle <= DX_PI_F)
		{
			m_angle = m_angle + kRotSpeed;
		}
		if (m_angle > DX_PI_F)
		{
			m_angle = m_angle - kRotSpeed;
		}
	}

	if (PressBottom)
	{
		m_Vec.z = max(m_Vec.z - kMoveSpeedUp, -kMaxMoveSpeed);
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

	if (PressRight)
	{
		m_Vec.x = min(m_Vec.x + kMoveSpeedUp, kMaxMoveSpeed);

		if (m_angle >= DX_PI_F / 2 && m_angle < (DX_PI_F / 2 * 3))
		{
			m_angle = m_angle + kRotSpeed;
		}
		if (m_angle >= (DX_PI_F / 2 * 3) || m_angle < DX_PI_F / 2)
		{
			m_angle = m_angle - kRotSpeed;
		}

	}

	if (PressLeft)
	{
		m_Vec.x = max(m_Vec.x - kMoveSpeedUp, -kMaxMoveSpeed);

		if (m_angle >= DX_PI_F / 2 && m_angle < (DX_PI_F / 2 * 3))
		{
			m_angle = m_angle - kRotSpeed;
		}
		if (m_angle >= (DX_PI_F / 2 * 3) || m_angle <= DX_PI_F / 2)
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

	if (!PressLeft && !PressRight)
	{
		m_Vec.x = min(max(m_Vec.x - kMoveSpeedUp, 0), m_Vec.x + kMoveSpeedUp);
	}

	if (!PressUp && !PressBottom)
	{
		m_Vec.z = min(max(m_Vec.z - kMoveSpeedUp, 0), m_Vec.z + kMoveSpeedUp);
	}

	Vec2 vec = { m_Vec.x,m_Vec.z };

	vec = vec.normalize() * kMaxMoveSpeed;

	m_Vec.x = vec.x;
	m_Vec.z = vec.y;

	if (!PressLeft && !PressRight &&
		!PressUp && !PressBottom)
	{
		m_updateFunc = &Player::updateIdle;
	}
}

void Player::updateJump()
{
}

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

	// アニメーション番号
	constexpr int kIdleAnimNo = 3;	// 待機モーション
	constexpr int kModeAnimNo = 11;// 移動モーション
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
	m_pModel->setAnimation(kIdleAnimNo, true, true);
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

//	printfDx("%f\n", static_cast<float>(m_Vec.z));
	printfDx("%f\n", static_cast<float>(m_Vec.x));
}

void Player::updateIdle()
{
	if (Pad::isPress(PAD_INPUT_UP) || Pad::isPress(PAD_INPUT_DOWN) ||
		Pad::isPress(PAD_INPUT_LEFT) || Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_updateFunc = &Player::updateMove;
		m_pModel->changeAnimation(kModeAnimNo, true, true, 2);
		return;
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

	IsMove(PressLeft, PressUp, PressRight, PressBottom);
	IsAngle(PressLeft, PressUp, PressRight, PressBottom);

	/*if (PressUp)
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
	}*/

	if (fabs(m_Vec.x) >= 5.0f && fabs(m_Vec.z) >= 5.0f)
	{
		Vec2 vec = { m_Vec.x,m_Vec.z };

		vec = vec.normalize() * kMaxMoveSpeed;

		m_Vec.x = vec.x;
		m_Vec.z = vec.y;
	}

	if (!PressLeft && !PressRight &&
		!PressUp && !PressBottom)
	{
		m_updateFunc = &Player::updateIdle;
		m_pModel->changeAnimation(kIdleAnimNo, true, true,1);
	}
}

void Player::updateJump()
{
}

void Player::IsMove(bool Left, bool Up, bool Right, bool Bottom)
{
	if (Up)
	{
		m_Vec.z = min(m_Vec.z + kMoveSpeedUp, kMaxMoveSpeed);
	}

	if (Bottom)
	{
		m_Vec.z = max(m_Vec.z - kMoveSpeedUp, -kMaxMoveSpeed);
	}

	if (Right)
	{
		m_Vec.x = min(m_Vec.x + kMoveSpeedUp, kMaxMoveSpeed);
	}

	if (Left)
	{
		m_Vec.x = max(m_Vec.x - kMoveSpeedUp, -kMaxMoveSpeed);
	}

	Vec2 vec = { m_Vec.x,m_Vec.z };
	vec = vec.normalize() * kMaxMoveSpeed;

	if (Up && Right)
	{
		if (m_Vec.x > 0 && m_Vec.z > 0)
		{
			m_Vec.x = vec.x;
			m_Vec.z = vec.y;
		}
	}

	if (Right && Bottom)
	{
		if (m_Vec.x > 0 && m_Vec.z < 0)
		{
			m_Vec.x = vec.x;
			m_Vec.z = vec.y;
		}
	}

	if (Bottom && Left)
	{
		if (m_Vec.x < 0 && m_Vec.z < 0)
		{
			m_Vec.x = vec.x;
			m_Vec.z = vec.y;
		}
	}

	if (Left && Up)
	{
		if (m_Vec.x < 0 && m_Vec.z > 0)
		{
			m_Vec.x = vec.x;
			m_Vec.z = vec.y;
		}
	}

	if (!Left && !Right)
	{
		m_Vec.x = min(max(m_Vec.x - kMoveSpeedUp, 0), m_Vec.x + kMoveSpeedUp);
	}

	if (!Up && !Bottom)
	{
		m_Vec.z = min(max(m_Vec.z - kMoveSpeedUp, 0), m_Vec.z + kMoveSpeedUp);
	}

}

void Player::IsAngle(bool Left, bool Up, bool Right, bool Bottom)
{
	if (m_angle > DX_PI_F * 2)
	{
		m_angle = 0;
	}

	if (m_angle < 0)
	{
		m_angle = DX_PI_F * 2;
	}

	if (Right && Bottom)
	{
		if (m_angle <= (DX_PI_F / 4) * 7 && m_angle >= (DX_PI_F / 4) * 3)
		{
			m_angle = m_angle + kRotSpeed;
		}
		if (m_angle >= (DX_PI_F / 4 * 7) || m_angle <= (DX_PI_F / 4) * 3)
		{
			m_angle = m_angle - kRotSpeed;
		}
		return;
	}

	if (Bottom && Left)
	{
		if (m_angle <= (DX_PI_F / 4) || m_angle >= (DX_PI_F / 4) * 5)
		{
			m_angle = m_angle + kRotSpeed;
		}
		if (m_angle >= (DX_PI_F / 4) && m_angle <= (DX_PI_F / 4) * 5)
		{
			m_angle = m_angle - kRotSpeed;
		}
		return;
	}

	if (Left && Up)
	{
		if (m_angle <= (DX_PI_F / 4) * 3 || m_angle >= (DX_PI_F / 4) * 7)
		{
			m_angle = m_angle + kRotSpeed;
		}
		if (m_angle >= (DX_PI_F / 4) * 3 && m_angle <= (DX_PI_F / 4) * 7)
		{
			m_angle = m_angle - kRotSpeed;
		}
		return;
	}

	if (Up && Right)
	{
		if (m_angle <= (DX_PI_F / 4) * 5 && m_angle >= (DX_PI_F / 4))
		{
			m_angle = m_angle + kRotSpeed;
		}
		if (m_angle >= (DX_PI_F / 4 * 5) || m_angle <= (DX_PI_F / 4))
		{
			m_angle = m_angle - kRotSpeed;
		}
		return;
	}

	if (Up)
	{
		if (m_angle <= DX_PI_F)
		{
			m_angle = m_angle + kRotSpeed;
		}
		if (m_angle > DX_PI_F)
		{
			m_angle = m_angle - kRotSpeed;
		}
		return;
	}

	if (Bottom)
	{
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
		return;
	}

	if (Right)
	{
		if (m_angle >= DX_PI_F / 2 && m_angle < (DX_PI_F / 2 * 3))
		{
			m_angle = m_angle + kRotSpeed;
		}
		if (m_angle >= (DX_PI_F / 2 * 3) || m_angle < DX_PI_F / 2)
		{
			m_angle = m_angle - kRotSpeed;
		}
		return;
	}

	if (Left)
	{
		if (m_angle >= DX_PI_F / 2 && m_angle < (DX_PI_F / 2 * 3))
		{
			m_angle = m_angle - kRotSpeed;
		}
		if (m_angle >= (DX_PI_F / 2 * 3) || m_angle <= DX_PI_F / 2)
		{
			m_angle = m_angle + kRotSpeed;
		}
		return;
	}
}

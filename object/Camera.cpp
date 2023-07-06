#include "Camera.h"
#include"Player.h"

namespace
{
	// カメラの位置
	constexpr float kCameraPosY = 1500.0f;
	constexpr float kCameraPosZ = -800.0f;
}

Camera::Camera(std::shared_ptr<Player> player) :
	m_cameraPos(VGet(player->GetPos().x,kCameraPosY,kCameraPosZ)),
	m_cameraTargetPos(player->GetPos()),
	m_inputX(0),
	m_inputZ(0)
{
}

Camera::~Camera()
{
	
}

void Camera::Update(std::shared_ptr<Player> player)
{
	// 入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &m_input);

	//X軸の入力状態が0じゃないとき
	if (m_input.Rx != 0)
	{
		if (m_input.Rx < 0)
		{
			m_input.Rx = -100;
		}

		if (m_input.Rx > 0)
		{
			m_input.Rx = 100;
		}
	}

	//Y軸の入力状態が0じゃないとき
	if (m_input.Ry != 0)
	{
		if (m_input.Ry < 0)
		{
			m_input.Ry = -100;
		}

		if (m_input.Ry > 0)
		{
			m_input.Ry = 100;
		}
	}

	//毎フレーム少しずつ値を足していく
	m_inputX = static_cast<int>(m_inputX * 0.85) + static_cast<int>(m_input.Rx * 0.15);
	m_inputZ = static_cast<int>(m_inputZ * 0.85) + static_cast<int>(m_input.Ry * 0.15);

	//カメラの位置、どこからどこを見ているかを設定
	m_cameraTargetPos.x = ((m_cameraTargetPos.x * 0.8f) + (player->GetPos().x * 0.2f)) + static_cast<float>(m_inputX);
	m_cameraTargetPos.z = ((m_cameraTargetPos.z * 0.8f) + (player->GetPos().z * 0.2f)) - static_cast<float>(m_inputZ);

	m_cameraPos.x = m_cameraTargetPos.x;
	m_cameraPos.z = m_cameraTargetPos.z + kCameraPosZ;

	//カメラの位置設定(カメラの位置、カメラが見る位置)
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTargetPos);
}

void Camera::ClearUpdate(std::shared_ptr<Player> player, bool menuScreen)
{
	VECTOR flontCamera = VAdd(player->GetPos(), VGet(0.0f, 300.0f, -600.0f));
	if (menuScreen)
	{
		flontCamera = VAdd(VGet(player->GetPos().x, player->GetPos().y, player->GetPos().z), VGet(350.0f, 300.0f, -600.0f));
	}

	m_cameraPos.x = (m_cameraPos.x * 0.96f) + (flontCamera.x * 0.04f);
	m_cameraPos.y = (m_cameraPos.y * 0.95f) + (flontCamera.y * 0.05f);
	m_cameraPos.z = (m_cameraPos.z * 0.95f) + (flontCamera.z * 0.05f);

	SetCameraPositionAndTarget_UpVecY(m_cameraPos, VGet(m_cameraPos.x,player->GetPos().y + 200, player->GetPos().z));

	//SetLightPosition(VGet(player->GetPos().x + 10000, 200, player->GetPos().z + 1000000));
	//	SetLightDirection(VGet(m_Pos.x, m_Pos.y, m_Pos.z));
}

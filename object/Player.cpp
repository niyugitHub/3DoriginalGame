#include "Player.h"
#include"Pad.h"
#include"Model.h"
#include"Shot.h"
#include <cassert>

namespace
{
	//ファイル名
	const char* const kEnemyModelFileName = "data/Character.mv1";

	// 旋回速度
	constexpr float kRotSpeed = 0.15f;

	// 最大移動速度
	constexpr float kMaxMoveSpeed = 7.0f;

	// 一フレームごとの移動速度上昇
	constexpr float kMoveSpeed = 1.0f; //地面にいるとき
	constexpr float kMoveJumpSpeed = 0.4f;//ジャンプ中

	// アニメーション番号
	constexpr int kIdleAnimNo = 3;	// 待機モーション
	constexpr int kModeAnimNo = 11;// 移動モーション
	constexpr int kJumpAnimNo = 6;// ジャンプモーション
	constexpr int kPunchAnimNo = 10;// ショットモーション
	constexpr int kClearAnimNo = 16;// クリアモーション

	// 当たり判定のサイズ
	constexpr float kColRadius = 90.0f;

	// 重力
	constexpr float kGravity = 0.5f;

	// ジャンプ力
	constexpr float kJumpPower = 20.0f;

	//ショットスピード
	constexpr float kShotSpeed = 20.0f;

	// カメラの位置
	constexpr float kCameraPosY = 1500.0f;
	constexpr float kCameraPosZ = -800.0f;
}

Player::Player(VECTOR pos) :
	m_updateFunc(&Player::updateIdle),
	m_modelHandle(-1),
	m_cameraPos(VGet(0.0f, kCameraPosY, kCameraPosZ)),
	m_animNo(3),
	m_angle(DX_PI_F),
	m_cameraAngle(0.0f),
	m_colFieldY(false),
	m_colFieldXZ(false)
	/*m_inputX(0),
	m_inputY(0)*/
{
	m_Pos = pos;
	m_NextPos = m_Pos;
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
	// なくなったショットは消す
	// 消す命令だが、実際には消してなくて、うしろによけているだけ
	auto rmIt = std::remove_if        // 条件に合致したものを消す
	(m_pShot.begin(),			// 対象はenemies_の最初から
		m_pShot.end(),			// 最後まで
	   // 消えてもらう条件を表すラムダ式
	   // trueだと消える。falseだと消えない
		[](Shot* shot)
		{
			return !shot->GetExist();
		});

	// 入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &m_input);


	// remove系の関数はちょっと罠があり、これを呼び出すだけでは、
	// 実際には消えていない。
	// 不要なものを後ろに避けてるだけ。
	// なので、必ずerase関数で実際に消す必要がある。
	// remove系関数は不要なものを後ろに避けて、避けた場所を
	// イテレータとして返す。

	// 実際に範囲を指定して消す
	m_pShot.erase(rmIt, m_pShot.end());
	// ここまでやらないと実際には消えないので注意

	for (auto& pShot : m_pShot)
	{
		pShot->Update(m_Pos);
	}
	//XZ軸から見てフィールドと当たってない場合
	if (!m_colFieldXZ)
	{
		m_Pos.x = m_NextPos.x;
		m_Pos.z = m_NextPos.z;
	}
	//Y軸から見てフィールドと当たってない場合
	if (!m_colFieldY)
	{
		m_Pos.y = m_NextPos.y;
		//ジャンプ中じゃないとき
		if (m_updateFunc != &Player::updateJump) 
		{
			m_Vec.y -= kGravity;
		}
	}

	//ジャンプ中ではなく、地面と当たっているとき
	else if(m_updateFunc != &Player::updateJump)
	{
		m_Vec.y = 0.0f;
	}

	m_NextPos = m_Pos;

	(this->*m_updateFunc)();

	m_colFieldY = false;
	m_colFieldXZ = false;


	//現在の座標に移動ベクトルを足す
	m_NextPos.x += m_Vec.x;
	m_NextPos.y += m_Vec.y;
	m_NextPos.z += m_Vec.z;
	//アニメーションを進める
	m_pModel->update();

	m_pModel->setPos(m_Pos);
	m_pModel->setRot(VGet(0.0f, m_angle, 0.0f));

	if (m_input.Rx != 0)
	{
		m_input.Rx /= 10;
	}

	if (m_input.Ry != 0)
	{
		m_input.Ry /= 10;
	}

	//カメラの位置、どこからどこを見ているかを設定
	m_cameraPos.x = ((m_cameraPos.x * 0.8f) + (m_Pos.x * 0.2f)) + static_cast<float>(m_input.Rx);
	m_cameraPos.z = ((m_cameraPos.z * 0.8f) + (m_Pos.z * 0.2f)) - static_cast<float>(m_input.Ry);
	//m_cameraPos.z = kCameraPosZ + m_Pos.z;
	SetCameraPositionAndTarget_UpVecY(VGet(m_cameraPos.x, m_cameraPos.y, m_cameraPos.z + kCameraPosZ), VGet(m_cameraPos.x, 0, m_cameraPos.z));


	//SetLightPosition(VGet(m_Pos.x, 500 , m_Pos.z));
	//SetLightDirection(VGet(m_Pos.x, 0 , m_Pos.z));
}

void Player::Draw()
{
	for (auto& pShot : m_pShot)
	{
		pShot->Draw();
	}

	m_pModel->draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "X:%d Y:%d Z:%d", m_input.X, m_input.Y, m_input.Z);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Rx:%d Ry:%d Rz:%d", m_input.Rx, m_input.Ry, m_input.Rz);
//	DrawFormatString(0, 16, GetColor(255, 255, 255), "Rx:%d Ry:%d Rz:%d", input.Rx, input.Ry, input.Rz);

//	printfDx("%d,%d\n", m_inputX, m_inputY);
	
	//printfDx("%f\n", m_Vec.x);
	//	printfDx("%f\n", static_cast<float>(m_Vec.z));
	//	printfDx("%f\n", static_cast<float>(m_Vec.x));
}

float Player::GetRadius()
{
	return kColRadius;
}

void Player::ClearUpdate()
{
	//プレイヤーの目の前にカメラを置く
	m_angle = max(0, m_angle - kRotSpeed);

	VECTOR flontCamera = VAdd(m_Pos, VGet(0.0f, 300.0f, -600.0f));

	m_cameraPos.x = (m_cameraPos.x * 0.95f) + (flontCamera.x * 0.05f);
	m_cameraPos.y = (m_cameraPos.y * 0.95f) + (flontCamera.y * 0.05f);
	m_cameraPos.z = (m_cameraPos.z * 0.95f) + (flontCamera.z * 0.05f); 

	//アニメーションを進める
	m_pModel->update();
	m_pModel->setRot(VGet(0.0f, m_angle, 0.0f));
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_Pos);
}

void Player::ClearCharaMotion()
{
	m_pModel->changeAnimation(kClearAnimNo, true, true, 2);
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

	

	//ボタンが押されるかつ、Y軸から見てフィールドと当たっているとき
	if (Pad::isTrigger(PAD_INPUT_1) && m_colFieldY) 
	{
		m_Vec.y = kJumpPower;
		m_updateFunc = &Player::updateJump;
		m_pModel->changeAnimation(kJumpAnimNo, false, true, 1);
		return;
	}

	m_Vec.x = min(max(m_Vec.x - kMoveSpeed, 0), m_Vec.x + kMoveSpeed);
	m_Vec.z = min(max(m_Vec.z - kMoveSpeed, 0), m_Vec.z + kMoveSpeed);

}

void Player::updateMove()
{
	//入力状態取得
	bool PressLeft = Pad::isPress(PAD_INPUT_LEFT);
	bool PressUp = Pad::isPress(PAD_INPUT_UP);
	bool PressRight = Pad::isPress(PAD_INPUT_RIGHT);
	bool PressBottom = Pad::isPress(PAD_INPUT_DOWN);

	IsMove(PressLeft, PressUp, PressRight, PressBottom, kMoveSpeed);
	IsAngle(PressLeft, PressUp, PressRight, PressBottom);

	if (Pad::isTrigger(PAD_INPUT_1) && m_colFieldY)
	{
		m_Vec.y = kJumpPower;
		m_updateFunc = &Player::updateJump;
		m_pModel->changeAnimation(kJumpAnimNo, false, true, 1);
		return;
	}

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
		m_pModel->changeAnimation(kIdleAnimNo, true, true, 1);
		return;
	}
}

void Player::updateJump()
{
	bool PressLeft = Pad::isPress(PAD_INPUT_LEFT);
	bool PressUp = Pad::isPress(PAD_INPUT_UP);
	bool PressRight = Pad::isPress(PAD_INPUT_RIGHT);
	bool PressBottom = Pad::isPress(PAD_INPUT_DOWN);

	m_Vec.y -= kGravity;
	m_Pos.y += m_Vec.y;

	IsMove(PressLeft, PressUp, PressRight, PressBottom, kMoveJumpSpeed);
	IsAngle(PressLeft, PressUp, PressRight, PressBottom);

	if (m_colFieldY && m_Vec.y < 0.0f)
	{
		m_pModel->changeAnimation(kIdleAnimNo, true, true, 2);
		m_updateFunc = &Player::updateIdle;
	}
}

void Player::IsMove(bool Left, bool Up, bool Right, bool Bottom, float MoveSpeed)
{
	if (Up)
	{
		m_Vec.z = min(m_Vec.z + MoveSpeed, kMaxMoveSpeed);
	}

	if (Bottom)
	{
		m_Vec.z = max(m_Vec.z - MoveSpeed, -kMaxMoveSpeed);
	}

	if (Right)
	{
		m_Vec.x = min(m_Vec.x + MoveSpeed, kMaxMoveSpeed);
	}

	if (Left)
	{
		m_Vec.x = max(m_Vec.x - MoveSpeed, -kMaxMoveSpeed);
	}

	Vec2 vec = { m_Vec.x,m_Vec.z };
	vec = vec.normalize() * kMaxMoveSpeed;

	if (Up && Right)//上、右入力されたとき
	{
		if (m_Vec.x > 0 && m_Vec.z > 0)
		{
			m_Vec.x = vec.x;
			m_Vec.z = vec.y;
		}
	}

	if (Right && Bottom)//下、右入力されたとき
	{
		if (m_Vec.x > 0 && m_Vec.z < 0)
		{
			m_Vec.x = vec.x;
			m_Vec.z = vec.y;
		}
	}

	if (Bottom && Left)//下、左入力されたとき
	{
		if (m_Vec.x < 0 && m_Vec.z < 0)
		{
			m_Vec.x = vec.x;
			m_Vec.z = vec.y;
		}
	}

	if (Left && Up)//上、左入力されたとき
	{
		if (m_Vec.x < 0 && m_Vec.z > 0)
		{
			m_Vec.x = vec.x;
			m_Vec.z = vec.y;
		}
	}

	if (!Left && !Right)//左、右入力がないときm_Vec.xの値をゼロにする
	{
		m_Vec.x = min(max(m_Vec.x - MoveSpeed, 0), m_Vec.x + MoveSpeed);
	}

	if (!Up && !Bottom)//上、下入力がないときm_Vec.	yの値をゼロにする
	{
		m_Vec.z = min(max(m_Vec.z - MoveSpeed, 0), m_Vec.z + MoveSpeed);
	}

}

void Player::IsAngle(bool Left, bool Up, bool Right, bool Bottom)
{
	//m_angleがDX_PI_F * 2より大きいとき
	if (m_angle > DX_PI_F * 2)
	{
		m_angle = 0;
	}
	//m_angleが0より小さいとき
	if (m_angle < 0.0f)
	{
		m_angle = DX_PI_F * 2;
	}

	
	///////////////////////////////
	//各入力ごとのm_angleの調整///
	//////////////////////////////
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
		if (m_angle <= DX_PI_F + kRotSpeed)
		{
			m_angle = min(m_angle + kRotSpeed, DX_PI_F);
		}
		if (m_angle > DX_PI_F + kRotSpeed)
		{
			m_angle = max(m_angle - kRotSpeed, DX_PI_F);
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

Vec2 Player::IsShot(Vec2 ShotSpeed)
{
	ShotSpeed.x = sin(m_angle);
	ShotSpeed.y = cos(m_angle);

	ShotSpeed = ShotSpeed.normalize();

	ShotSpeed *= -kShotSpeed;

	return ShotSpeed;
}


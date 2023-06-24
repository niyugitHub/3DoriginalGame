#include "Player.h"
#include"Pad.h"
#include"Model.h"
#include"Shot.h"
#include <cassert>

namespace
{
	//�t�@�C����
	const char* const kEnemyModelFileName = "data/Character.mv1";

	// ���񑬓x
	constexpr float kRotSpeed = 0.15f;

	// �ő�ړ����x
	constexpr float kMaxMoveSpeed = 7.0f;

	// ��t���[�����Ƃ̈ړ����x�㏸
	constexpr float kMoveSpeed = 1.0f; //�n�ʂɂ���Ƃ�
	constexpr float kMoveJumpSpeed = 0.4f;//�W�����v��

	// �A�j���[�V�����ԍ�
	constexpr int kIdleAnimNo = 3;	// �ҋ@���[�V����
	constexpr int kModeAnimNo = 11;// �ړ����[�V����
	constexpr int kJumpAnimNo = 6;// �W�����v���[�V����
	constexpr int kPunchAnimNo = 10;// �p���`���[�V����
	constexpr int kClearAnimNo = 16;// �N���A���[�V����

	// �����蔻��̃T�C�Y
	constexpr float kColRadius = 90.0f;

	// �d��
	constexpr float kGravity = 0.5f;

	// �W�����v��
	constexpr float kJumpPower = 20.0f;

	//�V���b�g�X�s�[�h
	constexpr float kShotSpeed = 20.0f;

	// �J�����̈ʒu
	constexpr float kCameraPosY = 1500.0f;
	constexpr float kCameraPosZ = -800.0f;
}

Player::Player(VECTOR pos) :
	m_updateFunc(&Player::updateIdle),
	m_modelHandle(-1),
	m_animNo(3),
	m_angle(DX_PI_F),
	m_cameraAngle(0.0f),
	m_colFieldY(false),
	m_colFieldXZ(false),
	m_inputX(0),
	m_inputZ(0)
	/*m_inputX(0),
	m_inputY(0)*/
{
	m_Pos = pos;
	m_NextPos = m_Pos;
	m_attackPos = m_Pos;
	m_Vec = VGet(0, 0, 0);

	m_cameraPos = VGet(m_Pos.x, kCameraPosY, kCameraPosZ);
	m_cameraTargetPos = VGet(m_Pos.x, 0, 0);
	//3D���f���̐���
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
	//XZ�����猩�ăt�B�[���h�Ɠ������ĂȂ��ꍇ
	if (!m_colFieldXZ)
	{
		m_Pos.x = m_NextPos.x;
		m_Pos.z = m_NextPos.z;
	}
	//Y�����猩�ăt�B�[���h�Ɠ������ĂȂ��ꍇ
	if (!m_colFieldY)
	{
		m_Pos.y = m_NextPos.y;
		//�W�����v������Ȃ��Ƃ�
		if (m_updateFunc != &Player::updateJump) 
		{
			m_Vec.y -= kGravity;
		}
	}

	//�W�����v���ł͂Ȃ��A�n�ʂƓ������Ă���Ƃ�
	else if(m_updateFunc != &Player::updateJump)
	{
		m_Vec.y = 0.0f;
	}

	m_NextPos = m_Pos;

	(this->*m_updateFunc)();

	//�}�C�t���[�������蔻���false�ɕύX
	m_colFieldY = false;
	m_colFieldXZ = false;


	//���݂̍��W�Ɉړ��x�N�g���𑫂�
	m_NextPos = VAdd(m_NextPos, m_Vec);

	//�A�j���[�V������i�߂�
	m_pModel->update();

	m_pModel->setPos(m_Pos);
	m_pModel->setRot(VGet(0.0f, m_angle, 0.0f));

	//X���̓��͏�Ԃ�0����Ȃ��Ƃ�
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

	//Y���̓��͏�Ԃ�0����Ȃ��Ƃ�
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

	if (m_updateFunc != &Player::updateIdle)
	{
		m_input.Rx = 0;
		m_input.Ry = 0;
	}

	//���t���[���������l�𑫂��Ă���
	m_inputX = (m_inputX * 0.85) + (m_input.Rx * 0.15);
	m_inputZ = (m_inputZ * 0.85) + (m_input.Ry * 0.15);

	//�J�����̈ʒu�A�ǂ�����ǂ������Ă��邩��ݒ�
	m_cameraTargetPos.x = ((m_cameraTargetPos.x * 0.8f) + (m_Pos.x * 0.2f)) + static_cast<float>(m_inputX);
	m_cameraTargetPos.z = ((m_cameraTargetPos.z * 0.8f) + (m_Pos.z * 0.2f)) - static_cast<float>(m_inputZ);

	m_cameraPos.x = m_cameraTargetPos.x;
	m_cameraPos.z = m_cameraTargetPos.z + kCameraPosZ;
	
	//�J�����̈ʒu�ݒ�(�J�����̈ʒu�A�J����������ʒu)
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTargetPos);


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
	//�v���C���[�̖ڂ̑O�ɃJ������u��
	m_angle = max(0, m_angle - kRotSpeed);

	VECTOR flontCamera = VAdd(m_Pos, VGet(0.0f, 300.0f, -600.0f));

	m_cameraPos.x = (m_cameraPos.x * 0.95f) + (flontCamera.x * 0.05f);
	m_cameraPos.y = (m_cameraPos.y * 0.95f) + (flontCamera.y * 0.05f);
	m_cameraPos.z = (m_cameraPos.z * 0.95f) + (flontCamera.z * 0.05f); 

	//�A�j���[�V������i�߂�
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
	//�㉺���E�ǂꂩ�����͂��ꂽ��updateMove�ɑJ��
	if (Pad::isPress(PAD_INPUT_UP) || Pad::isPress(PAD_INPUT_DOWN) ||
		Pad::isPress(PAD_INPUT_LEFT) || Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_updateFunc = &Player::updateMove;
		m_pModel->changeAnimation(kModeAnimNo, true, true, 2);
		return;
	}

	// ���͏�Ԃ��擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &m_input);

	//�{�^����������邩�AY�����猩�ăt�B�[���h�Ɠ������Ă���Ƃ�updateJump�ɑJ��
	if (Pad::isTrigger(PAD_INPUT_1) && m_colFieldY) 
	{
		m_Vec.y = kJumpPower;
		m_updateFunc = &Player::updateJump;
		m_pModel->changeAnimation(kJumpAnimNo, false, true, 1);
		return;
	}

	if (Pad::isTrigger(PAD_INPUT_3) && m_colFieldY)
	{
		m_isAttackFlag = true;
		//�x�N�g����0��
		m_Vec.x = 0;
		m_Vec.z = 0;
		m_updateFunc = &Player::updatePunch;
		m_pModel->changeAnimation(kPunchAnimNo, false, true, 1);
		return;
	}

	m_Vec.x = min(max(m_Vec.x - kMoveSpeed, 0), m_Vec.x + kMoveSpeed);
	m_Vec.z = min(max(m_Vec.z - kMoveSpeed, 0), m_Vec.z + kMoveSpeed);

}

void Player::updateMove()
{
	//���͏�Ԏ擾
	bool PressLeft = Pad::isPress(PAD_INPUT_LEFT);
	bool PressUp = Pad::isPress(PAD_INPUT_UP);
	bool PressRight = Pad::isPress(PAD_INPUT_RIGHT);
	bool PressBottom = Pad::isPress(PAD_INPUT_DOWN);

	IsMove(PressLeft, PressUp, PressRight, PressBottom, kMoveSpeed);
	IsAngle(PressLeft, PressUp, PressRight, PressBottom);

	//�{�^����������邩�AY�����猩�ăt�B�[���h�Ɠ������Ă���Ƃ�updateJump�ɑJ��
	if (Pad::isTrigger(PAD_INPUT_1) && m_colFieldY)
	{
		m_Vec.y = kJumpPower;
		m_updateFunc = &Player::updateJump;
		m_pModel->changeAnimation(kJumpAnimNo, false, true, 1);
		return;
	}

	if (Pad::isTrigger(PAD_INPUT_3) && m_colFieldY)
	{
		//�x�N�g����0��
		m_isAttackFlag = true;
		m_Vec.x = 0;
		m_Vec.z = 0;
		m_updateFunc = &Player::updatePunch;
		m_pModel->changeAnimation(kPunchAnimNo, false, true, 1);
		return;
	}

	if (fabs(m_Vec.x) >= 5.0f && fabs(m_Vec.z) >= 5.0f)
	{
		Vec2 vec = { m_Vec.x,m_Vec.z };

		vec = vec.normalize() * kMaxMoveSpeed;

		m_Vec.x = vec.x;
		m_Vec.z = vec.y;
	}

	//�㉺���E�̓��͂��Ȃ��Ƃ�updateIdle�ɑJ��
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

	//�n�ʂɂ��Ă��A�~�����̏ꍇupdateIdle�ɑJ��
	if (m_colFieldY && m_Vec.y < 0.0f)
	{
		m_pModel->changeAnimation(kIdleAnimNo, true, true, 2);
		m_updateFunc = &Player::updateIdle;
	}
}

void Player::updatePunch()
{
	if (m_pModel->isAnimEnd())
	{
		m_updateFunc = &Player::updateIdle;
		m_pModel->changeAnimation(kIdleAnimNo, true, true, 1);
		m_isAttackFlag = false;
		return;
	}
}

void Player::SetAttackPos()
{
	/*MATRIX cameraRotMtx = MGetRotY(m_angle);
	
	m_attackPos = VTransform(m_Pos, cameraRotMtx);*/
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

	if (Up && Right)//��A�E���͂��ꂽ�Ƃ�
	{
		if (m_Vec.x > 0 && m_Vec.z > 0)
		{
			m_Vec.x = vec.x;
			m_Vec.z = vec.y;
		}
	}

	if (Right && Bottom)//���A�E���͂��ꂽ�Ƃ�
	{
		if (m_Vec.x > 0 && m_Vec.z < 0)
		{
			m_Vec.x = vec.x;
			m_Vec.z = vec.y;
		}
	}

	if (Bottom && Left)//���A�����͂��ꂽ�Ƃ�
	{
		if (m_Vec.x < 0 && m_Vec.z < 0)
		{
			m_Vec.x = vec.x;
			m_Vec.z = vec.y;
		}
	}

	if (Left && Up)//��A�����͂��ꂽ�Ƃ�
	{
		if (m_Vec.x < 0 && m_Vec.z > 0)
		{
			m_Vec.x = vec.x;
			m_Vec.z = vec.y;
		}
	}

	if (!Left && !Right)//���A�E���͂��Ȃ��Ƃ�m_Vec.x�̒l���[���ɂ���
	{
		m_Vec.x = min(max(m_Vec.x - MoveSpeed, 0), m_Vec.x + MoveSpeed);
	}

	if (!Up && !Bottom)//��A�����͂��Ȃ��Ƃ�m_Vec.	y�̒l���[���ɂ���
	{
		m_Vec.z = min(max(m_Vec.z - MoveSpeed, 0), m_Vec.z + MoveSpeed);
	}

}

void Player::IsAngle(bool Left, bool Up, bool Right, bool Bottom)
{
	//m_angle��DX_PI_F * 2���傫���Ƃ�
	if (m_angle > DX_PI_F * 2)
	{
		m_angle = 0;
	}
	//m_angle��0��菬�����Ƃ�
	if (m_angle < 0.0f)
	{
		m_angle = DX_PI_F * 2;
	}

	
	///////////////////////////////
	//�e���͂��Ƃ�m_angle�̒���///
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


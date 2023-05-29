#include "Player.h"
#include"Pad.h"
#include"Model.h"
#include"Shot.h"

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
	constexpr int kShotAnimNo = 5;// �V���b�g���[�V����

	// �����蔻��̃T�C�Y
	constexpr float kColRadius = 90.0f;

	// �d��
	constexpr float kGravity = 0.5f;

	// �W�����v��
	constexpr float kJumpPower = 20.0f;

	//�V���b�g�X�s�[�h
	constexpr float kShotSpeed = 20.0f;
}

Player::Player() :
	m_updateFunc(&Player::updateIdle),
	m_modelHandle(-1),
	m_cameraPos(0.0f),
	m_animNo(3),
	m_angle(0),
	m_colFieldY(false),
	m_colFieldXZ(false)
{
	m_Pos = VGet(0, 0, 0);
	m_NextPos = m_Pos;
	m_Vec = VGet(0, 0, 0);
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
	// �Ȃ��Ȃ����V���b�g�͏���
	// �������߂����A���ۂɂ͏����ĂȂ��āA������ɂ悯�Ă��邾��
	auto rmIt = std::remove_if        // �����ɍ��v�������̂�����
	(m_pShot.begin(),			// �Ώۂ�enemies_�̍ŏ�����
		m_pShot.end(),			// �Ō�܂�
	   // �����Ă��炤������\�������_��
	   // true���Ə�����Bfalse���Ə����Ȃ�
		[](Shot* shot)
		{
			return !shot->GetExist();
		});

	// remove�n�̊֐��͂������㩂�����A������Ăяo�������ł́A
	// ���ۂɂ͏����Ă��Ȃ��B
	// �s�v�Ȃ��̂����ɔ����Ă邾���B
	// �Ȃ̂ŁA�K��erase�֐��Ŏ��ۂɏ����K�v������B
	// remove�n�֐��͕s�v�Ȃ��̂����ɔ����āA�������ꏊ��
	// �C�e���[�^�Ƃ��ĕԂ��B

	// ���ۂɔ͈͂��w�肵�ď���
	m_pShot.erase(rmIt, m_pShot.end());
	// �����܂ł��Ȃ��Ǝ��ۂɂ͏����Ȃ��̂Œ���

	for (auto& pShot : m_pShot)
	{
		pShot->Update(m_Pos);
	}

	if (!m_colFieldXZ)
	{
		m_Pos.x = m_NextPos.x;
		m_Pos.z = m_NextPos.z;
	}
	if (!m_colFieldY)
	{
		m_Pos.y = m_NextPos.y;
		if (m_updateFunc != &Player::updateJump)
		{
			m_Vec.y -= kGravity;
		}
	}
	else if(m_updateFunc != &Player::updateJump)
	{
		m_Vec.y = 0.0f;
	}

	m_NextPos = m_Pos;

	(this->*m_updateFunc)();

	m_colFieldY = false;
	m_colFieldXZ = false;


	//���݂̍��W�Ɉړ��x�N�g���𑫂�
	m_NextPos.x += m_Vec.x;
	m_NextPos.y += m_Vec.y;
	m_NextPos.z += m_Vec.z;
	//�A�j���[�V������i�߂�
	m_pModel->update();

	m_pModel->setPos(m_Pos);
	m_pModel->setRot(VGet(0.0f, m_angle, 0.0f));

	//�J�����̈ʒu�A�ǂ�����ǂ������Ă��邩��ݒ�
	m_cameraPos = (m_cameraPos * 0.8f) + (m_Pos.x * 0.2f);
	SetCameraPositionAndTarget_UpVecY(VGet(m_cameraPos, 1500, -800 + m_Pos.z), VGet(m_cameraPos, 0, m_Pos.z));


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
	

	//	printfDx("%f\n", static_cast<float>(m_Vec.z));
	//	printfDx("%f\n", static_cast<float>(m_Vec.x));
}

float Player::GetRadius()
{
	return kColRadius;
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

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_Vec.y = kJumpPower;
		m_updateFunc = &Player::updateJump;
		m_pModel->changeAnimation(kJumpAnimNo, false, true, 1);
		return;
	}

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_Vec.x = 0.0f;
		m_Vec.z = 0.0f;

		Vec2 vec = { 1.0f,1.0f };
		vec = IsShot(vec);
		m_pShot.push_back(new Shot(m_Pos, VGet(vec.x, 0.0f, vec.y)));

		m_updateFunc = &Player::updateShot;
		m_pModel->changeAnimation(kShotAnimNo, false, true, 1);
		return;
	}

	m_Vec.x = min(max(m_Vec.x - kMoveSpeed, 0), m_Vec.x + kMoveSpeed);
	m_Vec.z = min(max(m_Vec.z - kMoveSpeed, 0), m_Vec.z + kMoveSpeed);

}

void Player::updateMove()
{
	bool PressLeft = Pad::isPress(PAD_INPUT_LEFT);
	bool PressUp = Pad::isPress(PAD_INPUT_UP);
	bool PressRight = Pad::isPress(PAD_INPUT_RIGHT);
	bool PressBottom = Pad::isPress(PAD_INPUT_DOWN);

	IsMove(PressLeft, PressUp, PressRight, PressBottom, kMoveSpeed);
	IsAngle(PressLeft, PressUp, PressRight, PressBottom);

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_Vec.y = kJumpPower;
		m_updateFunc = &Player::updateJump;
		m_pModel->changeAnimation(kJumpAnimNo, false, true, 1);
		return;
	}

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_Vec.x = 0.0f;
		m_Vec.z = 0.0f;

		Vec2 vec = { 1.0f,1.0f };
		vec = IsShot(vec);
		m_pShot.push_back(new Shot(m_Pos, VGet(vec.x, 0.0f, vec.y)));

		m_updateFunc = &Player::updateShot;
		m_pModel->changeAnimation(kShotAnimNo, false, true, 1);
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

void Player::updateShot()
{
	if (m_pModel->isAnimEnd())
	{
		// �ҋ@�A�j���ɕύX����
		m_animNo = kIdleAnimNo;
		m_pModel->changeAnimation(kIdleAnimNo, true, true, 4);

		// update��ҋ@��
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
		m_Vec.x = min(max(m_Vec.x - MoveSpeed, 0), m_Vec.x + MoveSpeed);
	}

	if (!Up && !Bottom)
	{
		m_Vec.z = min(max(m_Vec.z - MoveSpeed, 0), m_Vec.z + MoveSpeed);
	}

}

void Player::IsAngle(bool Left, bool Up, bool Right, bool Bottom)
{
	if (m_angle > DX_PI_F * 2)
	{
		m_angle = 0;
	}

	if (m_angle < 0.0f)
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
		if (m_angle <= DX_PI_F + kRotSpeed)
		{
			m_angle = m_angle + kRotSpeed;
		}
		if (m_angle > DX_PI_F + kRotSpeed)
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

Vec2 Player::IsShot(Vec2 ShotSpeed)
{
	ShotSpeed.x = sin(m_angle);
	ShotSpeed.y = cos(m_angle);

	ShotSpeed = ShotSpeed.normalize();

	ShotSpeed *= -kShotSpeed;

	return ShotSpeed;
}


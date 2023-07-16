#include "HalfwayPoint.h"

namespace
{
	// �����蔻��̃T�C�Y
	constexpr float kColRadius = 100.0f;

	// ���ԃ|�C���g�t�@�C����
	const char* const kHalfwayPointName = "data/halfwaybefore.mv1";
	// ���ԃ|�C���g�擾���̃t�@�C����
	const char* const kGetHalfwayPointName = "data/halfwayafter.mv1";

	//��]�̏オ�蕝
	constexpr float kRotAcc = -0.08f;
	//��]���ő�
	constexpr float kRotSpeedMax = -0.5f;
	//������]��
	constexpr float kRotSpeedFirst = 0.4f;
}


HalfwayPoint::HalfwayPoint(VECTOR pos) :
	m_Pos(pos),
	m_modelRot(0.0f),
	m_rotSpeed(kRotSpeedFirst)
{
	m_modelHandleAfter = MV1LoadModel(kGetHalfwayPointName);
	m_modelHandleBefore = MV1LoadModel(kHalfwayPointName);

	//MV1SetRotationXYZ(m_modelHandleAfter, VGet(0, 80, 0));
	MV1SetPosition(m_modelHandleAfter, VGet(m_Pos.x, m_Pos.y - 80, m_Pos.z));
	MV1SetScale(m_modelHandleAfter, VGet(6, 6, 6));

	//MV1SetRotationXYZ(m_modelHandleBefore, VGet(0, 80, 0));
	MV1SetPosition(m_modelHandleBefore, VGet(m_Pos.x, m_Pos.y - 80, m_Pos.z));
	MV1SetScale(m_modelHandleBefore, VGet(6, 6, 6));

	m_modelHandle = m_modelHandleBefore;

}

HalfwayPoint::~HalfwayPoint()
{
}

void HalfwayPoint::Reset()
{
	m_modelHandle = m_modelHandleBefore;
	m_isCollision = false;
	m_modelRot = 0.0f;
	m_rotSpeed = kRotSpeedFirst;
}

void HalfwayPoint::Update()
{
	if (m_modelRot == 360) return;
	if (m_isCollision)
	{
		m_modelRot = max(m_modelRot + m_rotSpeed, -DX_PI_F * 2);
		m_rotSpeed = max(m_rotSpeed + kRotAcc, kRotSpeedMax);
		MV1SetRotationXYZ(m_modelHandle, VGet(0, 0, m_modelRot));
	}
}

void HalfwayPoint::Draw()
{
	MV1DrawModel(m_modelHandle);
}

float HalfwayPoint::GetRadius()
{
	return kColRadius;
}

void HalfwayPoint::ChangeModel()
{
	m_modelHandle = m_modelHandleAfter;
}

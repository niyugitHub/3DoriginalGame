#include "HalfwayPoint.h"

namespace
{
	// �����蔻��̃T�C�Y
	constexpr float kColRadius = 100.0f;

	// ���ԃ|�C���g�t�@�C����
	const char* const kGoalName = "data/goal.mv1";
}

HalfwayPoint::HalfwayPoint(VECTOR pos) :
	m_Pos(pos)
{
	m_modelHandle = MV1LoadModel(kGoalName);

	MV1SetRotationXYZ(m_modelHandle, VGet(0, 80, 0));
	MV1SetPosition(m_modelHandle, VGet(m_Pos.x, m_Pos.y - 80, m_Pos.z));
	MV1SetScale(m_modelHandle, VGet(2, 2, 2));
}

HalfwayPoint::~HalfwayPoint()
{
}

void HalfwayPoint::Update()
{
}

void HalfwayPoint::Draw()
{
	MV1DrawModel(m_modelHandle);
}

float HalfwayPoint::GetRadius()
{
	return kColRadius;
}
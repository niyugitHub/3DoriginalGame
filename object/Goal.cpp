#include "Goal.h"

namespace
{
	// 当たり判定のサイズ
	constexpr float kColRadius = 100.0f;

	// ゴールファイル名
	const char* const kGoalName = "data/goal.mv1";
}

Goal::Goal(VECTOR pos) : 
	m_Pos(pos)
{
	m_modelHandle = MV1LoadModel(kGoalName);

	MV1SetRotationXYZ(m_modelHandle, VGet(0, 80, 0));
	MV1SetPosition(m_modelHandle, VGet(m_Pos.x,m_Pos.y - 80,m_Pos.z));
	MV1SetScale(m_modelHandle, VGet(2, 2, 2));
}

Goal::~Goal()
{
}

void Goal::Update()
{
}

void Goal::Draw()
{
	/*DrawSphere3D(m_Pos, kColRadius, 50,
		0xffffff,
		0xffffff,
		true);*/

	MV1DrawModel(m_modelHandle);
}

float Goal::GetRadius()
{
	return kColRadius;
}

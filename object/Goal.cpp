#include "Goal.h"

namespace
{
	// “–‚½‚è”»’è‚ÌƒTƒCƒY
	constexpr float kColRadius = 100.0f;
}

Goal::Goal(VECTOR pos) : 
	m_Pos(pos)
{
}

Goal::~Goal()
{
}

void Goal::Update()
{
}

void Goal::Draw()
{
	DrawSphere3D(m_Pos, kColRadius, 50,
		0xffffff,
		0xffffff,
		true);
}

float Goal::GetRadius()
{
	return kColRadius;
}

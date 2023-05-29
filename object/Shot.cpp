#include "Shot.h"

namespace
{
	// ƒVƒ‡ƒbƒg‚Ì”¼Œa
	constexpr float kRadius = 40.0f;
}

Shot::Shot(VECTOR pos, VECTOR vec) :
	m_Pos(pos),
	m_lastPos(m_Pos),
	m_Vec(vec),
	m_Exist(true)
{
}

Shot::~Shot()
{
}

void Shot::Update(VECTOR PlayerPos)
{
	m_lastPos = m_Pos;

	m_Pos = VAdd(m_Pos, m_Vec);

	VECTOR toPos = VSub(m_Pos, PlayerPos);

	float dist = VSize(toPos);

	if (dist > 5000)
	{
		m_Exist = false;
	}
}

void Shot::Draw()
{
	DrawSphere3D(m_Pos, kRadius, 8, 0xff0000, 0xff0000, true);
}

float Shot::GetRadius() const
{
	return kRadius;
}

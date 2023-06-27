#include "Item.h"

namespace
{
	// “–‚½‚è”»’è‚ÌƒTƒCƒY
	constexpr float kColRadius = 100.0f;
}

Item::Item(VECTOR pos) : 
	m_Pos(pos)
{
}

Item::~Item()
{
}

void Item::Update()
{
}

void Item::Draw()
{
	DrawSphere3D(m_Pos, kColRadius, 50,
		0xffff00,
		0xffff00,
		true);
}

float Item::GetRadius()
{
	return kColRadius;
}

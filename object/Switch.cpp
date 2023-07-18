#include "Switch.h"
#include<cassert>
#include<DxLib.h>

namespace
{
	// 当たり判定のサイズ
	constexpr float kColRadius = 90.0f;

	//色情報
	constexpr int kRedNumber = 2;
	constexpr int kBlueNumber = 3;
	constexpr int kGreenNumber = 4;
}

Switch::Switch(VECTOR pos, std::array<int, 3> modelHandle) :
	m_Pos(pos),
	m_colorNum(2) // 赤の数値が2のため初期化で2を入れる
{
	for (int i= 0; i < m_modelHandle.size(); i++)
	{
		m_modelHandle[i] = MV1DuplicateModel(modelHandle[i]);;
	}

	for (auto& model : m_modelHandle)
	{
		MV1SetPosition(model, VGet(m_Pos.x, m_Pos.y - 80, m_Pos.z));
		MV1SetScale(model, VGet(8, 8, 8));
		assert(model != -1);
	}

	
}

Switch::~Switch()
{
}

void Switch::Update()
{
	
}

void Switch::Draw()
{
	if (m_colorNum == kRedNumber)
	{
		MV1DrawModel(m_modelHandle[0]);
	}
	if (m_colorNum == kBlueNumber)
	{
		MV1DrawModel(m_modelHandle[1]);
	}
	if (m_colorNum == kGreenNumber)
	{
		MV1DrawModel(m_modelHandle[2]);
	}
}

float Switch::GetRadius()
{
	return kColRadius * 1.5f;
}
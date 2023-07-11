#include "Item.h"

namespace
{
	// 当たり判定のサイズ
	constexpr float kColRadius = 100.0f;

	// 人参ファイル名
	const char* const kItemName = "data/carrot.mv1";

	//　モデルのサイズ
	constexpr float kMaxSize = 4.0f;
	constexpr float kMinSize = 3.0f;
	constexpr float kChangeSizeSpeed = 0.01f;
	
	// 座標移動
	constexpr float kMaxPosY = 100.0f;
	constexpr float kMinPosY = 0.0f;
	constexpr float kChangePosY = 1.0f;
}

Item::Item(VECTOR pos) : 
	m_Pos(pos),
	m_size(kMinSize),
	m_vecY(0.0f)
{
	m_modelHandle = MV1LoadModel(kItemName);
	MV1SetScale(m_modelHandle, VGet(m_size, m_size, m_size));

	MV1SetPosition(m_modelHandle, m_Pos);
}

Item::~Item()
{
}

void Item::Update()
{
	static float ChangeSizeSpeed = kChangeSizeSpeed;//モデルのサイズを変更させるための変数
	static float ChangePosSpeed = kChangePosY;//モデルの座標を変更させるための変数

	m_size += ChangeSizeSpeed;
	m_vecY += ChangePosSpeed;

	if (m_size < kMinSize || m_size > kMaxSize)
	{
		ChangeSizeSpeed *= -1;
	}

	if (m_vecY < kMinPosY || m_vecY > kMaxPosY)
	{
		ChangePosSpeed *= -1;
	}

	MV1SetScale(m_modelHandle, VGet(m_size, m_size, m_size));
	MV1SetPosition(m_modelHandle, VGet(m_Pos.x + 30, m_Pos.y + m_vecY, m_Pos.z));
}

void Item::Draw()
{
	/*DrawSphere3D(m_Pos, kColRadius, 50,
		0xffff00,
		0xffff00,
		true);*/

	MV1DrawModel(m_modelHandle);
}

float Item::GetRadius()
{
	return kColRadius;
}

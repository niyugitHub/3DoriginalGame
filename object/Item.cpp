#include"Item.h"

namespace
{
	// 半径の大きさ
	constexpr float kColRadius = 100.0f;

	// アイテムファイル名
	const char* const kItemName = "data/carrot.mv1";

	// サイズの変動のための変数
	constexpr float kMaxSize = 4.0f;
	constexpr float kMinSize = 3.0f;
	constexpr float kChangeSizeSpeed = 0.01f;
	
	// 座標移動のための変数
	constexpr float kMaxPosY = 100.0f;
	constexpr float kMinPosY = 0.0f;
	constexpr float kChangePosY = 1.0f;
}

Item::Item(VECTOR pos) : 
m_Pos(pos),
m_size(kMinSize),
m_vecY(0.0f),
m_Exist(true)
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
	static float ChangeSizeSpeed = kChangeSizeSpeed;// 一回だけサイズの変動スピードを代入
	static float ChangePosSpeed = kChangePosY;// 一回だけ座標の移動スピードを代入

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
	MV1DrawModel(m_modelHandle);
}

float Item::GetRadius()
{
	return kColRadius;
}
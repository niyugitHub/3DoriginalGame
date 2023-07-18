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
	constexpr float kGetItemChangeSize = 1.5f;
	constexpr float kGetItemChangeSpeed = 0.3f;

	
	// 座標移動のための変数
	constexpr float kMaxPosY = 100.0f;
	constexpr float kMinPosY = 0.0f;
	constexpr float kChangePosY = 1.0f;
}

Item::Item(VECTOR pos) : 
m_Pos(pos),
m_size(kMinSize),
m_vecY(0.0f),
m_changeSizeSpeed(kGetItemChangeSize),
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
	if (m_Exist)
	{
		static float ChangeSizeSpeed = kChangeSizeSpeed;// 一回だけサイズの変動スピードを代入
		static float ChangePosSpeed = kChangePosY;// 一回だけ座標の移動スピードを代入

		m_size += ChangeSizeSpeed;
		m_vecY += ChangePosSpeed;

		if (m_size > kMaxSize)
		{
			m_size = kMaxSize;
			ChangeSizeSpeed = -kChangeSizeSpeed;
		}

		if (m_size < kMinSize)
		{
			m_size = kMinSize;
			ChangeSizeSpeed = kChangeSizeSpeed;
		}

		if (m_vecY < kMinPosY || m_vecY > kMaxPosY)
		{
			ChangePosSpeed *= -1;
		}
	}
	else
	{
		m_size = max(m_size + m_changeSizeSpeed, 0);
		m_changeSizeSpeed -= kGetItemChangeSpeed;
	}

	MV1SetScale(m_modelHandle, VGet(m_size, m_size, m_size));
	MV1SetPosition(m_modelHandle, VGet(m_Pos.x + 30, m_Pos.y + m_vecY, m_Pos.z));
}

void Item::Draw()
{
	if (m_size <= 0) return;
	MV1DrawModel(m_modelHandle);
}

float Item::GetRadius()
{
	return kColRadius;
}

void Item::Reset(bool exist)
{
	m_Exist = exist;

	if (!m_Exist) return;
	//存在しているときはm_changeSizeSpeedを初期化
	m_changeSizeSpeed = kGetItemChangeSize;
}

#include "Switch.h"

namespace
{
	// �����蔻��̃T�C�Y
	constexpr float kColRadius = 90.0f;

	//�F���
	constexpr int kRedNumber = 2;
	constexpr int kBlueNumber = 3;
	constexpr int kGreenNumber = 4;

	//�F�ύX���x
//	constexpr int kColorChangeSpeed = 5;
}

Switch::Switch(VECTOR pos) : 
	m_Pos(pos),
	m_colorNum(2) // �Ԃ̐��l��2�̂��ߏ�������2������
{
}

Switch::~Switch()
{
}

void Switch::Update()
{
	if (m_colorNum == kRedNumber)
	{
		m_Color.x = 255;
		m_Color.y = 0;
		m_Color.z = 0;
	}

	if (m_colorNum == kBlueNumber)
	{
		m_Color.x = 0;
		m_Color.y = 0;
		m_Color.z = 255;
	}

	if (m_colorNum == kGreenNumber)
	{
		m_Color.x = 0;
		m_Color.y = 255;
		m_Color.z = 0;
	}
}

void Switch::Draw()
{
	DrawSphere3D(m_Pos, kColRadius,50,
		GetColor(m_Color.x, m_Color.y, m_Color.z),
		GetColor(m_Color.x, m_Color.y, m_Color.z),
		true);
}

float Switch::GetRadius()
{
	return kColRadius * 1.5f; //�V���b�g�𓖂Ă₷�����邽��
}

#pragma once
#include<DxLib.h>
#include<array>
class Switch
{
public:
	Switch(VECTOR pos, std::array<int, 3> model);

	virtual ~Switch();

	void Update();

	void Draw();

	VECTOR GetPos() { return m_Pos; }

	float GetRadius();

	void SetColorNum(int colorNum) { m_colorNum = colorNum; }

private:
	VECTOR m_Pos;//���݈ʒu

	int m_colorNum;	//�F�ԍ�(�ԍ��ɂ���ĐF���ς��)

	std::array<int, 3> m_modelHandle;
};


#pragma once
#include<DxLib.h>
class Switch
{
public:
	Switch(VECTOR pos);

	virtual ~Switch();

	void Update();

	void Draw();

	VECTOR GetPos() { return m_Pos; }

	float GetColRadius();

	void SetColorNum(int colorNum) { m_colorNum = colorNum; }

private:
	VECTOR m_Pos;//���݈ʒu

	VECTOR m_Color;//�F���(RGB)

	int m_colorNum;	//�F�ԍ�(�ԍ��ɂ���ĐF���ς��)
};


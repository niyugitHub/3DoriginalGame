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
	VECTOR m_Pos;//現在位置

	VECTOR m_Color;//色情報(RGB)

	int m_colorNum;	//色番号(番号によって色が変わる)
};


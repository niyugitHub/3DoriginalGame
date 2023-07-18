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
	VECTOR m_Pos;//現在位置

	int m_colorNum;	//色番号(番号によって色が変わる)

	std::array<int, 3> m_modelHandle;
};


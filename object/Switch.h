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
	VECTOR m_Pos;//Œ»İˆÊ’u

	int m_colorNum;	//F”Ô†(”Ô†‚É‚æ‚Á‚ÄF‚ª•Ï‚í‚é)

	std::array<int, 3> m_modelHandle;
};


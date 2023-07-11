#pragma once
#include<DxLib.h>
class Goal
{
public:
	Goal(VECTOR pos);

	virtual ~Goal();

	void Update();

	void Draw();

	float GetRadius();

	VECTOR GetPos() { return m_Pos; }
private:
	VECTOR m_Pos;//���݈ʒu

	int m_modelHandle = -1;
};

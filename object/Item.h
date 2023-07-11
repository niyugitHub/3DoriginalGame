#pragma once
#include<DxLib.h>
class Item
{
public:
	Item(VECTOR pos);
	~Item();

	void Update();
	void Draw();
	float GetRadius();

	VECTOR GetPos() { return m_Pos; }

	bool GetExist() { return m_Exist; }
	void SetExist(bool exist) { m_Exist = exist; };
	VECTOR m_Pos;//���݈ʒu

	bool m_Exist = true;//���݊m�F

private:
	int m_modelHandle = -1;
	float m_vecY;
	float m_size;

};


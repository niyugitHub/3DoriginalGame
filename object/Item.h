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
	void SetExist() { m_Exist = false; }
private:
	VECTOR m_Pos;//現在位置

	bool m_Exist = true;//存在確認
};


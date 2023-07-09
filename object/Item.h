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

private:
	VECTOR m_Pos;//åªç›à íu

	bool m_Exist;//ë∂ç›ämîF
};


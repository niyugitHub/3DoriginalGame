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
	void Spawn() { m_Exist = true; }
	void Get() { m_Exist = false; }

	void Reset(bool exist);

private:
	VECTOR m_Pos; //アイテム座標

	int m_modelHandle = -1;
	float m_vecY;
	float m_size;

	float m_changeSizeSpeed; //モデルサイズの変更スピード

	bool m_Exist; //存在するか
};
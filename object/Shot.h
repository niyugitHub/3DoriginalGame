#pragma once
#include<DxLib.h>

class Shot
{
public:
	Shot(VECTOR pos, VECTOR vec);

	virtual ~Shot();

	void Update(VECTOR PlayerPos);

	void Draw();

	VECTOR GetPos() { return m_Pos; }
	VECTOR GetlastPos() { return m_lastPos; }

	// 半径の取得
	float GetRadius() const;

	void SetExist(bool exist) { m_Exist = exist; }
	bool GetExist() { return m_Exist; }

private:
	VECTOR m_Pos; // 現在位置

	VECTOR m_lastPos; // 前のフレームの位置

	VECTOR m_Vec;// 移動量

	bool m_Exist;//存在するかどうか
};


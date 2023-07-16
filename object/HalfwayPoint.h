#pragma once
#include<DxLib.h>
class HalfwayPoint
{
public:
	HalfwayPoint(VECTOR pos);

	virtual ~HalfwayPoint();

	void Reset();

	void Update();

	void Draw();

	float GetRadius();

	VECTOR GetPos() { return m_Pos; }

	bool IsCollision() { return m_isCollision; }
	void OnCollision() { m_isCollision = true; }

	void ChangeModel();
private:
	VECTOR m_Pos;//現在位置

	//当たり判定
	bool m_isCollision = false;

	//モデルハンドル
	int m_modelHandle = -1;
	int m_modelHandleAfter = -1;
	int m_modelHandleBefore = -1;
	
	//モデル回転率
	float m_modelRot;

	float m_rotSpeed;//回転スピード
};



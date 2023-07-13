#pragma once
#include<DxLib.h>
class HalfwayPoint
{
public:
	HalfwayPoint(VECTOR pos);

	virtual ~HalfwayPoint();

	void Update();

	void Draw();

	float GetRadius();

	VECTOR GetPos() { return m_Pos; }

	bool IsCollision() { return m_isCollision; }
	void OnCollision() { m_isCollision = true; }
private:
	VECTOR m_Pos;//åªç›à íu

	//ìñÇΩÇËîªíË
	bool m_isCollision = false;

	int m_modelHandle = -1;
};



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
	VECTOR m_Pos;//���݈ʒu

	//�����蔻��
	bool m_isCollision = false;

	//���f���n���h��
	int m_modelHandle = -1;
	int m_modelHandleAfter = -1;
	int m_modelHandleBefore = -1;
	
	//���f����]��
	float m_modelRot;

	float m_rotSpeed;//��]�X�s�[�h
};



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

	// ���a�̎擾
	float GetRadius() const;

	void SetExist(bool exist) { m_Exist = exist; }
	bool GetExist() { return m_Exist; }

private:
	VECTOR m_Pos; // ���݈ʒu

	VECTOR m_lastPos; // �O�̃t���[���̈ʒu

	VECTOR m_Vec;// �ړ���

	bool m_Exist;//���݂��邩�ǂ���
};


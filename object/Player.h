#pragma once
#include<DxLib.h>
#include<memory>
#include<vector>
#include"Vec2.h"

class Model;
class Shot;

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update();
	void Draw();

	VECTOR GetPos() { return m_Pos; }
	VECTOR GetNextPos() { return m_NextPos; }

	float GetRadius();

	void SetcolFieldY(bool colFieldY) { m_colFieldY = colFieldY; }

	void SetcolFieldXZ(bool colFieldXZ) { m_colFieldXZ = colFieldXZ; }

	std::vector<Shot*> GetShot() { return m_pShot; }

private:
	void updateIdle();
	void updateMove();
	void updateJump();
	void updateShot();
	void IsMove(bool Left,bool Up,bool Right,bool Bottom, float MoveSpeed);
	void IsAngle(bool Left, bool Up, bool Right, bool Bottom);
	Vec2 IsShot(Vec2 ShotSpeed);


private:
	//�v���C���[�̃��f��
	std::shared_ptr<Model> m_pModel;
	
	int m_modelHandle; // ���f���n���h��

	float m_cameraPos;

	VECTOR m_Pos; // �v���C���[�̍��W

	VECTOR m_NextPos; // ���̃t���[���̃v���C���[�̍��W

	VECTOR m_Vec; // �v���C���[�̈ړ����x

	// �Đ����Ă���A�j���[�V�����ԍ�
	int m_animNo;

	//�t���[���J�E���g
	int m_frameCount;

	//�v���C���[�̌����Ă������
	float m_angle;

	//�t�B�[���h�Ƃ̓�����y����
	bool m_colFieldY;

	//�t�B�[���h�Ƃ̓����蔻��XZ
	bool m_colFieldXZ;

	//�����o�֐��|�C���^
	void (Player::* m_updateFunc)();

	std::vector<Shot*> m_pShot;
};


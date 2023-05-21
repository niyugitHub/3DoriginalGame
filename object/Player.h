#pragma once
#include<DxLib.h>
#include<memory>
#include<vector>

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

	float GetColRadius();

	void SetcolFieldY(bool colFieldY) { m_colFieldY = colFieldY; }

	void SetcolFieldXZ(bool colFieldXZ) { m_colFieldXZ = colFieldXZ; }

private:
	void updateIdle();
	void updateMove();
	void updateJump();
	void updatePunch();
	void IsMove(bool Left,bool Up,bool Right,bool Bottom, float MoveSpeed);
	void IsAngle(bool Left, bool Up, bool Right, bool Bottom);


private:
	int m_modelHandle; // ���f���n���h��

	VECTOR m_Pos; // �v���C���[�̍��W

	VECTOR m_NextPos; // ���̃t���[���̃v���C���[�̍��W

	VECTOR m_Vec; // �v���C���[�̈ړ����x

	float m_cameraPos;

	//�����o�֐��|�C���^
	void (Player::* m_updateFunc)();

	//�v���C���[�̃��f��
	std::shared_ptr<Model> m_pModel;


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

	//�V���b�g�̃|�C���^�[
//	std::vector<std::shared_ptr<Shot>> m_pShot;
};


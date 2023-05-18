#pragma once
#include<DxLib.h>
#include<memory>

class Model;

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update();
	void Draw();

	VECTOR GetPos() { return m_Pos; }

private:
	void updateIdle();
	void updateMove();
	void updateJump();

	void IsMove(bool Left,bool Up,bool Right,bool Bottom);
	void IsAngle(bool Left, bool Up, bool Right, bool Bottom);

private:
	int m_modelHandle;

	VECTOR m_Pos; // �v���C���[�̃T�C�Y

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
};


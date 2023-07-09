#pragma once
#include<DxLib.h>
#include<memory>
#include<vector>
#include "../util/Vec2.h"

class Model;
class Shot;

class Player
{
public:
	Player(VECTOR pos);
	virtual ~Player();

	void Init();
	void Update();
	void Draw();

	VECTOR GetPos() { return m_Pos; }
//	void SetPos(VECTOR pos) { m_Pos = m_NextPos = pos; }
	VECTOR GetNextPos() { return m_NextPos; }

	float GetRadius();

	void SetcolFieldY(bool colFieldY) { m_colFieldY = colFieldY; }

	void SetcolFieldXZ(bool colFieldXZ) { m_colFieldXZ = colFieldXZ; }

	void ClearUpdate(); //�N���A�����Ƃ��̃A�b�v�f�[�g

	void ClearCharaMotion(); //�N���A�����Ƃ��̃L�����N�^�[�̓����ύX

	void SetAttackFlag(bool attackFlag) { m_isAttackFlag = attackFlag; }
	bool GetAttackFlag() { return m_isAttackFlag; }

private:
	void updateIdle();	//�A�C�h����Ԏ��̃A�b�v�f�[�g
	void updateMove();	//�ړ���Ԏ��̃A�b�v�f�[�g
	void updateJump();	//�W�����v��Ԏ��̃A�b�v�f�[�g
	void updatePunch(); //�U����Ԏ��̃A�b�v�f�[�g

	void SetAttackPos();
	
	//�ړ����̏���
	void IsMove(bool Left,bool Up,bool Right,bool Bottom, float MoveSpeed);
	//�v���C���[�̌����̏���
	void IsAngle(bool Left, bool Up, bool Right, bool Bottom);
	//�v���C���[�̌����ɂ���ẴV���b�g�̕�������
	Vec2 IsShot(Vec2 ShotSpeed);

private:
	//�����o�֐��|�C���^
	void (Player::* m_updateFunc)();
	
	int m_modelHandle; // ���f���n���h��
	
	// �Đ����Ă���A�j���[�V�����ԍ�
	int m_animNo;
	
	//�v���C���[�̌����Ă������
	float m_angle;

	//�J�����̌����Ă������
	float m_cameraAngle;

	//�t�B�[���h�Ƃ̓�����y����
	bool m_colFieldY;

	//�t�B�[���h�Ƃ̓����蔻��XZ
	bool m_colFieldXZ;
	
	VECTOR m_Pos; // �v���C���[�̍��W
	
	VECTOR m_NextPos; // ���̃t���[���̃v���C���[�̍��W
	
	VECTOR m_attackPos;//�U�����W
	
	VECTOR m_Vec; // �v���C���[�̈ړ����x
	
	//�v���C���[�̃��f��
	std::shared_ptr<Model> m_pModel;

	//�U�������ǂ���
	bool m_isAttackFlag = false;
};


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

	std::vector<Shot*> GetShot() { return m_pShot; } //�V���b�g�̏��擾

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
	//�v���C���[�̃��f��
	std::shared_ptr<Model> m_pModel;
	
	int m_modelHandle; // ���f���n���h��

	VECTOR m_cameraPos; //�J�����|�W�V����

	VECTOR m_cameraTargetPos; //�J�����^�[�Q�b�g

	VECTOR m_Pos; // �v���C���[�̍��W

	VECTOR m_NextPos; // ���̃t���[���̃v���C���[�̍��W

	VECTOR m_Vec; // �v���C���[�̈ړ����x

	VECTOR m_attackPos;//�U�����W

	// �Đ����Ă���A�j���[�V�����ԍ�
	int m_animNo;

	//�t���[���J�E���g
	int m_frameCount;

	//�v���C���[�̌����Ă������
	float m_angle;

	//�J�����̌����Ă������
	float m_cameraAngle;

	//�t�B�[���h�Ƃ̓�����y����
	bool m_colFieldY;

	//�t�B�[���h�Ƃ̓����蔻��XZ
	bool m_colFieldXZ;

	//�����o�֐��|�C���^
	void (Player::* m_updateFunc)();

	// �V���b�g�̃|�C���^
	std::vector<Shot*> m_pShot;

	//�p�b�h�A�i���O���擾
	DINPUT_JOYSTATE m_input;

	int m_inputX;//X�����
	int m_inputZ;//Y�����

	//�U�������ǂ���
	bool m_isAttackFlag = false;
};


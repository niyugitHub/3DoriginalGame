#pragma once
#include <Dxlib.h>
#include <vector>
#include <memory>
class Model
{
public:
	//�t�@�C�������w�肵�ă��[�h���s��
	Model(const char* fileName);
	//�w�肳�ꂽ�n���h���̃��f����DuplicateModel���Đ�������
	Model(int orgModel);
	virtual ~Model();

	// �����蔻��ݒ�
	void setUseCollision(bool isUse, bool isNeedUpdate);

	void update();
	void draw();

	//���f���n���h���擾
	int getModelHandle() const { return m_modelHandle; }

	// �����蔻��Ɏg�p����t���[���C���f�b�N�X���擾����
	int getColFrameIndex() const { return m_colFrameIndex; }

	//�\���ʒu�̐ݒ�
	void setPos(VECTOR pos);

	VECTOR GetPos() { return m_Pos; }

	// ��]��Ԃ̐ݒ�
	void setRot(VECTOR rot);

	// �A�j���[�V�����̐���

	/// <summary>
	/// �A�j���[�V������ݒ肷��(�ς��Ɛ؂�ւ���)
	/// </summary>
	/// <param name="animNo">�ύX��A�j���[�V�����ԍ�</param>
	/// <param name="isLoop">�A�j���[�V���������[�v�����邩</param>
	/// <param name="isForceChange">���łɎw�肳�ꂽ�A�j�����Đ�����Ă���ꍇ���ύX���邩</param>
	void setAnimation(int animNo, bool isLoop, bool isForceChange);

	// �A�j���[�V������ω�������(changeFrame�t���[�������Đ؂�ւ���)
	void changeAnimation(int animNo, bool isLoop, bool isForceChange, int changeFrame);

	// ���݂̃A�j���[�V�������I�����Ă��邩�ǂ������擾����(Loop�A�j���̏ꍇ�͎擾�ł��Ȃ� = false��Ԃ�)
	bool isAnimEnd();

	//�f�o�b�O�p�����蔻��
	void SetDebugHandle(int handle);

private:
	//�A�j���[�V�������
	struct AnimData
	{
		int animNo;			// �A�j���[�V�����ԍ�

		int attachNo;		// �A�^�b�`�ԍ�
		float totalTime;	// �A�j���[�V�����̑��Đ�����
		bool isLoop;		// �A�j���[�V���������[�v���邩
	};
private:
	//���f���̈ʒu
	VECTOR m_Pos;
	// �A�j���[�V�����f�[�^�̃N���A
	void clearAnimData(AnimData& anim);

	// �A�j���[�V�����̍X�V
	void updateAnim(AnimData anim, float dt = 1.0f);

	// ���݂̃A�j���[�V�����؂�ւ���񂩂�A�j���[�V�����̃u�����h����ݒ肷��
	void updateAnimBlendRate();

private:
	// ���f���̃n���h��
	int m_modelHandle;

	// �����蔻������g�p����
	bool m_isUseCollision;
	// �����蔻����𖈃t���[���X�V����
	bool m_isUpdateCollision;
	// �����蔻��Ƃ��Ďg�p����t���[���̃C���f�b�N�X
	int m_colFrameIndex;

	// �A�j���[�V�����ύX���x
	int m_animSpeed;

	// �A�j���[�V�����̃A�^�b�`�ԍ�
	AnimData m_animPrev;	// �ύX�O�A�j���[�V�������
	AnimData m_animNext;	// �ύX��A�j���[�V�����f�[�^

	//�A�j���[�V�����̐؂�ւ����
	int m_animChangeFrame;			// ���݂̐؂�ւ��t���[����
	int m_animChangeFrameTotal;		// �؂�ւ��ɂ����鑍�t���[����




	//�f�o�b�O�p�ϐ�
	bool debugModelChange = false;
};


#include "Model.h"
#include <assert.h>

namespace
{
	// �����蔻��Ƃ��Ďg�p����t���[���̖��O
	const char* const kCollisionFrameName = "Cube_Grass_Single";
}

Model::Model(const char* fileName) :
	m_isUseCollision(false),
	m_isUpdateCollision(false),
	m_modelHandle(-1),
	m_animChangeFrame(0),
	m_animChangeFrameTotal(0),
	m_animSpeed(0)
{
	m_Pos = { 0,0,0 };
	m_modelHandle = MV1LoadModel(fileName);
	//�R�s�[�Ɏ��s�����ꍇ
	assert(m_modelHandle != -1);
	//�A�j���[�V�����f�[�^�̃N���A
	clearAnimData(m_animPrev);
	clearAnimData(m_animNext);
}

Model::Model(int orgModel) :
	m_animChangeFrame(0),
	m_modelHandle(-1),
	m_animChangeFrameTotal(0)
{
	m_modelHandle = MV1DuplicateModel(orgModel);
	//���[�h�Ɏ��s�������f�����R�s�[���Ƃ��Ďw�肳��Ă���
	assert(m_modelHandle != -1);
	//�A�j���[�V�����f�[�^�̃N���A
	clearAnimData(m_animPrev);
	clearAnimData(m_animNext);
}

Model::~Model()
{
	if (m_isUseCollision)
	{
		// �����蔻������g�p���Ă�����j������
		MV1TerminateCollInfo(m_modelHandle, -1);
		m_isUseCollision = false;
	}
	MV1DeleteModel(m_modelHandle);
}

void Model::setUseCollision(bool isUse, bool isNeedUpdate)
{
	// �����蔻����g��Ȃ��̂ɓ����蔻��̍X�V�𖈃t���[���s�������A���͂���
	assert(isUse || (!isNeedUpdate));

	if (m_isUseCollision != isUse)
	{
		if (isUse)
		{
			// �g��Ȃ����g��
			// �����蔻��p�t���[������������
			m_colFrameIndex = MV1SearchFrame(m_modelHandle, kCollisionFrameName);
			if (m_colFrameIndex < 0) // ������Ȃ����� or �G���[
			{
				m_colFrameIndex = -1;
			}

			MV1SetupCollInfo(m_modelHandle, m_colFrameIndex, 8, 8, 8);
		}
		else
		{
			// �g�����g��Ȃ�
			MV1TerminateCollInfo(m_modelHandle, -1);
		}
	}

	m_isUseCollision = isUse;
	m_isUpdateCollision = isNeedUpdate;
}

void Model::update()
{
	m_animSpeed++;
	if (m_animSpeed >= m_animChangeFrameTotal)
	{
		updateAnim(m_animPrev);
		updateAnim(m_animNext);
		m_animSpeed = 0;
	}

	//�w��t���[���ɂ����ăA�j���[�V������ύX����
	m_animChangeFrame++;
	if (m_animChangeFrame > m_animChangeFrameTotal)
	{
		m_animChangeFrame = m_animChangeFrameTotal;
	}
	//�A�j���[�V�����̃u�����h����ݒ肷��
	updateAnimBlendRate();

	// �����蔻��f�[�^�̍X�V
	if (m_isUseCollision && m_isUpdateCollision)
	{
		MV1RefreshCollInfo(m_modelHandle, m_colFrameIndex);
	}
}

void Model::draw()
{
	MV1DrawModel(m_modelHandle);
}

void Model::setPos(VECTOR pos)
{
	m_Pos = pos;
	MV1SetPosition(m_modelHandle, m_Pos);
}

void Model::setRot(VECTOR rot)
{
	MV1SetRotationXYZ(m_modelHandle, rot);
}

void Model::setAnimation(int animNo, bool isLoop, bool isForceChange)
{
	if (!isForceChange)
	{
		// ���łɍĐ�����Ă���A�j���͍Đ����Ȃ�
		if (m_animNext.animNo == animNo) return;
	}

	// �ȑO�̃A�j���[�V�������c���Ă���ΏI��
	if (m_animPrev.attachNo != -1)
	{
		MV1DetachAnim(m_modelHandle, m_animPrev.attachNo);
		clearAnimData(m_animPrev);
	}
	if (m_animNext.attachNo != -1)
	{
		MV1DetachAnim(m_modelHandle, m_animNext.attachNo);
		clearAnimData(m_animNext);
	}

	// �V�����A�j���[�V������ݒ�
	m_animNext.animNo = animNo;
	m_animNext.attachNo = MV1AttachAnim(m_modelHandle, animNo, -1, false);
	m_animNext.totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_animNext.attachNo);
	m_animNext.isLoop = isLoop;

	// �ύX�ɂ�����t���[�������o���Ă���
	m_animChangeFrameTotal = 1;
	m_animChangeFrame = 1;
}

void Model::changeAnimation(int animNo, bool isLoop, bool isForceChange, int changeFrame)
{
	if (!isForceChange)
	{
		// ���łɍĐ�����Ă���A�j���͍Đ����Ȃ�
		if (m_animNext.animNo == animNo) return;
	}


	// �ȑO�̃A�j���[�V�������c���Ă���ΏI��
	if (m_animPrev.attachNo != -1)
	{
		MV1DetachAnim(m_modelHandle, m_animPrev.attachNo);
		clearAnimData(m_animPrev);
	}
	// ���ݍĐ����Ă���A�j���[�V�������Â��A�j���Ƃ���
	m_animPrev = m_animNext;
	// �V�����A�j���[�V������ݒ�
	m_animNext.animNo = animNo;
	m_animNext.attachNo = MV1AttachAnim(m_modelHandle, animNo, -1, false);
	m_animNext.totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_animNext.attachNo);
	m_animNext.isLoop = isLoop;

	// �ύX�ɂ�����t���[�������o���Ă���
	m_animChangeFrameTotal = changeFrame;
	m_animChangeFrame = 0;

	// �A�j���[�V�����̃u�����h����ݒ肷��
	updateAnimBlendRate();
}

bool Model::isAnimEnd()
{
	// Loop�A�j���̏ꍇ�͏��false��Ԃ�
	if (m_animNext.isLoop) return false;

	float time = MV1GetAttachAnimTime(m_modelHandle, m_animNext.attachNo);
	if (time >= m_animNext.totalTime)
	{
		return true;
	}

	return false;
}

void Model::clearAnimData(AnimData& anim)
{
	anim.animNo = -1;
	anim.attachNo = -1;
	anim.totalTime = 0.0f;
	anim.isLoop = false;
}

void Model::updateAnim(AnimData anim, float dt)
{
	// �A�j���[�V�������ݒ肳��Ă��Ȃ��ꍇ�͉������Ȃ�
	if (anim.attachNo == -1) return;

	// �A�j���[�V�����̍X�V
	float time = MV1GetAttachAnimTime(m_modelHandle, anim.attachNo);
	time += dt;
	if (time > anim.totalTime)
	{
		if (anim.isLoop)
		{
			// �A�j���[�V�����̃��[�v
			time -= anim.totalTime;
		}
		else
		{
			time = anim.totalTime;
		}
	}
	MV1SetAttachAnimTime(m_modelHandle, anim.attachNo, time);
}

void Model::updateAnimBlendRate()
{
	// �A�j���[�V�����ω��̃t���[�����ɉ������u�����h����ݒ肷��
	float rate = static_cast<float>(m_animChangeFrame) / static_cast<float>(m_animChangeFrameTotal);
	if (rate > 1.0f)	rate = 1.0f;

	MV1SetAttachAnimBlendRate(m_modelHandle, m_animPrev.attachNo, 1.0f - rate);
	MV1SetAttachAnimBlendRate(m_modelHandle, m_animNext.attachNo, rate);
}
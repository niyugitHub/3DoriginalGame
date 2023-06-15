#include "SaveData.h"
#include <cstdio>
#include<DxLib.h>


namespace
{
	//�X�e�[�W��
	constexpr int kStageNum = 10;

	//1�X�e�[�W�̃X�^�[�̐�
	constexpr int kStarNum = 3;

	// �X�e�[�W���Ƃ̃X�^�[�̎擾���
	bool kGetStar[kStageNum][kStarNum];
}

void SaveData::Init()
{
	for (int i = 0; i < kStageNum; i++)
	{
		for (int j = 0; j < kStarNum; j++)
		{
			kGetStar[i][j] = false;
		}
	}
}

void SaveData::Update(int stageNum,  bool getStar[])
{
	//kGetStar�ɃX�^�[���擾�������ǂ����̏���^����
	for (int i = 0; i < kStarNum; i++)
	{
		kGetStar[stageNum][i] = getStar[i];
	}

	Write();//�X�^�[��񏑂�����
	Read();//�X�^�[���ǂݍ���
}

void SaveData::Read()
{
	FILE* fp = nullptr;

	// �o�C�i���f�[�^�ւ̓ǂݍ��݃��[�h�ŊJ��
	fopen_s(&fp, "SaveData.bin", "rb");

	// nullptr�Ȃ�ُ�I��
	if (!fp) return;

	//// �f�[�^�̓ǂݍ��݂��s��
	fread(&kGetStar, sizeof(kGetStar), 1, fp);

	fclose(fp);
}

void SaveData::Write()
{
	FILE* fp = nullptr;

	// �o�C�i���f�[�^�ւ̏������݃��[�h�ŊJ��
	fopen_s(&fp, "SaveData.bin", "wb");

	// nullptr�Ȃ�ُ�I��
	if (!fp)		return;

	//�X�^�[�f�[�^
	//kGetStar.resize(kGetStar);

	// �w�b�_�[�f�[�^���o�͂��� ���܂������[���ŏo�͂���
	fwrite(&kGetStar, sizeof(kGetStar), 1, fp);

	// �f�[�^�����̏o�́@�}�b�v�̑傫���ɂ���ăf�[�^�T�C�Y�ς��
	//fwrite(kGetStar.data(), kGetStar.size, 1, fp);

	fclose(fp);
}

void SaveData::Draw()
{
	for (int i = 0; i < kStageNum; i++)
	{
		for (int j = 0; j < kStarNum; j++)
		{
			printfDx("%d ", kGetStar[i][j]);
		}
		printfDx("\n");
	}
}


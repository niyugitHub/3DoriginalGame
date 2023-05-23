#include "FieldBase.h"
#include "Model.h"
#include"Pad.h"
#include"../Switch.h"
#include<cassert>
#include <iostream>


namespace
{
	//�t�@�C����
	const char* const kFileName1 = "data/field.mv1";
	const char* const kFileName2 = "data/fieldRed.mv1";
	const char* const kFileName3 = "data/fieldBlue.mv1";

	//�n�ʂɕ~���l�߂�u���b�N�̐�
	constexpr int kBlockNumX = 10;
	constexpr int kBlockNumZ = 10;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	//�u���b�N�̈�ӂ̒���
	constexpr float kBlockSideLength = 200.0f;

	//�n�ʂ̈�ӂ̒���
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;
}

FieldBase::FieldBase() : 
	m_lookBlock(1)
{
	
	////3D���f�������[�h
	//m_pModel.push_back(std::make_shared<Model>(kFileName));
	//m_pModel.back()->setUseCollision(true, true);

	////�ŏ��Ƀ��[�h�������f���ƍ��킹�ă��f����100����
	//int orgModel = m_pModel[0]->getModelHandle();
	//for (int i = 0; i < kBlockNum - 1; i++)
	//{
	//	m_pModel.push_back(std::make_shared<Model>(orgModel));
	//	m_pModel.back()->setUseCollision(true, true);
	//}

	////�n�ʂɕ��ׂ�
	//for (int i = 0; i < m_pModel.size(); i++)
	//{
	//	float x = 200.0f * (i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
	//	float z = 200.0f * (i / kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
	//	m_pModel[i]->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//��ʂ�y=0.0f�ɂȂ�悤�ɔz�u
	//}
}

FieldBase::~FieldBase()
{
	
}

void FieldBase::Init()
{
}

void FieldBase::Update()
{
	for (auto& model : m_pModel)
	{
		model->update();
	}

	for (auto& model : m_pModelRed)
	{
		model->update();
	}

	for (auto& model : m_pModelBlue)
	{
		model->update();
	}

	for (auto& Switch : m_pSwitch)
	{
		Switch->SetColorNum(m_lookBlock);
		Switch->Update();
	}
}

void FieldBase::Draw()
{
	for (auto& model : m_pModel)
	{
		model->draw();
		DrawString(500, 0, "���ӂ����G����", 0xffffff);
	}

	if (m_lookBlock == kRed)
	{
		for (auto& model : m_pModelRed)
		{
			model->draw();
			DrawString(500, 0, "��", 0xffffff);
		}
	}

	if (m_lookBlock == kBlue)
	{
		for (auto& model : m_pModelBlue)
		{
			model->draw();
			DrawString(500, 0, "��", 0xffffff);
		}
	}

	for (auto& Switch : m_pSwitch)
	{
		Switch->Draw();
	}
}

void FieldBase::FirstModelLoad()
{
	//3D���f�������[�h
	m_pModel.push_back(std::make_shared<Model>(kFileName1));
	m_pModel.back()->setPos(VGet(200.0f, -10000.0f, 200.0f));
	m_pModel.back()->setUseCollision(true, true);

	//3D���f�������[�h
	m_pModel.push_back(std::make_shared<Model>(kFileName2));
	m_pModel.back()->setPos(VGet(200.0f, -10000.0f, 200.0f));
	m_pModel.back()->setUseCollision(true, true);

	//3D���f�������[�h
	m_pModel.push_back(std::make_shared<Model>(kFileName3));
	m_pModel.back()->setPos(VGet(200.0f, -10000.0f, 200.0f));
	m_pModel.back()->setUseCollision(true, true);
}

void FieldBase::LoadFile(const char* fileName)
{
	// csv�t�@�C����ǂݍ���Ő����̔z��ɂ�����
	FILE* fp;

	if (fopen_s(&fp, fileName, "rt") != 0)
	{
		std::cout << "�t�@�C���ǂݍ��ݎ��s";
		return;	// �ُ�I��
	}

	int chr;

	// chr = fgetc(fp)	�t�@�C������1�����ǂݍ����int�ɂ���chr�ɓ����
	//					chr��53('5'�̕����R�[�h)������
	//					���̌�t�@�C���ʒu�w��q��i�߂�
	//					(����fgetc�����Ƃ��͍���ǂݍ��񂾕����̎����ǂݍ��܂��)

	// chr != FOF		53��EOF�̔�r���s����
	//					EOF -> End Of File		�t�@�C���̏I�[

	int wNum = -1;	// ���m��
	// ���̗v�f��������p
	int tempW = 0;

	int tempNum = 0;
	while (true)
	{
		chr = fgetc(fp);	// 1�����ǂݍ���
		// ��؂蕶������������
		if (chr == ',' ||
			chr == '\n' ||
			chr == EOF)
		{
			// dataTbl�Ƀf�[�^������
			m_blockNum.push_back(tempNum);
			tempNum = 0;

			// �t�@�C���̏I�[�ɗ�����I��
			if (chr == EOF)
			{
				break;
			}
			else if (chr == ',')
			{
				tempW++;	// �v�f��������
			}
			else   // chr == '\n'
			{
				tempW++;	// �v�f��������
				if (wNum < 0)
				{
					wNum = tempW;	// �v�f���m��
				}
				/*else
				{
					assert(wNum == tempW);
				}*/
				tempW = 0;
			}
			// �܂��I����ĂȂ��̂ő����ēǂݍ���
			continue;
		}

		// �f�[�^�͐����݂̂̂͂�
		assert(chr >= '0' && chr <= '9');

		// �����Ȃ̂͊m��
		// ������𐔒l�ɕϊ�������

		// 268��ǂݍ���
		// 1�����ڂ�'2'	����𐔒l�ɕϊ����Ă����
		// 2�����ڂ�'6'	tempNum��2 20 + 6  tempNum = 26
		// 3�����ڂ�'8' tempNum��26 260+ 8 tempNum = 268
		tempNum = (tempNum * 10) + chr - '0';

		// �f�[�^�̋�؂肪�����������_�ł����܂ł��f�[�^�̂ЂƂ܂Ƃ܂�

	}
	// �t�@�C�������
	fclose(fp);
}

void FieldBase::ModelLoad(int Model1, int Model2, int Model3)
{
	//�n�ʂɕ��ׂ�
	for (int i = 0; i < m_blockNum.size(); i++)
	{
		if (m_blockNum[i] == 8)
		{
			m_pModel.push_back(std::make_shared<Model>(Model1));
			m_pModel.back()->setUseCollision(true, true);
			float x = 200.0f * static_cast<float>(i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			float z = 200.0f * static_cast<float>(i / kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			m_pModel.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//��ʂ�y=0.0f�ɂȂ�悤�ɔz�u

			m_pSwitch.push_back(std::make_shared<Switch>(VGet(x, 100, z)));
			continue;
		}

		if (m_blockNum[i] == kField)
		{
			m_pModel.push_back(std::make_shared<Model>(Model1));
			m_pModel.back()->setUseCollision(true, true);
			float x = 200.0f * static_cast<float>(i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			float z = 200.0f * static_cast<float>(i / kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			m_pModel.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//��ʂ�y=0.0f�ɂȂ�悤�ɔz�u
			continue;
		}

		if (m_blockNum[i] == kRed)
		{
			m_pModelRed.push_back(std::make_shared<Model>(Model2));
			m_pModelRed.back()->setUseCollision(true, true);
			float x = 200.0f * static_cast<float>(i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			float z = 200.0f * static_cast<float>(i / kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			m_pModelRed.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//��ʂ�y=0.0f�ɂȂ�悤�ɔz�u
			continue;
		}

		if (m_blockNum[i] == kBlue)
		{
			m_pModelBlue.push_back(std::make_shared<Model>(Model3));
			m_pModelBlue.back()->setUseCollision(true, true);
			float x = 200.0f * static_cast<float>(i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			float z = 200.0f * static_cast<float>(i / kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			m_pModelBlue.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//��ʂ�y=0.0f�ɂȂ�悤�ɔz�u
			continue;
		}
	}
}

void FieldBase::ChangeBlock()
{
	m_lookBlock++;
	if (m_lookBlock >= 4)
	{
		m_lookBlock = 2;
	}
}

float FieldBase::GetFieldSizeX()
{
	return kFieldSideLengthX;
}

float FieldBase::GetFieldSizeZ()
{
	return kFieldSideLengthZ;
}

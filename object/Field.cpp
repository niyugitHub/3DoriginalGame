#include "Field.h"
#include "Model.h"

namespace
{
	//�t�@�C����
	const char* const kFileName = "data/field.mv1";

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

Field::Field()
{
	
	//3D���f�������[�h
	m_pModel.push_back(std::make_shared<Model>(kFileName));
	m_pModel.back()->setUseCollision(true, true);

	//�ŏ��Ƀ��[�h�������f���ƍ��킹�ă��f����100����
	int orgModel = m_pModel[0]->getModelHandle();
	for (int i = 0; i < kBlockNum - 1; i++)
	{
		m_pModel.push_back(std::make_shared<Model>(orgModel));
		m_pModel.back()->setUseCollision(true, true);
	}

	//�n�ʂɕ��ׂ�
	for (int i = 0; i < m_pModel.size(); i++)
	{
		float x = 200.0f * (i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
		float z = 200.0f * (i / kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
		m_pModel[i]->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//��ʂ�y=0.0f�ɂȂ�悤�ɔz�u
	}
}

Field::~Field()
{

}

void Field::Init()
{
}

void Field::Update()
{
	for (auto& model : m_pModel)
	{
		model->update();
	}
}

void Field::Draw()
{
	for (auto& model : m_pModel)
	{
		model->draw();
	}
}

float Field::GetFieldSizeX()
{
	return kFieldSideLengthX;
}


float Field::GetFieldSizeZ()
{
	return kFieldSideLengthZ;
}
#include "Field1.h"
#include "Model.h"
#include"../Switch.h"

namespace
{
	const char* const kFileStage = "data/stage/stage1.csv";
//	const char* const kFileName2 = "data/fieldGreen.mv1";

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

Field1::Field1()
{
	Init(kFileStage,kRed,kBlue);
}

Field1::~Field1()
{
	m_pModel.erase(m_pModel.begin(), m_pModel.end());
	m_pModelRed.erase(m_pModelRed.begin(), m_pModelRed.end());
	m_pModelBlue.erase(m_pModelBlue.begin(), m_pModelBlue.end());
}

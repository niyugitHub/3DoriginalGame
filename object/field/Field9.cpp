#include "Field9.h"

namespace
{
	const char* const kFileStage = "data/stage/stage9.csv";
	//	const char* const kFileName2 = "data/fieldGreen.mv1";

	//�n�ʂɕ~���l�߂�u���b�N�̐�
	constexpr int kBlockNumX = 40;
	constexpr int kBlockNumZ = 15;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	//�u���b�N�̈�ӂ̒���
	constexpr float kBlockSideLength = 200.0f;

	//�n�ʂ̈�ӂ̒���
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;
}

Field9::Field9()
{
	m_stageNum = 9;
	m_data.fileName = kFileStage;
	m_lookBlock = kRed;
	m_blockKinds = kGreen;
	m_data.blockNumX = kBlockNumX;
	m_data.blockNumZ = kBlockNumZ;

	Init(m_data);
}

Field9::~Field9()
{
	m_pModel.erase(m_pModel.begin(), m_pModel.end());
	m_pModelRed.erase(m_pModelRed.begin(), m_pModelRed.end());
	m_pModelBlue.erase(m_pModelBlue.begin(), m_pModelBlue.end());
}
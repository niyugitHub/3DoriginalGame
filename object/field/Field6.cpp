#include "Field6.h"

namespace
{
	const char* const kFileStage = "data/stage/stage6.csv";
	//	const char* const kFileName2 = "data/fieldGreen.mv1";

	//�n�ʂɕ~���l�߂�u���b�N�̐�
	constexpr int kBlockNumX = 14;
	constexpr int kBlockNumZ = 40;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	//�u���b�N�̈�ӂ̒���
	constexpr float kBlockSideLength = 200.0f;

	//�n�ʂ̈�ӂ̒���
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;
}

Field6::Field6()
{
	m_stageNum = 6;
	m_data.fileName = kFileStage;
	m_lookBlock = kRed;
	m_blockKinds = kGreen;
	m_data.blockNumX = kBlockNumX;
	m_data.blockNumZ = kBlockNumZ;
}

Field6::~Field6()
{
	m_pBlock.erase(m_pBlock.begin(), m_pBlock.end());
}

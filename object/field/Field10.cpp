#include "Field10.h"

namespace
{
	const char* const kFileStage = "data/stage/stage10.csv";
	//	const char* const kFileName2 = "data/fieldGreen.mv1";

	//�n�ʂɕ~���l�߂�u���b�N�̐�
	constexpr int kBlockNumX = 25;
	constexpr int kBlockNumZ = 25;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	//�u���b�N�̈�ӂ̒���
	constexpr float kBlockSideLength = 200.0f;

	//�n�ʂ̈�ӂ̒���
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;
}

Field10::Field10()
{
	m_stageNum = 10;
	m_data.fileName = kFileStage;
	m_lookBlock = Red;
	m_blockKinds = Green;
	m_data.blockNumX = kBlockNumX;
	m_data.blockNumZ = kBlockNumZ;
}

Field10::~Field10()
{
	m_pBlock.erase(m_pBlock.begin(), m_pBlock.end());
}

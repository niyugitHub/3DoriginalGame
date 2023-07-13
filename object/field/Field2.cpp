#include "Field2.h"

namespace
{
	const char* const kFileStage = "data/stage/stage2.csv";
	//	const char* const kFileName2 = "data/fieldGreen.mv1";

	//地面に敷き詰めるブロックの数
	constexpr int kBlockNumX = 30;
	constexpr int kBlockNumZ = 10;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	//ブロックの一辺の長さ
	constexpr float kBlockSideLength = 200.0f;

	//地面の一辺の長さ
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;
}

Field2::Field2()
{
	m_stageNum = 2;
	m_data.fileName = kFileStage;
	m_lookBlock = Red;
	m_blockKinds = Blue;
	m_data.blockNumX = kBlockNumX;
	m_data.blockNumZ = kBlockNumZ;
}

Field2::~Field2()
{
	m_pBlock.erase(m_pBlock.begin(), m_pBlock.end());
}

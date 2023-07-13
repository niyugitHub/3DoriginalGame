#include "Field5.h"

namespace
{
	const char* const kFileStage = "data/stage/stage5.csv";
	//	const char* const kFileName2 = "data/fieldGreen.mv1";

	//地面に敷き詰めるブロックの数
	constexpr int kBlockNumX = 40;
	constexpr int kBlockNumZ = 13;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	//ブロックの一辺の長さ
	constexpr float kBlockSideLength = 200.0f;

	//地面の一辺の長さ
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;
}

Field5::Field5()
{
	m_stageNum = 5;
	m_data.fileName = kFileStage;
	m_lookBlock = Red;
	m_blockKinds = Blue;
	m_data.blockNumX = kBlockNumX;
	m_data.blockNumZ = kBlockNumZ;
}

Field5::~Field5()
{
	m_pBlock.erase(m_pBlock.begin(), m_pBlock.end());
}
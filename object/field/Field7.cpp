#include "Field7.h"

namespace
{
	const char* const kFileStage = "data/stage/stage7.csv";
	//	const char* const kFileName2 = "data/fieldGreen.mv1";

	//地面に敷き詰めるブロックの数
	constexpr int kBlockNumX = 15;
	constexpr int kBlockNumZ = 35;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	//ブロックの一辺の長さ
	constexpr float kBlockSideLength = 200.0f;

	//地面の一辺の長さ
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;
}

Field7::Field7()
{
	m_stageNum = 7;
	m_data.fileName = kFileStage;
	m_lookBlock = kRed;
	m_blockKinds = kGreen;
	m_data.blockNumX = kBlockNumX;
	m_data.blockNumZ = kBlockNumZ;

	Init(m_data);
}

Field7::~Field7()
{
	m_pBlock.erase(m_pBlock.begin(), m_pBlock.end());
}
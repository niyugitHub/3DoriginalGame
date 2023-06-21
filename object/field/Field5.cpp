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
	m_lookBlock = kRed;
	m_blockKinds = kBlue;
	m_data.blockNumX = kBlockNumX;
	m_data.blockNumZ = kBlockNumZ;

	Init(m_data);
}

Field5::~Field5()
{
	m_pModel.erase(m_pModel.begin(), m_pModel.end());
	m_pModelRed.erase(m_pModelRed.begin(), m_pModelRed.end());
	m_pModelBlue.erase(m_pModelBlue.begin(), m_pModelBlue.end());
}
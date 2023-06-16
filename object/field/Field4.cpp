#include "Field4.h"

namespace
{
	const char* const kFileStage = "data/stage/stage4.csv";
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

Field4::Field4()
{
	m_stageNum = 4;
	m_data.fileName = kFileStage;
	m_lookBlock = kRed;
	m_blockKinds = kGreen;
	m_data.blockNumX = kBlockNumX;
	m_data.blockNumZ = kBlockNumZ;

	Init(m_data);
}

Field4::~Field4()
{
	m_pModel.erase(m_pModel.begin(), m_pModel.end());
	m_pModelRed.erase(m_pModelRed.begin(), m_pModelRed.end());
	m_pModelBlue.erase(m_pModelBlue.begin(), m_pModelBlue.end());
	m_pModelGreen.erase(m_pModelBlue.begin(), m_pModelBlue.end());
}


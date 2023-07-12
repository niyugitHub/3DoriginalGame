#include "Field1.h"
#include "../Block.h"
#include<DxLib.h>

namespace
{
	const char* const kFileStage = "data/stage/stage1.csv";
//	const char* const kFileStage = "data/stage/debug.csv";
//	const char* const kFileName2 = "data/fieldGreen.mv1";

	//地面に敷き詰めるブロックの数
	constexpr int kBlockNumX = 15;
	constexpr int kBlockNumZ = 30;

	/*constexpr int kBlockNumX = 100;
	constexpr int kBlockNumZ = 100;*/

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	//ブロックの一辺の長さ
	constexpr float kBlockSideLength = 200.0f;

	//地面の一辺の長さ
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;
}

Field1::Field1()
{
	//ステージ番号
	m_stageNum = 1;

	m_data.fileName = kFileStage;
	m_lookBlock = Block::kRed;
	m_blockKinds = Block::kBlue;
	m_data.blockNumX = kBlockNumX;
	m_data.blockNumZ = kBlockNumZ;
}

Field1::~Field1()
{
	m_pBlock.erase(m_pBlock.begin(), m_pBlock.end());
	m_pSwitch.erase(m_pSwitch.begin(), m_pSwitch.end());
}

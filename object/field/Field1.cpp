#include "Field1.h"
#include "Model.h"

namespace
{
	//ファイル名
	const char* const kFileName = "data/field.mv1";

	//地面に敷き詰めるブロックの数
	constexpr int kBlockNumX = 10;
	constexpr int kBlockNumZ = 10;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	//ブロックの一辺の長さ
	constexpr float kBlockSideLength = 200.0f;

	//地面の一辺の長さ
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;
}

Field1::Field1()
{
	m_lookBlock = 0;
	//3Dモデルをロード
	m_pModel.push_back(std::make_shared<Model>(kFileName));
	m_pModel.back()->setPos(VGet(200.0f, -10000.0f,200.0f));
	m_pModel.back()->setUseCollision(true, true);

	for (int i = 0; i < kBlockNum; i++)
	{
		m_blockNum.push_back(GetRand(2) + 1);
	}

	//最初にロードしたモデルと合わせてモデルを100個生成
	int orgModel = m_pModel[0]->getModelHandle();
	/*for (auto& block : m_blockNum)
	{		
		m_pModel.push_back(std::make_shared<Model>(orgModel));
		m_pModel.back()->setUseCollision(true, true);
	}*/

	//地面に並べる
	for (int i = 0; i < m_blockNum.size(); i++)
	{
		if (m_blockNum[i] == kField)
		{
			m_pModel.push_back(std::make_shared<Model>(orgModel));
			m_pModel.back()->setUseCollision(true, true);
			float x = 200.0f * (i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			float z = 200.0f * (i / kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			m_pModel.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
			continue;
		}

		if (m_blockNum[i] == kRed)
		{
			m_pModelRed.push_back(std::make_shared<Model>(orgModel));
			m_pModelRed.back()->setUseCollision(true, true);
			float x = 200.0f * (i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			float z = 200.0f * (i / kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			m_pModelRed.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
			continue;
		}

		if (m_blockNum[i] == kBlue)
		{
			m_pModelBlue.push_back(std::make_shared<Model>(orgModel));
			m_pModelBlue.back()->setUseCollision(true, true);
			float x = 200.0f * (i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			float z = 200.0f * (i / kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
			m_pModelBlue.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
			continue;
		}
	}
}

Field1::~Field1()
{
}

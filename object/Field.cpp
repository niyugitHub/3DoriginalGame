#include "Field.h"
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

Field::Field()
{
	
	//3Dモデルをロード
	m_pModel.push_back(std::make_shared<Model>(kFileName));
	m_pModel.back()->setUseCollision(true, true);

	//最初にロードしたモデルと合わせてモデルを100個生成
	int orgModel = m_pModel[0]->getModelHandle();
	for (int i = 0; i < kBlockNum - 1; i++)
	{
		m_pModel.push_back(std::make_shared<Model>(orgModel));
		m_pModel.back()->setUseCollision(true, true);
	}

	//地面に並べる
	for (int i = 0; i < m_pModel.size(); i++)
	{
		float x = 200.0f * (i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
		float z = 200.0f * (i / kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
		m_pModel[i]->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
	}
}

Field::~Field()
{

}

void Field::Init()
{
}

void Field::Update()
{
	for (auto& model : m_pModel)
	{
		model->update();
	}
}

void Field::Draw()
{
	for (auto& model : m_pModel)
	{
		model->draw();
	}
}

float Field::GetFieldSizeX()
{
	return kFieldSideLengthX;
}


float Field::GetFieldSizeZ()
{
	return kFieldSideLengthZ;
}

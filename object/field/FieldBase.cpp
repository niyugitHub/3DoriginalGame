#include "FieldBase.h"
#include "Model.h"
#include"Pad.h"

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

FieldBase::FieldBase()
{
	
	////3Dモデルをロード
	//m_pModel.push_back(std::make_shared<Model>(kFileName));
	//m_pModel.back()->setUseCollision(true, true);

	////最初にロードしたモデルと合わせてモデルを100個生成
	//int orgModel = m_pModel[0]->getModelHandle();
	//for (int i = 0; i < kBlockNum - 1; i++)
	//{
	//	m_pModel.push_back(std::make_shared<Model>(orgModel));
	//	m_pModel.back()->setUseCollision(true, true);
	//}

	////地面に並べる
	//for (int i = 0; i < m_pModel.size(); i++)
	//{
	//	float x = 200.0f * (i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
	//	float z = 200.0f * (i / kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
	//	m_pModel[i]->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
	//}
}

FieldBase::~FieldBase()
{

}

void FieldBase::Init()
{
}

void FieldBase::Update()
{
	for (auto& model : m_pModel)
	{
		model->update();
	}

	for (auto& model : m_pModelRed)
	{
		model->update();
	}

	for (auto& model : m_pModelBlue)
	{
		model->update();
	}

	if (Pad::isTrigger(PAD_INPUT_3))
	{
		m_lookBlock++;
		if (m_lookBlock >= 3)
		{
			m_lookBlock = 0;
		}
	}
}

void FieldBase::Draw()
{
	if (m_lookBlock == 0)
	{
		for (auto& model : m_pModel)
		{
			model->draw();
			DrawString(500, 0, "さふぇｄ；ｊヵ", 0xffffff);
		}
	}

	if (m_lookBlock == 1)
	{
		for (auto& model : m_pModelRed)
		{
			model->draw();
			DrawString(500, 0, "赤", 0xffffff);
		}
	}

	if (m_lookBlock == 2)
	{
		for (auto& model : m_pModelBlue)
		{
			model->draw();
			DrawString(500, 0, "青", 0xffffff);
		}
	}
}

float FieldBase::GetFieldSizeX()
{
	return kFieldSideLengthX;
}


float FieldBase::GetFieldSizeZ()
{
	return kFieldSideLengthZ;
}

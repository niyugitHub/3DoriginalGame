#include "FieldBase.h"
#include "../Model.h"
#include "../../util/Pad.h"
#include"../Switch.h"
#include"../Goal.h"
#include"../Item.h"
#include"../../SaveData.h"
#include<cassert>
#include <iostream>


namespace
{
	//ファイル名
	const char* const kFileName1 = "data/field.mv1";
	const char* const kFileName2 = "data/fieldRed.mv1";
	const char* const kFileName3 = "data/fieldBlue.mv1";
	const char* const kFileName4 = "data/fieldGreen.mv1";

	//地面に敷き詰めるブロックの数
	constexpr int kBlockNumX = 15;
	constexpr int kBlockNumZ = 30;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	//ブロックの一辺の長さ
	constexpr float kBlockSideLength = 200.0f;

	//地面の一辺の長さ
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;

	//スターの数
	//constexpr int kStarNum = 3;
}

FieldBase::FieldBase() : 
	m_lookBlock(kRed),
	m_blockKinds(kBlue),
	m_playerPos(VGet(0,0,0)),
	m_stageNum(0),
	m_gameFrameCount(0),
	m_limitFrame(3600),
	m_getItem(false)
{
	for (int i = 0; i < 3; i++)
	{
		m_getStar[i] = false;
	}

	m_data.blockNumX = 0;
	m_data.blockNumZ = 0;
	m_data.fileName = "";
	
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

void FieldBase::Init(loadData data)
{
	FirstModelLoad(); // 最初に複製するためにモデルを用意する

	LoadFile(data.fileName);

//	m_blockNum.push_back(8); //とりあえずスイッチ用意(8がスイッチ)

	//最初にロードしたモデルと合わせてモデルを100個生成
	int orgModel1 = m_pModel[0]->getModelHandle();
	int orgModel2 = m_pModel[1]->getModelHandle();
	int orgModel3 = m_pModel[2]->getModelHandle();
	int orgModel4 = m_pModel[3]->getModelHandle();
	/*for (auto& block : m_blockNum)
	{
		m_pModel.push_back(std::make_shared<Model>(orgModel));
		m_pModel.back()->setUseCollision(true, true);
	}*/

	ModelLoad(orgModel1, orgModel2, orgModel3, orgModel4);
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

	for (auto& model : m_pModelGreen)
	{
		model->update();
	}

	for (auto& Switch : m_pSwitch)
	{
		Switch->SetColorNum(m_lookBlock);
		Switch->Update();
	}

	if (!m_pItem->GetExist())
	{
		m_getItem = true;
	}

	m_gameFrameCount++;
}

void FieldBase::Draw()
{
	for (auto& model : m_pModel)
	{
		model->draw();
		//DrawString(500, 0, "さふぇｄ；ｊヵ", 0xffffff);
	}

	if (m_lookBlock == kRed)
	{
		for (auto& model : m_pModelRed)
		{
			model->draw();
			DrawString(500, 0, "赤", 0xffffff);
		}
	}

	if (m_lookBlock == kBlue)
	{
		for (auto& model : m_pModelBlue)
		{
			model->draw();
			DrawString(500, 0, "青", 0xffffff);
		}
	}

	if (m_lookBlock == kGreen)
	{
		for (auto& model : m_pModelGreen)
		{
			model->draw();
			DrawString(500, 0, "緑", 0xffffff);
		}
	}

	for (auto& Switch : m_pSwitch)
	{
		Switch->Draw();
	}

	m_pGoal->Draw();

	if (m_pItem->GetExist())
	{
		m_pItem->Draw();
	}
}

void FieldBase::FirstModelLoad()
{
	//3Dモデルをロード
	m_pModel.push_back(std::make_shared<Model>(kFileName1));
	m_pModel.back()->setPos(VGet(200.0f, -10000.0f, 200.0f));
	m_pModel.back()->setUseCollision(true, true);

	//3Dモデルをロード
	m_pModel.push_back(std::make_shared<Model>(kFileName2));
	m_pModel.back()->setPos(VGet(200.0f, -10000.0f, 200.0f));
	m_pModel.back()->setUseCollision(true, true);

	//3Dモデルをロード
	m_pModel.push_back(std::make_shared<Model>(kFileName3));
	m_pModel.back()->setPos(VGet(200.0f, -10000.0f, 200.0f));
	m_pModel.back()->setUseCollision(true, true);

	//3Dモデルをロード
	m_pModel.push_back(std::make_shared<Model>(kFileName4));
	m_pModel.back()->setPos(VGet(200.0f, -10000.0f, 200.0f));
	m_pModel.back()->setUseCollision(true, true);
}

void FieldBase::LoadFile(const char* fileName)
{
	// csvファイルを読み込んで数字の配列にしたい
	FILE* fp;

	if (fopen_s(&fp, fileName, "rt") != 0)
	{
		std::cout << "ファイル読み込み失敗";
		return;	// 異常終了
	}

	int chr;

	// chr = fgetc(fp)	ファイルから1文字読み込んでintにしてchrに入れる
	//					chrに53('5'の文字コード)が入る
	//					その後ファイル位置指定子を進める
	//					(次にfgetcしたときは今回読み込んだ文字の次が読み込まれる)

	// chr != FOF		53とEOFの比較が行われる
	//					EOF -> End Of File		ファイルの終端

	int wNum = -1;	// 未確定
	// 横の要素数数える用
	int tempW = 0;

	int tempNum = 0;
	while (true)
	{
		chr = fgetc(fp);	// 1文字読み込み
		// 区切り文字が見つかった
		if (chr == ',' ||
			chr == '\n' ||
			chr == EOF)
		{
			// dataTblにデータを入れる
			m_blockNum.push_back(tempNum);
			tempNum = 0;

			// ファイルの終端に来たら終了
			if (chr == EOF)
			{
				break;
			}
			else if (chr == ',')
			{
				tempW++;	// 要素数数える
			}
			else   // chr == '\n'
			{
				tempW++;	// 要素数数える
				if (wNum < 0)
				{
					wNum = tempW;	// 要素数確定
				}
				/*else
				{
					assert(wNum == tempW);
				}*/
				tempW = 0;
			}
			// まだ終わってないので続けて読み込み
			continue;
		}

		// データは数字のみのはず
		assert(chr >= '0' && chr <= '9');

		// 数字なのは確定
		// 文字列を数値に変換したい

		// 268を読み込む
		// 1文字目は'2'	これを数値に変換していれる
		// 2文字目は'6'	tempNumは2 20 + 6  tempNum = 26
		// 3文字目は'8' tempNumは26 260+ 8 tempNum = 268
		tempNum = (tempNum * 10) + chr - '0';

		// データの区切りが見つかった時点でそこまでがデータのひとまとまり

	}
	// ファイルを閉じる
	fclose(fp);
}

void FieldBase::ModelLoad(int Model1, int Model2, int Model3, int Model4)
{
	//地面に並べる
	for (int i = 0; i < m_blockNum.size(); i++)
	{
		float x = 200.0f * static_cast<float>(i % m_data.blockNumX) - m_data.blockNumX / 2;
		float z = 200.0f * static_cast<float>(m_data.blockNumZ - (i / m_data.blockNumX)) - m_data.blockNumX / 2;
		if (m_blockNum[i] == 10)
		{
			m_pModel.push_back(std::make_shared<Model>(Model1));
			m_pModel.back()->setUseCollision(true, true);
			m_pModel.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
			m_pGoal = std::make_shared<Goal>(VGet(x, 100, z));
			continue;
		}

		if (m_blockNum[i] == 8)
		{
			m_pModel.push_back(std::make_shared<Model>(Model1));
			m_pModel.back()->setUseCollision(true, true);
			m_pModel.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置

			m_pSwitch.push_back(std::make_shared<Switch>(VGet(x, 100, z)));
			continue;
		}

		if (m_blockNum[i] == kField)
		{
			m_pModel.push_back(std::make_shared<Model>(Model1));
			m_pModel.back()->setUseCollision(true, true);
			m_pModel.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
			continue;
		}

		if (m_blockNum[i] == kRed)
		{
			m_pModelRed.push_back(std::make_shared<Model>(Model2));
			m_pModelRed.back()->setUseCollision(true, true);
			m_pModelRed.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
			continue;
		}

		if (m_blockNum[i] == kBlue)
		{
			m_pModelBlue.push_back(std::make_shared<Model>(Model3));
			m_pModelBlue.back()->setUseCollision(true, true);
			m_pModelBlue.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
			continue;
		}

		if (m_blockNum[i] == kGreen)
		{
			m_pModelGreen.push_back(std::make_shared<Model>(Model4));
			m_pModelGreen.back()->setUseCollision(true, true);
			m_pModelGreen.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
			continue;
		}

		if (m_blockNum[i] == 5)
		{
			m_pModel.push_back(std::make_shared<Model>(Model1));
			m_pModel.back()->setUseCollision(true, true);
			m_pModel.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
			m_playerPos = VGet(x, 100, z);
			continue;
		}

		if (m_blockNum[i] == 6)
		{
			m_pModel.push_back(std::make_shared<Model>(Model1));
			m_pModel.back()->setUseCollision(true, true);
			m_pModel.back()->setPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
			m_pItem = std::make_shared<Item>(VGet(x, 100, z));
			continue;
		}
	}
}

void FieldBase::ChangeBlock()
{
	m_lookBlock++;
	if (m_lookBlock > m_blockKinds)
	{
		m_lookBlock = kRed;
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

void FieldBase::StageClear()
{
	m_getStar[0] = true;

	if (m_getItem)
	{
		m_getStar[1] = true;
	}

	if (m_gameFrameCount < m_limitFrame)
	{
		m_getStar[2] = true;
	}
	//セーブデータのアップデート(配列が0からなのでm_stageNumに-1をする)
	SaveData::Update(m_stageNum - 1, m_getStar);
}

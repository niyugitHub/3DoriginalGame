#include "FieldBase.h"
#include "../Model.h"
#include"../Block.h"
#include "../../util/Pad.h"
#include"../Switch.h"
#include"../Goal.h"
#include"../Item.h"
#include"../HalfwayPoint.h"
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
	m_lookBlock(Red),
	m_blockKinds(Blue),
	m_playerPos(VGet(0,0,0)),
	m_firstPlayerPos(VGet(0, 0, 0)),
	m_stageNum(0),
	m_gameFrameCount(0),
	m_getItem(false),
	m_limitFrame(3600)
{
	for (int i = 0; i < 3; i++)
	{
		m_getStar[i] = false;
	}

	m_data.fileName = "";
	m_data.blockNumX = 0;
	m_data.blockNumZ = 0;
	
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
//	FirstModelLoad(); // 最初に複製するためにモデルを用意する

	//ファイルのロード
	LoadFile(m_data.fileName);

//	m_blockNum.push_back(8); //とりあえずスイッチ用意(8がスイッチ)

	// 後でMV1DuplicateModelを使うために先にモデルロード
	int orgModel1 = MV1LoadModel(kFileName1);
	int orgModel2 = MV1LoadModel(kFileName2);
	int orgModel3 = MV1LoadModel(kFileName3);;
	int orgModel4 = MV1LoadModel(kFileName4);;
	/*for (auto& block : m_blockNum)
	{
		m_pModel.push_back(std::make_shared<Model>(orgModel));
		m_pModel.back()->setUseCollision(true, true);
	}*/

	//モデルロード
	ModelLoad(orgModel1, orgModel2, orgModel3, orgModel4);
}

void FieldBase::Reset()
{
	m_pItem->SetExist(m_halfwayPointItem);
}

void FieldBase::Update()
{
	for (auto& block : m_pBlock)
	{
		block->Update(m_lookBlock);
	}

	for (auto& Switch : m_pSwitch)
	{
		Switch->SetColorNum(m_lookBlock);
		Switch->Update();
	}

	m_pItem->Update();

	m_pHalfwayPoint->Update();

	m_gameFrameCount++;
}

void FieldBase::Draw()
{
	for (auto& block : m_pBlock)
	{
		block->Draw();
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

	m_pHalfwayPoint->Draw();

	//printfDx("%d\n", m_gameFrameCount);
}

//void FieldBase::FirstModelLoad()
//{
//	//3Dモデルをロード
//	m_pBlock.push_back(std::make_shared<Model>(kFileName1));
//	m_pBlock.back()->setPos(VGet(200.0f, -10000.0f, 200.0f));
//	m_pBlock.back()->setUseCollision(true, true);
//
//	//3Dモデルをロード
//	m_pBlock.push_back(std::make_shared<Model>(kFileName2));
//	m_pBlock.back()->setPos(VGet(200.0f, -10000.0f, 200.0f));
//	m_pBlock.back()->setUseCollision(true, true);
//
//	//3Dモデルをロード
//	m_pBlock.push_back(std::make_shared<Model>(kFileName3));
//	m_pBlock.back()->setPos(VGet(200.0f, -10000.0f, 200.0f));
//	m_pBlock.back()->setUseCollision(true, true);
//
//	//3Dモデルをロード
//	m_pBlock.push_back(std::make_shared<Model>(kFileName4));
//	m_pBlock.back()->setPos(VGet(200.0f, -10000.0f, 200.0f));
//	m_pBlock.back()->setUseCollision(true, true);
//}

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
			if (tempNum == 1) tempNum = Block::kField;
			if (tempNum == 2) tempNum = Block::kRed;
			if (tempNum == 3) tempNum = Block::kBlue;
			if (tempNum == 4) tempNum = Block::kGreen;

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
	for (int i = 0; i < static_cast<int>(m_blockNum.size()); i++)
	{
		int x = 200 * (i % m_data.blockNumX) - m_data.blockNumX / 2;
		int z = 200 * (m_data.blockNumZ - (i / m_data.blockNumX)) - m_data.blockNumX / 2;
		float posX = static_cast<float>(x);
		float posZ = static_cast<float>(z);
		if (m_blockNum[i] == GoalObj)
		{
			m_pBlock.push_back(std::make_shared<Block>(static_cast<int>(Field),Model1));
			m_pBlock.back()->SetPos(VGet(posX, -kBlockSideLength / 2.0f, posZ));//上面がy=0.0fになるように配置
			m_pGoal = std::make_shared<Goal>(VGet(posX, 100, posZ));
			continue;
		}

		if (m_blockNum[i] == SwitchObj)
		{
			m_pBlock.push_back(std::make_shared<Block>(static_cast<int>(Field),Model1));
			m_pBlock.back()->SetPos(VGet(posX, -kBlockSideLength / 2.0f, posZ));//上面がy=0.0fになるように配置
			m_pSwitch.push_back(std::make_shared<Switch>(VGet(posX, 100, posZ)));
			continue;
		}

		if (m_blockNum[i] == Block::kField)
		{
			m_pBlock.push_back(std::make_shared<Block>(static_cast<int>(Field),Model1));
			m_pBlock.back()->SetPos(VGet(posX, -kBlockSideLength / 2.0f, posZ));//上面がy=0.0fになるように配置
			continue;
		}

		if (m_blockNum[i] == Block::kRed)
		{
			m_pBlock.push_back(std::make_shared<Block>(static_cast<int>(Red),Model2));
			m_pBlock.back()->SetPos(VGet(posX, -kBlockSideLength / 2.0f, posZ));//上面がy=0.0fになるように配置
			continue;
		}

		if (m_blockNum[i] == Block::kBlue)
		{
			m_pBlock.push_back(std::make_shared<Block>(static_cast<int>(Blue),Model3));
			m_pBlock.back()->SetPos(VGet(posX, -kBlockSideLength / 2.0f, posZ));//上面がy=0.0fになるように配置
			continue;
		}

		if (m_blockNum[i] == Block::kGreen)
		{
			m_pBlock.push_back(std::make_shared<Block>(static_cast<int>(Green),Model4));
			m_pBlock.back()->SetPos(VGet(posX, -kBlockSideLength / 2.0f, posZ));//上面がy=0.0fになるように配置
			continue;
		}

		if (m_blockNum[i] == PlayerPos)
		{
			m_pBlock.push_back(std::make_shared<Block>(static_cast<int>(Field),Model1));
			m_pBlock.back()->SetPos(VGet(posX, -kBlockSideLength / 2.0f, posZ));//上面がy=0.0fになるように配置
			m_playerPos = VGet(posX, 0, posZ);
			m_firstPlayerPos = VGet(posX, 0, posZ);
			continue;
		}

		if (m_blockNum[i] == ItemObj)
		{
			m_pBlock.push_back(std::make_shared<Block>(static_cast<int>(Field),Model1));
			m_pBlock.back()->SetPos(VGet(posX, -kBlockSideLength / 2.0f, posZ));//上面がy=0.0fになるように配置
			m_pItem = std::make_shared<Item>(VGet(posX, 100, posZ));
			continue;
		}

		if (m_blockNum[i] == HalfwayPointObj)
		{
			m_pBlock.push_back(std::make_shared<Block>(static_cast<int>(Field), Model1));
			m_pBlock.back()->SetPos(VGet(posX, -kBlockSideLength / 2.0f, posZ));//上面がy=0.0fになるように配置
			m_pHalfwayPoint = std::make_shared<HalfwayPoint>(VGet(posX, kBlockSideLength / 2.0f, posZ));
		}
	}
}

void FieldBase::ChangeBlock()
{
	m_lookBlock++;
	if (m_lookBlock > m_blockKinds)
	{
		m_lookBlock = Red;
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

void FieldBase::OnStageClear()
{
	m_getStar[0] = true;

	m_getStar[1] = !m_pItem->GetExist();

	m_getStar[2] = m_gameFrameCount < m_limitFrame;

	//セーブデータのアップデート(配列が0からなのでm_stageNumに-1をする)
	SaveData::Update(m_stageNum - 1, m_getStar);
}

void FieldBase::OnSetPlayerRespawn()
{
	m_playerPos = m_pHalfwayPoint->GetPos();
}

void FieldBase::ResetPlayerPos()
{
	m_playerPos = m_firstPlayerPos;
}

#include "SaveData.h"
#include <cstdio>
#include<DxLib.h>


namespace
{
	//ステージ数
	constexpr int kStageNum = 10;

	//1ステージのスターの数
	constexpr int kStarNum = 3;

	// ステージごとのスターの取得状態
	bool kGetStar[kStageNum][kStarNum];
}

void SaveData::Init()
{
	for (int i = 0; i < kStageNum; i++)
	{
		for (int j = 0; j < kStarNum; j++)
		{
			kGetStar[i][j] = false;
		}
	}
}

void SaveData::Update(int stageNum,  bool getStar[])
{
	//kGetStarにスターを取得したかどうかの情報を与える
	for (int i = 0; i < kStarNum; i++)
	{
		kGetStar[stageNum][i] = getStar[i];
	}

	Write();//スター情報書き込み
	Read();//スター情報読み込み
}

void SaveData::Read()
{
	FILE* fp = nullptr;

	// バイナリデータへの読み込みモードで開く
	fopen_s(&fp, "SaveData.bin", "rb");

	// nullptrなら異常終了
	if (!fp) return;

	//// データの読み込みを行う
	fread(&kGetStar, sizeof(kGetStar), 1, fp);

	fclose(fp);
}

void SaveData::Write()
{
	FILE* fp = nullptr;

	// バイナリデータへの書き込みモードで開く
	fopen_s(&fp, "SaveData.bin", "wb");

	// nullptrなら異常終了
	if (!fp)		return;

	//スターデータ
	//kGetStar.resize(kGetStar);

	// ヘッダーデータを出力する 決まったルールで出力する
	fwrite(&kGetStar, sizeof(kGetStar), 1, fp);

	// データ部分の出力　マップの大きさによってデータサイズ変わる
	//fwrite(kGetStar.data(), kGetStar.size, 1, fp);

	fclose(fp);
}

void SaveData::Draw()
{
	for (int i = 0; i < kStageNum; i++)
	{
		for (int j = 0; j < kStarNum; j++)
		{
			printfDx("%d ", kGetStar[i][j]);
		}
		printfDx("\n");
	}
}


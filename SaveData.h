#pragma once

namespace SaveData
{
	//スターの取得状態初期化(書き込んだファイルは変わらない)
	void Init();
	/// <summary>
	/// セーブデータのアップデート
	/// </summary>
	/// <param name="stageNum">ステージ番号</param>
	/// <param name="getStar">スター取得状態(1ステージにつき3つ)</param>
	void Update(int stageNum, bool getStar[]);
	//セーブデータ読み込み
	void Read();
	//セーブデータ書き込み
	void Write();

	void Draw();

	bool GetStar(int i, int j);
}
#pragma once

namespace SaveData
{
	//スターの取得状態初期化(書き込んだファイルは変わらない)
	void Init();
	//セーブデータアップデート
	void Update(int stageNum, bool getStar[]);
	//セーブデータ読み込み
	void Read();
	//セーブデータ書き込み
	void Write();

	void Draw();
}
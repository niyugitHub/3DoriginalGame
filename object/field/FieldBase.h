#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

class Model;
class Switch;
class Goal;

class FieldBase
{
protected:
	//ロードする際のデータ構造体
	struct loadData
	{
		const char* fileName;//ファイル名
		int blockNumX;//X軸のブロックの数
		int blockNumZ;//Y軸のブロックの数
	};
public:
	FieldBase();
	virtual ~FieldBase();

	void Init(loadData data);
	void Update();
	void Draw();
	
	void FirstModelLoad(); // モデルロード(最初の一個だけ)

	void LoadFile(const char* fileName);

	void ModelLoad(int Model1, int Model2, int Model3, int Model4);//モデルロード(全部のモデル)

	void ChangeBlock();

	float GetFieldSizeX();	//X軸のフィールドの長さ
	float GetFieldSizeZ();	//Z軸のフィールドの長さ

	VECTOR GetPlayerPos() { return m_playerPos; }

	void StageClear();

	enum
	{
		kField = 1,
		kRed = 2,
		kBlue = 3,
		kGreen = 4,
	};

	/*int GetBlockNumX() { return m_blockNum.x; }
	int GetBlockNumZ() { return m_blockNum.z; }*/

	std::vector<std::shared_ptr<Model>> GetModel() { return m_pModel; }

	std::vector<std::shared_ptr<Model>> GetModelRed() { return m_pModelRed; }

	std::vector<std::shared_ptr<Model>> GetModelBlue() { return m_pModelBlue; }

	std::vector<std::shared_ptr<Model>> GetModelGreen() { return m_pModelGreen; }

	std::vector<std::shared_ptr<Switch>> GetSwitch() { return m_pSwitch; }

	std::shared_ptr<Goal> GetGoal() { return m_pGoal; }

	int GetLookBlock() { return m_lookBlock; }

protected:
	//モデルのポインター
	std::vector<std::shared_ptr<Model>> m_pModel;

	//モデルのポインター(赤)
	std::vector<std::shared_ptr<Model>> m_pModelRed;

	//モデルのポインター(青)
	std::vector<std::shared_ptr<Model>> m_pModelBlue;

	//モデルのポインター(緑)
	std::vector<std::shared_ptr<Model>> m_pModelGreen;

	//スイッチのポインター
	std::vector<std::shared_ptr<Switch>> m_pSwitch;

	//ゴールのポインター
	std::shared_ptr<Goal> m_pGoal;

	//ブロックの番号(番号によってブロックの色が変わる)
	std::vector<int> m_blockNum; 

	int m_lookBlock;//今見えるブロックの番号
	int m_blockKinds;//ステージで使われるブロックの種類

	loadData m_data; // ロードデータ

	//プレイヤー初期位置
	VECTOR m_playerPos;

	//ステージ番号
	int m_stageNum;

	//スター取得状態(スターの数は3つ)
	bool m_getStar[3];
};


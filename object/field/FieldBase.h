#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

class Block;
class Switch;
class Goal;
class Item;

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

	void Init();
	void Update();
	void Draw();
	
	//void FirstModelLoad(); // モデルロード(最初の一個だけ)

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

	std::vector<std::shared_ptr<Block>> GetBlock() { return m_pBlock; }

	std::vector<std::shared_ptr<Switch>> GetSwitch() { return m_pSwitch; }

	std::shared_ptr<Goal> GetGoal() { return m_pGoal; }

	std::shared_ptr<Item> GetItem() { return m_pItem; }

	int GetLookBlock() { return m_lookBlock; }

	bool GetStar(int i) { return m_getStar[i]; }

	void ResetTime() { m_gameFrameCount = 0; }

protected:
	int m_lookBlock;//今見えるブロックの番号
	int m_blockKinds;//ステージで使われるブロックの種類
	
	//プレイヤー初期位置
	VECTOR m_playerPos;
	
	//ステージ番号
	int m_stageNum;

	//ゲームが始まってからの時間
	int m_gameFrameCount;

	//アイテムを取得したかどうか
	bool m_getItem;

	//スターをもらうための制限時間
	int m_limitFrame;

	//スター取得状態(スターの数は3つ)
	bool m_getStar[3];

	loadData m_data; // ロードデータ

	//フィールドのポインター
	std::vector<std::shared_ptr<Block>> m_pBlock;

	//スイッチのポインター
	std::vector<std::shared_ptr<Switch>> m_pSwitch;

	//ゴールのポインター
	std::shared_ptr<Goal> m_pGoal;

	//アイテムのポインター
	std::shared_ptr<Item> m_pItem;

	////ブロックの番号(番号によってブロックの色が変わる)
	std::vector<int> m_blockNum; 
};


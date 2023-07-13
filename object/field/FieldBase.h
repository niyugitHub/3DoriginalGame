#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

class Block;
class Switch;
class Goal;
class Item;
class HalfwayPoint;

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

	//プレイヤー死亡時にリセット
	void Reset();
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

	enum BlockKind
	{
		Field = 1,
		Red = 2,
		Blue = 3,
		Green = 4,
		PlayerPos = 5,
		ItemObj = 6,
		HalfwayPointObj = 7,
		SwitchObj = 8,
		GoalObj = 10,
	};

	/*int GetBlockNumX() { return m_blockNum.x; }
	int GetBlockNumZ() { return m_blockNum.z; }*/

	std::vector<std::shared_ptr<Block>> GetBlock() { return m_pBlock; }

	std::vector<std::shared_ptr<Switch>> GetSwitch() { return m_pSwitch; }

	std::shared_ptr<Goal> GetGoal() { return m_pGoal; }

	std::shared_ptr<Item> GetItem() { return m_pItem; }

	std::shared_ptr<HalfwayPoint> GetHalfwayPoint() { return m_pHalfwayPoint; }

	int GetLookBlock() { return m_lookBlock; }

	bool GetStar(int i) { return m_getStar[i]; }

	void ResetTime() { m_gameFrameCount = 0; }

	//プレイヤーのリスポーン位置変更
	void OnSetPlayerRespawn();

	void SetmHalfwayPointItem(bool getItem) { m_halfwayPointItem = getItem; }

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

	//中間ポイントの前にアイテムを取得していたかどうか
	bool m_halfwayPointItem;

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

	//中間ポイントのポインター
	std::shared_ptr<HalfwayPoint> m_pHalfwayPoint;

	////ブロックの番号(番号によってブロックの色が変わる)
	std::vector<int> m_blockNum; 
};


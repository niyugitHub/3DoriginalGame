#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

class Model;
class Switch;
class Goal;

class FieldBase
{
public:
	FieldBase();
	virtual ~FieldBase();

	void Init(const char* FileName,int lookBlock,int blockKind);
	void Update();
	void Draw();
	
	void FirstModelLoad(); // モデルロード(最初の一個だけ)

	void LoadFile(const char* fileName);

	void ModelLoad(int Model1, int Model2, int Model3);//モデルロード(全部のモデル)

	void ChangeBlock();

	float GetFieldSizeX();	//X軸のフィールドの長さ
	float GetFieldSizeZ();	//Z軸のフィールドの長さ

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

	//スイッチのポインター
	std::vector<std::shared_ptr<Switch>> m_pSwitch;

	//ゴールのポインター
	std::shared_ptr<Goal> m_pGoal;

	//ブロックの番号(番号によってブロックの色が変わる)
	std::vector<int> m_blockNum; 

	//今見えるブロックの番号
	int m_lookBlock;

	//ステージで使われるブロックの種類
	int m_blockKinds;
};


#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

class Model;
class Switch;
class FieldBase
{
public:
	FieldBase();
	virtual ~FieldBase();

	void Init();
	void Update();
	void Draw();

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

	//ブロックの番号(番号によってブロックの色が変わる)
	std::vector<int> m_blockNum; 

	//今見えるブロックの番号
	int m_lookBlock;
};


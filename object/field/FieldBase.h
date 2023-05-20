#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

class Model;
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

	/*int GetBlockNumX() { return m_blockNum.x; }
	int GetBlockNumZ() { return m_blockNum.z; }*/

	std::vector<std::shared_ptr<Model>> GetModel() { return m_pModel; }

	std::vector<std::shared_ptr<Model>> GetModelRed() { return m_pModelRed; }

	std::vector<std::shared_ptr<Model>> GetModelBlue() { return m_pModelBlue; }

protected:
	//モデルのポインター
	std::vector<std::shared_ptr<Model>> m_pModel;

	//モデルのポインター(赤)
	std::vector<std::shared_ptr<Model>> m_pModelRed;

	//モデルのポインター(青)
	std::vector<std::shared_ptr<Model>> m_pModelBlue;

	//ブロックの番号(番号によってブロックの色が変わる)
	std::vector<int> m_blockNum; 

	//今見えるブロックの番号
	int m_lookBlock;
};


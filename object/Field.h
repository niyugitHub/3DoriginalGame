#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

class Model;
class Field
{
public:
	Field();
	virtual ~Field();

	void Init();
	void Update();
	void Draw();

	float GetFieldSizeX();	//X軸のフィールドの長さ
	float GetFieldSizeZ();	//Z軸のフィールドの長さ

	int GetBlockNumX() { return m_blockNum.x; }
	int GetBlockNumZ() { return m_blockNum.z; }

	std::vector<std::shared_ptr<Model>> GetModel() { return m_pModel; }

private:
	std::vector<std::shared_ptr<Model>> m_pModel;

	VECTOR m_blockNum = { 20,0,20 };
};


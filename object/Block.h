#pragma once
#include<memory>
#include<DxLib.h>

class Model;

class Block
{
public:
	enum
	{
		kField = 1,
		kRed = 2,
		kBlue = 3,
		kGreen = 4,
	};
public:
	Block(int blockKind, int modelHandle);

	~Block();

	void Update(int colorNum);

	void Draw();

	int GetBlockKind() { return m_blockKind; }

	std::shared_ptr<Model> GetBlock() { return m_pModel; }

	void SetPos(VECTOR pos);
	VECTOR GetPos() { return m_pos; }

private:
	int m_blockKind;

	int m_modelHandle;

	std::shared_ptr<Model>m_pModel;

	int m_fadeBright;

	VECTOR m_pos;
};
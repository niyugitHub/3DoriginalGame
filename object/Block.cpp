#include "Block.h"
#include"Model.h"

Block::Block(int blockKind, int modelHandle) : 
	m_blockKind(blockKind),
	m_modelHandle(modelHandle)
{
	m_pModel = std::make_shared<Model>(m_modelHandle);
	m_pModel->setUseCollision(true, true);
}

Block::~Block()
{
}

void Block::Update()
{
	m_pModel->update();
}

void Block::Draw()
{
	m_pModel->draw();
}

void Block::SetPos(VECTOR pos)
{
	m_pModel->setPos(pos);
}

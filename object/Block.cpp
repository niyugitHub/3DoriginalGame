#include "Block.h"
#include"Model.h"

namespace
{
	//�t�F�[�h�A�E�g�A�t�F�[�h�C���X�s�[�h
	constexpr int kFadeSpeed = 12;

	//�t�F�[�h�ő�l,�ŏ��l
	constexpr int kFadeMax = 255;
	constexpr int kFadeMin = 0;
}

Block::Block(int blockKind, int modelHandle) : 
	m_blockKind(blockKind),
	m_modelHandle(modelHandle)
{
	m_pModel = std::make_shared<Model>(m_modelHandle);
	m_pModel->setUseCollision(true, true);
	m_fadeBright = 0;
}

Block::~Block()
{
}

void Block::Update(int colorNum)
{
	m_pModel->update();

	if (m_blockKind == colorNum)
	{
		m_fadeBright = min(m_fadeBright + kFadeSpeed, kFadeMax);
	}
	else
	{
		m_fadeBright = max(m_fadeBright - kFadeSpeed, kFadeMin);
	}
}

void Block::Draw()
{
	if (m_blockKind == kField)
	{
		m_pModel->draw();
	}
	else
	{
		m_pModel->blockDraw(m_fadeBright);
	}
}

void Block::SetPos(VECTOR pos)
{
	m_pos = pos;
	m_pModel->setPos(pos);
}

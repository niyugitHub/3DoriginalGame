#include "ImageUI.h"
#include<DxLib.h>

ImageUI::ImageUI()
{
}

ImageUI::~ImageUI()
{
	m_pImage.erase(m_pImage.begin(), m_pImage.end());
}

void ImageUI::AddUI(Vec2 pos, Vec2 size, int handle)
{
	m_pImage.push_back(std::make_shared<Image>(pos, size, handle));
}

void ImageUI::Init()
{
}

void ImageUI::Update()
{
}

void ImageUI::Draw(int selectNum, int scroll)
{
	for (int i = 0; i < static_cast<int>(m_pImage.size()); i++)
	{
		if (i == selectNum)
		{
			m_pImage[i]->Draw(true, scroll);
			continue;
		}
		m_pImage[i]->Draw(false, scroll);
	}
}

Image::Image(Vec2 pos, Vec2 size, int handle) : 
	m_pos(pos),
	m_size(size),
	m_handle(handle)
{
}

Image::~Image()
{
}

void Image::Init()
{
}

void Image::Update()
{
}

void Image::Draw(bool select,int scroll)
{
	int posX = static_cast<int>(m_pos.x) + scroll;
	int posY = static_cast<int>(m_pos.y);
	int sizeX = static_cast<int>(m_size.x);
	int sizeY = static_cast<int>(m_size.y);
	if (select)
	{
		DrawExtendGraph(posX - sizeX - 20, posY- sizeY - 20,
			posX + sizeX + 20, posY + sizeY + 20,
			m_handle, true);
		return;
	}

	DrawExtendGraph(posX - sizeX, posY - sizeY,
		posX + sizeX, posY + sizeY,
		m_handle, true);
}

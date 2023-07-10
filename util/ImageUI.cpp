#include "ImageUI.h"
#include "../game.h"

ImageUI::ImageUI() : 
	m_frameCount(0)
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
	for (auto& Image : m_pImage)
	{
		Image->Init();
	}
	m_frameCount = 0;
}

void ImageUI::FadeinUpdate()
{
	m_frameCount++;
	for (int i = 0; i < static_cast<int>(m_pImage.size()); i++)
	{
		m_pImage[i]->FadeinUpdate(static_cast<int>(m_frameCount / (i + 1)));
	}
}

void ImageUI::FadeoutUpdate()
{
	m_frameCount++;
	for (int i = 0; i < static_cast<int>(m_pImage.size()); i++)
	{
		m_pImage[i]->FadeoutUpdate(static_cast<int>(m_frameCount / (i + 1)));
	}
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

bool ImageUI::GetFadein()
{
	/*auto image = m_pImage.end()->get();*/
	return m_pImage.back()->GetFadein();
}

bool ImageUI::GetFadeout()
{
	/*auto image = m_pImage.end()->get();*/
	return m_pImage.back()->GetFadeout();
}

int ImageUI::GetScrollSize(int imageNum)
{
	return m_pImage[imageNum]->GetfadeScroll();
}

Image::Image(Vec2 pos, Vec2 size, int handle) : 
	m_pos(pos),
	m_size(size),
	m_handle(handle),
	m_fadeScroll(0)
{
}

Image::~Image()
{
}

void Image::Init()
{
	m_fadeScroll = Game::kScreenWidth;
	m_fadeIn = false;
	m_fadeOut = false;
}

void Image::FadeinUpdate(int count)
{
	if (count > 5)
	{
		m_fadeScroll -= 100;

		if (m_fadeScroll < 0)
		{
			m_fadeScroll = 0;
			m_fadeIn = true;
		}
	}
}

void Image::FadeoutUpdate(int count)
{
	if (count > 5)
	{
		m_fadeScroll -= 100;

		if (m_fadeScroll < -Game::kScreenWidth)
		{
			m_fadeScroll = -Game::kScreenWidth;
			m_fadeOut = true;
		}
	}
}
	

void Image::Draw(bool select,int scroll)
{
	int posX = static_cast<int>(m_pos.x) + scroll + m_fadeScroll;
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

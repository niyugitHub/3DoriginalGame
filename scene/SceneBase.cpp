#include "SceneBase.h"
#include "DxLib.h"
#include "../game.h"
#include"../SoundManager.h"
#include"../util/Pad.h"
#include"../util/ImageUI.h"

namespace
{
	// フェード速度
	constexpr int kFadeSpeed = 8;
}

SceneBase::SceneBase()
{
	// 初期設定はフェードアウト状態
	m_fadeColor = GetColor(0, 0, 0);
	m_fadeBright = 255;
	m_fadeSpeed = -kFadeSpeed;
	m_updateFunc = &SceneBase::fadeinUpdate;
}

void SceneBase::updateFade()
{
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		if (m_fadeSpeed > 0)
		{
			m_fadeSpeed = 0;
		}
	}
	if (m_fadeBright <= 0)
	{
		m_fadeBright = 0;
		if (m_fadeSpeed < 0)
		{
			m_fadeSpeed = 0;
		}
	}
}

void SceneBase::drawFade() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeBright);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_fadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool SceneBase::isFadingIn() const
{
	if (m_fadeSpeed < 0)	return true;
	return false;
}

bool SceneBase::isFadingOut() const
{
	if (m_fadeSpeed > 0)	return true;
	return false;
}

void SceneBase::startFadeOut()
{
	m_fadeSpeed = kFadeSpeed;
}

void SceneBase::SelectSE()
{
	if (Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_UP) ||
		Pad::isTrigger(PAD_INPUT_RIGHT) || Pad::isTrigger(PAD_INPUT_DOWN))
	{
		SoundManager::GetInstance().Play("cursorMove");
	}

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		SoundManager::GetInstance().Play("decision");
	}
}

void SceneBase::fadeinUpdate()
{
	m_pImageUI->FadeinUpdate();

	if (m_pImageUI->GetFadein())
	{
		m_updateFunc = &SceneBase::normalUpdate;
		m_pImageUI->SetResetCount();
	}
}

void SceneBase::fadeoutUpdate()
{
	m_pImageUI->FadeoutUpdate();
}

#pragma once

namespace Game
{
	// ウインドウモード設定
#ifdef _DEBUG 
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif

	// ウインドウ名
	const char* const kTitleText = "BlockJumper";
	// ウインドウサイズ
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	// カラーモード
	constexpr int kColorDepth = 32;		// 32 or 16
};
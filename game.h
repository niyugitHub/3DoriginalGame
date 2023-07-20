#pragma once

namespace Game
{
	// �E�C���h�E���[�h�ݒ�
#ifdef _DEBUG 
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif

	// �E�C���h�E��
	const char* const kTitleText = "BlockJumper";
	// �E�C���h�E�T�C�Y
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	// �J���[���[�h
	constexpr int kColorDepth = 32;		// 32 or 16
};
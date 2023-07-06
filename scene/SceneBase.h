#pragma once
#include"../util/Vec2.h"
#include<memory>

class ImageUI;
// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}


	virtual void init() {}
	virtual void end()	{}

	virtual SceneBase* update() { return this; }
	virtual void draw() {}

	// フェード関連
	void updateFade();
	void drawFade() const;

	bool isFadingIn() const;	// フェードイン中
	bool isFadingOut() const;	// フェードアウト中
	bool isFading() const { return isFadingIn() || isFadingOut(); }	// フェードインorアウト中

	void startFadeOut();	// フェードアウト開始

	/// <summary>
	/// フェードの明るさを取得
	/// </summary>
	/// <returns>0(フェードしていない)～255(真っ黒)</returns>
	int getFadeBright() const { return m_fadeBright; }

protected:
	void SelectSE();//シーンを選ぶ際のSE
	//仮UI
	struct UI
	{
		Vec2 pos = { 0.0f,0.0f };
		Vec2 size = {0.0f,0.0f};
		int handle = -1;
	};

	std::shared_ptr<ImageUI> m_pImageUI;//UIポインター
private:
	// フェード関連処理
	int m_fadeColor;
	int m_fadeBright;
	int m_fadeSpeed;
};
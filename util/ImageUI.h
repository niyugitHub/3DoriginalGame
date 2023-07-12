#pragma once
#include <vector>
#include <memory>
#include"Vec2.h"
#include<DxLib.h>


class Image;
/// <summary>
/// UI画像作成クラス
/// </summary>
class ImageUI
{
public:
	ImageUI();
	virtual ~ImageUI();

	
	void AddUI(Vec2 pos, Vec2 size,int handle);
	void Init();

	void FadeinUpdate(); //フェードイン処理
	void FadeoutUpdate();//フェードアウト処理
	/// <summary>
	/// 画像表示
	/// </summary>
	/// <param name="selectNum">選ばれた番号の画像だけ少し大きくする</param>
	void Draw(int selectNum,int scroll);

	bool GetFadein();
	bool GetFadeout();

	int GetScrollSize(int imageNum);

	void SetResetCount() { m_frameCount = 0; }
private:
	//Uiのポインター
	std::vector<std::shared_ptr<Image>>m_pImage;

	int m_frameCount; //フレームカウント
};

/// <summary>
/// UI画像を複製してアニメーションするクラス
/// </summary>
class Image
{
public:
	Image(Vec2 pos, Vec2 size, int handle);
	virtual ~Image();

	void Init();
	void FadeinUpdate(int count);
	void FadeoutUpdate(int count);

	bool GetFadein() { return m_fadeIn; }
	bool GetFadeout() { return m_fadeOut; }

	int GetfadeScroll() { return m_fadeScroll; }

	/// <summary>
	/// 画像表示
	/// </summary>
	/// <param name="select">画像が選ばれてるかどうか</param>
	void Draw(bool select,int scroll);

private:
	Vec2 m_pos;//画像位置(真ん中)
	Vec2 m_size;//画像サイズ
	int m_handle;// 画像ハンドル

	int m_fadeScroll;//フェードするさいのスクロール値

	bool m_fadeIn = false;
	bool m_fadeOut = false;
};


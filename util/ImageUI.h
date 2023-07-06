#pragma once
#include <vector>
#include <memory>
#include"Vec2.h"

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
	void Update();
	/// <summary>
	/// 画像表示
	/// </summary>
	/// <param name="selectNum">選ばれた番号の画像だけ少し大きくする</param>
	void Draw(int selectNum,int scroll);
private:
	//Uiのポインター
	std::vector<std::shared_ptr<Image>>m_pImage;
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
	void Update();
	/// <summary>
	/// 画像表示
	/// </summary>
	/// <param name="select">画像が選ばれてるかどうか</param>
	void Draw(bool select,int scroll);

private:
	Vec2 m_pos;//画像位置(真ん中)
	Vec2 m_size;//画像サイズ
	int m_handle;// 画像ハンドル
};


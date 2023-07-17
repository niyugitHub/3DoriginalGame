#pragma once
#include "SceneBase.h"
#include <array>
class SceneExplanation : public SceneBase
{
public:
	SceneExplanation(SceneBase* scene);
	virtual ~SceneExplanation();

	virtual void init();
	virtual SceneBase* update() override;
	virtual void draw();

private:
	enum SelectAction
	{
		Next = 0,		//もう一度同じステージを遊ぶ
		Back = 1,		//ステージセレクト
	};

	void SelectAction();	//次のシーンを決定するための関数

	bool SelectPage();	//ページを移動する際の関数

	//ActionUI情報()
	std::array<UI, 2> m_UI;

	//何ページ目を開いているか
	int m_pageNum;

	// 次のアクションを決めるための変数
	int m_actionNum;

	//ページごとのハンドル
	std::array<int, 4> m_pageHandle;

	//ページごとの動画ハンドル
	std::array<int, 4> m_movieHandle;

	//次のシーン
	SceneBase* m_nextScene = nullptr;
};


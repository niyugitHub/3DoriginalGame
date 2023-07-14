#pragma once
#include "SceneBase.h"
#include <memory>
#include<array>
class SceneOption : public SceneBase
{
public:
	SceneOption(SceneBase* pScene, bool isSceneMain);
	virtual ~SceneOption();

	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;
	virtual void draw() override;

	int GetVolumeBGM() { return m_volumeBGM; }
	int GetVolumeSE() { return m_volumeSE; }

	virtual void normalUpdate() override;

private:

	void SelectUpdate();
	void AccelerateChangeBGMVoluem(); //BGMボリューム設定
	void AccelerateChangeSEVoluem(); //SEボリューム設定

	enum SelectAction
	{
		Bgm,//BGM
		Se,//SE
		StageSelect, //ステージセレクトに戻る
		Back//戻る
	};

	SceneBase* m_pScene;

	std::array<UI,4> m_UI;

	bool m_isSceneMain;//ゲーム中のオプションかどうか

	int m_selectOption; //選択したオプション

	int m_volumeBGM;//BGMボリューム(5段階)
	int m_volumeSE;//SEボリューム(5段階)

	int m_corsorHandle;//カーソルハンドル

	SceneBase* m_nextScene;
};


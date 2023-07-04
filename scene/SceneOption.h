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

private:

	void SelectUpdate();
	void AccelerateChangeBGMVoluem(); //BGMボリューム設定
	void AccelerateChangeSEVoluem(); //SEボリューム設定

	enum
	{
		kBgm,//BGM
		kSe,//SE
		kBack//戻る
	};

	SceneBase* m_pScene;

	std::array<UI,3> m_UI;

	bool m_isSceneMain;//ゲーム中のオプションかどうか

	int m_selectOption; //選択したオプション

	int m_volumeBGM;//BGMボリューム(5段階)
	int m_volumeSE;//SEボリューム(5段階)

	int m_corsorHandle;//カーソルハンドル
};


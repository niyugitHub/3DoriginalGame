#pragma once
#include "SceneBase.h"
#include <EffekseerForDXLib.h>
#include <memory>
#include<array>
class FieldBase;
class Player;
class Camera;
class Map;

class SceneGameClear : public SceneBase
{
public:
	SceneGameClear(std::shared_ptr<Player> pPlayer, std::shared_ptr<FieldBase> pField,
		std::shared_ptr<Camera>pCamera);
	virtual ~SceneGameClear();

	virtual void init();
	virtual SceneBase* update() override;
	virtual void draw();

//	bool GetGameClear() { return m_GameClear; }

private:
	//コインのハンドル
	int m_coinHandle;
	enum
	{
		kRestart = 1,		//もう一度同じステージを遊ぶ
		kStageSelect = 2,	//ステージセレクト
	};

	//エフェクトデータ
	struct Effect
	{
		int resourceHandle = -1;
		int playingEffectHandle = -1;
		Vec2 pos = { 0,0 };
		VECTOR color = {VGet(0.0f,0.0f,0.0f)};
	};

	void DecisionNum(int& selectNum);	//決定表

	//エフェクトの色アップデート(rbg)
	void EffectColor(VECTOR& color,int colorNum);

	int m_selectNum  = kRestart; //選んだ番号
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<FieldBase> m_pField;
	std::shared_ptr<Camera> m_pCamera;

	//UI情報
	std::array<UI, 3> m_UI;

	std::array<Vec2, 3> m_coinPos;//コイン座標

	std::array<Effect, 5> m_data; //エフェクトデータ
};


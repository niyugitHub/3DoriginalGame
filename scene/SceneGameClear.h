#pragma once
#include "SceneBase.h"
#include <memory>
class FieldBase;
class Player;
class Map;

class SceneGameClear : public SceneBase
{
public:
	SceneGameClear(std::shared_ptr<Player> pPlayer, std::shared_ptr<FieldBase> pField);
	virtual ~SceneGameClear();

	virtual void init();
	virtual SceneBase* update() override;
	virtual void draw();

//	bool GetGameClear() { return m_GameClear; }

private:
	enum
	{
		kStageSelect,	//ステージセレクト
		kRestart,		//もう一度同じステージを遊ぶ
		kTitle			//タイトルに戻る
	};

	void DecisionNum(int& selectNum);	//決定表

	int m_selectNum; //選んだ番号
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<FieldBase> m_pField;

};


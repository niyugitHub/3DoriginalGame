#pragma once
#include "SceneBase.h"
#include<memory>

class FieldBase;
class Player;
class Map;

class SceneMain : public SceneBase
{
public:
	SceneMain(std::shared_ptr<FieldBase> Field);
	virtual ~SceneMain();

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

	void IsColl();

	bool StageClear();
private:
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<FieldBase> m_Field;
	bool m_GameClear;	//クリアしたかどうか

	int m_HitCount;

	// シャドウマップ
	int m_shadowMap;

	//スイッチとプレイヤーの当たり判定
	bool m_SwitchColl = false;
	bool m_SwitchColled = false;
};
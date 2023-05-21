#pragma once
#include "SceneBase.h"
#include<memory>

class FieldBase;
class Player;
class Map;
class SceneGameClear;

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

	void IsColl();
private:
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<FieldBase> m_Field;
	std::shared_ptr<SceneGameClear> m_SceneGameClear;
	bool m_GameClear;	//クリアしたかどうか

	int m_HitCount;

	// シャドウマップ
	int m_shadowMap;
};
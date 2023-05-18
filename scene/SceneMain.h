#pragma once
#include "SceneBase.h"
#include<memory>

class Field;
class Player;
class Map;
class SceneGameClear;

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain() {}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;
private:
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Field> m_Field;
	std::shared_ptr<SceneGameClear> m_SceneGameClear;
	bool m_GameClear;	//ÉNÉäÉAÇµÇΩÇ©Ç«Ç§Ç©

	int m_HitCount;
};
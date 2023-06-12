#pragma once
#include "SceneBase.h"
#include <memory>
class SceneOption : public SceneBase
{
public:
	SceneOption(SceneBase* pScene);
	virtual ~SceneOption();

	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;
	virtual void draw() override;

private:
	SceneBase* m_pScene;
};


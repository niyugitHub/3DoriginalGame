#pragma once

#include <memory>

class SceneBase;
class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	void init();
	void end();

	void update();
	void draw();
private:
	//	SceneBase* m_pScene;
	SceneBase* m_pScene;
};
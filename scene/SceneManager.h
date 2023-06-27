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
	void backGraundUpdate();
	//	SceneBase* m_pScene;
	SceneBase* m_pScene;

	int m_backGraundHandle[2];

	int m_backGraundPos[2];
};
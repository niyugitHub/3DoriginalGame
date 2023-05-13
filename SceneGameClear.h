#pragma once
class SceneGameClear
{
public:
	SceneGameClear();
	virtual ~SceneGameClear();

	void Init();
	void Update();
	void Draw();

	bool GetGameClear() { return m_GameClear; }

private:
	bool m_GameClear = false;
};


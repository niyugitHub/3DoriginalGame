#pragma once
#include<vector>
class Map
{
public:
	Map();
	virtual ~Map();

	void Init();
	void Update();
	void Draw();

private:
	std::vector<int> m_MapData;
};


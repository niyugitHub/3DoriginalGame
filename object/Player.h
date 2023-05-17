#pragma once
#include<DxLib.h>
#include<memory>

class Model;

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update();
	void Draw();

	VECTOR GetPos() { return m_Pos; }

private:
	int m_modelHandle;

	VECTOR m_Pos;

	float m_cameraPos;

	//メンバ関数ポインタ
	void (Player::* m_updateFunc)();

	//プレイヤーのモデル
	std::shared_ptr<Model> m_pModel;

	// 再生しているアニメーション番号
	int m_animNo;

	//フレームカウント
	int m_frameCount;

	//プレイヤーの向いている方向
	float m_angle;
};


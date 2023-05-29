#pragma once
#include<DxLib.h>
#include<memory>
#include<vector>
#include"Vec2.h"

class Model;
class Shot;

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update();
	void Draw();

	VECTOR GetPos() { return m_Pos; }
	VECTOR GetNextPos() { return m_NextPos; }

	float GetRadius();

	void SetcolFieldY(bool colFieldY) { m_colFieldY = colFieldY; }

	void SetcolFieldXZ(bool colFieldXZ) { m_colFieldXZ = colFieldXZ; }

	std::vector<Shot*> GetShot() { return m_pShot; }

private:
	void updateIdle();
	void updateMove();
	void updateJump();
	void updateShot();
	void IsMove(bool Left,bool Up,bool Right,bool Bottom, float MoveSpeed);
	void IsAngle(bool Left, bool Up, bool Right, bool Bottom);
	Vec2 IsShot(Vec2 ShotSpeed);


private:
	//プレイヤーのモデル
	std::shared_ptr<Model> m_pModel;
	
	int m_modelHandle; // モデルハンドル

	float m_cameraPos;

	VECTOR m_Pos; // プレイヤーの座標

	VECTOR m_NextPos; // 次のフレームのプレイヤーの座標

	VECTOR m_Vec; // プレイヤーの移動速度

	// 再生しているアニメーション番号
	int m_animNo;

	//フレームカウント
	int m_frameCount;

	//プレイヤーの向いている方向
	float m_angle;

	//フィールドとの当たりy判定
	bool m_colFieldY;

	//フィールドとの当たり判定XZ
	bool m_colFieldXZ;

	//メンバ関数ポインタ
	void (Player::* m_updateFunc)();

	std::vector<Shot*> m_pShot;
};


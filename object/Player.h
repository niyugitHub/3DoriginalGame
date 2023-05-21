#pragma once
#include<DxLib.h>
#include<memory>
#include<vector>

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

	float GetColRadius();

	void SetcolFieldY(bool colFieldY) { m_colFieldY = colFieldY; }

	void SetcolFieldXZ(bool colFieldXZ) { m_colFieldXZ = colFieldXZ; }

private:
	void updateIdle();
	void updateMove();
	void updateJump();
	void updatePunch();
	void IsMove(bool Left,bool Up,bool Right,bool Bottom, float MoveSpeed);
	void IsAngle(bool Left, bool Up, bool Right, bool Bottom);


private:
	int m_modelHandle; // モデルハンドル

	VECTOR m_Pos; // プレイヤーの座標

	VECTOR m_NextPos; // 次のフレームのプレイヤーの座標

	VECTOR m_Vec; // プレイヤーの移動速度

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

	//フィールドとの当たりy判定
	bool m_colFieldY;

	//フィールドとの当たり判定XZ
	bool m_colFieldXZ;

	//ショットのポインター
//	std::vector<std::shared_ptr<Shot>> m_pShot;
};


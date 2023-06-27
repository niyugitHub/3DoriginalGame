#pragma once
#include<DxLib.h>
#include<memory>
#include<vector>
#include "../util/Vec2.h"

class Model;
class Shot;

class Player
{
public:
	Player(VECTOR pos);
	virtual ~Player();

	void Init();
	void Update();
	void Draw();

	VECTOR GetPos() { return m_Pos; }
//	void SetPos(VECTOR pos) { m_Pos = m_NextPos = pos; }
	VECTOR GetNextPos() { return m_NextPos; }

	float GetRadius();

	void SetcolFieldY(bool colFieldY) { m_colFieldY = colFieldY; }

	void SetcolFieldXZ(bool colFieldXZ) { m_colFieldXZ = colFieldXZ; }

	std::vector<Shot*> GetShot() { return m_pShot; } //ショットの情報取得

	void ClearUpdate(); //クリアしたときのアップデート

	void ClearCharaMotion(); //クリアしたときのキャラクターの動き変更

	void SetAttackFlag(bool attackFlag) { m_isAttackFlag = attackFlag; }
	bool GetAttackFlag() { return m_isAttackFlag; }

private:
	void updateIdle();	//アイドル状態時のアップデート
	void updateMove();	//移動状態時のアップデート
	void updateJump();	//ジャンプ状態時のアップデート
	void updatePunch(); //攻撃状態時のアップデート

	void SetAttackPos();
	
	//移動時の処理
	void IsMove(bool Left,bool Up,bool Right,bool Bottom, float MoveSpeed);
	//プレイヤーの向きの処理
	void IsAngle(bool Left, bool Up, bool Right, bool Bottom);
	//プレイヤーの向きによってのショットの方向処理
	Vec2 IsShot(Vec2 ShotSpeed);

private:
	//プレイヤーのモデル
	std::shared_ptr<Model> m_pModel;
	
	int m_modelHandle; // モデルハンドル

	VECTOR m_cameraPos; //カメラポジション

	VECTOR m_cameraTargetPos; //カメラターゲット

	VECTOR m_Pos; // プレイヤーの座標

	VECTOR m_NextPos; // 次のフレームのプレイヤーの座標

	VECTOR m_Vec; // プレイヤーの移動速度

	VECTOR m_attackPos;//攻撃座標

	// 再生しているアニメーション番号
	int m_animNo;

	//フレームカウント
	int m_frameCount;

	//プレイヤーの向いている方向
	float m_angle;

	//カメラの向いている方向
	float m_cameraAngle;

	//フィールドとの当たりy判定
	bool m_colFieldY;

	//フィールドとの当たり判定XZ
	bool m_colFieldXZ;

	//メンバ関数ポインタ
	void (Player::* m_updateFunc)();

	// ショットのポインタ
	std::vector<Shot*> m_pShot;

	//パッドアナログ情報取得
	DINPUT_JOYSTATE m_input;

	int m_inputX;//X軸情報
	int m_inputZ;//Y軸情報

	//攻撃中かどうか
	bool m_isAttackFlag = false;
};


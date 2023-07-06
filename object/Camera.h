#pragma once
#include<DxLib.h>
#include<memory>

class Player;
class Camera
{
public:
	Camera(std::shared_ptr<Player> player);
	~Camera();

	//カメラアップデート
	void Update(std::shared_ptr<Player> player);

	//ステージクリアした際のカメラアップデート
	void ClearUpdate(std::shared_ptr<Player> player, bool menuScreen);

private:
	//カメラポジション
	VECTOR m_cameraPos;
	//カメラターゲット
	VECTOR m_cameraTargetPos;

	//パッドアナログ情報取得
	DINPUT_JOYSTATE m_input;

	int m_inputX;
	int m_inputZ;
};


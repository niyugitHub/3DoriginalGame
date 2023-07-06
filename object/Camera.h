#pragma once
#include<DxLib.h>
#include<memory>

class Player;
class Camera
{
public:
	Camera(std::shared_ptr<Player> player);
	~Camera();

	//�J�����A�b�v�f�[�g
	void Update(std::shared_ptr<Player> player);

	//�X�e�[�W�N���A�����ۂ̃J�����A�b�v�f�[�g
	void ClearUpdate(std::shared_ptr<Player> player, bool menuScreen);

private:
	//�J�����|�W�V����
	VECTOR m_cameraPos;
	//�J�����^�[�Q�b�g
	VECTOR m_cameraTargetPos;

	//�p�b�h�A�i���O���擾
	DINPUT_JOYSTATE m_input;

	int m_inputX;
	int m_inputZ;
};


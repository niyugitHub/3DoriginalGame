#pragma once
#include "SceneBase.h"
#include <memory>
#include<array>
class FieldBase;
class Player;
class Camera;
class Map;

class SceneGameClear : public SceneBase
{
public:
	SceneGameClear(std::shared_ptr<Player> pPlayer, std::shared_ptr<FieldBase> pField,
		std::shared_ptr<Camera>pCamera);
	virtual ~SceneGameClear();

	virtual void init();
	virtual SceneBase* update() override;
	virtual void draw();

//	bool GetGameClear() { return m_GameClear; }

private:
	//�R�C���̃n���h��
	int m_coinHandle;
	enum
	{
		kRestart = 1,		//������x�����X�e�[�W��V��
		kStageSelect = 2,	//�X�e�[�W�Z���N�g
	};

	void DecisionNum(int& selectNum);	//����\

	int m_selectNum  = kRestart; //�I�񂾔ԍ�
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<FieldBase> m_pField;
	std::shared_ptr<Camera> m_pCamera;

	//UI���
	std::array<UI, 3> m_UI;

	std::array<Vec2, 3> m_coinPos;
};


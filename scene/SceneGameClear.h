#pragma once
#include "SceneBase.h"
#include <memory>
class FieldBase;
class Player;
class Map;

class SceneGameClear : public SceneBase
{
public:
	SceneGameClear(std::shared_ptr<Player> pPlayer, std::shared_ptr<FieldBase> pField);
	virtual ~SceneGameClear();

	virtual void init();
	virtual SceneBase* update() override;
	virtual void draw();

//	bool GetGameClear() { return m_GameClear; }

private:
	enum
	{
		kStageSelect,	//�X�e�[�W�Z���N�g
		kRestart,		//������x�����X�e�[�W��V��
		kTitle			//�^�C�g���ɖ߂�
	};

	void DecisionNum(int& selectNum);	//����\

	int m_selectNum; //�I�񂾔ԍ�
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<FieldBase> m_pField;

};


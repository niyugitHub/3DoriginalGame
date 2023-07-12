#pragma once
#include "SceneBase.h"
#include <EffekseerForDXLib.h>
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

	//�G�t�F�N�g�f�[�^
	struct Effect
	{
		int resourceHandle = -1;
		int playingEffectHandle = -1;
		Vec2 pos = { 0,0 };
		VECTOR color = {VGet(0.0f,0.0f,0.0f)};
	};

	void DecisionNum(int& selectNum);	//����\

	//�G�t�F�N�g�̐F�A�b�v�f�[�g(rbg)
	void EffectColor(VECTOR& color,int colorNum);

	int m_selectNum  = kRestart; //�I�񂾔ԍ�
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<FieldBase> m_pField;
	std::shared_ptr<Camera> m_pCamera;

	//UI���
	std::array<UI, 3> m_UI;

	std::array<Vec2, 3> m_coinPos;//�R�C�����W

	std::array<Effect, 5> m_data; //�G�t�F�N�g�f�[�^
};


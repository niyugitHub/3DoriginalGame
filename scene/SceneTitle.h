#pragma once
#include "SceneBase.h"
#include<array>
#include <DxLib.h>

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;
	virtual void draw() override;

private:
	//UI�̃A�b�v�f�[�g
	void UiUpdate();

	void SelectAction();	//����\

	struct Data
	{
		int handle = -1;
		VECTOR pos = {0.0f,0.0f};
		float speed = 0.0f;
		bool isModelUp = false;//���f���̈ړ����㏸�����ǂ���
	};

	struct stringData
	{
		int handle = -1;
		Vec2 pos = {0,0};
		float jumpPower = 0.0f;
	};

	enum //TitleAction
	{
		Instructions = 0,
		Start = 1,
		Exit = 2
	};

	//�u���b�N���f���̃n���h��
	std::array<Data, 4>m_data;

	//�摜UI�̔z��
	std::array<UI, 3> m_UI;

	//�����摜UI�̔z��
	std::array<stringData, 12> m_stringUI;

	UI m_underbar;

	//�I�񂾔ԍ�
	int m_selectNum;
};


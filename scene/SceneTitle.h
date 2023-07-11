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
	struct Data
	{
		int handle = -1;
		VECTOR pos;
		float speed;
		bool isModelUp;//���f���̈ړ����㏸�����ǂ���
	};
	//�u���b�N���f���̃n���h��
	std::array<Data, 4>m_data;
};


#pragma once
#include "SceneBase.h"
#include <memory>
#include<array>
class SceneOption : public SceneBase
{
public:
	SceneOption(SceneBase* pScene, bool isSceneMain);
	virtual ~SceneOption();

	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;
	virtual void draw() override;

	int GetVolumeBGM() { return m_volumeBGM; }
	int GetVolumeSE() { return m_volumeSE; }

private:

	void SelectUpdate();
	void AccelerateChangeBGMVoluem(); //BGM�{�����[���ݒ�
	void AccelerateChangeSEVoluem(); //SE�{�����[���ݒ�

	enum
	{
		kBgm,//BGM
		kSe,//SE
		kBack//�߂�
	};

	SceneBase* m_pScene;

	std::array<UI,3> m_UI;

	bool m_isSceneMain;//�Q�[�����̃I�v�V�������ǂ���

	int m_selectOption; //�I�������I�v�V����

	int m_volumeBGM;//BGM�{�����[��(5�i�K)
	int m_volumeSE;//SE�{�����[��(5�i�K)

	int m_corsorHandle;//�J�[�\���n���h��
};


#pragma once
#include "SceneBase.h"
#include <array>
class SceneExplanation : public SceneBase
{
public:
	SceneExplanation(SceneBase* scene);
	virtual ~SceneExplanation();

	virtual void init();
	virtual SceneBase* update() override;
	virtual void draw();

private:
	enum SelectAction
	{
		Next = 0,		//������x�����X�e�[�W��V��
		Back = 1,		//�X�e�[�W�Z���N�g
	};

	void SelectAction();	//���̃V�[�������肷�邽�߂̊֐�

	bool SelectPage();	//�y�[�W���ړ�����ۂ̊֐�

	//ActionUI���()
	std::array<UI, 2> m_UI;

	//���y�[�W�ڂ��J���Ă��邩
	int m_pageNum;

	// ���̃A�N�V���������߂邽�߂̕ϐ�
	int m_actionNum;

	//�y�[�W���Ƃ̃n���h��
	std::array<int, 4> m_pageHandle;

	//�y�[�W���Ƃ̓���n���h��
	std::array<int, 4> m_movieHandle;

	//���̃V�[��
	SceneBase* m_nextScene = nullptr;
};


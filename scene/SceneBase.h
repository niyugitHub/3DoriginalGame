#pragma once
#include"../util/Vec2.h"
#include<memory>

class ImageUI;
// �Q�[���V�[�����N���X
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}


	virtual void init() {}
	virtual void end()	{}

	virtual SceneBase* update() { return this; }
	virtual void draw() {}

	// �t�F�[�h�֘A
	void updateFade();
	void drawFade() const;

	bool isFadingIn() const;	// �t�F�[�h�C����
	bool isFadingOut() const;	// �t�F�[�h�A�E�g��
	bool isFading() const { return isFadingIn() || isFadingOut(); }	// �t�F�[�h�C��or�A�E�g��

	void startFadeOut();	// �t�F�[�h�A�E�g�J�n

	/// <summary>
	/// �t�F�[�h�̖��邳���擾
	/// </summary>
	/// <returns>0(�t�F�[�h���Ă��Ȃ�)�`255(�^����)</returns>
	int getFadeBright() const { return m_fadeBright; }

protected:
	void SelectSE();//�V�[����I�ԍۂ�SE
	//��UI
	struct UI
	{
		Vec2 pos = { 0.0f,0.0f };
		Vec2 size = {0.0f,0.0f};
		int handle = -1;
	};

	std::shared_ptr<ImageUI> m_pImageUI;//UI�|�C���^�[
private:
	// �t�F�[�h�֘A����
	int m_fadeColor;
	int m_fadeBright;
	int m_fadeSpeed;
};
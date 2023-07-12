#pragma once
#include <vector>
#include <memory>
#include"Vec2.h"
#include<DxLib.h>


class Image;
/// <summary>
/// UI�摜�쐬�N���X
/// </summary>
class ImageUI
{
public:
	ImageUI();
	virtual ~ImageUI();

	
	void AddUI(Vec2 pos, Vec2 size,int handle);
	void Init();

	void FadeinUpdate(); //�t�F�[�h�C������
	void FadeoutUpdate();//�t�F�[�h�A�E�g����
	/// <summary>
	/// �摜�\��
	/// </summary>
	/// <param name="selectNum">�I�΂ꂽ�ԍ��̉摜���������傫������</param>
	void Draw(int selectNum,int scroll);

	bool GetFadein();
	bool GetFadeout();

	int GetScrollSize(int imageNum);

	void SetResetCount() { m_frameCount = 0; }
private:
	//Ui�̃|�C���^�[
	std::vector<std::shared_ptr<Image>>m_pImage;

	int m_frameCount; //�t���[���J�E���g
};

/// <summary>
/// UI�摜�𕡐����ăA�j���[�V��������N���X
/// </summary>
class Image
{
public:
	Image(Vec2 pos, Vec2 size, int handle);
	virtual ~Image();

	void Init();
	void FadeinUpdate(int count);
	void FadeoutUpdate(int count);

	bool GetFadein() { return m_fadeIn; }
	bool GetFadeout() { return m_fadeOut; }

	int GetfadeScroll() { return m_fadeScroll; }

	/// <summary>
	/// �摜�\��
	/// </summary>
	/// <param name="select">�摜���I�΂�Ă邩�ǂ���</param>
	void Draw(bool select,int scroll);

private:
	Vec2 m_pos;//�摜�ʒu(�^��)
	Vec2 m_size;//�摜�T�C�Y
	int m_handle;// �摜�n���h��

	int m_fadeScroll;//�t�F�[�h���邳���̃X�N���[���l

	bool m_fadeIn = false;
	bool m_fadeOut = false;
};


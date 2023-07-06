#pragma once
#include <vector>
#include <memory>
#include"Vec2.h"

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
	void Update();
	/// <summary>
	/// �摜�\��
	/// </summary>
	/// <param name="selectNum">�I�΂ꂽ�ԍ��̉摜���������傫������</param>
	void Draw(int selectNum,int scroll);
private:
	//Ui�̃|�C���^�[
	std::vector<std::shared_ptr<Image>>m_pImage;
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
	void Update();
	/// <summary>
	/// �摜�\��
	/// </summary>
	/// <param name="select">�摜���I�΂�Ă邩�ǂ���</param>
	void Draw(bool select,int scroll);

private:
	Vec2 m_pos;//�摜�ʒu(�^��)
	Vec2 m_size;//�摜�T�C�Y
	int m_handle;// �摜�n���h��
};


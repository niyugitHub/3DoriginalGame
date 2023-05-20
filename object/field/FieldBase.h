#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

class Model;
class Switch;
class FieldBase
{
public:
	FieldBase();
	virtual ~FieldBase();

	void Init();
	void Update();
	void Draw();

	float GetFieldSizeX();	//X���̃t�B�[���h�̒���
	float GetFieldSizeZ();	//Z���̃t�B�[���h�̒���

	enum
	{
		kField = 1,
		kRed = 2,
		kBlue = 3,
		kGreen = 4,
	};

	/*int GetBlockNumX() { return m_blockNum.x; }
	int GetBlockNumZ() { return m_blockNum.z; }*/

	std::vector<std::shared_ptr<Model>> GetModel() { return m_pModel; }

	std::vector<std::shared_ptr<Model>> GetModelRed() { return m_pModelRed; }

	std::vector<std::shared_ptr<Model>> GetModelBlue() { return m_pModelBlue; }

	std::vector<std::shared_ptr<Switch>> GetSwitch() { return m_pSwitch; }

	int GetLookBlock() { return m_lookBlock; }

protected:
	//���f���̃|�C���^�[
	std::vector<std::shared_ptr<Model>> m_pModel;

	//���f���̃|�C���^�[(��)
	std::vector<std::shared_ptr<Model>> m_pModelRed;

	//���f���̃|�C���^�[(��)
	std::vector<std::shared_ptr<Model>> m_pModelBlue;

	//�X�C�b�`�̃|�C���^�[
	std::vector<std::shared_ptr<Switch>> m_pSwitch;

	//�u���b�N�̔ԍ�(�ԍ��ɂ���ău���b�N�̐F���ς��)
	std::vector<int> m_blockNum; 

	//��������u���b�N�̔ԍ�
	int m_lookBlock;
};


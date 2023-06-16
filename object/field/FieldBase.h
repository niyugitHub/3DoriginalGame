#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

class Model;
class Switch;
class Goal;

class FieldBase
{
protected:
	//���[�h����ۂ̃f�[�^�\����
	struct loadData
	{
		const char* fileName;//�t�@�C����
		int blockNumX;//X���̃u���b�N�̐�
		int blockNumZ;//Y���̃u���b�N�̐�
	};
public:
	FieldBase();
	virtual ~FieldBase();

	void Init(loadData data);
	void Update();
	void Draw();
	
	void FirstModelLoad(); // ���f�����[�h(�ŏ��̈����)

	void LoadFile(const char* fileName);

	void ModelLoad(int Model1, int Model2, int Model3, int Model4);//���f�����[�h(�S���̃��f��)

	void ChangeBlock();

	float GetFieldSizeX();	//X���̃t�B�[���h�̒���
	float GetFieldSizeZ();	//Z���̃t�B�[���h�̒���

	VECTOR GetPlayerPos() { return m_playerPos; }

	void StageClear();

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

	std::vector<std::shared_ptr<Model>> GetModelGreen() { return m_pModelGreen; }

	std::vector<std::shared_ptr<Switch>> GetSwitch() { return m_pSwitch; }

	std::shared_ptr<Goal> GetGoal() { return m_pGoal; }

	int GetLookBlock() { return m_lookBlock; }

protected:
	//���f���̃|�C���^�[
	std::vector<std::shared_ptr<Model>> m_pModel;

	//���f���̃|�C���^�[(��)
	std::vector<std::shared_ptr<Model>> m_pModelRed;

	//���f���̃|�C���^�[(��)
	std::vector<std::shared_ptr<Model>> m_pModelBlue;

	//���f���̃|�C���^�[(��)
	std::vector<std::shared_ptr<Model>> m_pModelGreen;

	//�X�C�b�`�̃|�C���^�[
	std::vector<std::shared_ptr<Switch>> m_pSwitch;

	//�S�[���̃|�C���^�[
	std::shared_ptr<Goal> m_pGoal;

	//�u���b�N�̔ԍ�(�ԍ��ɂ���ău���b�N�̐F���ς��)
	std::vector<int> m_blockNum; 

	int m_lookBlock;//��������u���b�N�̔ԍ�
	int m_blockKinds;//�X�e�[�W�Ŏg����u���b�N�̎��

	loadData m_data; // ���[�h�f�[�^

	//�v���C���[�����ʒu
	VECTOR m_playerPos;

	//�X�e�[�W�ԍ�
	int m_stageNum;

	//�X�^�[�擾���(�X�^�[�̐���3��)
	bool m_getStar[3];
};


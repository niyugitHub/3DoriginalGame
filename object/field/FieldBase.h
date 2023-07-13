#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

class Block;
class Switch;
class Goal;
class Item;
class HalfwayPoint;

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

	void Init();

	//�v���C���[���S���Ƀ��Z�b�g
	void Reset();
	void Update();
	void Draw();
	
	//void FirstModelLoad(); // ���f�����[�h(�ŏ��̈����)

	void LoadFile(const char* fileName);

	void ModelLoad(int Model1, int Model2, int Model3, int Model4);//���f�����[�h(�S���̃��f��)

	void ChangeBlock();

	float GetFieldSizeX();	//X���̃t�B�[���h�̒���
	float GetFieldSizeZ();	//Z���̃t�B�[���h�̒���

	VECTOR GetPlayerPos() { return m_playerPos; }

	void StageClear();

	enum BlockKind
	{
		Field = 1,
		Red = 2,
		Blue = 3,
		Green = 4,
		PlayerPos = 5,
		ItemObj = 6,
		HalfwayPointObj = 7,
		SwitchObj = 8,
		GoalObj = 10,
	};

	/*int GetBlockNumX() { return m_blockNum.x; }
	int GetBlockNumZ() { return m_blockNum.z; }*/

	std::vector<std::shared_ptr<Block>> GetBlock() { return m_pBlock; }

	std::vector<std::shared_ptr<Switch>> GetSwitch() { return m_pSwitch; }

	std::shared_ptr<Goal> GetGoal() { return m_pGoal; }

	std::shared_ptr<Item> GetItem() { return m_pItem; }

	std::shared_ptr<HalfwayPoint> GetHalfwayPoint() { return m_pHalfwayPoint; }

	int GetLookBlock() { return m_lookBlock; }

	bool GetStar(int i) { return m_getStar[i]; }

	void ResetTime() { m_gameFrameCount = 0; }

	//�v���C���[�̃��X�|�[���ʒu�ύX
	void OnSetPlayerRespawn();

	void SetmHalfwayPointItem(bool getItem) { m_halfwayPointItem = getItem; }

protected:
	int m_lookBlock;//��������u���b�N�̔ԍ�
	int m_blockKinds;//�X�e�[�W�Ŏg����u���b�N�̎��
	
	//�v���C���[�����ʒu
	VECTOR m_playerPos;
	
	//�X�e�[�W�ԍ�
	int m_stageNum;

	//�Q�[�����n�܂��Ă���̎���
	int m_gameFrameCount;

	//�A�C�e�����擾�������ǂ���
	bool m_getItem;

	//���ԃ|�C���g�̑O�ɃA�C�e�����擾���Ă������ǂ���
	bool m_halfwayPointItem;

	//�X�^�[�����炤���߂̐�������
	int m_limitFrame;

	//�X�^�[�擾���(�X�^�[�̐���3��)
	bool m_getStar[3];

	loadData m_data; // ���[�h�f�[�^

	//�t�B�[���h�̃|�C���^�[
	std::vector<std::shared_ptr<Block>> m_pBlock;

	//�X�C�b�`�̃|�C���^�[
	std::vector<std::shared_ptr<Switch>> m_pSwitch;

	//�S�[���̃|�C���^�[
	std::shared_ptr<Goal> m_pGoal;

	//�A�C�e���̃|�C���^�[
	std::shared_ptr<Item> m_pItem;

	//���ԃ|�C���g�̃|�C���^�[
	std::shared_ptr<HalfwayPoint> m_pHalfwayPoint;

	////�u���b�N�̔ԍ�(�ԍ��ɂ���ău���b�N�̐F���ς��)
	std::vector<int> m_blockNum; 
};


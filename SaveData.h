#pragma once

namespace SaveData
{
	//�X�^�[�̎擾��ԏ�����(�������񂾃t�@�C���͕ς��Ȃ�)
	void Init();
	/// <summary>
	/// �Z�[�u�f�[�^�̃A�b�v�f�[�g
	/// </summary>
	/// <param name="stageNum">�X�e�[�W�ԍ�</param>
	/// <param name="getStar">�X�^�[�擾���(1�X�e�[�W�ɂ�3��)</param>
	void Update(int stageNum, bool getStar[]);
	//�Z�[�u�f�[�^�ǂݍ���
	void Read();
	//�Z�[�u�f�[�^��������
	void Write();

	void Draw();

	bool GetStar(int i, int j);
}
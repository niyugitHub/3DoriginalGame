#pragma once

namespace SaveData
{
	//�X�^�[�̎擾��ԏ�����(�������񂾃t�@�C���͕ς��Ȃ�)
	void Init();
	//�Z�[�u�f�[�^�A�b�v�f�[�g
	void Update(int stageNum, bool getStar[]);
	//�Z�[�u�f�[�^�ǂݍ���
	void Read();
	//�Z�[�u�f�[�^��������
	void Write();

	void Draw();
}
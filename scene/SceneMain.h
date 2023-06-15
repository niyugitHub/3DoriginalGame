#pragma once
#include "SceneBase.h"
#include<memory>

class FieldBase;
class Player;
class Map;

class SceneMain : public SceneBase
{
public:
	SceneMain(std::shared_ptr<FieldBase> Field);
	virtual ~SceneMain();

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

	void IsColl();

	bool StageClear();
private:
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<FieldBase> m_Field;
	bool m_GameClear;	//�N���A�������ǂ���

	int m_HitCount;

	// �V���h�E�}�b�v
	int m_shadowMap;

	//�X�C�b�`�ƃv���C���[�̓����蔻��
	bool m_SwitchColl = false;
	bool m_SwitchColled = false;
};
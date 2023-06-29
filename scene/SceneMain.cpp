#include "DxLib.h"
#include "../game.h"
#include "SceneMain.h"
#include "SceneDebug.h"
#include "../object/field/FieldBase.h"
#include "../object/field/Field1.h"
#include "../object/Player.h"
#include "../object/Camera.h"
#include "SceneGameClear.h"
#include "SceneOption.h"
#include"../object/Model.h"
#include"../object/Shot.h"
#include"../object/Switch.h"
#include"../object/Goal.h"
#include"../object/Item.h"

#include "../util/Pad.h"

#include <cassert>

namespace
{
	
}

SceneMain::SceneMain(std::shared_ptr<FieldBase> Field) :
	m_GameClear(false),
	m_HitCount(0)
{
	m_Field = Field;
	m_Player = std::make_shared<Player>(m_Field->GetPlayerPos());
	m_Camera = std::make_shared<Camera>(m_Player);
//	m_Player->SetPos(m_Field->GetPlayerPos());

	//3D�֘A�̐ݒ�

	//Z�o�b�t�@���g�p����
	SetUseZBuffer3D(true);
	//Z�o�b�t�@�ւ̏������݂��s��
	SetWriteZBuffer3D(true);

	//�|���S���̗��ʂ�`�悵�Ȃ�
	SetUseBackCulling(true);


	// �J�����̐ݒ�
	// �ǂ��܂ŕ\�����邩
	SetCameraNearFar(5.0f, 2800.0f);
	// �J�����̎���p(���W�A��)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// �J�����̈ʒu�A�ǂ�����ǂ������Ă��邩��ݒ�
	SetCameraPositionAndTarget_UpVecY(VGet(0, 1500, -800), VGet(0.0f, 0.0f, 0.0f));

	m_Player->Init();
	//m_Field->Init();

	//SetLightPosition(VGet(-1500, -1500 , 1000));
	SetLightDirection(VGet(300, -1000, 300));
	//SetLightDirection(GetLightDirection());
	// �V���h�E�}�b�v�̐���
	m_shadowMap = MakeShadowMap(4096, 4096);
	SetShadowMapLightDirection(m_shadowMap, GetLightDirection());
}

SceneMain::~SceneMain()
{
	
}

void SceneMain::init()
{
	////3D�֘A�̐ݒ�

	////Z�o�b�t�@���g�p����
	//SetUseZBuffer3D(true);
	////Z�o�b�t�@�ւ̏������݂��s��
	//SetWriteZBuffer3D(true);

	////�|���S���̗��ʂ�`�悵�Ȃ�
	//SetUseBackCulling(true);


	//// �J�����̐ݒ�
	//// �ǂ��܂ŕ\�����邩
	//SetCameraNearFar(5.0f, 2800.0f);
	//// �J�����̎���p(���W�A��)
	//SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	//// �J�����̈ʒu�A�ǂ�����ǂ������Ă��邩��ݒ�
	//SetCameraPositionAndTarget_UpVecY(VGet(0, 1500, -800), VGet(0.0f, 0.0f, 0.0f));

	//m_Player->Init();
	////m_Field->Init();

	////SetLightPosition(VGet(-1500, -1500 , 1000));
	//SetLightDirection(VGet(300, -1000 , 300));
	//SetLightDirection(GetLightDirection());
	//// �V���h�E�}�b�v�̐���
	//m_shadowMap = MakeShadowMap(4096, 4096);
	//SetShadowMapLightDirection(m_shadowMap, GetLightDirection());
}

void SceneMain::end()
{
	
}

SceneBase* SceneMain::update()
{
	/*if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_Player->ClearCharaMotion();
		m_Field->StageClear();
		return new SceneGameClear(m_Player, m_Field);
	}*/

	if (StageClear())
	{
		m_GameClear = true;
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
	}

	m_Player->Update();
	m_Camera->Update(m_Player);
	m_Field->Update();
	
	if (m_GameClear)
	{
		m_Player->ClearCharaMotion();
		m_Field->StageClear();
		return new SceneGameClear(m_Player, m_Field,m_Camera);
	}

//	int a = m_Field->GetModel().size();

	IsColl();

	updateFade();

	if (m_Player->GetPos().y < -500)
	{
		return new SceneMain(m_Field);
	}

	if (Pad::isTrigger(PAD_INPUT_8))
	{
		//���g�̃|�C���^�[�A�Q�[�����̃I�v�V������ʂ��̃t���O�������Ɏ���
		return new SceneOption(this,true);
	}

	return this;
}

void SceneMain::draw()
{
	DrawString(64, 64,"����͂ŃN���A",0xffffff);

	// �V���h�E�}�b�v�ւ̏�������
	ShadowMap_DrawSetup(m_shadowMap);

	m_Player->Draw();
	m_Field->Draw();

	ShadowMap_DrawEnd();

	// �V���h�E�}�b�v���g�p���ă��f���̕`����s��
	SetUseShadowMap(0, m_shadowMap);

	m_Player->Draw();
	m_Field->Draw();

	SetUseShadowMap(0, -1);

	/*if (m_GameClear)
	{
		m_SceneGameClear->Draw();
	}*/

	//-500~500�͈̔͂ɃO���b�h��\��
	/*for (float x = -500.0f; x <= 500.0f; x += 100)
	{
		VECTOR start = VGet(x, 0.0f, -500.0f);
		VECTOR end = VGet(x, 0.0f, 500.0f);
		DrawLine3D(start, end, 0xff00ff);
	}
	for (float z = -500.0f; z <= 500.0f; z += 100)
	{
		VECTOR start = VGet(-500.0f, 0.0f, z);
		VECTOR end = VGet(500.0f, 0.0f, z);
		DrawLine3D(start, end, 0xffff00);
	}*/


	SceneBase::drawFade();
}

void SceneMain::IsColl()
{
	VECTOR PlayerPos = m_Player->GetPos();

	if (m_Field->GetItem()->GetExist())
	{
		VECTOR ItemToPlayer = VSub(PlayerPos,m_Field->GetItem()->GetPos());
		float dist = VSize(ItemToPlayer);

		if (dist < (m_Player->GetRadius() + m_Field->GetItem()->GetRadius()))
		{
			m_Field->GetItem()->SetExist();
		}
	}

	for (auto& pSwitch : m_Field->GetSwitch())
	{
		VECTOR switchPos = pSwitch->GetPos();
		VECTOR toSwitch = VSub(PlayerPos, switchPos);

		float dist = VSize(toSwitch);
		if (dist < (m_Player->GetRadius() + pSwitch->GetRadius()) && m_Player->GetAttackFlag())
		{
			// ��������
			m_SwitchColl = true;
			m_Player->SetAttackFlag(false);
			break;
			
		}
		else
		{
			m_SwitchColl = false;
		}
	}
	
	if (m_SwitchColl)
	{
		if (!m_SwitchColled)
		{
			m_Field->ChangeBlock();
			m_SwitchColled = true;
		}
	}
	else
	{
		m_SwitchColled = false;
	}

	for (auto& pModel : m_Field->GetModel())
	{
		// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
		MV1_COLL_RESULT_POLY_DIM result;	// ������f�[�^

		VECTOR pos = m_Player->GetNextPos();
		pos.y = m_Player->GetNextPos().y + 60;

		//result = MV1CollCheck_Sphere(Enemy->getModelHandle(), -1, Shot->getPos(), Shot->getRadius());
		result = MV1CollCheck_Capsule(pModel->getModelHandle(), pModel->getColFrameIndex(),
			pos, pos, m_Player->GetRadius());

		//�|���S������ł��������Ă����ꍇ
		if (result.HitNum > 0)
		{
			m_HitCount++;
		//	printfDx("Hit %d\n", m_HitCount);
			//pModel->OnDamage(10);

			m_Player->SetcolFieldY(true);

			if (m_Player->GetPos().y - 80 < pModel->GetPos().y) // ���������t�B�[���h���v���C���[�̈ʒu���Ⴂ�Ƃ�
			{
				m_Player->SetcolFieldXZ(true);
				m_Player->SetcolFieldY(false);
			}
			// �����蔻����̌�n��
			MV1CollResultPolyDimTerminate(result);
			return;
		}

		// �����蔻����̌�n��
		MV1CollResultPolyDimTerminate(result);
	}
	
	for (auto& pModel : m_Field->GetModelRed())
	{
		// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
		MV1_COLL_RESULT_POLY_DIM result;	// ������f�[�^

		VECTOR pos = m_Player->GetNextPos();
		pos.y = m_Player->GetNextPos().y + 60;

		//result = MV1CollCheck_Sphere(Enemy->getModelHandle(), -1, Shot->getPos(), Shot->getRadius());
		result = MV1CollCheck_Capsule(pModel->getModelHandle(), pModel->getColFrameIndex(),
			pos, pos, m_Player->GetRadius());

		//�|���S������ł��������Ă����ꍇ
		if (result.HitNum > 0)
		{
			m_HitCount++;
		//	printfDx("Hit %d\n", m_HitCount);
			//pModel->OnDamage(10);

			m_Player->SetcolFieldY(true);

			if (m_Player->GetPos().y - 80 < pModel->GetPos().y) // ���������t�B�[���h���v���C���[�̈ʒu���Ⴂ�Ƃ�
			{
				m_Player->SetcolFieldXZ(true);
				m_Player->SetcolFieldY(false);
			}
			// �����蔻����̌�n��
			MV1CollResultPolyDimTerminate(result);
			return;
		}

		//	// �����蔻����̌�n��
		MV1CollResultPolyDimTerminate(result);
	}
	
	for (auto& pModel : m_Field->GetModelBlue())
	{
		// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
		MV1_COLL_RESULT_POLY_DIM result;	// ������f�[�^

		VECTOR pos = m_Player->GetNextPos();
		pos.y = m_Player->GetNextPos().y + 60;

		//result = MV1CollCheck_Sphere(Enemy->getModelHandle(), -1, Shot->getPos(), Shot->getRadius());
		result = MV1CollCheck_Capsule(pModel->getModelHandle(), pModel->getColFrameIndex(),
			pos, pos, m_Player->GetRadius());

		//�|���S������ł��������Ă����ꍇ
		if (result.HitNum > 0)
		{
			m_HitCount++;
		//	printfDx("Hit %d\n", m_HitCount);
			//pModel->OnDamage(10);

			m_Player->SetcolFieldY(true);

			if (m_Player->GetPos().y - 80 < pModel->GetPos().y) // ���������t�B�[���h���v���C���[�̈ʒu���Ⴂ�Ƃ�
			{
				m_Player->SetcolFieldXZ(true);
				m_Player->SetcolFieldY(false);
			}
			// �����蔻����̌�n��
			MV1CollResultPolyDimTerminate(result);
			return;
		}

		// �����蔻����̌�n��
		MV1CollResultPolyDimTerminate(result);
	}
	
	for (auto& pModel : m_Field->GetModelGreen())
	{
		// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
		MV1_COLL_RESULT_POLY_DIM result;	// ������f�[�^

		VECTOR pos = m_Player->GetNextPos();
		pos.y = m_Player->GetNextPos().y + 60;

		//result = MV1CollCheck_Sphere(Enemy->getModelHandle(), -1, Shot->getPos(), Shot->getRadius());
		result = MV1CollCheck_Capsule(pModel->getModelHandle(), pModel->getColFrameIndex(),
			pos, pos, m_Player->GetRadius());

		//�|���S������ł��������Ă����ꍇ
		if (result.HitNum > 0)
		{
			m_HitCount++;
			//	printfDx("Hit %d\n", m_HitCount);
				//pModel->OnDamage(10);

			m_Player->SetcolFieldY(true);

			if (m_Player->GetPos().y - 80 < pModel->GetPos().y) // ���������t�B�[���h���v���C���[�̈ʒu���Ⴂ�Ƃ�
			{
				m_Player->SetcolFieldXZ(true);
				m_Player->SetcolFieldY(false);
			}
			// �����蔻����̌�n��
			MV1CollResultPolyDimTerminate(result);
			return;
		}

		// �����蔻����̌�n��
		MV1CollResultPolyDimTerminate(result);
	}
}

bool SceneMain::StageClear()
{
	VECTOR GoalPos = m_Field->GetGoal()->GetPos();
	VECTOR PlayerPos = m_Player->GetPos();
	VECTOR toGoal = VSub(GoalPos, PlayerPos);

	float dist = VSize(toGoal);
	if (dist < (m_Field->GetGoal()->GetRadius() + m_Player->GetRadius()))
	{
		return true;
	}
	return false;
}


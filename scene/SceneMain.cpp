#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneDebug.h"
#include "../object/field/FieldBase.h"
#include "../object/field/Field1.h"
#include "Player.h"
#include "SceneGameClear.h"
#include"Model.h"

#include "Pad.h"

#include <cassert>

namespace
{
	
}

SceneMain::SceneMain() : 
	m_GameClear(false),
	m_HitCount(0)
{
	m_Player = std::make_shared<Player>();
	m_Field = std::make_shared<Field1>();
	m_SceneGameClear = std::make_shared<SceneGameClear>();
}

void SceneMain::init()
{
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
	m_Field->Init();

	//SetLightPosition(VGet(-1500, -1500 , 1000));
	SetLightDirection(VGet(300, -1000 , 300));
	SetLightDirection(GetLightDirection());
	// �V���h�E�}�b�v�̐���
	m_shadowMap = MakeShadowMap(4096, 4096);
	SetShadowMapLightDirection(m_shadowMap, GetLightDirection());
}

void SceneMain::end()
{
	
}

SceneBase* SceneMain::update()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
	}

	/*if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_GameClear = true;
	}*/
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
	}

	m_Player->Update();
	m_Field->Update();
	
	if (m_GameClear)
	{
		m_SceneGameClear->Update();
	}

//	int a = m_Field->GetModel().size();

	IsColl();

	//for (auto& pModel : m_Field->GetModel())
	//{
	//	// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
	//	MV1_COLL_RESULT_POLY_DIM result;	// ������f�[�^

	//	VECTOR pos = m_Player->GetNextPos();
	//	pos.y = m_Player->GetNextPos().y + 60;

	//	//result = MV1CollCheck_Sphere(Enemy->getModelHandle(), -1, Shot->getPos(), Shot->getRadius());
	//	result = MV1CollCheck_Capsule(pModel->getModelHandle(), pModel->getColFrameIndex(),
	//		pos, pos, m_Player->GetColRadius());

	//	//�|���S������ł��������Ă����ꍇ
	//	if (result.HitNum > 0)
	//	{
	//		m_HitCount++;
	//		printfDx("Hit %d\n", m_HitCount);
	//		//pModel->OnDamage(10);

	//		m_Player->SetcolFieldY(true);

	//		if (m_Player->GetPos().y - 80 < pModel->GetPos().y) // ���������t�B�[���h���v���C���[�̈ʒu���Ⴂ�Ƃ�
	//		{
	//			m_Player->SetcolFieldXZ(true);
	//			m_Player->SetcolFieldY(false);
	//		}
	//		// �����蔻����̌�n��
	//		MV1CollResultPolyDimTerminate(result);
	//		break;
	//	}

	//	// �����蔻����̌�n��
	//	MV1CollResultPolyDimTerminate(result);
	//}

	updateFade();

	if (m_SceneGameClear->GetGameClear())
	{
		return new SceneDebug();
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

	if (m_GameClear)
	{
		m_SceneGameClear->Draw();
	}

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
	for (auto& pModel : m_Field->GetModel())
	{
		// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
		MV1_COLL_RESULT_POLY_DIM result;	// ������f�[�^

		VECTOR pos = m_Player->GetNextPos();
		pos.y = m_Player->GetNextPos().y + 60;

		//result = MV1CollCheck_Sphere(Enemy->getModelHandle(), -1, Shot->getPos(), Shot->getRadius());
		result = MV1CollCheck_Capsule(pModel->getModelHandle(), pModel->getColFrameIndex(),
			pos, pos, m_Player->GetColRadius());

		//�|���S������ł��������Ă����ꍇ
		if (result.HitNum > 0)
		{
			m_HitCount++;
			printfDx("Hit %d\n", m_HitCount);
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

	if (m_Field->GetLookBlock() == FieldBase::kRed)
	{
		for (auto& pModel : m_Field->GetModelRed())
		{
			// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
			MV1_COLL_RESULT_POLY_DIM result;	// ������f�[�^

			VECTOR pos = m_Player->GetNextPos();
			pos.y = m_Player->GetNextPos().y + 60;

			//result = MV1CollCheck_Sphere(Enemy->getModelHandle(), -1, Shot->getPos(), Shot->getRadius());
			result = MV1CollCheck_Capsule(pModel->getModelHandle(), pModel->getColFrameIndex(),
				pos, pos, m_Player->GetColRadius());

			//�|���S������ł��������Ă����ꍇ
			if (result.HitNum > 0)
			{
				m_HitCount++;
				printfDx("Hit %d\n", m_HitCount);
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
	}


	if (m_Field->GetLookBlock() == FieldBase::kBlue)
	{
		for (auto& pModel : m_Field->GetModelBlue())
		{
			// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
			MV1_COLL_RESULT_POLY_DIM result;	// ������f�[�^

			VECTOR pos = m_Player->GetNextPos();
			pos.y = m_Player->GetNextPos().y + 60;

			//result = MV1CollCheck_Sphere(Enemy->getModelHandle(), -1, Shot->getPos(), Shot->getRadius());
			result = MV1CollCheck_Capsule(pModel->getModelHandle(), pModel->getColFrameIndex(),
				pos, pos, m_Player->GetColRadius());

			//�|���S������ł��������Ă����ꍇ
			if (result.HitNum > 0)
			{
				m_HitCount++;
				printfDx("Hit %d\n", m_HitCount);
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
}


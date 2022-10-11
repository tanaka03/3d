//��������������������������
//camera.cpp
//��������������������������
#include "application.h"
#include "camera.h"
#include "input.h"
#include "keyboard.h"
#include "player.h"

CCamera::CCamera()
{
	memset(&m_camera, 0, sizeof(CCamera));
	m_bTraction = false;
}

CCamera::~CCamera()
{
}

//��������������������������
//�J�����̏�����
//��������������������������
HRESULT CCamera::Init()
{
	//���_�E�����_�E�������ݒ肷��
	m_camera.posV = D3DXVECTOR3(0.0f, 150.0f, 300.0f);	//���_
	m_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̎��_
	m_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����_
	m_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̒����_
	m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//������x�N�g��
	m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̌���

	//�O���������Ȃ񂾂��̂��
	float x = m_camera.posR.x - m_camera.posV.x;
	float z = m_camera.posR.z - m_camera.posV.z;
	m_camera.fDistance = sqrtf((x * x) + (z * z));		//���_���璍���_�̋���

	return S_OK;
}

//��������������������������
//�J�����̏I��
//��������������������������
void CCamera::Uninit()
{
}

//��������������������������
//�J�����̍X�V
//��������������������������
void CCamera::Update()
{	
	//===========================
	//�����_
	//===========================
	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_Q))
	{
		m_camera.rot.y -= 0.05f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//�E
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_E))
	{
		m_camera.rot.y += 0.05f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//===========================
	//���_
	//===========================
	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_J))
	{
		m_camera.rot.y -= 0.05f;
		m_camera.posV.x = m_camera.posR.x + sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posV.z = m_camera.posR.z + cosf(m_camera.rot.y) * m_camera.fDistance;
	}
	
	//�E
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_L))
	{
		m_camera.rot.y += 0.05f;
		m_camera.posV.x = m_camera.posR.x + sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posV.z = m_camera.posR.z + cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//===========================
	//�J�����ړ�
	//===========================
	//�O
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_W))
	{
		m_camera.posV.x -= sinf(m_camera.rot.y) * 0.8f;
		m_camera.posV.z -= cosf(m_camera.rot.y) * 0.8f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_S))
	{
		m_camera.posV.x += sinf(m_camera.rot.y) * 0.8f;
		m_camera.posV.z += cosf(m_camera.rot.y) * 0.8f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//�E
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_D))
	{
		m_camera.posV.x -= sinf(m_camera.rot.y + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posV.z -= cosf(m_camera.rot.y + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_A))
	{
		m_camera.posV.x += sinf(m_camera.rot.y + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posV.z += cosf(m_camera.rot.y + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//�㏸
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_R))
	{
		m_camera.posV.y += sinf(m_camera.rot.x + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posV.y += cosf(m_camera.rot.z + D3DX_PI * 0.5f) * 0.8f;
	}

	//���~
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_F))
	{
		m_camera.posV.y -= sinf(m_camera.rot.x + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posV.y -= cosf(m_camera.rot.z + D3DX_PI * 0.5f) * 0.8f;
	}

	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_I))
	{
		m_camera.rot.x -= 0.05f;
		m_camera.posR.y = m_camera.posV.y - tanf(m_camera.rot.x) * m_camera.fDistance;
	}

	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_K))
	{
		m_camera.rot.x += 0.05f;
		m_camera.posR.y = m_camera.posV.y - tanf(m_camera.rot.x) * m_camera.fDistance;
	}
	
	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_Z))
	{
		m_bTraction = ((!m_bTraction) ? true : false);
	}

	//===========================
	//���f���ɒǏ]
	//===========================
	//if (m_bTraction)
	//{
	//	for (int i = 0; i < MAX_OBJECT; i++)
	//	{
	//		CObject *pObject = nullptr;
	//		pObject = pObject->GetMyObject(i);

	//		if (pObject == nullptr)
	//		{
	//			continue;
	//		}

	//		CObject::EObjType objType;
	//		objType = pObject->GetObjType();

	//		if (objType != CObject::OBJTYPE_PLAYER)
	//		{
	//			continue;
	//		}
	//		CPlayer *pPlayer = (CPlayer*)pObject;

	//		m_camera.posR.x += (m_camera.posRDest.x - m_camera.posR.x) * 0.5f;
	//		m_camera.posV.x += (m_camera.posVDest.x - m_camera.posV.x) * 0.5f;

	//		m_camera.posR.z += (m_camera.posRDest.z - m_camera.posR.z) * 0.5f;
	//		m_camera.posV.z += (m_camera.posVDest.z - m_camera.posV.z) * 0.5f;

	//		m_camera.posRDest.x = pPlayer->GetPos().x + sinf(pPlayer->GetRot().y) * 0.5f;
	//		m_camera.posRDest.z = pPlayer->GetPos().z + cosf(pPlayer->GetRot().y) * 0.5f;

	//		m_camera.posVDest.x = pPlayer->GetPos().x + sinf(m_camera.rot.x) * m_camera.fDistance;
	//		m_camera.posVDest.z = pPlayer->GetPos().z + cosf(m_camera.rot.z) * m_camera.fDistance;
	//	}
	//}

	//======================
	//���K��
	//======================
	if (m_camera.rot.y > D3DX_PI)
	{
		m_camera.rot.y -= D3DX_PI * 2;
	}

	else if (m_camera.rot.y < -D3DX_PI)
	{
		m_camera.rot.y += D3DX_PI * 2;
	}

	//======================
	//�Ȃ񂩂��낢��
	//======================
	//�����̈ʒu�ɖ߂�
	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_F1) == true)
	{
		//���_�E�����_�E�������ݒ肷��
		m_camera.posV = D3DXVECTOR3(0.0f, 150.0f, 300.0f);	//���_
		m_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����_
		m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//������x�N�g��
		m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	}
}

//��������������������������
//�J�����̐ݒ�
//��������������������������
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_camera.mtxView,
		&m_camera.posV,
		&m_camera.posR,
		&m_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		5.0f,
		1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_camera.mtxProjection);
}
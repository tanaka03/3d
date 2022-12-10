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
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	CPlayer *pPlayer = CApplication::GetInstance()->GetPlayer();
	D3DXMATRIX mtxTrans, mtxRot;

	//===========================
	//�����_
	//===========================
	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_Q))
	{
		m_camera.rot.y -= 0.05f;
	}

	//�E
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_E))
	{
		m_camera.rot.y += 0.05f;
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

	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_R))
	{
		m_camera.posV.y -= 0.5f;
		m_camera.posV.z -= 1.5f;
	}

	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_F))
	{
		m_camera.posV.y += 0.5f;
		m_camera.posV.z += 1.5f;
	}

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_camera.rot.y, m_camera.rot.x, m_camera.rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pPlayer->GetPos().x, pPlayer->GetPos().y, pPlayer->GetPos().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	D3DXVec3TransformCoord(&m_worldposV, &m_camera.posV, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_worldposR, &m_camera.posR, &m_mtxWorld);

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
		&m_worldposV,
		&m_worldposR,
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
		10000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_camera.mtxProjection);
}
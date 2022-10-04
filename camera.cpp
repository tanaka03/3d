//��������������������������
//camera.cpp
//��������������������������
#include "application.h"
#include "camera.h"
#include "input.h"
#include "keyboard.h"

CCamera::CCamera()
{
	memset(&m_camera, 0, sizeof(CCamera));
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
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_Q) == true)
	{
		m_camera.rot.y -= 0.05f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//�E
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_E) == true)
	{
		m_camera.rot.y += 0.05f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//===========================
	//���_
	//===========================
	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_J) == true)
	{
		m_camera.rot.y -= 0.05f;
		m_camera.posV.x = m_camera.posR.x + sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posV.z = m_camera.posR.z + cosf(m_camera.rot.y) * m_camera.fDistance;
	}
	
	//�E
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_L) == true)
	{
		m_camera.rot.y += 0.05f;
		m_camera.posV.x = m_camera.posR.x + sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posV.z = m_camera.posR.z + cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//===========================
	//�J�����ړ�
	//===========================
	//�O
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{
		m_camera.posV.x -= sinf(m_camera.rot.y) * 0.8f;
		m_camera.posV.z -= cosf(m_camera.rot.y) * 0.8f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{
		m_camera.posV.x += sinf(m_camera.rot.y) * 0.8f;
		m_camera.posV.z += cosf(m_camera.rot.y) * 0.8f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//�E
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{
		m_camera.posV.x -= sinf(m_camera.rot.y + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posV.z -= cosf(m_camera.rot.y + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{
		m_camera.posV.x += sinf(m_camera.rot.y + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posV.z += cosf(m_camera.rot.y + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//�㏸
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_R) == true)
	{
		m_camera.posV.y += sinf(m_camera.rot.x + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posV.y += cosf(m_camera.rot.z + D3DX_PI * 0.5f) * 0.8f;
	}

	//���~
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_F) == true)
	{
		m_camera.posV.y -= sinf(m_camera.rot.x + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posV.y -= cosf(m_camera.rot.z + D3DX_PI * 0.5f) * 0.8f;
	}

	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_I) == true)
	{
		m_camera.rot.x -= 0.05f;
		m_camera.posR.y = m_camera.posV.y - tanf(m_camera.rot.x) * m_camera.fDistance;
	}

	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_K) == true)
	{
		m_camera.rot.x += 0.05f;
		m_camera.posR.y = m_camera.posV.y - tanf(m_camera.rot.x) * m_camera.fDistance;
	}
	

	//===========================
	//���f���ɒǏ]
	//===========================
	//m_camera.posR.x += (m_camera.posRDest.x - m_camera.posR.x) * 0.5f;
	//m_camera.posV.x += (m_camera.posVDest.x - m_camera.posV.x) * 0.5f;

	//m_camera.posR.z += (m_camera.posRDest.z - m_camera.posR.z) * 0.5f;
	//m_camera.posV.z += (m_camera.posVDest.z - m_camera.posV.z) * 0.5f;

	//m_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y) * 0.5f;
	//m_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y) * 0.5f;

	//m_camera.posVDest.x = pPlayer->pos.x + sinf(m_camera.rot.x) * m_camera.fDistance;
	//m_camera.posVDest.z = pPlayer->pos.z + cosf(m_camera.rot.z) * m_camera.fDistance;


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
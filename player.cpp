#include <stdlib.h>
#include "objectx.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "player.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "debugproc.h"
#include "file.h"
#include "light.h"
#include "model.h"

//����������������������������������������
//�v���C���[�̃R���X�g���N�^
//����������������������������������������
CPlayer::CPlayer()
{
	SetObjType(OBJTYPE_PLAYER);
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_fSpeed = 1.5f;
	m_bCollision = false;
	m_bJump = false;
}

//����������������������������������������
//�v���C���[�̃f�X�g���N�^
//����������������������������������������
CPlayer::~CPlayer()
{
}

//����������������������������������������
//�v���C���[�̐���
//����������������������������������������
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = nullptr;
	pPlayer = new CPlayer;

	//�k���`�F�b�N
	if (pPlayer != nullptr)
	{
		// �|���S���̏���������
		pPlayer->Init();
		pPlayer->SetPos(pos);
	}

	return pPlayer;
}

//����������������������������������������
//�v���C���[�̏���������
//����������������������������������������
HRESULT CPlayer::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���(��)
	D3DXLoadMeshFromX("data\\MODEL\\fokko.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_buffMat,
		NULL,
		&m_dwNum,
		&m_mesh);

	m_pShadow = CShadow::Create(GetPos(), D3DXVECTOR3(30.0f, 0.0f, 30.0f), 100);
	m_pShadow->SetLifeNone(true);

	m_pModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModel::MODEL_FOKKO);

	m_pModel[1] = CModel::Create(D3DXVECTOR3(20.0f,20.0f, 20.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),CModel::MODEL_STAR);
	m_pModel[1]->SetParent(m_pModel[0]);

	m_pModel[2] = CModel::Create(D3DXVECTOR3(-20.0f, 20.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModel::MODEL_STAR);
	m_pModel[2]->SetParent(m_pModel[0]);
	return S_OK;
}

//����������������������������������������
//�v���C���[�̏I������
//����������������������������������������
void CPlayer::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//���b�V���̉��
	if (m_mesh = nullptr)
	{
		m_mesh->Release();
		m_mesh = nullptr;
	}

	//�}�e���A���̔j��
	if (m_buffMat != nullptr)
	{
		m_buffMat->Release();
		m_buffMat = nullptr;
	}
}

//����������������������������������������
//�v���C���[�̍X�V����
//����������������������������������������
void CPlayer::Update()
{
	CCamera *pCamera = CApplication::GetCamera();
	CCamera::CAMERA *camera = pCamera->GetCamera();
	m_objpos += m_move;
	auto posOld = m_objpos;

	//������̏ゾ�����ꍇ
	if (m_bCollision)
	{
		m_objpos.y = posOld.y;
		m_bJump = true;
	}

	else
	{
		m_move.y -= 0.5f;
		m_bJump = false;
	}

	//��
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_UP))
	{
		m_objpos.z -= m_fSpeed;
		m_rotDest.y = camera->rot.y + D3DX_PI * 0.0f;				//�ړI�̊p�x

		//�E��
		if(CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
			m_objpos.x -= m_fSpeed,
			m_rotDest.y = camera->rot.y + D3DX_PI * 0.25f;

		//����
		else if(CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
			m_objpos.x += m_fSpeed,
			m_rotDest.y = camera->rot.y - D3DX_PI * 0.25f;
	}

	//��
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_DOWN))
	{
		m_objpos.z += m_fSpeed;
		m_rotDest.y = camera->rot.y - D3DX_PI * 1.0f;

		//�E��
		if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
			m_objpos.x -= m_fSpeed,
			m_rotDest.y = camera->rot.y + D3DX_PI * 0.75f;

		//����
		else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
			m_objpos.x += m_fSpeed,
			m_rotDest.y = camera->rot.y - D3DX_PI * 0.75f;
	}

	//�E
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
	{
		m_objpos.x -= m_fSpeed;
		m_rotDest.y = camera->rot.y + D3DX_PI * 0.5f;
	}

	//��
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
	{
		m_objpos.x += m_fSpeed;
		m_rotDest.y = camera->rot.y - D3DX_PI * 0.5f;
	}

	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		CBullet::Create(D3DXVECTOR3(m_objpos.x, m_objpos.y + 30.0f, m_objpos.z), D3DXVECTOR3(-sinf(m_rot.y), 0.0f, -cosf(m_rot.y)), 100);
	}

	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_SPACE))
	{
		if (m_bJump)
		{
 			m_move.y = ((m_move.y + 20.0f) - m_move.y) * 0.4f;
		}
	}

	if (m_bCollision)
	{
		m_pShadow->SetScale(D3DXVECTOR3(30.0f, 0.0f, 30.0f));

		if(m_objpos.y < m_Collisionpos.y) m_objpos.y = m_Collisionpos.y;
	}

	else if(!m_bCollision)
	{
		//�����鑬�x���O���ゾ�����ꍇ�A�e���k��
		if (m_move.y > 0) m_pShadow->SetScaleDown(true);
		//�����鑬�x��-�R��艺�������ꍇ�A�e���g��
		else if (m_move.y < -3) m_pShadow->SetScaleDown(false);
	}

	BackBased(-300.0f);

#ifdef _DEBUG
	//CDebugProc::Print("�ړI�̌���%f\n���݂̌���%f\n���݂̈ʒu X:%f Y:%f Z:%f", m_rotDest.y, m_rot.y, m_pos.x, m_pos.y, m_pos.z);
#endif

	//�ړI�̕����̐��K��
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2;
	}

	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2;
	}

	//���f���̉�]�̊���
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	//���f���̍X�V
	for (int i = 0; i < 3; i++)
	{
		m_pModel[i]->Update();
	}

	m_pShadow->SetPos(D3DXVECTOR3(m_objpos.x / 2, m_Collisionpos.y, m_objpos.z / 2));

	//���������܂�����
	//m_pShadow->SetZBuff(D3DCMP_EQUAL);

	//======================
	//���K��
	//======================
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}

	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}

//����������������������������������������
//�v���C���[�̕`�揈��
//����������������������������������������
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A����ۑ�
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	//�e�N�X�`���̐ݒ��߂�
	pDevice->SetTexture(0, NULL);

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���f���̉e
	Shadow();

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_buffMat->GetBufferPointer();

	pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�}�e���A���̐ݒ�
	pDevice->SetMaterial(&pMat->MatD3D);

	//���f���p�[�c�̕`��
	m_mesh->DrawSubset(0);

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//���f���̕`��
	for (int i = 0; i < 3; i++)
	{
		m_pModel[i]->Draw();
	}
}

void CPlayer::Shadow()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXVECTOR3 vecdir = CApplication::GetLight()->GetVecDir();
	D3DMATERIAL9 matDef;						//���݂̃}�e���A����ۑ�
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;

	//�V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = D3DXVECTOR4(-vecdir, 0.0f);

	pos = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	D3DXMatrixMultiply(&mtxShadow, &mtxShadow, &m_mtxWorld);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_buffMat->GetBufferPointer();

	pMat->MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�}�e���A���̐ݒ�
	pDevice->SetMaterial(&pMat->MatD3D);

	//���f���p�[�c�̕`��
	m_mesh->DrawSubset(0);

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

void CPlayer::BackBased(float Y)
{
	if (m_objpos.y < Y)
	{
		m_objpos = m_Collisionpos;
		m_move.y = 0.0f;
	}
}
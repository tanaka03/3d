#include <stdlib.h>
#include "objectx.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "player.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"

//����������������������������������������
//�v���C���[�̃R���X�g���N�^
//����������������������������������������
CPlayer::CPlayer()
{
	SetObjType(OBJTYPE_PLAYER);
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
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
	CObjectX::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//X�t�@�C���̓ǂݍ���(��)
	D3DXLoadMeshFromX("data\\MODEL\\fokko.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_buffMat,
		NULL,
		&m_dwNum,
		&m_mesh);

	CObjectX::Init();
	m_pShadow = m_pShadow->Create(GetPos());

	return S_OK;
}

//����������������������������������������
//�v���C���[�̏I������
//����������������������������������������
void CPlayer::Uninit()
{
	CObjectX::Uninit();
	CObjectX::Release();
}

//����������������������������������������
//�v���C���[�̍X�V����
//����������������������������������������
void CPlayer::Update()
{
	CCamera *pCamera = CApplication::GetCamera();
	CCamera::CAMERA *camera = pCamera->GetCamera();
	CObjectX::Update();
	m_pos = GetPos();
	auto posOld = GetPos();

	//������̏ゾ�����ꍇ
	if (m_bCollision)
	{
		m_pos.y = posOld.y;
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
		m_pos.z -= 1.5f;
		m_rotDest.y = camera->rot.y + D3DX_PI * 0.0f;				//�ړI�̊p�x

		//�E��
		if(CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
			m_pos.x -= 1.5f,
			m_rotDest.y = camera->rot.y + D3DX_PI * 0.25f;

		//����
		else if(CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
			m_pos.x += 1.5f,
			m_rotDest.y = camera->rot.y - D3DX_PI * 0.25f;
	}

	//��
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_DOWN))
	{
		m_pos.z += 1.5f;
		m_rotDest.y = camera->rot.y - D3DX_PI * 1.0f;

		//�E��
		if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
			m_pos.x -= 1.5f,
			m_rotDest.y = camera->rot.y + D3DX_PI * 0.75f;

		//����
		else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
			m_pos.x += 1.5f,
			m_rotDest.y = camera->rot.y - D3DX_PI * 0.75f;
	}

	//�E
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
	{
		m_pos.x -= 1.5f;
		m_rotDest.y = camera->rot.y + D3DX_PI * 0.5f;
	}

	//��
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
	{
		m_pos.x += 1.5f;
		m_rotDest.y = camera->rot.y - D3DX_PI * 0.5f;
	}

	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		m_pBullet = m_pBullet->Create(D3DXVECTOR3(m_pos.x, m_pos.y + 15.0f, m_pos.z), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
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
		if(m_pos.y < m_Collisionpos.y) m_pos.y = m_Collisionpos.y;
	}

	KillZ(-300.0f);

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

	SetPos(m_pos);
	SetMove(m_move);
	SetRot(m_rot);
	m_pShadow->SetPos(m_pos / 2);
	m_pShadow->SetZBuff(D3DCMP_EQUAL);

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
	CObjectX::Draw();
}

void CPlayer::KillZ(float Z)
{
	if (m_pos.y < Z)
	{
		m_pos = m_Collisionpos;
	}
}
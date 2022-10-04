#include <stdlib.h>
#include "objectx.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "player.h"
#include "shadow.h"

//����������������������������������������
//�v���C���[�̃R���X�g���N�^
//����������������������������������������
CPlayer::CPlayer()
{
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
	m_pShadow->SetPos(GetPos());
	CObjectX::Update();
}

//����������������������������������������
//�v���C���[�̕`�揈��
//����������������������������������������
void CPlayer::Draw()
{
	CObjectX::Draw();
}
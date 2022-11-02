#include "objectx.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "enemy.h"
#include "shadow.h"

//����������������������������������������
//�v���C���[�̃R���X�g���N�^
//����������������������������������������
CEnemy::CEnemy()
{
	SetObjType(OBJTYPE_ENEMY);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bCollision = false;
}

//����������������������������������������
//�v���C���[�̃f�X�g���N�^
//����������������������������������������
CEnemy::~CEnemy()
{
}

//����������������������������������������
//�v���C���[�̐���
//����������������������������������������
CEnemy * CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy *pEnemy = nullptr;
	pEnemy = new CEnemy;

	//�k���`�F�b�N
	if (pEnemy != nullptr)
	{
		// �|���S���̏���������
		pEnemy->Init();
		pEnemy->SetPos(pos);
	}

	return pEnemy;
}

//����������������������������������������
//�v���C���[�̏���������
//����������������������������������������
HRESULT CEnemy::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	CObjectX::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//X�t�@�C���̓ǂݍ���(��)
	D3DXLoadMeshFromX("data\\MODEL\\OBK.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_buffMat,
		NULL,
		&m_dwNum,
		&m_mesh);

	CObjectX::Init();
	m_pShadow = CShadow::Create(GetPos(), D3DXVECTOR3(30.0f, 0.0f, 30.0f), 100);
	m_pShadow->SetLifeNone(true);

	return S_OK;
}

//����������������������������������������
//�v���C���[�̏I������
//����������������������������������������
void CEnemy::Uninit()
{
	CObjectX::Uninit();
}

//����������������������������������������
//�v���C���[�̍X�V����
//����������������������������������������
void CEnemy::Update()
{
	CObjectX::Update();
	m_pos = GetPos();
	auto posOld = GetPos();

	//������̏ゾ�����ꍇ
	if (m_bCollision)
	{
		m_pos.y = posOld.y;
	}

	else
	{
		m_move.y -= 0.5f;
	}

	if (m_bCollision)
	{
		m_pShadow->SetScale(D3DXVECTOR3(30.0f, 0.0f, 30.0f));
		if (m_pos.y < m_Collisionpos.y) m_pos.y = m_Collisionpos.y;
	}

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
	m_pShadow->SetPos(D3DXVECTOR3(m_pos.x / 2, m_Collisionpos.y, m_pos.z / 2));

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
void CEnemy::Draw()
{
	CObjectX::Draw();
}
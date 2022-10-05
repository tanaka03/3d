#include "objectx.h"
#include "application.h"

//��������������������������
//�I�u�W�F�N�gX�̃R���X�g���N�^
//��������������������������
CObjectX::CObjectX()
{
}

//��������������������������
//�I�u�W�F�N�gX�̃f�X�g���N�^
//��������������������������
CObjectX::~CObjectX()
{
}

//��������������������������
//�I�u�W�F�N�gX�̏�����
//��������������������������
HRESULT CObjectX::Init()
{
	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = m_mesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_mesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//���_�o�b�t�@�̃A�����b�N
	m_mesh->UnlockVertexBuffer();

	return S_OK;
}

//��������������������������
//�I�u�W�F�N�gX�̏I��
//��������������������������
void CObjectX::Uninit()
{
	//���b�V���̉��
	if (m_mesh = NULL)
	{
		m_mesh->Release();
		m_mesh = NULL;
	}

	//�}�e���A���̔j��
	if (m_buffMat != NULL)
	{
		m_buffMat->Release();
		m_buffMat = NULL;
	}
}

//��������������������������
//�I�u�W�F�N�gX�̍X�V
//��������������������������
void CObjectX::Update()
{
	auto pos = GetPos();
	pos += GetMove();
	SetPos(pos);
}

//��������������������������
//�I�u�W�F�N�gX�̕`��
//��������������������������
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A����ۑ�
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	//�e�N�X�`���̐ݒ��߂�
	pDevice->SetTexture(0, NULL);

	//���[���h�}�g���b�N�X��������(�e)
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f(�e)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f(�e)
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_buffMat->GetBufferPointer();

	//�}�e���A���̐ݒ�
	pDevice->SetMaterial(&pMat->MatD3D);

	//���f���p�[�c�̕`��
	m_mesh->DrawSubset(0);

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
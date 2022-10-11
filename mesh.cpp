#include "application.h"
#include "renderer.h"
#include "mesh.h"
#include "object3d.h"

CMesh::CMesh()
{
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_meshX = 5;
	m_meshZ = 5;
}

CMesh::~CMesh()
{
}

HRESULT CMesh::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	m_MeshField_VertexNum = (m_meshX + 1) * (m_meshZ + 1);				//���_��
	m_MeshField_IndexNum = (m_meshX + 1) * 2 * (m_meshZ - 1) * 2;			//�C���f�b�N�X
	m_MeshField_PrimitiveNum = m_meshX * m_meshZ * 2 + (m_meshZ - 1) * 4;	//�|���S��

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_MeshField_VertexNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * m_MeshField_IndexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//==========================
	//�C���f�b�N�X�o�b�t�@
	//==========================
	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD * pIdx;

	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nIdxCnt = 0;

	for (int nCntZ = 0; nCntZ <= m_meshZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= m_meshX; nCntX++)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[nIdxCnt] = nCntX + (nCntZ * (m_meshZ + 1)) + (m_meshZ + 1);
			pIdx[nIdxCnt + 1] = nCntX + (nCntZ * (m_meshZ + 1));

			nIdxCnt += 2;

			//�k�ރ|���S��
			if (nCntX == m_meshX)
			{
				pIdx[nIdxCnt] = nCntX + (nCntZ * (m_meshZ + 1)) + (m_meshZ + 1);
				pIdx[nIdxCnt + 1] = nCntX + (nCntZ * (m_meshZ + 1));

				nIdxCnt += 2;
			}
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//��������������������������
//���b�V���t�B�[���h�̏I��
//��������������������������
void CMesh::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
}

//��������������������������
//���b�V���t�B�[���h�̍X�V
//��������������������������
void CMesh::Update()
{
}

//��������������������������
//���b�V���t�B�[���h�̕`��
//��������������������������
void CMesh::Draw()
{
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_objpos.y, m_objpos.x, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_MeshField_VertexNum,	//���_��
		0,
		m_MeshField_PrimitiveNum	/*�`�悷��v���~�e�B�u��*/);
}
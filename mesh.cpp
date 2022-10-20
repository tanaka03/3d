#include "application.h"
#include "renderer.h"
#include "mesh.h"
#include "object3d.h"
#include "player.h"

#include "debugproc.h"

#include <vector>
#include <stdio.h>

using namespace std;

//��������������������������
//���b�V���̃R���X�g���N�^
//��������������������������
CMesh::CMesh()
{
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_meshX = 5;
	m_meshZ = 5;
}


//��������������������������
//���b�V���̃f�X�g���N�^
//��������������������������
CMesh::~CMesh()
{
}

//��������������������������
//���b�V���̏�����
//��������������������������
HRESULT CMesh::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	m_MeshField_VertexNum = (m_meshX + 1) * (m_meshZ + 1);					//���_��
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
	WORD *pIdx;

	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nIdxCnt = 0;

	for (int nCntZ = 0; nCntZ < m_meshZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= m_meshX; nCntX++)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[nIdxCnt] = nCntX + nCntZ * (m_meshZ + 1) + (m_meshZ + 1);
			pIdx[nIdxCnt + 1] = nCntX + nCntZ * (m_meshZ + 1);

			nIdxCnt += 2;

			//�k�ރ|���S��
			if (nCntX == m_meshX)
			{
				pIdx[nIdxCnt] = nCntX + nCntZ * (m_meshZ + 1);
				pIdx[nIdxCnt + 1] = (nCntX + nCntZ * (m_meshX + 1) + (m_meshZ + 1)) + 1;

				nIdxCnt += 2;
			}
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//��������������������������
//���b�V���̏I��
//��������������������������
void CMesh::Uninit()
{
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	SetDestroy(true);
}

//��������������������������
//���b�V���̍X�V
//��������������������������
void CMesh::Update()
{
	CPlayer *pPlayer = CApplication::GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�o�b�t�@�����b�N
	VERTEX_3D *pVtx = nullptr;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int cnt = 0; cnt < m_MeshField_VertexNum; cnt++)
	{
		pVtx[cnt].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	}

	for (int i = 0; i < m_MeshField_PrimitiveNum; i++)
	{
		if (pIdx[i] == pIdx[i + 1] && pIdx[i] == pIdx[i + 2] && pIdx[i + 1] == pIdx[i + 2])
		{
			continue;
		}

		//���_�̈ʒu
		auto posA = pVtx[pIdx[i]].pos;
		auto posB = pVtx[pIdx[i + 1]].pos;
		auto posC = pVtx[pIdx[i + 2]].pos;

		//���_�̃x�N�g��
		auto vecA = posB - posA;
		auto vecB = posC - posB;
		auto vecC = posA - posC;

		//�|���S���̒��_�ƃv���C���[�̈ʒu�̃x�N�g��
		auto DistanceA = playerPos - posA;
		auto DistanceB = playerPos - posB;
		auto DistanceC = playerPos - posC;

		//�|���S���̒��_�̃x�N�g���ƃv���C���[���璸�_�̃x�N�g���̌v�Z����
		float fResult1 = vecA.x * DistanceA.z - vecA.z * DistanceA.x;
		float fResult2 = vecB.x * DistanceB.z - vecB.z * DistanceB.x;
		float fResult3 = vecC.x * DistanceC.z - vecC.z * DistanceC.x;

		if (fResult1 * fResult2 >= 0 &&
			fResult2 * fResult3 >= 0 &&
			fResult3 * fResult1 >= 0)
		{//�|���S���͈͓̔��ɓ������ꍇ
			//pVtx[pIdx[i]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			//pVtx[pIdx[i + 1]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			//pVtx[pIdx[i + 2]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			//���b�V���̔���
			auto V1 = posB - posA;
			auto V2 = posC - posA;
			D3DXVECTOR3 normal;

			D3DXVec3Cross(&normal, &V2, &V1);
			D3DXVec3Normalize(&normal, &normal);
			playerPos.y = posA.y - ((playerPos.x - posA.x) * normal.x + (playerPos.z - posA.z) * normal.z) / normal.y;

			pPlayer->SetCollision(true);
			pPlayer->SetPos(playerPos);
			break;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
}

//��������������������������
//���b�V���̕`��
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
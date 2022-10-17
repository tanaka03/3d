#include "meshfield.h"
#include "object3d.h"

CMeshField::CMeshField()
{
}

CMeshField::~CMeshField()
{
}

CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int X, int Z)
{
	CMeshField *pMesh = nullptr;
	pMesh = new CMeshField;

	//�k���`�F�b�N
	if (pMesh != nullptr)
	{
		// �|���S���̏���������
		pMesh->SetX(X);
		pMesh->SetZ(Z);
		pMesh->SetPos(pos);
		pMesh->SetScale(scale);
		pMesh->Init();
	}

	return pMesh;
}

HRESULT CMeshField::Init()
{
	CMesh::Init();

	auto pos = GetPos();
	auto scale = GetScale();
	int meshX = GetX();
	int meshZ = GetZ();
	m_MeshField_VertexNum = GetVtxNum();

	//���_�o�b�t�@�����b�N
	VERTEX_3D * pVtx = nullptr;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_MeshField_VertexNum; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[nCnt].pos = D3DXVECTOR3(pos.x + scale.x * (nCnt % (meshX + 1)), rand() % 50, pos.z - scale.z * (nCnt / (meshZ + 1)));

		//�e���_�̖@���̐ݒ�@���@�x�N�g���̑傫����1�ɂ���K�v������
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[nCnt].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//�e�N�X�`�����W
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + 0.5f * (nCnt % (meshZ + 1)), 0.0f + 0.5f * (nCnt / (meshZ + 1)));
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//��������������������������
//���b�V���t�B�[���h�̏I��
//��������������������������
void CMeshField::Uninit()
{
	CMesh::Uninit();
}

//��������������������������
//���b�V���t�B�[���h�̍X�V
//��������������������������
void CMeshField::Update()
{
	CMesh::Update();
}

//��������������������������
//���b�V���t�B�[���h�̕`��
//��������������������������
void CMeshField::Draw()
{
	CMesh::Draw();
}
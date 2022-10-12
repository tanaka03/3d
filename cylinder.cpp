#include "cylinder.h"
#include "object3d.h"

CCylinder::CCylinder()
{
	m_fAngle = 0.0f;
	m_fRadius = 0.0f;
	m_fHeight = 10.0f;
}

CCylinder::~CCylinder()
{
}

CCylinder *CCylinder::Create(D3DXVECTOR3 pos, float height, float radius, int X, int Z)
{
	CCylinder *pMesh = nullptr;
	pMesh = new CCylinder;

	//�k���`�F�b�N
	if (pMesh != nullptr)
	{
		// �|���S���̏���������
		pMesh->SetX(X);
		pMesh->SetZ(Z);
		pMesh->SetRadius(radius);
		pMesh->SetHeight(height);
		pMesh->SetPos(pos);
		pMesh->Init();
	}

	return pMesh;
}

HRESULT CCylinder::Init()
{
	CMesh::Init();

	SetScale(D3DXVECTOR3(10.0f, 10.0f, 10.0f));

	auto pos = GetPos();
	int meshX = GetX();
	int meshZ = GetZ();

	//���_�o�b�t�@�����b�N
	VERTEX_3D * pVtx = nullptr;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV <= meshZ; nCntV++)
	{
		for (int nCntH = 0; nCntH <= meshX; nCntH++)
		{
			m_fAngle = (D3DX_PI * 2) / meshX;

			//���_���W�̐ݒ�
			pVtx[(nCntV * (meshZ + 1)) + nCntH].pos = D3DXVECTOR3(sinf(m_fAngle * nCntH) * m_fRadius,
				m_fHeight * nCntV,
				cosf(m_fAngle * nCntH) * m_fRadius);

			//�e���_�̖@���̐ݒ�@���x�N�g���̑傫����1�ɂ���K�v������
			pVtx[(nCntV * (meshZ + 1)) + nCntH].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[(nCntV * (meshZ + 1)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W
			pVtx[(nCntV * (meshZ + 1)) + nCntH].tex = D3DXVECTOR2(0.0f + (nCntH % (meshX + 1)), 1.0f + (nCntV / (meshZ + 1)));
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//��������������������������
//���b�V���t�B�[���h�̏I��
//��������������������������
void CCylinder::Uninit()
{
	CMesh::Uninit();
}

//��������������������������
//���b�V���t�B�[���h�̍X�V
//��������������������������
void CCylinder::Update()
{
	CMesh::Update();
}

//��������������������������
//���b�V���t�B�[���h�̕`��
//��������������������������
void CCylinder::Draw()
{
	CMesh::Draw();
}
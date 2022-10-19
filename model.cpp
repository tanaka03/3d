#include "model.h"
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "player.h"

const char* CModel::s_FileName[] =
{// �e�N�X�`���̃p�X
	"data\\MODEL\\fokko.x",
	"data\\MODEL\\star.x"
};
static_assert(sizeof(CModel::s_FileName) / sizeof(CModel::s_FileName[0]) == CModel::MODEL_MAX, "aho");

CModel::CModel()
{
}

CModel::~CModel()
{
}

CModel *CModel::Create(D3DXVECTOR3 posOffset, D3DXVECTOR3 rotOffset, MODEL parts)
{
	CModel *pModel = nullptr;
	pModel = new CModel;

	if (pModel != nullptr)
	{
		pModel->SetPosOffset(posOffset);
		pModel->SetRotOffset(rotOffset);
		pModel->SetModel(parts);
		pModel->Init();
	}

	return pModel;
}

HRESULT CModel::Init()
{
	Load(m_model);

	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = m_mesh[m_model]->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_mesh[m_model]->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_mesh[m_model]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//���_�o�b�t�@�̃A�����b�N
	m_mesh[m_model]->UnlockVertexBuffer();

	return S_OK;
}

void CModel::ReleaseAll()
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		//���_�o�b�t�@�̔j��
		if (m_pVtxBuff != nullptr)
		{
			m_pVtxBuff->Release();
			m_pVtxBuff = nullptr;
		}

		//���b�V���̉��
		if (m_mesh[i] = nullptr)
		{
			m_mesh[i]->Release();
			m_mesh[i] = nullptr;
		}

		//�}�e���A���̔j��
		if (m_buffMat[i] != nullptr)
		{
			m_buffMat[i]->Release();
			m_buffMat[i] = nullptr;
		}
	}
}

void CModel::Update()
{
	m_rotOffset.y += 0.2f;
}

//��������������������������
//�I�u�W�F�N�gX�̕`��
//��������������������������
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	CPlayer *pPlayer = CApplication::GetPlayer();
	D3DXMATRIX parent = pPlayer->GetMtx();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A����ۑ�
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	//�e�N�X�`���̐ݒ��߂�
	pDevice->SetTexture(0, NULL);

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotOffset.y, m_rotOffset.x, m_rotOffset.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_posOffset.x, m_posOffset.y, m_posOffset.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�̃}�g���b�N�X�Ƃ������킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &parent);

	//Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���f���̉e
	//Shadow();

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_buffMat[m_model]->GetBufferPointer();

	pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�}�e���A���̐ݒ�
	pDevice->SetMaterial(&pMat->MatD3D);

	//���f���p�[�c�̕`��
	m_mesh[m_model]->DrawSubset(0);

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

void CModel::Shadow()
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
	pMat = (D3DXMATERIAL*)m_buffMat[m_model]->GetBufferPointer();

	pMat->MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pMat->MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�}�e���A���̐ݒ�
	pDevice->SetMaterial(&pMat->MatD3D);

	//���f���p�[�c�̕`��
	m_mesh[m_model]->DrawSubset(0);

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

void CModel::Load(MODEL model)
{
	if (m_bLoaded[model])
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(s_FileName[model],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_buffMat[model],
		NULL,
		&m_dwNum[model],
		&m_mesh[model]);

	m_bLoaded[model] = true;
}
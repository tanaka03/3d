#include "model.h"
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "player.h"
#include "line.h"

using namespace std;

vector<CModel*> CModel::m_Data;
bool CModel::m_bLoaded[MODEL_MAX] = {};

const char* CModel::s_FileName[] =
{// �e�N�X�`���̃p�X
	"data\\MODEL\\fokko.x",
	"data\\MODEL\\star.x",
	"data\\MODEL\\Circle.x"
};
static_assert(sizeof(CModel::s_FileName) / sizeof(CModel::s_FileName[0]) == CModel::MODEL_MAX, "aho");

CModel::CModel() : 
	m_buffMat(),
	m_dwNum(), 
	m_mesh(), 
	m_pParent(), 
	m_scale(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),
	m_AlphaFunc(D3DCMP_GREATER),
	m_pTexture(nullptr)
{
	m_bRelease = false;
	m_Data.resize(MODEL_MAX);
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
	m_startPos = m_posOffset;
	m_startRot = m_rotOffset;

	Load(m_model);

	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	//X�t�@�C���œǂݍ��񂾏��
	m_mesh = m_Data.at(m_model)->m_mesh;
	m_buffMat = m_Data.at(m_model)->m_buffMat;
	m_dwNum = m_Data.at(m_model)->m_dwNum;

	//���_���̎擾
	nNumVtx = m_mesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_mesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int i = 0; i < nNumVtx; i++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X
		if (vtx.x > m_maxModel.x)
		{
			m_maxModel.x = floorf(vtx.x);
		}

		if (vtx.x < m_minModel.x)
		{
			m_minModel.x = floorf(vtx.x);
		}

		//Y
		if (vtx.y > m_maxModel.y)
		{
			m_maxModel.y = floorf(vtx.y);
		}

		if (vtx.y < m_minModel.y)
		{
			m_minModel.y = floorf(vtx.y);
		}

		//Z
		if (vtx.z > m_maxModel.z)
		{
			m_maxModel.z = floorf(vtx.z);
		}

		if (vtx.z < m_minModel.z)
		{
			m_minModel.z = floorf(vtx.z);
		}
		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	//���f���T�C�Y
	m_modelSize.x = m_maxModel.x - m_minModel.x;
	m_modelSize.y = m_maxModel.y - m_minModel.y;
	m_modelSize.z = m_maxModel.z - m_minModel.z;

	//���_�o�b�t�@�̃A�����b�N
	m_mesh->UnlockVertexBuffer();

	//======================
	//����̐�
	//======================
	//���l�p
	m_pLine[0] = CLine::Create(m_posOffset, m_minModel,
	D3DXVECTOR3(m_maxModel.x, m_minModel.y, m_minModel.z),
	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[1] = CLine::Create(m_posOffset, m_minModel,
	D3DXVECTOR3(m_minModel.x, m_minModel.y, m_maxModel.z),
	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[2] = CLine::Create(m_posOffset,
	D3DXVECTOR3(m_maxModel.x, m_minModel.y, m_maxModel.z),
	D3DXVECTOR3(m_minModel.x, m_minModel.y, m_maxModel.z),
	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[3] = CLine::Create(m_posOffset,
	D3DXVECTOR3(m_maxModel.x, m_minModel.y, m_maxModel.z),
	D3DXVECTOR3(m_maxModel.x, m_minModel.y, m_minModel.z),
	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	//�c�_
	m_pLine[4] = CLine::Create(m_posOffset,
	D3DXVECTOR3(m_minModel.x, m_minModel.y, m_minModel.z),
	D3DXVECTOR3(m_minModel.x, m_maxModel.y, m_minModel.z),
	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[5] = CLine::Create(m_posOffset,
	D3DXVECTOR3(m_maxModel.x, m_minModel.y, m_minModel.z),
	D3DXVECTOR3(m_maxModel.x, m_maxModel.y, m_minModel.z),
	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[6] = CLine::Create(m_posOffset,
	D3DXVECTOR3(m_minModel.x, m_minModel.y, m_maxModel.z),
	D3DXVECTOR3(m_minModel.x, m_maxModel.y, m_maxModel.z),
	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[7] = CLine::Create(m_posOffset,
	D3DXVECTOR3(m_maxModel.x, m_minModel.y, m_maxModel.z),
	D3DXVECTOR3(m_maxModel.x, m_maxModel.y, m_maxModel.z),
	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	//��l�p
	m_pLine[8] = CLine::Create(m_posOffset,
	D3DXVECTOR3(m_minModel.x, m_maxModel.y, m_minModel.z),
	D3DXVECTOR3(m_maxModel.x, m_maxModel.y, m_minModel.z),
	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[9] = CLine::Create(m_posOffset,
	D3DXVECTOR3(m_minModel.x, m_maxModel.y, m_minModel.z),
	D3DXVECTOR3(m_minModel.x, m_maxModel.y, m_maxModel.z),
	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[10] = CLine::Create(m_posOffset,
	D3DXVECTOR3(m_maxModel.x, m_maxModel.y, m_maxModel.z),
	D3DXVECTOR3(m_minModel.x, m_maxModel.y, m_maxModel.z),
	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[11] = CLine::Create(m_posOffset,
	D3DXVECTOR3(m_maxModel.x, m_maxModel.y, m_maxModel.z),
	D3DXVECTOR3(m_maxModel.x, m_maxModel.y, m_minModel.z),
	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	return S_OK;
}

void CModel::Release()
{
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

	for (int i = 0; i < 12; i++)
	{
		if (m_pLine[i] != nullptr)
		{
			m_pLine[i]->Uninit();
			delete m_pLine[i];
		}
	}

	delete this;
}

void CModel::Update()
{
	for (int i = 0; i < 12; i++)
	{
		if (m_pLine[i] == nullptr)
		{
			continue;
		}
		m_pLine[i]->SetPos(m_modelPos);
		m_pLine[i]->Update();
	}
}

//��������������������������
//�I�u�W�F�N�gX�̕`��
//��������������������������
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX parent;

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;		//�v�Z�p�}�g���b�N�X
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

	// �s��g�k�֐�
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//�e�̃}�g���b�N�X�Ƃ������킹��
	if (m_pParent != nullptr)
	{
		parent = m_pParent->GetMtxWorld();
	}

	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &parent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &parent);

	for (int i = 0; i < 12; i++)
	{
		if (m_pLine[i] == nullptr)
		{
			continue;
		}
		m_pLine[i]->Draw();
	}

	//Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, m_AlphaFunc);

	//���C�g�𖳌��ɂ���
	if (m_property.bLight)
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	//���f���̉e
	//Shadow();

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_buffMat->GetBufferPointer();

	pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�}�e���A���̐ݒ�
	pDevice->SetMaterial(&pMat->MatD3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//���f���p�[�c�̕`��
	m_mesh->DrawSubset(0);

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//�e�N�X�`���̐ݒ��߂�
	pDevice->SetTexture(0, NULL);
}

void CModel::Shadow()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXVECTOR3 vecdir = CApplication::GetInstance()->GetLight()->GetVecDir();
	D3DMATERIAL9 matDef;						//���݂̃}�e���A����ۑ�
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;

	//�V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = D3DXVECTOR4(-vecdir, 0.0f);

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	D3DXMatrixMultiply(&mtxShadow, &mtxShadow, &m_mtxWorld);

	//�X�e���V���o�b�t�@�̗L��
	pDevice->SetRenderState(D3DRS_STENCILENABLE, true);

	//�X�e���V���o�b�t�@�Ɣ�r����
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	//�X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//�X�e���V���e�X�g�̔�r���@�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

	//�X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	//�J�����O����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_buffMat->GetBufferPointer();

	pMat->MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pMat->MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�}�e���A���̐ݒ�
	pDevice->SetMaterial(&pMat->MatD3D);

	//���f���p�[�c�̕`��
	m_mesh->DrawSubset(0);

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//�X�e���V���o�b�t�@�̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_STENCILENABLE, false);

	//�J�����O�̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
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
		&m_buffMat,
		NULL,
		&m_dwNum,
		&m_mesh);

	m_bLoaded[model] = true;
	m_Data.insert(m_Data.begin() + model, this);
}

void CModel::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		//�e�N�X�`���̃|�C���^
}

void CModel::SetProperty(bool light)
{
	m_property.bLight = light;
}
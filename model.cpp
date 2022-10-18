//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

#include "application.h"
#include "model.h"
#include "renderer.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const char* CModel::s_FileName[] =
{// �e�N�X�`���̃p�X
	"data/MODEL/fokko.x",			// �t�H�b�R
	"data/MODEL/star.x"
};
static_assert(sizeof(CModel::s_FileName) / sizeof(CModel::s_FileName[0]) == CModel::MODEL_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CModel::CModel() : m_model()
{
	memset(m_model, 0, sizeof(m_model));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CModel::~CModel()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CModel::LoadAll()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	for (int i = 0; i < MODEL_MAX; ++i)
	{
		if (m_model[i].m_mesh != nullptr)
		{// �e�N�X�`���̓ǂݍ��݂�����Ă���
			continue;
		}

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(s_FileName[i],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_model[i].m_buffMat,
			NULL,
			&m_model[i].m_dwNum,
			&m_model[i].m_mesh);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CModel::Load(EModel model)
{
	assert(model >= 0 && model < MODEL_MAX);

	if (m_model[model].m_mesh != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(s_FileName[model],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_model[model].m_buffMat,
		NULL,
		&m_model[model].m_dwNum,
		&m_model[model].m_mesh);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CModel::ReleaseAll(void)
{
	for (int i = 0; i < MODEL_MAX; ++i)
	{
		if (m_model[i].m_mesh != NULL)
		{// ���b�V���̉��
			m_model[i].m_mesh->Release();
			m_model[i].m_mesh = NULL;
		}

		//�}�e���A���̔j��
		if (m_model[i].m_buffMat != nullptr)
		{
			m_model[i].m_buffMat->Release();
			m_model[i].m_buffMat = nullptr;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CModel::Release(EModel model)
{
	assert(model >= 0 && model < MODEL_MAX);

	if (m_model[model].m_mesh != NULL)
	{// ���b�V���̉��
		m_model[model].m_mesh->Release();
		m_model[model].m_mesh = NULL;
	}

	//�}�e���A���̔j��
	if (m_model[model].m_buffMat != nullptr)
	{
		m_model[model].m_buffMat->Release();
		m_model[model].m_buffMat = nullptr;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
CModel::ModelData CModel::GetModel(EModel model)
{
	if (model == MODEL_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return {};
	}

	assert(model >= 0 && model < MODEL_MAX);

	// �ǂݍ���
	Load(model);

	return m_model[model];
}

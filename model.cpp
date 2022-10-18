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
// 定義
//==================================================
const char* CModel::s_FileName[] =
{// テクスチャのパス
	"data/MODEL/fokko.x",			// フォッコ
	"data/MODEL/star.x"
};
static_assert(sizeof(CModel::s_FileName) / sizeof(CModel::s_FileName[0]) == CModel::MODEL_MAX, "aho");

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CModel::CModel() : m_model()
{
	memset(m_model, 0, sizeof(m_model));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CModel::~CModel()
{
}

//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void CModel::LoadAll()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	for (int i = 0; i < MODEL_MAX; ++i)
	{
		if (m_model[i].m_mesh != nullptr)
		{// テクスチャの読み込みがされている
			continue;
		}

		//Xファイルの読み込み
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
// 読み込み
//--------------------------------------------------
void CModel::Load(EModel model)
{
	assert(model >= 0 && model < MODEL_MAX);

	if (m_model[model].m_mesh != nullptr)
	{// テクスチャの読み込みがされている
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//Xファイルの読み込み
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
// 全ての解放
//--------------------------------------------------
void CModel::ReleaseAll(void)
{
	for (int i = 0; i < MODEL_MAX; ++i)
	{
		if (m_model[i].m_mesh != NULL)
		{// メッシュの解放
			m_model[i].m_mesh->Release();
			m_model[i].m_mesh = NULL;
		}

		//マテリアルの破棄
		if (m_model[i].m_buffMat != nullptr)
		{
			m_model[i].m_buffMat->Release();
			m_model[i].m_buffMat = nullptr;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CModel::Release(EModel model)
{
	assert(model >= 0 && model < MODEL_MAX);

	if (m_model[model].m_mesh != NULL)
	{// メッシュの解放
		m_model[model].m_mesh->Release();
		m_model[model].m_mesh = NULL;
	}

	//マテリアルの破棄
	if (m_model[model].m_buffMat != nullptr)
	{
		m_model[model].m_buffMat->Release();
		m_model[model].m_buffMat = nullptr;
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
CModel::ModelData CModel::GetModel(EModel model)
{
	if (model == MODEL_NONE)
	{// テクスチャを使用しない
		return {};
	}

	assert(model >= 0 && model < MODEL_MAX);

	// 読み込み
	Load(model);

	return m_model[model];
}

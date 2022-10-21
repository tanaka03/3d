#include "model.h"
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "player.h"

using namespace std;

vector<CModel*> CModel::m_Data;
bool CModel::m_bLoaded[MODEL_MAX] = {};

const char* CModel::s_FileName[] =
{// テクスチャのパス
	"data\\MODEL\\fokko.x",
	"data\\MODEL\\star.x"
};
static_assert(sizeof(CModel::s_FileName) / sizeof(CModel::s_FileName[0]) == CModel::MODEL_MAX, "aho");

CModel::CModel() : m_buffMat(), m_dwNum(), m_mesh(), m_pParent()
{
	m_bRelease = false;
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

	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

	//Xファイルで読み込んだ情報
	m_mesh = m_Data.at(m_model)->m_mesh;
	m_buffMat = m_Data.at(m_model)->m_buffMat;
	m_dwNum = m_Data.at(m_model)->m_dwNum;

	//頂点数の取得
	nNumVtx = m_mesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_mesh->GetFVF());

	//頂点バッファのロック
	m_mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//頂点バッファのアンロック
	m_mesh->UnlockVertexBuffer();

	return S_OK;
}

void CModel::Release()
{
	//メッシュの解放
	if (m_mesh = nullptr)
	{
		m_mesh->Release();
		m_mesh = nullptr;
	}

	//マテリアルの破棄
	if (m_buffMat != nullptr)
	{
		m_buffMat->Release();
		m_buffMat = nullptr;
	}

	delete this;
}

void CModel::Update()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクトXの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	CPlayer *pPlayer = CApplication::GetPlayer();
	D3DXMATRIX parent = pPlayer->GetMtx();

	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	//テクスチャの設定を戻す
	pDevice->SetTexture(0, NULL);

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotOffset.y, m_rotOffset.x, m_rotOffset.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_posOffset.x, m_posOffset.y, m_posOffset.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//親のマトリックスとかけ合わせる
	if (m_pParent != nullptr)
	{
		parent = m_pParent->m_mtxWorld;
	}

	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &parent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &parent);

	//Zテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//モデルの影
	//Shadow();

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを保存
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_buffMat->GetBufferPointer();

	pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//マテリアルの設定
	pDevice->SetMaterial(&pMat->MatD3D);

	//モデルパーツの描画
	m_mesh->DrawSubset(0);

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

void CModel::Shadow()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXVECTOR3 vecdir = CApplication::GetLight()->GetVecDir();
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;

	//シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = D3DXVECTOR4(-vecdir, 0.0f);

	pos = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	D3DXMatrixMultiply(&mtxShadow, &mtxShadow, &m_mtxWorld);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//現在のマテリアルを保存
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_buffMat->GetBufferPointer();

	pMat->MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pMat->MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//マテリアルの設定
	pDevice->SetMaterial(&pMat->MatD3D);

	//モデルパーツの描画
	m_mesh->DrawSubset(0);

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

void CModel::Load(MODEL model)
{
	if (m_bLoaded[model])
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

	//Xファイルの読み込み
	D3DXLoadMeshFromX(s_FileName[model],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_buffMat,
		NULL,
		&m_dwNum,
		&m_mesh);

	m_bLoaded[model] = true;
	m_Data.push_back(this);
}
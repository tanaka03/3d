#include "objectx.h"
#include "application.h"
#include "light.h"
#include "object3d.h"
#include "model.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクトXのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝
CObjectX::CObjectX() :
	m_pTexture(nullptr)
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクトXのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝
CObjectX::~CObjectX()
{
}

CObjectX * CObjectX::Create(D3DXVECTOR3 pos)
{
	CObjectX *pObj = nullptr;
	pObj = new CObjectX;

	//ヌルチェック
	if (pObj != nullptr)
	{
		// ポリゴンの初期化処理
		pObj->Init();
		pObj->SetPos(pos);
	}

	return pObj;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクトXの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CObjectX::Init()
{
	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = m_mesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_mesh->GetFVF());

	//頂点バッファのロック
	m_mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//頂点座標の代入
	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

	for (int i = 0; i < nNumVtx; i++)
	{
		//頂点座標の代入
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
		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	//モデルサイズ
	m_scale.x = m_maxModel.x - m_minModel.x;
	m_scale.y = m_maxModel.y - m_minModel.y;
	m_scale.z = m_maxModel.z - m_minModel.z;

	//頂点バッファのアンロック
	m_mesh->UnlockVertexBuffer();

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクトXの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObjectX::Uninit()
{
	//頂点バッファの破壊
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

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

	SetDestroy(true);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクトXの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObjectX::Update()
{
	D3DXVECTOR3 pos = GetPos();
	pos += GetMove();
	SetPos(pos);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクトXの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	//テクスチャの設定を戻す
	pDevice->SetTexture(0, NULL);

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

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

	for (int nCntMat = 0; nCntMat < (int)m_dwNum; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		//モデルパーツの描画
		m_mesh->DrawSubset(nCntMat);
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	//テクスチャの設定を戻す
	pDevice->SetTexture(0, NULL);
}

void CObjectX::Shadow()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXVECTOR3 vecdir = CApplication::GetInstance()->GetLight()->GetVecDir();
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

	//マテリアルの設定
	pDevice->SetMaterial(&pMat->MatD3D);

	//モデルパーツの描画
	m_mesh->DrawSubset(0);

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

void CObjectX::LoadModel(std::string path)
{
	CModel *pModel = CApplication::GetInstance()->GetModel();

	m_mesh = pModel->GetMesh(path);
	m_buffMat = pModel->GetBuffMat(path);
	m_dwNum = pModel->GetModelNum(path);
}

void CObjectX::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		//テクスチャのポインタ
}
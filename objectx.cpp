#include "objectx.h"
#include "application.h"
#include "light.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクトXのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝
CObjectX::CObjectX()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクトXのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝
CObjectX::~CObjectX()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクトXの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CObjectX::Init()
{
	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

	//↓これ不完全
	//CModel::ModelData Modeldata = CApplication::GetModel()->GetModel(m_model);

	//m_mesh = Modeldata.m_mesh;
	//m_buffMat = Modeldata.m_buffMat;
	//m_dwNum = Modeldata.m_dwNum;

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
	auto pos = GetPos();
	pos += GetMove();
	SetPos(pos);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクトXの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXVECTOR3 vecdir = CApplication::GetLight()->GetVecDir();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	//モデルの影
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;

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

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//-----------------------------------------------------------------
	//シャドウマトリックスの初期化
	//D3DXMatrixIdentity(&mtxShadow);

	//vecLight = D3DXVECTOR4(vecdir.x, vecdir.y, vecdir.z, 0.0f);

	//pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	//D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	//D3DXMatrixMultiply(&mtxShadow, &mtxShadow, &m_mtxWorld);
	//-----------------------------------------------------------------

	//現在のマテリアルを保存
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_buffMat->GetBufferPointer();

	//マテリアルの設定
	pDevice->SetMaterial(&pMat->MatD3D);

	//モデルパーツの描画
	m_mesh->DrawSubset(0);

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
#include "objectx.h"
#include "application.h"

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
	//メッシュの解放
	if (m_mesh = NULL)
	{
		m_mesh->Release();
		m_mesh = NULL;
	}

	//マテリアルの破棄
	if (m_buffMat != NULL)
	{
		m_buffMat->Release();
		m_buffMat = NULL;
	}
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
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	//テクスチャの設定を戻す
	pDevice->SetTexture(0, NULL);

	//ワールドマトリックスを初期化(親)
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映(親)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映(親)
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//Zテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

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
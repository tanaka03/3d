#include "application.h"
#include "renderer.h"
#include "mesh.h"
#include "object3d.h"

CMesh::CMesh()
{
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_meshX = 5;
	m_meshZ = 5;
}

CMesh::~CMesh()
{
}

HRESULT CMesh::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	m_MeshField_VertexNum = (m_meshX + 1) * (m_meshZ + 1);				//頂点数
	m_MeshField_IndexNum = (m_meshX + 1) * 2 * (m_meshZ - 1) * 2;			//インデックス
	m_MeshField_PrimitiveNum = m_meshX * m_meshZ * 2 + (m_meshZ - 1) * 4;	//ポリゴン

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_MeshField_VertexNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * m_MeshField_IndexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//==========================
	//インデックスバッファ
	//==========================
	//インデックスバッファをロック
	WORD * pIdx;

	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nIdxCnt = 0;

	for (int nCntZ = 0; nCntZ <= m_meshZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= m_meshX; nCntX++)
		{
			//インデックスの設定
			pIdx[nIdxCnt] = nCntX + (nCntZ * (m_meshZ + 1)) + (m_meshZ + 1);
			pIdx[nIdxCnt + 1] = nCntX + (nCntZ * (m_meshZ + 1));

			nIdxCnt += 2;

			//縮退ポリゴン
			if (nCntX == m_meshX)
			{
				pIdx[nIdxCnt] = nCntX + (nCntZ * (m_meshZ + 1)) + (m_meshZ + 1);
				pIdx[nIdxCnt + 1] = nCntX + (nCntZ * (m_meshZ + 1));

				nIdxCnt += 2;
			}
		}
	}

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュフィールドの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CMesh::Uninit()
{
	//頂点バッファの破壊
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//インデックスバッファの破壊
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュフィールドの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CMesh::Update()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュフィールドの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CMesh::Draw()
{
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_objpos.y, m_objpos.x, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデバイスのデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_MeshField_VertexNum,	//頂点数
		0,
		m_MeshField_PrimitiveNum	/*描画するプリミティブ数*/);
}
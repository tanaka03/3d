#include "application.h"
#include "renderer.h"
#include "mesh.h"
#include "object3d.h"
#include "player.h"

#include "debugproc.h"

#include <vector>
#include <stdio.h>

using namespace std;

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝
CMesh::CMesh() :
	m_pTexture(nullptr)
{
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_meshX = 5;
	m_meshZ = 5;
}


//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝
CMesh::~CMesh()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CMesh::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	m_MeshField_VertexNum = (m_meshX + 1) * (m_meshZ + 1);					//頂点数
	m_MeshField_IndexNum = (m_meshX + 1) * 2 * m_meshX + (m_meshZ - 1) * 2;	//インデックス
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
	WORD *pIdx;

	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nIdxCnt = 0;

	for (int nCntZ = 0; nCntZ < m_meshZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= m_meshX; nCntX++)
		{
			//インデックスの設定
			pIdx[nIdxCnt] = nCntX + nCntZ * (m_meshZ + 1) + (m_meshZ + 1);
			pIdx[nIdxCnt + 1] = nCntX + nCntZ * (m_meshZ + 1);

			nIdxCnt += 2;

			//縮退ポリゴン
			if (nCntX == m_meshX)
			{
				pIdx[nIdxCnt] = nCntX + nCntZ * (m_meshZ + 1);
				pIdx[nIdxCnt + 1] = (nCntX + nCntZ * (m_meshX + 1) + (m_meshZ + 1)) + 1;

				nIdxCnt += 2;
			}
		}
	}

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CMesh::Uninit()
{
	//インデックスバッファの破壊
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	SetDestroy(true);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CMesh::Update()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CMesh::Draw()
{
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
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
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_MeshField_VertexNum,	//頂点数
		0,
		m_MeshField_PrimitiveNum	/*描画するプリミティブ数*/);
}

void CMesh::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		//テクスチャのポインタ
}

bool CMesh::Collision(D3DXVECTOR3 pos)
{
	//インデックスバッファをロック
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点バッファをロック
	VERTEX_3D *pVtx = nullptr;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int cnt = 0; cnt < m_MeshField_VertexNum; cnt++)
	{
		pVtx[cnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	for (int i = 0; i < m_MeshField_PrimitiveNum; i++)
	{
		if (pIdx[i] == pIdx[i + 1] && pIdx[i] == pIdx[i + 2] && pIdx[i + 1] == pIdx[i + 2])
		{
			continue;
		}

		//頂点の位置
		D3DXVECTOR3 posA = pVtx[pIdx[i]].pos;
		D3DXVECTOR3 posB = pVtx[pIdx[i + 1]].pos;
		D3DXVECTOR3 posC = pVtx[pIdx[i + 2]].pos;

		//頂点のベクトル
		D3DXVECTOR3 vecA = posB - posA;
		D3DXVECTOR3 vecB = posC - posB;
		D3DXVECTOR3 vecC = posA - posC;

		//ポリゴンの頂点とプレイヤーの位置のベクトル
		D3DXVECTOR3 DistanceA = pos - posA;
		D3DXVECTOR3 DistanceB = pos - posB;
		D3DXVECTOR3 DistanceC = pos - posC;

		//ポリゴンの頂点のベクトルとプレイヤーから頂点のベクトルの計算結果
		float fResult1 = vecA.x * DistanceA.z - vecA.z * DistanceA.x;
		float fResult2 = vecB.x * DistanceB.z - vecB.z * DistanceB.x;
		float fResult3 = vecC.x * DistanceC.z - vecC.z * DistanceC.x;

		if (fResult1 * fResult2 >= 0 &&
			fResult2 * fResult3 >= 0 &&
			fResult3 * fResult1 >= 0)
		{//ポリゴンの範囲内に入った場合
		 //pVtx[pIdx[i]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		 //pVtx[pIdx[i + 1]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		 //pVtx[pIdx[i + 2]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			m_meshPt = i;

		 //メッシュの判定
			D3DXVECTOR3 V1 = posB - posA;
			D3DXVECTOR3 V2 = posC - posA;
			D3DXVECTOR3 normal;

			D3DXVec3Cross(&normal, &V2, &V1);
			D3DXVec3Normalize(&normal, &normal);

			m_posOld = pos;
			pos.y = posA.y - ((pos.x - posA.x) * normal.x + (pos.z - posA.z) * normal.z) / normal.y;

			if (normal == D3DXVECTOR3(0.0f,0.0f,0.0f))
			{//法線が0の時、pos.yの値が-nan(ind)になる為、ヒットした地点が代入される前に終了
				return true;
			}

			m_CollisionPos = pos;
			return true;
		}
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();
}

void CMesh::SetIdxPos(D3DXVECTOR3 pos, int idx)
{
	//インデックスバッファをロック
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点バッファをロック
	VERTEX_3D *pVtx = nullptr;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[pIdx[idx]].pos = pos;

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();
}

D3DXVECTOR3 CMesh::GetIdxPos(int idx)
{
	//インデックスバッファをロック
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点バッファをロック
	VERTEX_3D *pVtx = nullptr;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 pos;
	pos = pVtx[pIdx[idx]].pos;

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	return pos;
}
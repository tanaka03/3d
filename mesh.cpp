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
CMesh::CMesh()
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
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	m_MeshField_VertexNum = (m_meshX + 1) * (m_meshZ + 1);					//頂点数
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
	CPlayer *pPlayer = CApplication::GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	//インデックスバッファをロック
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点バッファをロック
	VERTEX_3D *pVtx = nullptr;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int cnt = 0; cnt < m_MeshField_VertexNum; cnt++)
	{
		pVtx[cnt].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	}

	for (int i = 0; i < m_MeshField_PrimitiveNum; i++)
	{
		if (pIdx[i] == pIdx[i + 1] && pIdx[i] == pIdx[i + 2] && pIdx[i + 1] == pIdx[i + 2])
		{
			continue;
		}

		//頂点の位置
		auto posA = pVtx[pIdx[i]].pos;
		auto posB = pVtx[pIdx[i + 1]].pos;
		auto posC = pVtx[pIdx[i + 2]].pos;

		//頂点のベクトル
		auto vecA = posB - posA;
		auto vecB = posC - posB;
		auto vecC = posA - posC;

		//ポリゴンの頂点とプレイヤーの位置のベクトル
		auto DistanceA = playerPos - posA;
		auto DistanceB = playerPos - posB;
		auto DistanceC = playerPos - posC;

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

			//メッシュの判定
			auto V1 = posB - posA;
			auto V2 = posC - posA;
			D3DXVECTOR3 normal;

			D3DXVec3Cross(&normal, &V2, &V1);
			D3DXVec3Normalize(&normal, &normal);
			playerPos.y = posA.y - ((playerPos.x - posA.x) * normal.x + (playerPos.z - posA.z) * normal.z) / normal.y;

			pPlayer->SetCollision(true);
			pPlayer->SetPos(playerPos);
			break;
		}
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュの描画
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
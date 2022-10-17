#include "meshfield.h"
#include "object3d.h"

CMeshField::CMeshField()
{
}

CMeshField::~CMeshField()
{
}

CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int X, int Z)
{
	CMeshField *pMesh = nullptr;
	pMesh = new CMeshField;

	//ヌルチェック
	if (pMesh != nullptr)
	{
		// ポリゴンの初期化処理
		pMesh->SetX(X);
		pMesh->SetZ(Z);
		pMesh->SetPos(pos);
		pMesh->SetScale(scale);
		pMesh->Init();
	}

	return pMesh;
}

HRESULT CMeshField::Init()
{
	CMesh::Init();

	auto pos = GetPos();
	auto scale = GetScale();
	int meshX = GetX();
	int meshZ = GetZ();
	m_MeshField_VertexNum = GetVtxNum();

	//頂点バッファをロック
	VERTEX_3D * pVtx = nullptr;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_MeshField_VertexNum; nCnt++)
	{
		//頂点座標の設定
		pVtx[nCnt].pos = D3DXVECTOR3(pos.x + scale.x * (nCnt % (meshX + 1)), rand() % 100, pos.z - scale.z * (nCnt / (meshZ + 1)));

		//各頂点の法線の設定　※　ベクトルの大きさは1にする必要がある
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//頂点カラー
		pVtx[nCnt].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//テクスチャ座標
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + 0.5f * (nCnt % (meshZ + 1)), 0.0f + 0.5f * (nCnt / (meshZ + 1)));
	}

	//インデックスバッファをロック
	WORD * pIdx;

	D3DXVECTOR3 Vtx[3], edge[2], Normal;

	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int i = 0; i < GetIdxNum() - 2; i++)
	{
		Vtx[0] = pVtx[pIdx[i + 0]].pos;
		Vtx[1] = pVtx[pIdx[i + 1]].pos;
		Vtx[2] = pVtx[pIdx[i + 2]].pos;

		edge[0] = Vtx[1] - Vtx[0];
		edge[1] = Vtx[2] - Vtx[1];

		//ポリゴンの面の法線を求める
		if (i % 2 == 0)
		{
			D3DXVec3Cross(&Normal, &edge[0], &edge[1]);
		}

		else
		{
			D3DXVec3Cross(&Normal, &edge[1], &edge[0]);
		}

		D3DXVec3Normalize(&Normal, &Normal);

		pVtx[pIdx[i]].nor += Normal;
		pVtx[pIdx[i + 1]].nor += Normal;
		pVtx[pIdx[i + 2]].nor += Normal;
	}

	for (int j = 0; j < m_MeshField_VertexNum; j++)
	{
		D3DXVec3Normalize(&pVtx[j].nor, &pVtx[j].nor);
	}

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュフィールドの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CMeshField::Uninit()
{
	CMesh::Uninit();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュフィールドの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CMeshField::Update()
{
	CMesh::Update();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュフィールドの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CMeshField::Draw()
{
	CMesh::Draw();
}
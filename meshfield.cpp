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
		pVtx[nCnt].pos = D3DXVECTOR3(pos.x + scale.x * (nCnt % (meshX + 1)), rand() % 50, pos.z - scale.z * (nCnt / (meshZ + 1)));

		//各頂点の法線の設定　※　ベクトルの大きさは1にする必要がある
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラー
		pVtx[nCnt].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//テクスチャ座標
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + 0.5f * (nCnt % (meshZ + 1)), 0.0f + 0.5f * (nCnt / (meshZ + 1)));
	}

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
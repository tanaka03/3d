#include "sphere.h"
#include "object3d.h"

CSphere::CSphere()
{
	m_fAngleX = 0.0f;
	m_fAngleZ = 0.0f;
	m_fRadius = 0.0f;
}

CSphere::~CSphere()
{
}

CSphere *CSphere::Create(D3DXVECTOR3 pos, float radius, int X, int Z)
{
	CSphere *pMesh = nullptr;
	pMesh = new CSphere;

	//ヌルチェック
	if (pMesh != nullptr)
	{
		// ポリゴンの初期化処理
		pMesh->SetX(X);
		pMesh->SetZ(Z);
		pMesh->SetRadius(radius);
		pMesh->SetPos(pos);
		pMesh->Init();
	}

	return pMesh;
}

HRESULT CSphere::Init()
{
	CMesh::Init();

	auto pos = GetPos();
	int meshX = GetX();
	int meshZ = GetZ();

	//頂点バッファをロック
	VERTEX_3D * pVtx = nullptr;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < meshZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= meshX; nCntX++)
		{
			m_fAngleX = (D3DX_PI * 2.0f) / meshX;
			m_fAngleZ = (D3DX_PI * 2.0f) / meshZ;

			//頂点座標の設定
			pVtx[nCntX + (nCntZ * meshX)].pos = D3DXVECTOR3(sinf(m_fAngleX * nCntX) * cosf(m_fAngleZ * nCntZ),
				sinf(m_fAngleZ * nCntZ),
				cosf(m_fAngleX * nCntX) * cosf(m_fAngleZ * nCntZ)) * m_fRadius;

			//各頂点の法線の設定　※ベクトルの大きさは1にする必要がある
			pVtx[nCntX + (nCntZ * meshX)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラー
			pVtx[nCntX + (nCntZ * meshX)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標
			pVtx[nCntX + (nCntZ * meshX)].tex = D3DXVECTOR2(0.0f + 0.5 * (nCntX % (meshX + 1)), 0.0f + 0.5 * (nCntZ / (meshZ + 1)));
		}
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュフィールドの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CSphere::Uninit()
{
	CMesh::Uninit();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュフィールドの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CSphere::Update()
{
	CMesh::Update();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//メッシュフィールドの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CSphere::Draw()
{
	CMesh::Draw();
}
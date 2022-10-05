#include "application.h"
#include "billboard.h"
#include "object3d.h"
#include "input.h"
#include "keyboard.h"
#include "texture.h"

CBillboard::CBillboard() : m_texture(CTexture::TEXTURE_NONE)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_scale = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	m_blend = BLEND_NONE;
}

CBillboard::~CBillboard()
{
}

HRESULT CBillboard::Init()
{
	//頂点バッファの生成
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(-m_scale.x, m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_scale.x, m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_scale.x, -m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_scale.x, -m_scale.y, 0.0f);

	//各頂点の法線の設定　※　ベクトルの大きさは1にする必要がある
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CBillboard::Uninit()
{
	//頂点バッファの破壊
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	CBillboard::Release();
}

void CBillboard::Update()
{
	auto pos = GetPos();
	pos += GetMove();
	SetPos(pos);
}

void CBillboard::Draw()
{
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxTrans, mtxView;				//計算用マトリックス

	switch (m_blend)
	{
	case BLEND_ADDITIVE:
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	case BLEND_SUBSTRUCT:
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	default:
		break;
	}

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//カメラの逆行列を設定
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//カメラから見て近い部分を上書き
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

}

void CBillboard::SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom)
{
	VERTEX_3D* pVtx;        //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(Xtop, Ytop);
	pVtx[1].tex = D3DXVECTOR2(Xbottom, Ytop);
	pVtx[2].tex = D3DXVECTOR2(Xtop, Ybottom);
	pVtx[3].tex = D3DXVECTOR2(Xbottom, Ybottom);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
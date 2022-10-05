#include "application.h"
#include "object3d.h"
#include "input.h"
#include "keyboard.h"
#include "texture.h"

CObject3D::CObject3D() : m_texture(CTexture::TEXTURE_NONE)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_scale = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	m_Zfunc = D3DCMP_EQUAL;
}

CObject3D::~CObject3D()
{
}

HRESULT CObject3D::Init()
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
	pVtx[0].pos = D3DXVECTOR3(-m_scale.x, -m_scale.y, m_scale.z);
	pVtx[1].pos = D3DXVECTOR3(m_scale.x, -m_scale.y, m_scale.z);
	pVtx[2].pos = D3DXVECTOR3(-m_scale.x, m_scale.y, -m_scale.z);
	pVtx[3].pos = D3DXVECTOR3(m_scale.x, m_scale.y, -m_scale.z);

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

void CObject3D::Uninit()
{
	//頂点バッファの破壊
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	CObject3D::Release();
}

void CObject3D::Update()
{
	auto pos = GetPos();
	pos += GetMove();

	SetPos(pos);

	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = m_objpos + D3DXVECTOR3(-GetScale().x, -GetScale().y, GetScale().z);
	pVtx[1].pos = m_objpos + D3DXVECTOR3(GetScale().x, -GetScale().y, GetScale().z);
	pVtx[2].pos = m_objpos + D3DXVECTOR3(-GetScale().x, GetScale().y, -GetScale().z);
	pVtx[3].pos = m_objpos + D3DXVECTOR3(GetScale().x, GetScale().y, -GetScale().z);

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

void CObject3D::Draw()
{
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	//テクスチャの設定を戻す
	pDevice->SetTexture(0, NULL);

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

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//Zテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, m_Zfunc);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//カリング無効
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

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

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

}

void CObject3D::SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom)
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

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//平面判定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
bool CObject3D::PlaneCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Length, float CollisionVal)
{
	float fDistance = ((Destpos.x - pos.x) * (Destpos.x - pos.x)) +
		((Destpos.z - pos.z) * (Destpos.z - pos.z));

	D3DXVECTOR3 vec = Destpos - pos;
	float fYDistance = ((Destpos.y - pos.y) * (Destpos.y - pos.y));
	float Y = D3DXVec3Dot(&D3DXVECTOR3(0, 1, 0), &vec);

	float fRad = powf((Length + Length), CollisionVal);

	if (fDistance <= fRad && fYDistance <= Y)
	{
		return true;
	}
	return false;
}
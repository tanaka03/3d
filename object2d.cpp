#include "application.h"
#include "object2d.h"
#include "input.h"
#include "keyboard.h"
#include "texture.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクト２Ｄのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CObject2D::CObject2D() : m_texture(CTexture::TEXTURE_NONE)
{
	m_objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nCntY = 0;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクト２Ｄのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CObject2D::~CObject2D()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクト２Ｄの初期化処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CObject2D::Init()
{
	//頂点バッファの生成
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,    //確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,            //頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;        //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクト２Ｄの終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObject2D::Uninit()
{
	//頂点バッファの破壊
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	SetDestroy(true);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクト２Ｄの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObject2D::Update()
{
	if (m_bUseMyCol)
	{
		switch (GetMyCol())
		{
		case COLOR_RED:				//赤
			CObject2D::SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case COLOR_ORANGE:			//橙
			CObject2D::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
			break;

		case COLOR_YELLOW:			//黄
			CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			break;

		case COLOR_LIGHTGREEN:		//黄緑
			CObject2D::SetCol(D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f));
			break;

		case COLOR_GREEN:			//緑
			CObject2D::SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			break;

		case COLOR_LIGHTBLUE:		//水
			CObject2D::SetCol(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
			break;

		case COLOR_BLUE:			//青
			CObject2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
			break;

		case COLOR_PURPLE:			//紫
			CObject2D::SetCol(D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f));
			break;

		case COLOR_PINK:			//桃
			CObject2D::SetCol(D3DXCOLOR(1.0f, 0.5f, 1.0f, 1.0f));
			break;

		case COLOR_WHITE:			//白
			CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;

		default:
			CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetMyCol(COLOR_INVALID);
			break;
		}
	}

	VERTEX_2D*pVtx;        //頂点情報へのポインタ 

	m_objpos += m_move;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(m_objpos.x - m_Width, m_objpos.y - m_Height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_objpos.x + m_Width, m_objpos.y - m_Height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_objpos.x - m_Width, m_objpos.y + m_Height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_objpos.x + m_Width, m_objpos.y + m_Height, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//オブジェクト２Ｄの描画処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObject2D::Draw()
{
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	//頂点バッファの生成
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,
		2);						//プリミティブ(ポリゴン)数
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//テクスチャ座標
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObject2D::SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom)
{
	VERTEX_2D*pVtx;        //頂点情報へのポインタ

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
//アニメーション
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CObject2D::SetAnim(int DivX, int DivY, int speed, int interval, bool loop)
{
	m_nCounterAnim++;

	//アニメーション
	if ((m_nCounterAnim % speed) == interval)//ここで速度調整
	{
		m_nPatternAnim++;

		CObject2D::SetUV((1.0f / DivX) * m_nPatternAnim,
			(1.0f / DivX) + (1.0f / DivX) * m_nPatternAnim,
			(1.0f / DivY) * m_nCntY,
			(1.0f / DivY) + (1.0f / DivY) * m_nCntY);

		if (DivX == m_nPatternAnim)
		{
			m_nCntY++;
		}

		if (m_nPatternAnim == (DivX + DivY) && !loop)
		{
			Uninit();
			return;
		}
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//四角判定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
bool CObject2D::SquareCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Length, float CollisionVal)
{
	float fDistance = ((Destpos.x - pos.x) * (Destpos.x - pos.x)) +
		((Destpos.y - pos.y) * (Destpos.y - pos.y));

	float fRad = powf((Length + Length), CollisionVal);

	if (fDistance <= fRad)
	{
		return true;
	}
	return false;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//丸判定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
bool CObject2D::CircleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Radius, float CollisionVal)
{
	float fDistance = ((Destpos.x - pos.x) * (Destpos.x - pos.x)) +
		((Destpos.y - pos.y) * (Destpos.y - pos.y));

	float fRad = powf((Radius + Radius) * D3DX_PI, CollisionVal);

	if (fDistance <= fRad)
	{
		return true;
	}
	return false;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//内積判定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
bool CObject2D::AngleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float minAngle, float maxAngle, float radius)
{
	//Min -1.0 Max 1.0で円形判定
	D3DXVECTOR3 vec = Destpos - pos;

	//正規化
	D3DXVec3Normalize(&vec, &vec);

	//内積
	float fDot = sinf(D3DXVec3Dot(&D3DXVECTOR3(0, 1, 0), &vec));

	bool Radius = CircleCollision(pos, Destpos, radius, 2);

	if (fDot <= maxAngle && fDot > minAngle && Radius)
	{
		return true;
	}

	return false;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//指定の範囲判定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
bool CObject2D::RangeCollision(D3DXVECTOR3* pos, float Xmin, float Xmax, float Ymin, float Ymax)
{
	D3DXVECTOR3 Pos = *pos;

	if (Pos.x <= Xmin)
	{
		return true;
	}

	if (Pos.x >= Xmax)
	{
		return true;
	}

	if (Pos.y <= Ymin)
	{
		return true;
	}

	if (Pos.y >= Ymax)
	{
		return true;
	}

	return false;
}

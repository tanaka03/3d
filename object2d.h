//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Object2D.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "object.h"
#include "texture.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

// 頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

class CObject2D : public CObject
{
public:
	enum EColor
	{
		COLOR_INVALID = 0,
		COLOR_RED,
		COLOR_ORANGE,
		COLOR_YELLOW,
		COLOR_LIGHTGREEN,
		COLOR_GREEN,
		COLOR_LIGHTBLUE,
		COLOR_BLUE,
		COLOR_PURPLE,
		COLOR_PINK,
		COLOR_WHITE,
		COLOR_MAX
	};

	CObject2D();
	~CObject2D() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom);
	void SetAnim(int DivX, int DivY, int speed, int interval, bool loop);
	bool SquareCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Length, float CollisionVal);
	bool CircleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Radius, float CollisionVal);
	bool AngleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float minAngle, float maxAngle, float radius);
	bool RangeCollision(D3DXVECTOR3* pos, float Xmin, float Xmax, float Ymin, float Ymax);

	//セッター
	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetMyCol(EColor col) { m_Ecol = col, m_bUseMyCol = true; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetScale(float width, float height) { m_Width = width, m_Height = height; }
	void SetTexture(CTexture::TEXTURE texture) { m_texture = texture; }// テクスチャの設定

	//ゲッター
	D3DXVECTOR3 GetPos() override { return m_objpos; }
	D3DXVECTOR3 GetMove() { return m_move; }
	D3DXVECTOR2 GetScale() { return D3DXVECTOR2(m_Width, m_Height); }
	D3DXCOLOR GetCol() { return m_col; }
	EColor GetMyCol() { return m_Ecol; }
	int GetLife() { return m_nLife; }
	float GetWidth() { return m_Width; }
	float GetHeight() { return m_Height; }

private:
	D3DXVECTOR3 m_objpos;
	CTexture::TEXTURE m_texture;	// テクスチャの列挙型
	D3DXVECTOR3 m_move;
	D3DXCOLOR m_col;
	EColor m_Ecol;
	int m_nLife;
	float m_Width;
	float m_Height;
	int m_nCounterAnim;
	int m_nPatternAnim;
	int m_nCntY;
	bool m_bState;
	bool m_bUseMyCol = false;
};

#endif
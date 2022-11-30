//＝＝＝＝＝＝＝＝＝＝＝＝＝
//line.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _LINE_H_
#define _LINE_H_

class CLine
{
public:
	CLine();
	~CLine();

	static CLine *Create(D3DXVECTOR3 pos, D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col);

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetCol(D3DXCOLOR col) { m_col = col; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_start;
	D3DXVECTOR3 m_end;
	D3DXCOLOR m_col;
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
};

#endif

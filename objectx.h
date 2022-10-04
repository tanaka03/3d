//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ObjectX.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "object.h"
#include "texture.h"

class CObjectX : public CObject
{
public:
	CObjectX();
	~CObjectX() override;

	static CObjectX* Create(D3DXVECTOR3 pos);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//セッター
	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }
	void SetTexture(CTexture::TEXTURE texture) { m_texture = texture; }// テクスチャの設定

	//ゲッター
	D3DXVECTOR3 GetPos() override { return m_objpos; }
	D3DXVECTOR3 GetMove() { return m_move; }
	D3DXVECTOR3 GetScale() { return m_scale; }
	D3DXCOLOR GetCol() { return m_col; }

protected:
	LPD3DXBUFFER m_buffMat;
	DWORD m_dwNum;
	LPD3DXMESH m_mesh;

private:
	D3DXVECTOR3 m_objpos;
	CTexture::TEXTURE m_texture;	// テクスチャの列挙型
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;
};

#endif
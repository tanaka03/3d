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

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Shadow();
	void BindTexture(std::string inPath);

	//セッター
	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetDestroy(bool set) override { m_bRelease = set; }

	//ゲッター
	D3DXVECTOR3 GetPos() override { return m_objpos; }
	D3DXVECTOR3 GetMove() { return m_move; }
	D3DXVECTOR3 GetScale() { return m_scale; }
	D3DXVECTOR3 GetRot() { return m_rot; }
	D3DXVECTOR3 GetMaxModel() { return m_maxModel; }
	D3DXVECTOR3 GetMinModel() { return m_minModel; }
	D3DXCOLOR GetCol() { return m_col; }
	bool GetDestroy() override { return m_bRelease; }

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_objpos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_maxModel;
	D3DXVECTOR3 m_minModel;
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;
	bool m_bRelease;
};

#endif
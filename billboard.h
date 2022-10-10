//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Billboard.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "object.h"
#include "texture.h"

class CBillboard : public CObject
{
public:
	enum EBlend
	{
		BLEND_NONE = 0,
		BLEND_ADDITIVE,
		BLEND_SUBSTRUCT,
		BLEND_MAX
	};

	CBillboard();
	~CBillboard() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom);

	//セッター
	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }
	void SetTexture(CTexture::TEXTURE texture) { m_texture = texture; }// テクスチャの設定
	void SetBlend(EBlend blend) { m_blend = blend; }
	void SetZBuff(_D3DCMPFUNC func) { m_Zfunc = func; }
	void SetRelease(bool set) override { m_bRelease = set; }

	//ゲッター
	D3DXVECTOR3 GetPos() override { return m_objpos; }
	D3DXVECTOR3 GetMove() { return m_move; }
	D3DXVECTOR3 GetScale() { return m_scale; }
	D3DXCOLOR GetCol() { return m_col; }
	EBlend GetBlend() { return m_blend; }
	float GetWidth() { return m_Width; }
	float GetHeight() { return m_Height; }
	bool GetRelease() override { return m_bRelease; }

private:
	CTexture::TEXTURE m_texture;	// テクスチャの列挙型
	D3DXVECTOR3 m_objpos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;
	_D3DCMPFUNC m_Zfunc;
	EBlend m_blend;
	float m_Width;
	float m_Height;
	bool m_bRelease;
};

#endif
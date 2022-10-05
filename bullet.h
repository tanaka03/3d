//
//Bullet.h
//
#ifndef _BULLET_H_
#define _BULLET_H_

#include "billboard.h"

class CShadow;

class CBullet : public CBillboard
{
public:
	CBullet();
	~CBullet() override;

	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	CShadow *m_pShadow;
};

#endif
//
//Bullet.h
//
#ifndef _BULLET_H_
#define _BULLET_H_

#include "billboard.h"

class CBullet : public CBillboard
{
public:
	CBullet();
	~CBullet() override;

	static CBullet* Create(D3DXVECTOR3 pos);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
};

#endif
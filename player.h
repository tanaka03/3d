//
//Player.h
//
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "objectx.h"

class CShadow;

class CPlayer : public CObjectX
{
public:
	CPlayer();
	~CPlayer() override;

	static CPlayer *Create(D3DXVECTOR3 pos);
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	CShadow *m_pShadow;
};

#endif
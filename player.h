//
//Player.h
//
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "objectx.h"

class CShadow;
class CCamera;
class CBullet;

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
	void KillZ(float Z);

	void SetCollisionPos(D3DXVECTOR3 pos) { m_Collisionpos = pos; }
	void SetCollision(bool set) { m_bCollision = set; }

	D3DXVECTOR3 GetCollisionPos() { return m_Collisionpos; }
	bool GetCollision() { return m_bCollision; }

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Collisionpos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_rotDest;
	CShadow *m_pShadow;
	CCamera *m_pCamera;
	CBullet *m_pBullet;
	bool m_bCollision;
	bool m_bJump;
};

#endif
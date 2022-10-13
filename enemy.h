//
//Enemy.h
//
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "objectx.h"

class CShadow;

class CEnemy : public CObjectX
{
public:
	CEnemy();
	~CEnemy() override;

	static CEnemy *Create(D3DXVECTOR3 pos);
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void BackBased(float Y);

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
	bool m_bCollision;
};

#endif
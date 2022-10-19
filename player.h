//����������������������������������������
//Player.h
//����������������������������������������
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"

class CShadow;
class CCamera;
class CBullet;
class CModel;

class CPlayer : public CObject
{
public:
	CPlayer();
	~CPlayer() override;

	static CPlayer *Create(D3DXVECTOR3 pos);
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Shadow();
	void BackBased(float Y);

	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }
	void SetCollisionPos(D3DXVECTOR3 pos) { m_Collisionpos = pos; }
	void SetCollision(bool set) { m_bCollision = set; }
	void SetDestroy(bool set) override { m_bRelease = set; }

	D3DXVECTOR3 GetPos() override { return m_objpos; }
	D3DXVECTOR3 GetCollisionPos() { return m_Collisionpos; }
	D3DXMATRIX GetMtx() { return m_mtxWorld; }
	bool GetCollision() { return m_bCollision; }
	bool GetDestroy() override { return m_bRelease; }

private:
	D3DXVECTOR3 m_objpos;
	D3DXVECTOR3 m_Collisionpos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_rotDest;
	D3DXMATRIX m_mtxWorld;
	CShadow *m_pShadow;
	CCamera *m_pCamera;
	CBullet *m_pBullet;
	CModel *m_pModel;
	float m_fSpeed;
	bool m_bCollision;
	bool m_bJump;
	bool m_bRelease;
};

#endif
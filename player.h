//
//Player.h
//
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"

class CCamera;
class CBullet;
class CModel;

class CPlayer : public CObject
{
public:
	struct KEY
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	};

	struct KEYSET
	{
		int nFrame;
		KEY key[3];
	};

	CPlayer();
	~CPlayer() override;

	static CPlayer *Create(D3DXVECTOR3 pos);
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void BackBased(float Y);
	void Motion(int Num);

	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }
	void SetCollisionPos(D3DXVECTOR3 pos) { m_Collisionpos = pos; }
	void SetCollision(bool set) { m_bCollision = set; }
	void SetDestroy(bool set) override { m_bRelease = set; }
	void SetMeshIdx(int idx) { m_meshIdx = idx; }

	D3DXVECTOR3 GetPos() override { return m_objpos; }
	D3DXVECTOR3 GetCollisionPos() { return m_Collisionpos; }
	D3DXMATRIX GetMtx() { return m_mtxWorld; }
	bool GetCollision() { return m_bCollision; }
	bool GetDestroy() override { return m_bRelease; }
	int GetMeshIdx() { return m_meshIdx; }
	CModel *GetPlayerModel(int idx) { return m_pModel[idx]; }

private:
	static const int MaxParts = 3;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPD3DXMESH m_mesh;
	LPD3DXBUFFER m_buffMat;

	D3DXVECTOR3 m_objpos;
	D3DXVECTOR3 m_Collisionpos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_rotDest;
	D3DXMATRIX m_mtxWorld;
	CCamera *m_pCamera;
	CBullet *m_pBullet;
	CModel *m_pModel[3];
	KEYSET m_KeySet[2];
	int m_meshIdx;

	int m_numKey;
	int m_currentKey;
	int m_cntMotion;
	float m_fSpeed;
	bool m_bCollision;
	bool m_bJump;
	bool m_bRelease;

	D3DXVECTOR3 m_rotate;
};

#endif
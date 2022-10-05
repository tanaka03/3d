//
//Shadow.h
//
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "object3d.h"

class CShadow : public CObject3D
{
public:
	CShadow();
	~CShadow() override;

	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int life);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetLife(int life) { m_nLife = life; }
	void SetLifeNone(bool set) { m_bInfinity = set; }
	void SetScaleDown(bool set) { m_bScaleDown = set; }

	int GetLife() { return m_nLife; }
	bool SetLifeNone() { return m_bInfinity; }
	bool GetScaleDown() { return m_bScaleDown; }

private:
	int m_nLife;
	D3DXVECTOR3 m_Scale;
	D3DXVECTOR3 m_startScale;
	bool m_bInfinity = false;
	bool m_bScaleDown;
};

#endif
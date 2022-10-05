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

	static CShadow* Create(D3DXVECTOR3 pos, int life);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetLife(int life) { m_nLife = life; }
	void SetEnable(bool set) { m_bInfinity = set; }

	int GetLife() { return m_nLife; }
	bool GetEnable() { return m_bInfinity; }

private:
	int m_nLife;
	bool m_bInfinity = false;
};

#endif
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

	static CShadow* Create(D3DXVECTOR3 pos);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
};

#endif
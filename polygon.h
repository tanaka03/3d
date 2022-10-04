//
//Polygon.h
//
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "object3d.h"

class CPolygon : public CObject3D
{
public:
	CPolygon();
	~CPolygon() override;

	static CPolygon* Create(D3DXVECTOR3 pos);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
};

#endif
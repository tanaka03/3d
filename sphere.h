//＝＝＝＝＝＝＝＝＝＝＝＝＝
//sphere.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _SPHERE_H_		//二重ガードインクルード
#define _SPHERE_H_

#include "mesh.h"
#include "texture.h"

class CSphere : public CMesh
{
public:
	CSphere();
	~CSphere();

	static CSphere* Create(D3DXVECTOR3 pos, float radius, int X, int Z);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void SetRadius(float radius) { m_fRadius = radius; }

	float GetRadius() { return m_fRadius; }

private:
	float m_fAngleX;
	float m_fAngleZ;
	float m_fRadius;
};

#endif

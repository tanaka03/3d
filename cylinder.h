//＝＝＝＝＝＝＝＝＝＝＝＝＝
//cylinder.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _CYLINDER_H_		//二重ガードインクルード
#define _CYLINDER_H_

#include "mesh.h"
#include "texture.h"

class CCylinder : public CMesh
{
public:
	CCylinder();
	~CCylinder();

	static CCylinder* Create(D3DXVECTOR3 pos, float radius, int X, int Z);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void SetRadius(float radius) { m_fRadius = radius; }

	float GetRadius() { return m_fRadius; }

private:
	float m_fAngle;
	float m_fRadius;
};

#endif

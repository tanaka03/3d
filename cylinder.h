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

	static CCylinder* Create(D3DXVECTOR3 pos, float height,float radius, int X, int Z);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void SetRadius(float radius) { m_fRadius = radius; }
	void SetHeight(float height) { m_fHeight = height; }

	float GetRadius() { return m_fRadius; }
	float GetHeight() { return m_fHeight; }

private:
	float m_fAngle;
	float m_fRadius;
	float m_fHeight;
};

#endif

//��������������������������
//light.h
//��������������������������
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "renderer.h"

class CLight
{
public:
	CLight();
	~CLight();

	void Init();
	void Uninit();
	void Update();

private:
	static const int MaxLight = 1;
	D3DLIGHT9 m_light[MaxLight];		//���C�g���
};

#endif

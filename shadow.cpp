#include "shadow.h"
#include "application.h"

CShadow::CShadow()
{
}

CShadow::~CShadow()
{
}

CShadow* CShadow::Create(D3DXVECTOR3 pos)
{
	CShadow *pObj = nullptr;
	pObj = new CShadow;

	if (pObj != nullptr)
	{
		pObj->SetPos(pos);
		pObj->Init();
	}

	return pObj;
}

HRESULT CShadow::Init()
{
	CObject3D::SetScale(D3DXVECTOR3(30.0f, 0.0f, 30.0f));
	CObject3D::Init();
	CObject3D::SetBlend(BLEND_SUBSTRUCT);
	SetZBuff(D3DCMP_LESSEQUAL);
	CObject3D::SetTexture(CTexture::TEXTURE_SHADOW);
	return S_OK;
}

void CShadow::Uninit()
{
	CObject3D::Uninit();
}

void CShadow::Update()
{
	CObject3D::Update();

	auto pos = GetPos();
	SetPos(pos);
}

void CShadow::Draw()
{
	CObject3D::Draw();
}
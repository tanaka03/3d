#include "polygon.h"

CPolygon::CPolygon()
{
}

CPolygon::~CPolygon()
{
}

CPolygon* CPolygon::Create(D3DXVECTOR3 pos)
{
	CPolygon *pObj = nullptr;
	pObj = new CPolygon;

	if (pObj != nullptr)
	{
		pObj->SetPos(pos);
		pObj->Init();
	}

	return pObj;
}

HRESULT CPolygon::Init()
{
	CObject3D::Init();
	CObject3D::SetTexture(CTexture::TEXTURE_GRASS);
	return S_OK;
}

void CPolygon::Uninit()
{
	CObject3D::Uninit();
}

void CPolygon::Update()
{
	CObject3D::Update();
}

void CPolygon::Draw()
{
	CObject3D::Draw();
}
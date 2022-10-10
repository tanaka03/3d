#include "polygon.h"
#include "object3d.h"
#include "player.h"
#include "application.h"

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
	SetZBuff(D3DCMP_LESSEQUAL);
	return S_OK;
}

void CPolygon::Uninit()
{
	CObject3D::Uninit();
}

void CPolygon::Update()
{
	CPlayer *pPlayer = CApplication::GetPlayer();
	CObject3D::Update();
	m_scale = GetScale();
	auto pos = GetPos();

	auto playerPos = pPlayer->GetPos();
	auto collision = PlaneCollision(playerPos, pos, 62.0f, 2.0f);
	pPlayer->SetCollision(false);

	if (collision)
	{
		pPlayer->SetCollision(true);
		pPlayer->SetCollisionPos(pos);
	}
}

void CPolygon::Draw()
{
	CObject3D::Draw();
}
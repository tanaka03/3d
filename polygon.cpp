#include "polygon.h"
#include "object3d.h"
#include "player.h"

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
	CObject3D::Update();
	auto pos = GetPos();

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject *pObject = nullptr;
		pObject = pObject->GetMyObject(i);

		if (pObject == nullptr)
		{
			continue;
		}

		CObject::EObjType objType;
		objType = pObject->GetObjType();

		if (objType != CObject::OBJTYPE_PLAYER)
		{
			continue;
		}

		CPlayer *pPlayer = (CPlayer*)pObject;
		auto playerPos = pPlayer->GetPos();
		auto collision = PlaneCollision(playerPos, pos, 50.0f, 2.0f);

		if (!collision)
		{
			pPlayer->SetCollision(false);
			continue;
		}

		pPlayer->SetCollision(true);
	}
}

void CPolygon::Draw()
{
	CObject3D::Draw();
}
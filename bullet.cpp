#include "bullet.h"
#include "object3d.h"
#include "player.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

CBullet* CBullet::Create(D3DXVECTOR3 pos)
{
	CBullet *pObj = nullptr;
	pObj = new CBullet;

	if (pObj != nullptr)
	{
		pObj->SetPos(pos);
		pObj->Init();
	}

	return pObj;
}

HRESULT CBullet::Init()
{
	CBillboard::Init();
	CBillboard::SetTexture(CTexture::TEXTURE_GRASS);
	SetZBuff(D3DCMP_LESSEQUAL);
	return S_OK;
}

void CBullet::Uninit()
{
	CBillboard::Uninit();
}

void CBullet::Update()
{
	CBillboard::Update();
}

void CBullet::Draw()
{
	CBillboard::Draw();
}
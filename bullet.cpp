#include "bullet.h"
#include "object3d.h"
#include "player.h"
#include "shadow.h"

CBullet::CBullet()
{
	SetObjType(OBJTYPE_BULLET);
	m_life = 0;
}

CBullet::~CBullet()
{
}

CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int life)
{
	CBullet *pObj = nullptr;
	pObj = new CBullet;

	if (pObj != nullptr)
	{
		pObj->SetPos(pos);
		pObj->SetMove(move);
		pObj->SetLife(life);
		pObj->Init();
	}

	return pObj;
}

HRESULT CBullet::Init()
{
	SetCol(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	SetScale(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CBillboard::SetTexture(CTexture::TEXTURE_BULLET);
	CBillboard::Init();
	SetBlend(BLEND_NONE);

	m_pShadow = CShadow::Create(GetPos(), 100);
	m_pShadow->SetScale(D3DXVECTOR3(5.0f, 0.0f, 5.0f));

	return S_OK;
}

void CBullet::Uninit()
{
	CBillboard::Uninit();
}

void CBullet::Update()
{
	CBillboard::Update();
	m_pos = GetPos();
	m_life--;

	m_pShadow->SetPos(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z) / 2);

	if (m_life <= 0)
	{
		m_pShadow->Uninit();
		Uninit();
		return;
	}
}

void CBullet::Draw()
{
	CBillboard::Draw();
}
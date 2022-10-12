#include "bullet.h"
#include "object3d.h"
#include "player.h"
#include "shadow.h"
#include "effect.h"

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
	SetScale(D3DXVECTOR3(5.0f, 5.0f, 0.0f));
	CBillboard::SetTexture(CTexture::TEXTURE_BULLET);
	CBillboard::Init();
	SetBlend(BLEND_NONE);
	SetZBuff(D3DCMP_LESS);

	m_pShadow = CShadow::Create(GetPos(), D3DXVECTOR3(5.0f, 0.0f, 5.0f), 100);

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

	CEffect::Create(m_pos, D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXCOLOR(0.0f,0.6f,0.6f,1.0f), 80, CEffect::EFFECT_DEFAULT);
	m_pShadow->SetPos(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z) / 2);

	m_life--;
	if (m_life <= 0)
	{
		m_pShadow->SetDestroy(true);
		Uninit();
		return;
	}
}

void CBullet::Draw()
{
	CBillboard::Draw();
}
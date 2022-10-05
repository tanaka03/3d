#include "bullet.h"
#include "object3d.h"
#include "player.h"
#include "shadow.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet *pObj = nullptr;
	pObj = new CBullet;

	if (pObj != nullptr)
	{
		pObj->SetPos(pos);
		pObj->SetMove(move);
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

	m_pShadow = m_pShadow->Create(GetPos());
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
	m_pos.x += 2.5f;
	SetPos(m_pos);

	m_pShadow->SetPos(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z) / 2);
	m_pShadow->SetScale(D3DXVECTOR3(10.0f,0.0f,10.0f));
}

void CBullet::Draw()
{
	CBillboard::Draw();
}
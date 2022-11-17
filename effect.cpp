#include "effect.h"
#include "billboard.h"
#include "player.h"
#include "shadow.h"

CEffect::CEffect() : m_type(EFFECT_DEFAULT)
{
	m_life = 0;
}

CEffect::~CEffect()
{
}

CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int life, EType type)
{
	CEffect *pObj = nullptr;
	pObj = new CEffect;

	if (pObj != nullptr)
	{
		pObj->SetPos(pos);
		pObj->SetMove(move);
		pObj->SetCol(col);
		pObj->SetLife(life);
		pObj->SetType(type);
		pObj->Init();
	}

	return pObj;
}

HRESULT CEffect::Init()
{
	SetScale(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CBillboard::Init();
	SetBlend(BLEND_ADDITIVE);
	SetZBuff(D3DCMP_LESS);

	switch (m_type)
	{
	case EFFECT_DEFAULT:
		CBillboard::BindTexture("SHADOW");
		break;

	default:
		break;
	}

	return S_OK;
}

void CEffect::Uninit()
{
	CBillboard::Uninit();
}

void CEffect::Update()
{
	CBillboard::Update();
	m_pos = GetPos();
	m_scale = GetScale();
	m_col = GetCol();

	m_col.a -= 0.02f;
	m_scale.x -= 0.1f;
	m_scale.y -= 0.1f;

	SetScale(m_scale);
	SetCol(m_col);

	m_life--;
	if (m_life <= 0 || m_col.a <= 0.0f)
	{
		Uninit();
		return;
	}
}

void CEffect::Draw()
{
	CBillboard::Draw();
}
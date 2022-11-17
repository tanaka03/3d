#include "shadow.h"
#include "application.h"

CShadow::CShadow()
{
	m_bInfinity = false;
	m_bScaleDown = false;
}

CShadow::~CShadow()
{
}

CShadow* CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int life)
{
	CShadow *pObj = nullptr;
	pObj = new CShadow;

	if (pObj != nullptr)
	{
		pObj->SetPos(pos);
		pObj->SetScale(scale);
		pObj->SetLife(life);
		pObj->Init();
	}

	return pObj;
}

HRESULT CShadow::Init()
{
	CObject3D::Init();
	CObject3D::SetBlend(BLEND_SUBSTRUCT);
	SetZBuff(D3DCMP_LESSEQUAL);
	CObject3D::BindTexture("SHADOW");

	m_startScale = GetScale();
	return S_OK;
}

void CShadow::Uninit()
{
	CObject3D::Uninit();
}

void CShadow::Update()
{
	CObject3D::Update();
	m_Scale = GetScale();

	if (m_bScaleDown)
	{
		m_Scale.x += (10.0f - m_Scale.x) * 0.2f;
		m_Scale.z += (10.0f - m_Scale.z) * 0.2f;
	}

	else if (!m_bScaleDown)
	{
		m_Scale.x += (m_startScale.x - m_Scale.x) * 0.2f;
		m_Scale.z += (m_startScale.z - m_Scale.z) * 0.2f;
	}

	SetScale(m_Scale);

	if (m_nLife <= 0)
	{
		if (!m_bInfinity)
		{
			Uninit();
			return;
		}
	}
}

void CShadow::Draw()
{
	CObject3D::Draw();
}
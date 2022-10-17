//＝＝＝＝＝＝＝＝＝＝＝＝＝
//light.cpp
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "light.h"
#include "application.h"
#include "renderer.h"

CLight::CLight()
{
}

CLight::~CLight()
{
}

void CLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;								//ライトの方向ベクトル

	//ライトをクリアする
	memset(&m_light, 0, sizeof(D3DLIGHT9));

	//==========================
	//1つ目
	//==========================
	//ライトの種類を設定
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光を設定
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.6f, -3.0f, 0.6f);

	//正規化する
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light[0].Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(0, &m_light[0]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//ライトの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CLight::Uninit()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//ライトの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CLight::Update()
{
}
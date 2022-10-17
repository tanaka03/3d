//��������������������������
//light.cpp
//��������������������������
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
	D3DXVECTOR3 vecDir;								//���C�g�̕����x�N�g��

	//���C�g���N���A����
	memset(&m_light, 0, sizeof(D3DLIGHT9));

	//==========================
	//1��
	//==========================
	//���C�g�̎�ނ�ݒ�
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.6f, -3.0f, 0.6f);

	//���K������
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light[0].Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &m_light[0]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
}

//��������������������������
//���C�g�̏I��
//��������������������������
void CLight::Uninit()
{
}

//��������������������������
//���C�g�̍X�V
//��������������������������
void CLight::Update()
{
}
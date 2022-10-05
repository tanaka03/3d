#include "application.h"
#include "renderer.h"
#include "texture.h"
#include "keyboard.h"
#include "camera.h"
#include "light.h"
#include "object.h"
#include "object3d.h"
#include "objectx.h"

#include "polygon.h"
#include "player.h"

CApplication* CApplication::m_pApplication = nullptr;
CInputKeyboard *CApplication::m_pInputKeyboard = nullptr;
CRenderer *CApplication::m_pRenderer = nullptr;
CTexture *CApplication::m_pTexture = nullptr;
CCamera *CApplication::m_pCamera = nullptr;
CObject *g_apObject = nullptr;
CObject3D *g_apObject3d = nullptr;

CApplication::CApplication()
{
}

CApplication::~CApplication()
{

}

HRESULT CApplication::Init(HWND hWnd, HINSTANCE hInstance)
{
	//�����_�����O�N���X�̐���
	m_pRenderer = new CRenderer;

	// ����������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//�L�[�{�[�h�N���X�̐���
	m_pInputKeyboard = new CInputKeyboard;

	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return -1;
	}

	//�e�N�X�`���N���X�̐���
	m_pTexture = new CTexture;

	m_pLight = new CLight;
	m_pLight->Init();

	m_pCamera = new CCamera;
	m_pCamera->Init();

	m_pPolygon->Create(D3DXVECTOR3(0.0f, 0.0f,0.0f));
	m_pPlayer->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

void CApplication::Uninit()
{
	//�e�N�X�`���N���X�̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->ReleaseAll();

		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//�J�����N���X�̔j��
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//�L�[�{�[�h�N���X�̔j��
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//�����_�����O�N���X�̔j��
	if (m_pRenderer != nullptr)
	{
		// �I������
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// �A�v���P�[�V�����̉��
	if (m_pApplication != nullptr)
	{
		delete m_pApplication;
		m_pApplication = nullptr;
	}
}

void CApplication::Update()
{
	//�L�[�{�[�h�̍X�V�����͍ŏ��ɍs��
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	m_pRenderer->Update();
	m_pCamera->Update();
}

void CApplication::Draw()
{
	m_pRenderer->Draw();
	m_pCamera->SetCamera();
}
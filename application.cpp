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

#include "debugproc.h"

CApplication* CApplication::m_pApplication = nullptr;
CInputKeyboard *CApplication::m_pInputKeyboard = nullptr;
CRenderer *CApplication::m_pRenderer = nullptr;
CTexture *CApplication::m_pTexture = nullptr;
CCamera *CApplication::m_pCamera = nullptr;
CPlayer *CApplication::m_pPlayer = nullptr;

CDebugProc *CApplication::m_pDebugProc = nullptr;

CObject *g_apObject = nullptr;
CObject3D *g_apObject3d = nullptr;

CApplication::CApplication()
{
	m_bWire = false;
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

#ifdef _DEBUG
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();
#endif

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

	m_pPolygon = CPolygon::Create(D3DXVECTOR3(0.0f, 0.0f,0.0f));
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

void CApplication::Uninit()
{
#ifdef _DEBUG
	//�f�o�b�O�v���V�[�W���̔j��
	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Uninit();

		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}
#endif

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

	//���C���[�t���[���ɂ��鏈��
	if (m_pInputKeyboard->GetTrigger(DIK_F2))
	{
		m_bWire = ((!m_bWire) ? true : false);
		if(m_bWire) m_pRenderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else if(!m_bWire) m_pRenderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

void CApplication::Draw()
{
	m_pRenderer->Draw();
	m_pCamera->SetCamera();
}
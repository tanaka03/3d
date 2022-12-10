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
#include "file.h"
#include "model.h"
#include "myimgui.h"

#include "meshfield.h"
#include "cylinder.h"
#include "sphere.h"
#include "ball.h"

#include "debugproc.h"

CApplication* CApplication::m_pApplication = nullptr;

CObject *g_apObject = nullptr;
CObject3D *g_apObject3d = nullptr;

CApplication* CApplication::GetInstance()
{
	if (m_pApplication == nullptr)
	{
		m_pApplication = new CApplication;
	}

	return m_pApplication;
}

CApplication::CApplication() :
	m_pRenderer(nullptr)
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

	//�t�@�C���N���X�̐���
	m_pFile = new CFile;

	//�e�N�X�`���N���X�̐���
	m_pTexture = new CTexture;
	m_pTexture->LoadAll();

	m_pModel = new CModel;
	m_pModel->LoadAll();

	//Imgui
	m_pMyImgui = new CMyImgui;
	m_pMyImgui->Init();

	//���C�g�N���X�̐���
	m_pLight = new CLight;
	m_pLight->Init();

	//�J�����N���X�̐���
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//m_pPolygon = CPolygon::Create(D3DXVECTOR3(0.0f, 0.0f,0.0f));
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//CBall::Create(D3DXVECTOR3(100.0f, 0.0f, -100.0f));

	//m_pMesh = CMeshField::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(25.0f,0.0f, 25.0f), 40, 40);
	//CCylinder::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), 10.0f, 25.0f, 10, 10);
	//CSphere::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), 30.0f, 30, 30);
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

	CObject::ReleaseAll();

	//Imgui
	if (m_pMyImgui != nullptr)
	{
		m_pMyImgui->Uninit();

		delete m_pMyImgui;
		m_pMyImgui = nullptr;
	}

	//�e�N�X�`���N���X�̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->UnloadAll();

		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//���f���N���X�̔j��
	if (m_pModel != nullptr)
	{
		m_pModel->Clear();

		delete m_pModel;
		m_pModel = nullptr;
	}

	//�J�����N���X�̔j��
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//���C�g�N���X�̔j��
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = nullptr;
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

	//�t�@�C���N���X�̔j��
	if (m_pFile != nullptr)
	{
		delete m_pFile;
		m_pFile = nullptr;
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
	m_pMyImgui->Update();
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
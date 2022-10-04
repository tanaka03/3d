//＝＝＝＝＝＝＝＝＝＝＝＝＝
//camera.cpp
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "application.h"
#include "camera.h"
#include "input.h"
#include "keyboard.h"

CCamera::CCamera()
{
	memset(&m_camera, 0, sizeof(CCamera));
}

CCamera::~CCamera()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//カメラの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CCamera::Init()
{
	//視点・注視点・上方向を設定する
	m_camera.posV = D3DXVECTOR3(0.0f, 150.0f, 300.0f);	//視点
	m_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の視点
	m_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//注視点
	m_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の注視点
	m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//上方向ベクトル
	m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の向き

	//三平方だかなんだかのやつ
	float x = m_camera.posR.x - m_camera.posV.x;
	float z = m_camera.posR.z - m_camera.posV.z;
	m_camera.fDistance = sqrtf((x * x) + (z * z));		//視点から注視点の距離

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//カメラの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CCamera::Uninit()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//カメラの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CCamera::Update()
{	
	//===========================
	//注視点
	//===========================
	//左
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_Q) == true)
	{
		m_camera.rot.y -= 0.05f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//右
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_E) == true)
	{
		m_camera.rot.y += 0.05f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//===========================
	//視点
	//===========================
	//左
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_J) == true)
	{
		m_camera.rot.y -= 0.05f;
		m_camera.posV.x = m_camera.posR.x + sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posV.z = m_camera.posR.z + cosf(m_camera.rot.y) * m_camera.fDistance;
	}
	
	//右
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_L) == true)
	{
		m_camera.rot.y += 0.05f;
		m_camera.posV.x = m_camera.posR.x + sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posV.z = m_camera.posR.z + cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//===========================
	//カメラ移動
	//===========================
	//前
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{
		m_camera.posV.x -= sinf(m_camera.rot.y) * 0.8f;
		m_camera.posV.z -= cosf(m_camera.rot.y) * 0.8f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//後
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{
		m_camera.posV.x += sinf(m_camera.rot.y) * 0.8f;
		m_camera.posV.z += cosf(m_camera.rot.y) * 0.8f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//右
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{
		m_camera.posV.x -= sinf(m_camera.rot.y + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posV.z -= cosf(m_camera.rot.y + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//左
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{
		m_camera.posV.x += sinf(m_camera.rot.y + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posV.z += cosf(m_camera.rot.y + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posR.x = m_camera.posV.x - sinf(m_camera.rot.y) * m_camera.fDistance;
		m_camera.posR.z = m_camera.posV.z - cosf(m_camera.rot.y) * m_camera.fDistance;
	}

	//上昇
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_R) == true)
	{
		m_camera.posV.y += sinf(m_camera.rot.x + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posV.y += cosf(m_camera.rot.z + D3DX_PI * 0.5f) * 0.8f;
	}

	//下降
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_F) == true)
	{
		m_camera.posV.y -= sinf(m_camera.rot.x + D3DX_PI * 0.5f) * 0.8f;
		m_camera.posV.y -= cosf(m_camera.rot.z + D3DX_PI * 0.5f) * 0.8f;
	}

	//上
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_I) == true)
	{
		m_camera.rot.x -= 0.05f;
		m_camera.posR.y = m_camera.posV.y - tanf(m_camera.rot.x) * m_camera.fDistance;
	}

	//下
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_K) == true)
	{
		m_camera.rot.x += 0.05f;
		m_camera.posR.y = m_camera.posV.y - tanf(m_camera.rot.x) * m_camera.fDistance;
	}
	

	//===========================
	//モデルに追従
	//===========================
	//m_camera.posR.x += (m_camera.posRDest.x - m_camera.posR.x) * 0.5f;
	//m_camera.posV.x += (m_camera.posVDest.x - m_camera.posV.x) * 0.5f;

	//m_camera.posR.z += (m_camera.posRDest.z - m_camera.posR.z) * 0.5f;
	//m_camera.posV.z += (m_camera.posVDest.z - m_camera.posV.z) * 0.5f;

	//m_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y) * 0.5f;
	//m_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y) * 0.5f;

	//m_camera.posVDest.x = pPlayer->pos.x + sinf(m_camera.rot.x) * m_camera.fDistance;
	//m_camera.posVDest.z = pPlayer->pos.z + cosf(m_camera.rot.z) * m_camera.fDistance;


	//======================
	//正規化
	//======================
	if (m_camera.rot.y > D3DX_PI)
	{
		m_camera.rot.y -= D3DX_PI * 2;
	}

	else if (m_camera.rot.y < -D3DX_PI)
	{
		m_camera.rot.y += D3DX_PI * 2;
	}

	//======================
	//なんかいろいろ
	//======================
	//初期の位置に戻す
	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_F1) == true)
	{
		//視点・注視点・上方向を設定する
		m_camera.posV = D3DXVECTOR3(0.0f, 150.0f, 300.0f);	//視点
		m_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//注視点
		m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//上方向ベクトル
		m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//カメラの設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_camera.mtxView,
		&m_camera.posV,
		&m_camera.posR,
		&m_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		5.0f,
		1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_camera.mtxProjection);
}
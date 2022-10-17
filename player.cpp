#include <stdlib.h>
#include "objectx.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "player.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "debugproc.h"
#include "file.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayer::CPlayer()
{
	SetObjType(OBJTYPE_PLAYER);
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_bCollision = false;
	m_bJump = false;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayer::~CPlayer()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = nullptr;
	pPlayer = new CPlayer;

	//ヌルチェック
	if (pPlayer != nullptr)
	{
		// ポリゴンの初期化処理
		pPlayer->Init();
		pPlayer->SetPos(pos);
	}

	return pPlayer;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの初期化処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CPlayer::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	CObjectX::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//Xファイルの読み込み(体)
	D3DXLoadMeshFromX("data\\MODEL\\fokko.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_buffMat,
		NULL,
		&m_dwNum,
		&m_mesh);

	CObjectX::Init();
	m_pShadow = CShadow::Create(GetPos(), D3DXVECTOR3(30.0f, 0.0f, 30.0f), 100);
	m_pShadow->SetLifeNone(true);

	CApplication::GetFile()->LoadText("data/FILE/aa.txt");

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Uninit()
{
	CObjectX::Uninit();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Update()
{
	CCamera *pCamera = CApplication::GetCamera();
	CCamera::CAMERA *camera = pCamera->GetCamera();
	CObjectX::Update();
	m_pos = GetPos();
	auto posOld = GetPos();

	//床判定の上だった場合
	if (m_bCollision)
	{
		m_pos.y = posOld.y;
		m_bJump = true;
	}

	else
	{
		m_move.y -= 0.5f;
		m_bJump = false;
	}

	//奥
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_UP))
	{
		m_pos.z -= 1.5f;
		m_rotDest.y = camera->rot.y + D3DX_PI * 0.0f;				//目的の角度

		//右奥
		if(CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
			m_pos.x -= 1.5f,
			m_rotDest.y = camera->rot.y + D3DX_PI * 0.25f;

		//左奥
		else if(CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
			m_pos.x += 1.5f,
			m_rotDest.y = camera->rot.y - D3DX_PI * 0.25f;
	}

	//後
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_DOWN))
	{
		m_pos.z += 1.5f;
		m_rotDest.y = camera->rot.y - D3DX_PI * 1.0f;

		//右後
		if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
			m_pos.x -= 1.5f,
			m_rotDest.y = camera->rot.y + D3DX_PI * 0.75f;

		//左後
		else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
			m_pos.x += 1.5f,
			m_rotDest.y = camera->rot.y - D3DX_PI * 0.75f;
	}

	//右
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
	{
		m_pos.x -= 1.5f;
		m_rotDest.y = camera->rot.y + D3DX_PI * 0.5f;
	}

	//左
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
	{
		m_pos.x += 1.5f;
		m_rotDest.y = camera->rot.y - D3DX_PI * 0.5f;
	}

	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z), D3DXVECTOR3(-sinf(m_rot.y), 0.0f, -cosf(m_rot.y)), 100);
	}

	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_SPACE))
	{
		if (m_bJump)
		{
 			m_move.y = ((m_move.y + 20.0f) - m_move.y) * 0.4f;
		}
	}

	if (m_bCollision)
	{
		m_pShadow->SetScale(D3DXVECTOR3(30.0f, 0.0f, 30.0f));

		if(m_pos.y < m_Collisionpos.y) m_pos.y = m_Collisionpos.y;
	}

	else if(!m_bCollision)
	{
		//落ちる速度が０より上だった場合、影が縮小
		if (m_move.y > 0) m_pShadow->SetScaleDown(true);
		//落ちる速度が-３より下だった場合、影が拡大
		else if (m_move.y < -3) m_pShadow->SetScaleDown(false);
	}

	BackBased(-300.0f);

#ifdef _DEBUG
	CDebugProc::Print("目的の向き%f\n現在の向き%f\n現在の位置 X:%f Y:%f Z:%f", m_rotDest.y, m_rot.y, m_pos.x, m_pos.y, m_pos.z);
#endif

	//目的の方向の正規化
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2;
	}

	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2;
	}

	//モデルの回転の慣性
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	SetPos(m_pos);
	SetMove(m_move);
	SetRot(m_rot);
	m_pShadow->SetPos(D3DXVECTOR3(m_pos.x / 2, m_Collisionpos.y, m_pos.z / 2));

	//こいつがやりました↓
	//m_pShadow->SetZBuff(D3DCMP_EQUAL);

	//======================
	//正規化
	//======================
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}

	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの描画処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Draw()
{
	CObjectX::Draw();
}

void CPlayer::BackBased(float Y)
{
	if (m_pos.y < Y)
	{
		m_pos = m_Collisionpos;
		m_move.y = 0.0f;
	}
}
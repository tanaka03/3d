#include "objectx.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "ball.h"
#include "shadow.h"
#include "meshfield.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBall::CBall()
{
	SetObjType(OBJTYPE_ENEMY);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bCollision = false;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBall::~CBall()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CBall * CBall::Create(D3DXVECTOR3 pos)
{
	CBall *pEnemy = nullptr;
	pEnemy = new CBall;

	//ヌルチェック
	if (pEnemy != nullptr)
	{
		// ポリゴンの初期化処理
		pEnemy->Init();
		pEnemy->SetPos(pos);
	}

	return pEnemy;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの初期化処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CBall::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	CObjectX::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//Xファイルの読み込み(体)
	D3DXLoadMeshFromX("data\\MODEL\\sphere.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_buffMat,
		NULL,
		&m_dwNum,
		&m_mesh);

	CObjectX::Init();
	CObjectX::BindTexture("BULLET");

	//m_pShadow = CShadow::Create(GetPos(), D3DXVECTOR3(30.0f, 0.0f, 30.0f), 100);
	//m_pShadow->SetLifeNone(true);

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CBall::Uninit()
{
	CObjectX::Uninit();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CBall::Update()
{
	CObjectX::Update();
	m_pos = GetPos();
	D3DXVECTOR3 posOld = GetPos();

	CMeshField *pMesh = CApplication::GetInstance()->GetMeshField();
	bool collision = pMesh->Collision(m_pos);

	float fSpeed = 3.0f;
	float length = GetMaxModel().y - GetMinModel().y;

	//ボールの回転
	auto Rotate = [length, fSpeed]() {
		float pi = length * D3DX_PI;
		float rotate = fSpeed / pi * (D3DX_PI * 2);
		return rotate;
	};

	if (collision)
	{
		m_pos = D3DXVECTOR3(m_pos.x, pMesh->GetHitPos().y, m_pos.z);
	}

	if (m_bCollision)
	{
		/*m_pShadow->SetScale(D3DXVECTOR3(30.0f, 0.0f, 30.0f));*/
		if (m_pos.y < m_Collisionpos.y) m_pos.y = m_Collisionpos.y;
	}

	//奥
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_UP))
	{
		m_pos.z -= fSpeed;

		//ボールの回転
		m_rot.x += Rotate();

		//右奥
		if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
			m_pos.x -= fSpeed;

		//左奥
		else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
			m_pos.x += fSpeed;
	}

	//後
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_DOWN))
	{
		m_pos.z += fSpeed;

		//ボールの回転
		m_rot.x -= Rotate();

		//右後
		if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
			m_pos.x -= fSpeed;

			//左後
		else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
			m_pos.x += fSpeed;
	}

	//右
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
	{
		m_pos.x -= fSpeed;

		//ボールの回転
		m_rot.z -= Rotate();
	}

	//左
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
	{
		m_pos.x += fSpeed;

		//ボールの回転
		m_rot.z += Rotate();
	}

	//目的の方向の正規化
	if (m_rotDest.y - m_rot.y > D3DX_PI)
		m_rotDest.y -= D3DX_PI * 2;

	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
		m_rotDest.y += D3DX_PI * 2;

	SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + length, m_pos.z));
	SetMove(m_move);
	SetRot(m_rot);
	//m_pShadow->SetPos(D3DXVECTOR3(m_pos.x / 2, m_Collisionpos.y, m_pos.z / 2));

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
void CBall::Draw()
{
	CObjectX::Draw();
}
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
#include "light.h"
#include "model.h"
#include "meshfield.h"

#include "line.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayer::CPlayer()
{
	SetObjType(OBJTYPE_PLAYER);
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_fSpeed = 1.5f;
	m_bCollision = false;
	m_bJump = false;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayer::~CPlayer()
{
	m_cntMotion = 1;
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

	LoadModel("UnityChan");

	//頂点バッファをロック
	VERTEX_3D * pVtx = nullptr;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_numVtx; nCnt++)
	{
		//頂点カラー
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	//m_pModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModel::MODEL_FOKKO);

	//m_pModel[1] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModel::MODEL_CYLINDER);
	//m_pModel[1]->BindTexture("EFFECT_0");

	//m_pModel[1] = CModel::Create(D3DXVECTOR3(20.0f,20.0f, 20.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),CModel::MODEL_STAR);
	//m_pModel[1]->SetParent(m_pModel[0]);
	//m_KeySet[0].nFrame = 60;
	//m_KeySet[0].key[0].rot = D3DXVECTOR3(0.0f, 120.0f, 0.0f);
	//m_KeySet[0].key[1].rot = D3DXVECTOR3(0.0f, 360.0f, 0.0f);

	//m_KeySet[1].key[0].rot = D3DXVECTOR3(0.0f, 360.0f, 0.0f);
	//m_KeySet[1].key[1].rot = D3DXVECTOR3(0.0f, 120.0f, 0.0f);

	//m_pModel[2] = CModel::Create(D3DXVECTOR3(-20.0f, 20.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModel::MODEL_STAR);
	//m_pModel[2]->SetParent(m_pModel[0]);
	//m_KeySet.key[2].pos = D3DXVECTOR3(100.0f, 100.0f, 100.0f);

	for (int i = 0; i < MaxLine; i++)
	{
		if (m_pLine[i] != nullptr)
		{
			m_pLine[i]->Uninit();
			delete m_pLine[i];
		}
	}

	//下四角
	m_pLine[0] = CLine::Create(m_objpos, m_minModel,
		D3DXVECTOR3(m_maxModel.x, m_minModel.y, m_minModel.z),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[1] = CLine::Create(m_objpos, m_minModel,
		D3DXVECTOR3(m_minModel.x, m_minModel.y, m_maxModel.z),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[2] = CLine::Create(m_objpos,
		D3DXVECTOR3(m_maxModel.x, m_minModel.y, m_maxModel.z),
		D3DXVECTOR3(m_minModel.x, m_minModel.y, m_maxModel.z),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[3] = CLine::Create(m_objpos,
		D3DXVECTOR3(m_maxModel.x, m_minModel.y, m_maxModel.z),
		D3DXVECTOR3(m_maxModel.x, m_minModel.y, m_minModel.z),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	//縦棒
	m_pLine[4] = CLine::Create(m_objpos,
		D3DXVECTOR3(m_minModel.x, m_minModel.y, m_minModel.z),
		D3DXVECTOR3(m_minModel.x, m_maxModel.y, m_minModel.z),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[5] = CLine::Create(m_objpos,
		D3DXVECTOR3(m_maxModel.x, m_minModel.y, m_minModel.z),
		D3DXVECTOR3(m_maxModel.x, m_maxModel.y, m_minModel.z),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[6] = CLine::Create(m_objpos,
		D3DXVECTOR3(m_minModel.x, m_minModel.y, m_maxModel.z),
		D3DXVECTOR3(m_minModel.x, m_maxModel.y, m_maxModel.z),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[7] = CLine::Create(m_objpos,
		D3DXVECTOR3(m_maxModel.x, m_minModel.y, m_maxModel.z),
		m_maxModel,
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	//上四角
	m_pLine[8] = CLine::Create(m_objpos,
		D3DXVECTOR3(m_minModel.x, m_maxModel.y, m_minModel.z),
		D3DXVECTOR3(m_maxModel.x, m_maxModel.y, m_minModel.z),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[9] = CLine::Create(m_objpos,
		D3DXVECTOR3(m_minModel.x, m_maxModel.y, m_minModel.z),
		D3DXVECTOR3(m_minModel.x, m_maxModel.y, m_maxModel.z),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[10] = CLine::Create(m_objpos,
		D3DXVECTOR3(m_maxModel.x, m_maxModel.y, m_maxModel.z),
		D3DXVECTOR3(m_minModel.x, m_maxModel.y, m_maxModel.z),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pLine[11] = CLine::Create(m_objpos,
		D3DXVECTOR3(m_maxModel.x, m_maxModel.y, m_maxModel.z),
		D3DXVECTOR3(m_maxModel.x, m_maxModel.y, m_minModel.z),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Uninit()
{
	//頂点バッファの破壊
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//メッシュの解放
	if (m_mesh != nullptr)
	{
		m_mesh->Release();
		m_mesh = nullptr;
	}

	//マテリアルの破棄
	if (m_buffMat != nullptr)
	{
		m_buffMat->Release();
		m_buffMat = nullptr;
	}

	for (int i = 0; i < MaxLine; i++)
	{
		if (m_pLine[i] != nullptr)
		{
			m_pLine[i]->Uninit();
			delete m_pLine[i];
		}
	}

	SetDestroy(true);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Update()
{
	CCamera *pCamera = CApplication::GetInstance()->GetCamera();
	CCamera::CAMERA *camera = pCamera->GetCamera();
	m_objpos += m_move;
	D3DXVECTOR3 posOld = m_objpos;

	//CMeshField *pMesh = CApplication::GetInstance()->GetMeshField();
	//bool collision = pMesh->Collision(m_objpos);

	//if (collision)
	//{
	//	D3DXVECTOR3 collisionPos =  pMesh->GetHitPos();
	//	m_objpos = D3DXVECTOR3(m_objpos.x, collisionPos.y + 1.5f, m_objpos.z);
	//	m_meshIdx = pMesh->GetPointIdx();
	//	m_bJump = true;
	//}
	//else
	//{
	//	m_move.y -= 0.5f;
	//	m_bJump = false;
	//}

	//奥
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_UP))
	{
		m_objpos.z -= m_fSpeed;
		m_rotDest.y = camera->rot.y + D3DX_PI * 0.0f;				//目的の角度

		//右奥
		if(CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
			m_objpos.x -= m_fSpeed,
			m_rotDest.y = camera->rot.y + D3DX_PI * 0.25f;

		//左奥
		else if(CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
			m_objpos.x += m_fSpeed,
			m_rotDest.y = camera->rot.y - D3DX_PI * 0.25f;
	}

	//後
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_DOWN))
	{
		m_objpos.z += m_fSpeed;
		m_rotDest.y = camera->rot.y - D3DX_PI * 1.0f;

		//右後
		if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
			m_objpos.x -= m_fSpeed,
			m_rotDest.y = camera->rot.y + D3DX_PI * 0.75f;

		//左後
		else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
			m_objpos.x += m_fSpeed,
			m_rotDest.y = camera->rot.y - D3DX_PI * 0.75f;
	}

	//右
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
	{
		m_objpos.x -= m_fSpeed;
		m_rotDest.y = camera->rot.y + D3DX_PI * 0.5f;
	}

	//左
	else if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
	{
		m_objpos.x += m_fSpeed;
		m_rotDest.y = camera->rot.y - D3DX_PI * 0.5f;
	}

	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		CBullet::Create(D3DXVECTOR3(m_objpos.x, m_objpos.y + 30.0f, m_objpos.z), D3DXVECTOR3(-sinf(m_rot.y), 0.0f, -cosf(m_rot.y)), 100);
	}

	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_SPACE))
	{
 		m_move.y = ((m_move.y + 20.0f) - m_move.y) * 0.4f;
	}

	if (m_bCollision)
	{
		if(m_objpos.y < m_Collisionpos.y) m_objpos.y = m_Collisionpos.y;
	}

	//m_pModel[0]->SetModelPos(m_objpos);

	BackBased(-300.0f);

#ifdef _DEBUG
	//CDebugProc::Print("目的の向き%f\n現在の向き%f\n現在の位置 X:%f Y:%f Z:%f", m_rotDest.y, m_rot.y, m_pos.x, m_pos.y, m_pos.z);
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

	//Motion(1);

	//モデルの回転の慣性
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	m_rotate.y += 0.2f;
	//m_pModel[1]->SetRotOffset(m_rotate);

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

	for (int i = 0; i < MaxLine; i++)
	{
		if (m_pLine[i] != nullptr)
		{
			m_pLine[i]->Update();
		}
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの描画処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Draw()
{
	for (int i = 0; i < MaxLine; i++)
	{
		if (m_pLine[i] != nullptr)
		{
			m_pLine[i]->Draw();
		}
	}

	if (m_modelMode == "xFile")
	{
		ModelDrawX();
	}

	if (m_modelMode == "fbxFile")
	{
		ModelDrawFbx();
	}
}

void CPlayer::ModelDrawX()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	//テクスチャの設定を戻す
	pDevice->SetTexture(0, NULL);

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//Zテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを保存
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_buffMat->GetBufferPointer();

	pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < (int)m_dwNum; i++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat->MatD3D);

		//モデルパーツの描画
		m_mesh->DrawSubset(i);
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	//テクスチャの設定を戻す
	pDevice->SetTexture(0, NULL);
}

void CPlayer::ModelDrawFbx()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	//テクスチャの設定を戻す
	pDevice->SetTexture(0, NULL);

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//Zテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデバイスのデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
		0,
		0,
		m_numVtx,	//頂点数
		0,
		m_numPrim	/*描画するプリミティブ数*/);
}

void CPlayer::BackBased(float Y)
{
	if (m_objpos.y < Y)
	{
		m_objpos = m_Collisionpos;
		m_move.y = 0.0f;
	}
}

void CPlayer::Motion(int Num)
{
	//if (m_pModel[Num] == nullptr)
	//{
	//	return;
	//}

	//int relative_Value = m_cntMotion / m_KeySet[m_currentKey].nFrame;

	//auto posDifference = m_KeySet.key[m_currentKey].pos - m_pModel[Num]->GetStartPos();
	//auto pos_Value = m_pModel[Num]->GetStartPos() + (posDifference * relative_Value);

	//D3DXVECTOR3 rotDifference = m_KeySet[m_currentKey].key[m_currentKey].rot - m_pModel[Num]->GetStartRot();
	//D3DXVECTOR3 rot_Value = m_pModel[Num]->GetStartRot() + (rotDifference * relative_Value);

	//m_pModel[Num]->SetPosOffset(pos_Value);
	//m_pModel[Num]->SetRotOffset(rot_Value);
	 
	//m_cntMotion++;

	//if (m_KeySet[m_currentKey].nFrame < m_cntMotion)
	//{
	//	m_cntMotion = 1;
	//	m_currentKey++;
	//}

	//if (m_numKey < m_currentKey)
	//{
	//	m_currentKey = 0;
	//}
}

void CPlayer::LoadModel(std::string path)
{
	CModel *pModel = CApplication::GetInstance()->GetModel();

	m_mesh = pModel->GetMesh(path);
	m_buffMat = pModel->GetBuffMat(path);
	m_dwNum = pModel->GetModelNum(path);
	m_maxModel = pModel->GetMaxModel(path);
	m_minModel = pModel->GetMinModel(path);
	m_pVtxBuff = pModel->GetVtxBuff(path);
	m_pIdxBuff = pModel->GetIdxBuff(path);
	m_numVtx = pModel->GetVertexCount(path);
	m_numPrim = pModel->GetPrimitiveCount(path);
	m_modelMode = pModel->GetModelMode(path);
}
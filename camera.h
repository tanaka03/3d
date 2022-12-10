//＝＝＝＝＝＝＝＝＝＝＝＝＝
//camera.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _CAMERA_H_		//二重ガードインクルード
#define _CAMERA_H_

#include "renderer.h"

class CObject;

class CCamera
{
public:
	struct CAMERA
	{
		D3DXVECTOR3 posV;			//視点
		D3DXVECTOR3 posVDest;		//目的の視点
		D3DXVECTOR3 posR;			//注視点
		D3DXVECTOR3 posRDest;		//目的の注視点
		D3DXVECTOR3 vecU;			//上方向ベクトル
		D3DXVECTOR3 rot;			//向き
		D3DXVECTOR3 rotDest;		//目的の向き
		D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
		D3DXMATRIX mtxView;			//ビューマトリックス
		float fDistance;			//視点から注視点の距離
	};

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	//セッター
	void SetCamera(void);
	void SetTraction(bool set) { m_bTraction = set; }

	//ゲッター
	CAMERA *GetCamera(void) { return &m_camera; }
	D3DXVECTOR3 GetWorldPosR() { return m_worldposR; }

private:
	CAMERA m_camera;
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_worldposV;	//視点
	D3DXVECTOR3 m_worldposR;	//注視点

	bool m_bTraction;
};

#endif

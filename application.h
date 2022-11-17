//
//Application.h
//
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "main.h"

class CInputKeyboard;
class CObject;
class CRenderer;
class CTexture;
class CCamera;
class CLight;
class CDebugProc;
class CFile;

class CPolygon;
class CPlayer;

class CApplication
{
public:
	static CApplication *GetInstance();

	CApplication();
	~CApplication();

	HRESULT Init(HWND hWnd, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	CInputKeyboard *GetInputKeyboard() { return m_pInputKeyboard; }
	CRenderer *GetRenderer() { return m_pRenderer; }
	CCamera *GetCamera() { return m_pCamera; }
	CDebugProc *GetDebugProc() { return m_pDebugProc; }
	CPlayer *GetPlayer() { return m_pPlayer; }
	CFile *GetFile() { return m_pFile; }
	CLight *GetLight() { return m_pLight; }
	CTexture *GetTexture() { return m_pTexture; }

private:
	static CApplication *m_pApplication;

	CObject *m_pObject;
	CPolygon *m_pPolygon;
	CLight *m_pLight;
	CPlayer *m_pPlayer;
	CCamera *m_pCamera;
	CInputKeyboard *m_pInputKeyboard;
	CRenderer *m_pRenderer;
	CTexture *m_pTexture;
	CDebugProc *m_pDebugProc;
	CFile *m_pFile;

	bool m_bWire;
};

#endif
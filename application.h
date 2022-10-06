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

class CPolygon;
class CPlayer;

class CApplication
{
public:
	static CApplication *m_pApplication;

	CApplication();
	~CApplication();

	HRESULT Init(HWND hWnd, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	static CInputKeyboard *GetInputKeyboard() { return m_pInputKeyboard; }
	static CRenderer *GetRenderer() { return m_pRenderer; }
	CTexture *GetTexture() { return m_pTexture; }
	static CCamera *GetCamera() { return m_pCamera; }
	CLight *GetLight() { return m_pLight; }
	static CDebugProc *GetDebugProc() { return m_pDebugProc; }

	static CApplication* GetInstance()
	{
		if (m_pApplication == nullptr)
		{
			m_pApplication = new CApplication;
		}

		return m_pApplication;
	}

private:
	CObject *m_pObject;
	CLight *m_pLight;
	CPlayer *m_pPlayer;
	CPolygon *m_pPolygon;
	bool m_bWire;

	static CCamera *m_pCamera;
	static CInputKeyboard *m_pInputKeyboard;
	static CRenderer *m_pRenderer;
	static CTexture *m_pTexture;
	static CDebugProc *m_pDebugProc;
};

#endif
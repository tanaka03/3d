//
//Input.h
//
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;
	LPDIRECTINPUTDEVICE8 GetInputDevice();

private:
	LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

#endif
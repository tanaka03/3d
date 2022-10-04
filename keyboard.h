//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Keyboard.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "input.h"

//===============================
//ライブラリのリンク
//===============================
#define NUM_KEY_MAX	(256)	//キーの最大数

class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard() override;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;
	bool GetTrigger(int nKey);
	bool GetPress(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];		//キーボードのプレス情報
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
};

#endif
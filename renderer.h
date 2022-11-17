//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Renderer.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _RENDERER_H_
#define _RENDERER_H_

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }	/*値をreturnするだけの場合こう書く、２行以上はcppで*/

private:
	void DrawFPS();

	// Direct3Dオブジェクト
	LPDIRECT3D9 m_pD3D;

	// Deviceオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPD3DXFONT m_pFont;
	D3DPRESENT_PARAMETERS m_pD3dpp;
};

#endif
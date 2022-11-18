//
//light.h
//
#ifndef _MYIMGUI_H_
#define _MYIMGUI_H_

class CMeshField;

class CMyImgui
{
public:
	CMyImgui();
	~CMyImgui();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	bool ImGuiText(bool show_demo_window, bool show_another_window);

private:
	CMeshField *m_pMesh;

	D3DXVECTOR3 m_meshPos;

	bool show_demo_window = true;
	bool show_another_window = false;
};

#endif
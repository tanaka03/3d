//
//DebugProc.h
//
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void Init();
	void Uninit();

	void Print(const char *pFormat, ...);
	void Draw();

private:
	std::string m_Str;
	LPD3DXFONT m_pFont;
};

#endif

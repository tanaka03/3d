#include "debugproc.h"
#include "main.h"
#include "application.h"
#include "renderer.h"
#include <tchar.h> 
#include <iostream>
#include <vector>

using namespace std;

LPD3DXFONT CDebugProc::m_pFont = nullptr;
string CDebugProc::m_Str;

CDebugProc::CDebugProc()
{
}

CDebugProc::~CDebugProc()
{
}

void CDebugProc::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	D3DXCreateFont(pDevice, 25, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Debug"), &m_pFont);
}

void CDebugProc::Uninit()
{
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

void CDebugProc::Print(const char *pFormat, ...)
{
	va_list args;
	va_start(args, pFormat);

	vector<int> Find;
	m_Str = pFormat;
	int nCntStr = 0;
	int nCntDeleted = 0;
	int nCntAdd = 0;

	//特定の文字の位置の数値を保存
	while(nCntStr < m_Str.length())
	{
		if (m_Str.substr(nCntStr, 1) == "%")
		{
			Find.push_back(nCntStr);
		}
		nCntStr++;
	}

	//特定の数値の場所を検索
	for (const auto &pos:Find)
	{
		string destStr = m_Str.substr(pos - nCntDeleted, 2);
		string argStr;

		if (destStr == "%d")
		{//int型
			auto Arg = va_arg(args, int);
			argStr = to_string(Arg);
			nCntAdd = argStr.length();
			m_Str.replace(pos - nCntDeleted, destStr.length(), argStr);
			nCntDeleted += destStr.length();
		}

		if (destStr == "%f")
		{//double型（floatだとva_argで暗黙的にdoubleに変換されてうまくいかない）
			auto Arg = va_arg(args, double);
			argStr = to_string(Arg);
			argStr += 'f';
			nCntAdd = argStr.length();
			m_Str.replace(pos - nCntDeleted, destStr.length(), argStr);
			nCntDeleted += destStr.length();
		}

		if (destStr == "%c")
		{//char型
			auto Arg = va_arg(args, char);
			argStr = Arg;
			nCntAdd = argStr.length();
			m_Str.replace(pos - nCntDeleted, destStr.length(), argStr);
			nCntDeleted += destStr.length();
		}

		if (destStr == "%s")
		{//const char型
			const char* Arg = va_arg(args, const char*);
			argStr = Arg;
			nCntAdd = argStr.length();
			m_Str.replace(pos - nCntDeleted, destStr.length(), argStr);
			nCntDeleted += destStr.length();
		}

		nCntDeleted -= nCntAdd;
	}

	va_end(args);
}

void CDebugProc::Draw()
{
	if (m_pFont == nullptr)
	{
		return;
	}

	RECT rect = { 0, 10, SCREEN_WIDTH, SCREEN_HEIGHT };

	wsprintf((TCHAR*)m_Str.c_str(), _T(m_Str.c_str()));

	// テキスト描画
	m_pFont->DrawText(NULL, m_Str.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#include "object.h"
#include <assert.h>

//===============================
//静的メンバ変数宣言
//===============================
CObject *CObject::m_apObject[MAX_OBJECT];
int CObject::m_nNumAll = 0;

//===============================
//オブジェクトのコンストラクタ
//===============================
CObject::CObject()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] == nullptr)
		{
			m_apObject[i] = this;
			m_nID = i;
			m_nNumAll++;
			break;
		}
	}
}

//===============================
//オブジェクトのデストラクタ
//===============================
CObject::~CObject()
{
}

//===============================
//オブジェクトの全解放
//===============================
void CObject::ReleaseAll()
{
	//メモリ解放
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		//NULLチェック
		if (m_apObject[i] != nullptr)
		{
			m_apObject[i]->Release();
		}
	}
}

//===============================
//オブジェクトの更新
//===============================
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] != nullptr)
		{
			// ポリゴンの更新処理
			m_apObject[i]->Update();
		}
	}
}

//===============================
//オブジェクトの描画
//===============================
void CObject::DrawAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		// ポリゴンの描画処理
		if (m_apObject[i] != nullptr)
		{
			// ポリゴンの更新処理
			m_apObject[i]->Draw();
		}
	}
}

//===============================
//オブジェクトの解放
//===============================
void CObject::Release()
{
	if (m_apObject[m_nID] != nullptr)
	{
		int nID = m_nID;

		delete m_apObject[nID];
		m_apObject[nID] = nullptr;
		m_nNumAll--;
	}
}

CObject *CObject::GetMyObject(int nNum)
{
	return m_apObject[nNum];
}
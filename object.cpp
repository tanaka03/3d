#include "object.h"
#include <assert.h>
#include <iostream>

using namespace std;

//===============================
//静的メンバ変数宣言
//===============================
list<CObject*> CObject::m_lst;
list<CObject*>::iterator CObject::m_prev;

//===============================
//オブジェクトのコンストラクタ
//===============================
CObject::CObject()
{
	m_lst.push_back(this);
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
	for (auto itr = m_lst.begin(); itr != m_lst.end();)
	{
		CObject *p = *itr;
		if (p != nullptr)
		{
			continue;
		}

		p->Uninit();
	}

	m_lst.clear();
}

//===============================
//オブジェクトの更新
//===============================
void CObject::UpdateAll()
{
	for (auto itr = m_lst.begin(); itr != m_lst.end();)
	{
		CObject *p = *itr;
		if (p == nullptr)
		{
			continue;
		}

		p->Update();

		if (p->GetRelease())
		{
			itr = m_prev;
		}

		itr++;
	}
}

//===============================
//オブジェクトの描画
//===============================
void CObject::DrawAll()
{
	for (CObject *p : m_lst)
	{
		if (p == nullptr)
		{
			continue;
		}

		p->Draw();
	}
}

//===============================
//オブジェクトの解放
//===============================
void CObject::Release()
{
	for (auto itr = m_lst.begin(); itr != m_lst.end();)
	{
		CObject *p = *itr;
		bool check = p->GetRelease();
		if (check)
		{
			m_prev = prev(itr);
			m_lst.erase(itr);
			return;
		}

		else
		{
			itr++;
		}
	}
}
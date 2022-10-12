#include "object.h"
#include <assert.h>
#include <iostream>

using namespace std;

//===============================
//静的メンバ変数宣言
//===============================
//list<CObject*> CObject::m_lst;
//list<CObject*>::iterator CObject::m_prev;

CObject* CObject::m_Top = nullptr;
CObject* CObject::m_Current = nullptr;

//===============================
//オブジェクトのコンストラクタ
//===============================
CObject::CObject()
{
	//m_lst.push_back(this);

	if (m_Top == nullptr)
	{
		this->m_Prev = nullptr;
		this->m_Next = nullptr;
		m_Top = this;
		m_Current = this;
	}

	else
	{
		this->m_Next = nullptr;
		this->m_Prev = m_Current;
		this->m_Prev->m_Next = this;
		m_Current = this;
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
	/*STL使う方*/
	//for (auto itr = m_lst.begin(); itr != m_lst.end();)
	//{
	//	CObject *p = *itr;
	//	if (p != nullptr)
	//	{
	//		continue;
	//	}

	//	p->Uninit();
	//}

	CObject *pObj = m_Top;
	while (pObj)
	{
		CObject *pObjNext = pObj->m_Next;
		pObj->Release();
		pObj = pObjNext;
	}
}

//===============================
//オブジェクトの更新
//===============================
void CObject::UpdateAll()
{
	/*STL使う方*/
	//for (auto itr = m_lst.begin(); itr != m_lst.end();)
	//{
	//	CObject *p = *itr;
	//	if (p == nullptr)
	//	{
	//		continue;
	//	}

	//	p->Update();

	//	if (p->GetRelease())
	//	{
	//		itr = m_prev;
	//	}

	//	itr++;
	//}

	CObject *pObj = m_Top;
	while(pObj)
	{
		CObject *pObjNext = pObj->m_Next;
		pObj->Update();
		pObj = pObjNext;
	}

	pObj = m_Top;
	while (pObj)
	{
		CObject *pObjNext = pObj->m_Next;
		pObj->Release();
		pObj = pObjNext;
	}
}

//===============================
//オブジェクトの描画
//===============================
void CObject::DrawAll()
{
	/*STL使う方*/
	//for (CObject *p : m_lst)
	//{
	//	if (p == nullptr)
	//	{
	//		continue;
	//	}

	//	p->Draw();
	//}

	CObject *pObj = m_Top;
	while (pObj)
	{
		CObject *pObjNext = pObj->m_Next;
		pObj->Draw();
		pObj = pObj->m_Next;
	}
}

//===============================
//オブジェクトの解放
//===============================
void CObject::Release()
{
	/*STL使う方*/
	//for (auto itr = m_lst.begin(); itr != m_lst.end();)
	//{
	//	CObject *p = *itr;
	//	bool check = p->GetRelease();
	//	if (check)
	//	{
	//		m_prev = prev(itr);
	//		m_lst.erase(itr);

	//		if (p != nullptr)
	//		{
	//			delete p;
	//			p = nullptr;
	//		}
	//		return;
	//	}

	//	else
	//	{
	//		itr++;
	//	}
	//}

	if (this->GetDestroy())
	{
		if (this->m_Next != nullptr && this->m_Prev != nullptr)
		{
			this->m_Next->m_Prev = this->m_Prev;
			this->m_Prev->m_Next = this->m_Next;
		}

		else if (this->m_Prev == nullptr && this->m_Next != nullptr)
		{
			this->m_Next->m_Prev = nullptr;
			m_Top = this->m_Next;
		}

		else if (this->m_Next == nullptr && this->m_Prev != nullptr)
		{
			this->m_Prev->m_Next = nullptr;
			m_Current = this->m_Prev;
		}

		else if (this->m_Next == nullptr && this->m_Prev == nullptr)
		{
			m_Top = nullptr;
			m_Current = nullptr;
		}

		delete this;
	}
}
#include "object.h"
#include <assert.h>
#include <iostream>

using namespace std;

//===============================
//�ÓI�����o�ϐ��錾
//===============================
//list<CObject*> CObject::m_lst;
//list<CObject*>::iterator CObject::m_prev;

CObject* CObject::m_Top = nullptr;
CObject* CObject::m_Current = nullptr;

//===============================
//�I�u�W�F�N�g�̃R���X�g���N�^
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
//�I�u�W�F�N�g�̃f�X�g���N�^
//===============================
CObject::~CObject()
{
}

//===============================
//�I�u�W�F�N�g�̑S���
//===============================
void CObject::ReleaseAll()
{
	/*STL�g����*/
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
//�I�u�W�F�N�g�̍X�V
//===============================
void CObject::UpdateAll()
{
	/*STL�g����*/
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
//�I�u�W�F�N�g�̕`��
//===============================
void CObject::DrawAll()
{
	/*STL�g����*/
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
//�I�u�W�F�N�g�̉��
//===============================
void CObject::Release()
{
	/*STL�g����*/
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
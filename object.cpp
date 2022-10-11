#include "object.h"
#include <assert.h>
#include <iostream>

using namespace std;

//===============================
//�ÓI�����o�ϐ��錾
//===============================
list<CObject*> CObject::m_lst;
list<CObject*>::iterator CObject::m_prev;

//===============================
//�I�u�W�F�N�g�̃R���X�g���N�^
//===============================
CObject::CObject()
{
	m_lst.push_back(this);
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
//�I�u�W�F�N�g�̍X�V
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
//�I�u�W�F�N�g�̕`��
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
//�I�u�W�F�N�g�̉��
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
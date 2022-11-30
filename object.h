//
//Object.h
//
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "renderer.h"

class CObject
{
public:
	enum EObjType
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_BULLET,
		OBJTYPE_ENEMY,
		OBJTYPE_MAX
	};

	CObject();
	virtual ~CObject();

	//explicit CObject(int nPriority = 3);
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();

	void SetObjType(EObjType obj) { m_objtype = obj; }
	virtual void SetPos(D3DXVECTOR3 pos) = 0;
	//virtual void SetPriority(int priority) = 0;
	virtual void SetDestroy(bool set) = 0;

	EObjType GetObjType() { return m_objtype; }
	virtual D3DXVECTOR3 GetPos() = 0;
	//virtual int GetPriority() = 0;
	virtual bool GetDestroy() = 0;

	CObject *GetPrev() { return m_Prev; }

protected:
	void Release();

private:
	//static std::list<CObject*> m_lst;
	//static std::list<CObject*>::iterator m_prev;

	static CObject *m_Top;
	static CObject *m_Current;
	CObject *m_Prev;
	CObject *m_Next;

	EObjType m_objtype;
	int m_nID;			//Ši”[æ‚Ì”Ô†

	bool m_bDestroy = false;

	//LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	//LPD3DXBUFFER m_buffMat;
	//DWORD m_dwNum;
	//LPD3DXMESH m_mesh;
};

#endif
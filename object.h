//
//Object.h
//
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "renderer.h"
#include <list>

#define MAX_OBJECT	(1024)

class CObject
{
public:
	enum EObjType
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_BULLET,
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
	virtual void SetRelease(bool set) = 0;

	CObject *GetMyObject(int nNum);
	EObjType GetObjType() { return m_objtype; }
	int GetObjAll() { return m_nNumAll; }

	virtual D3DXVECTOR3 GetPos() = 0;
	virtual bool GetRelease() = 0;

protected:
	void Release();
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPD3DXBUFFER m_buffMat;
	DWORD m_dwNum;
	LPD3DXMESH m_mesh;

private:
	static std::list<CObject*> m_lst;
	static std::list<CObject*>::iterator m_prev;

	static CObject *CObject::m_apObject[MAX_OBJECT];
	static int m_nNumAll;

	EObjType m_objtype;
	int m_nID;			//Ši”[æ‚Ì”Ô†

	bool m_bRelease = false;
};

#endif
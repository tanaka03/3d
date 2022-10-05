//
//Object.h
//
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "renderer.h"

#define MAX_OBJECT	(512)

class CObject
{
public:
	enum EObjType
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_MAX
	};

	CObject();
	virtual ~CObject();

	//explicit CObject(int nPriority = 3);
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void SetPos(D3DXVECTOR3 pos) = 0;
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();

	void SetObjType(EObjType obj) { m_objtype = obj; }

	CObject *GetMyObject(int nNum);
	EObjType GetObjType() { return m_objtype; }
	virtual D3DXVECTOR3 GetPos() = 0;
	int GetObjAll() { return m_nNumAll; }

protected:
	void Release();
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPD3DXBUFFER m_buffMat;
	DWORD m_dwNum;
	LPD3DXMESH m_mesh;

private:
	static CObject *CObject::m_apObject[MAX_OBJECT];
	static int m_nNumAll;
	EObjType m_objtype;
	int m_nID;			//Ši”[æ‚Ì”Ô†
};

#endif
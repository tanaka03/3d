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

	CObject *GetMyObject(int nNum);
	virtual D3DXVECTOR3 GetPos() = 0;
	int GetObjAll() { return m_nNumAll; }

protected:
	void Release();
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

private:
	static CObject *CObject::m_apObject[MAX_OBJECT];
	static int m_nNumAll;
	int m_nID;			//Ši”[æ‚Ì”Ô†
};

#endif
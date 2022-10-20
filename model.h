//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//model.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _MODEL_H_	//このマクロ定義がされてなかったら
#define _MODEL_H_	//２重インクルード防止のマクロ定義

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

class CModel
{
public:
	enum MODEL
	{
		MODEL_FOKKO,
		MODEL_STAR,
		MODEL_MAX,
		MODEL_NONE
	};

	static const char* s_FileName[];	// ファイルパス

	CModel();
	~CModel();

	static CModel *Create(D3DXVECTOR3 posOffset, D3DXVECTOR3 rotOffset, MODEL parts);

	HRESULT Init();
	void ReleaseAll();
	void Update();
	void Draw();
	void Shadow();
	void Load(MODEL model);

	void SetPosOffset(D3DXVECTOR3 pos) { m_posOffset = pos; }
	void SetRotOffset(D3DXVECTOR3 rot) { m_rotOffset = rot; }
	void SetModel(MODEL model) { m_model = model; }
	void SetParent(CModel* model) { m_pParent = model; }

	CModel GetParent() { return *m_pParent; }

private:
	static std::vector<CModel*> m_Data;
	static bool m_bLoaded[MODEL_MAX];

	LPD3DXBUFFER m_buffMat;
	DWORD m_dwNum;
	LPD3DXMESH m_mesh;
	MODEL m_model;
	CModel *m_pParent;
	D3DXVECTOR3 m_posOffset;
	D3DXVECTOR3 m_rotOffset;
	D3DXMATRIX m_mtxWorld;
};

#endif

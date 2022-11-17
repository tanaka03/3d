//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//model.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _MODEL_H_	//このマクロ定義がされてなかったら
#define _MODEL_H_	//２重インクルード防止のマクロ定義

#include "texture.h"

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
	void Release();
	void Update();
	void Draw();
	void Shadow();
	void BindTexture(std::string inPath);
	void Load(MODEL model);

	//セッター
	void SetPosOffset(D3DXVECTOR3 pos) { m_posOffset = pos; }
	void SetRotOffset(D3DXVECTOR3 rot) { m_rotOffset = rot; }
	void SetModel(MODEL model) { m_model = model; }
	void SetParent(CModel* model) { m_pParent = model; }

	//ゲッター
	CModel GetParent() { return *m_pParent; }
	D3DXVECTOR3 GetStartPos() { return m_startPos; }
	D3DXVECTOR3 GetStartRot() { return m_startRot; }
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }
	LPD3DXBUFFER GetBuffMat() { return m_buffMat; }
	LPD3DXMESH GetMesh() { return m_mesh; }
	DWORD GetModelNum() { return m_dwNum; }

private:
	static std::vector<CModel*> m_Data;
	static bool m_bLoaded[MODEL_MAX];

	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXBUFFER m_buffMat;
	DWORD m_dwNum;
	LPD3DXMESH m_mesh;
	MODEL m_model;
	CModel *m_pParent;
	D3DXVECTOR3 m_posOffset;
	D3DXVECTOR3 m_rotOffset;
	D3DXVECTOR3 m_startPos;
	D3DXVECTOR3 m_startRot;
	D3DXMATRIX m_mtxWorld;
	bool m_bRelease;
};

#endif

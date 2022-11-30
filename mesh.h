//＝＝＝＝＝＝＝＝＝＝＝＝＝
//mesh.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _MESH_H_		//二重ガードインクルード
#define _MESH_H_

#include "object.h"
#include "texture.h"

class CMesh : public CObject
{
public:
	CMesh();
	~CMesh();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	bool Collision(D3DXVECTOR3 pos);
	void BindTexture(std::string inPath);

	//セッター
	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }
	void SetDestroy(bool set) override { m_bRelease = set; }
	void SetVtxNum(int num) { m_MeshField_VertexNum = num; }
	void SetIdxNum(int num) { m_MeshField_IndexNum = num; }
	void SetPrimNum(int num) { m_MeshField_PrimitiveNum = num; }
	void SetX(int X) { m_meshX = X; }
	void SetZ(int Z) { m_meshZ = Z; }
	void SetIdxPos(D3DXVECTOR3 pos, int idx);

	//ゲッター
	D3DXVECTOR3 GetPos() override { return m_objpos; }
	D3DXVECTOR3 GetIdxPos(int idx);
	D3DXVECTOR3 GetMove() { return m_move; }
	D3DXVECTOR3 GetScale() { return m_scale; }
	D3DXVECTOR3 GetHitPos() { return m_CollisionPos; }
	D3DXCOLOR GetCol() { return m_col; }
	int GetVtxNum() { return m_MeshField_VertexNum; }
	int GetIdxNum() { return m_MeshField_IndexNum; }
	int GetPrimNum() { return m_MeshField_PrimitiveNum; }
	int GetX() { return m_meshX; }
	int GetZ() { return m_meshZ; }
	int GetPointIdx() { return m_meshPt; }
	bool GetDestroy() override { return m_bRelease; }

protected:
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		//インデックスバッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_CollisionPos;
	D3DXVECTOR3 m_objpos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;
	int m_meshPt;
	int m_meshX;
	int m_meshZ;
	int m_MeshField_VertexNum;
	int m_MeshField_IndexNum;
	int m_MeshField_PrimitiveNum;
	bool m_bRelease;
};

#endif

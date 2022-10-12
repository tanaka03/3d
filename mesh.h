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

	//セッター
	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }
	void SetTexture(CTexture::TEXTURE texture) { m_texture = texture; }// テクスチャの設定
	void SetDestroy(bool set) override { m_bRelease = set; }
	void SetVtxNum(int num) { m_MeshField_VertexNum = num; }
	void SetIdxNum(int num) { m_MeshField_IndexNum = num; }
	void SetPrimNum(int num) { m_MeshField_PrimitiveNum = num; }
	void SetX(int X) { m_meshX = X; }
	void SetZ(int Z) { m_meshZ = Z; }

	//ゲッター
	D3DXVECTOR3 GetPos() override { return m_objpos; }
	D3DXVECTOR3 GetMove() { return m_move; }
	D3DXVECTOR3 GetScale() { return m_scale; }
	D3DXCOLOR GetCol() { return m_col; }
	int GetVtxNum() { return m_MeshField_VertexNum; }
	int GetIdxNum() { return m_MeshField_IndexNum; }
	int GetPrimNum() { return m_MeshField_PrimitiveNum; }
	int GetX() { return m_meshX; }
	int GetZ() { return m_meshZ; }
	bool GetDestroy() override { return m_bRelease; }

protected:
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		//インデックスバッファへのポインタ

private:
	CTexture::TEXTURE m_texture;	// テクスチャの列挙型
	D3DXVECTOR3 m_objpos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;
	int m_meshX;
	int m_meshZ;
	int m_MeshField_VertexNum;
	int m_MeshField_IndexNum;
	int m_MeshField_PrimitiveNum;
	bool m_bRelease;
};

#endif

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//model.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _MODEL_H_	//このマクロ定義がされてなかったら
#define _MODEL_H_	//２重インクルード防止のマクロ定義

#include <d3d9.h>
#include <d3dx9.h>

class CModel
{
public:
	enum EModel
	{
		MODEL_FOKKO = 0,
		MODEL_STAR,
		MODEL_MAX,
		MODEL_NONE
	};

	struct ModelData
	{
		LPD3DXBUFFER m_buffMat;
		DWORD m_dwNum;
		LPD3DXMESH m_mesh;
	};

	static const char* s_FileName[];	// ファイルパス

public:
	CModel();		// デフォルトコンストラクタ
	~CModel();	// デストラクタ

public: /* メンバ関数 */
	void LoadAll();										// 全ての読み込み
	void Load(EModel Model);							// 指定の読み込み
	void ReleaseAll();									// 全ての破棄
	void Release(EModel Model);							// 指定の破棄
	ModelData GetModel(EModel Model);					// 情報の取得

private: /* メンバ変数 */
	ModelData m_model[MODEL_MAX];
};

#endif // !_TEXTURE_H_

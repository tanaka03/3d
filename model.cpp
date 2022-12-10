#include "model.h"
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "player.h"
#include "line.h"
#include "file.h"
#include "object3d.h"

CModel::CModel() : 
	m_pParent(), 
	m_scale(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),
	m_pTexture(nullptr)
{
}

CModel::~CModel()
{
}

void CModel::Load(std::string str, std::string path)
{
	if (m_model.count(str) != 0)
	{
		return;
	}

	SModelData model = {};
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

	std::string fileName = path;
	std::string ext = std::strrchr(fileName.c_str(), '.');

	if (ext == ".x")
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(&path.front(),
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&model.buffMat,
			NULL,
			&model.dwNum,
			&model.mesh);

		int nNumVtx;		//頂点数
		DWORD sizeFVF;		//頂点フォーマットのサイズ
		BYTE *pVtxBuff;		//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = model.mesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(model.mesh->GetFVF());

		//頂点バッファのロック
		model.mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int i = 0; i < nNumVtx; i++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//X
			if (vtx.x > model.maxModel.x)
			{
				model.maxModel.x = floorf(vtx.x);
			}

			if (vtx.x < model.minModel.x)
			{
				model.minModel.x = floorf(vtx.x);
			}

			//Y
			if (vtx.y > model.maxModel.y)
			{
				model.maxModel.y = floorf(vtx.y);
			}

			if (vtx.y < model.minModel.y)
			{
				model.minModel.y = floorf(vtx.y);
			}

			//Z
			if (vtx.z > model.maxModel.z)
			{
				model.maxModel.z = floorf(vtx.z);
			}

			if (vtx.z < model.minModel.z)
			{
				model.minModel.z = floorf(vtx.z);
			}
			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//モデルサイズ
		m_modelSize = D3DXVECTOR3(model.maxModel.x - model.minModel.x, model.maxModel.y - model.minModel.y, model.maxModel.z - model.minModel.z);

		//頂点バッファのアンロック
		model.mesh->UnlockVertexBuffer();
	}

#ifndef _DEBUG
	SetLines();
#endif // !_DEBUG

	if (m_model.count(str) == 0)
	{
		m_model.insert(std::make_pair(str, model));
	}
	else
	{
		m_model[str] = model;
	}
}

void CModel::Load(std::vector<std::string> data)
{
	if (m_model.count(data[0]) != 0)
	{
		return;
	}

	std::string ext = std::strrchr(data[1].c_str(), '.');

	if (ext == ".x")
	{
		Load_XFile(data);
	}

	else if (ext == ".fbx")
	{
		Load_FbxFile(data);
	}
}

void CModel::LoadAll()
{
	nlohmann::json list = CFile::LoadJsonStage(L"Data/FILE/model.json");

	int size = (int)list["MODEL"].size();

	std::string test = list["MODEL"][0][0];
	for (int i = 0; i < size; i++)
	{
		Load(list["MODEL"].at(i));
	}
}

void CModel::Load_XFile(std::vector<std::string> data)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	SModelData model = {};
	std::string path = data[1];

	model.minModel = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	model.maxModel = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	model.modelMode = "xFile";

	//Xファイルの読み込み
	D3DXLoadMeshFromX(&path.front(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&model.buffMat,
		NULL,
		&model.dwNum,
		&model.mesh);

	int nNumVtx;	// 頂点数保存用変数
	DWORD sizeFVF;	// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;	// 頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = model.mesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(model.mesh->GetFVF());

	//頂点バッファのロック
	model.mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int i = 0; i < nNumVtx; i++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X
		if (vtx.x > model.maxModel.x)
		{
			model.maxModel.x = floorf(vtx.x);
		}

		if (vtx.x < model.minModel.x)
		{
			model.minModel.x = floorf(vtx.x);
		}

		//Y
		if (vtx.y >model.maxModel.y)
		{
			model.maxModel.y = floorf(vtx.y);
		}

		if (vtx.y < model.minModel.y)
		{
			model.minModel.y = floorf(vtx.y);
		}

		//Z
		if (vtx.z > model.maxModel.z)
		{
			model.maxModel.z = floorf(vtx.z);
		}

		if (vtx.z < model.minModel.z)
		{
			model.minModel.z = floorf(vtx.z);
		}
		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	//モデルサイズ
	m_modelSize = D3DXVECTOR3(model.maxModel.x - model.minModel.x, model.maxModel.y - model.minModel.y, model.maxModel.z - model.minModel.z);

	//頂点バッファのアンロック
	model.mesh->UnlockVertexBuffer();

	if (m_model.count(data[0]) == 0)
	{
		m_model.insert(std::make_pair(data[0], model));
	}
	else
	{
		m_model[data[0]] = model;
	}
}

void CModel::Load_FbxFile(std::vector<std::string> data)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	SModelData model = {};
	std::string path = data[1];

	model.minModel = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	model.maxModel = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	model.modelMode = "fbxFile";

	//FbxManagerを生成
	FbxManager *pManager = FbxManager::Create();

	//IOSettingを生成
	FbxIOSettings *pSettings = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(pSettings);

	//Importerを生成
	FbxImporter *pImporter = FbxImporter::Create(pManager, "Importer");

	//シーンオブジェクトにFbxファイルの情報を流す
	FbxScene *pScene = FbxScene::Create(pManager, "Scene");

	if (pImporter->Initialize(path.c_str(), -1, pManager->GetIOSettings()) == false)
	{	//Fbxの読み込みに失敗した場合
		pManager->Destroy();
		return;
	}
	pImporter->Import(pScene);
	pImporter->Destroy();

	//シーンオブジェクトの解析
	FbxNode *pRootNode = pScene->GetRootNode();

	std::map<std::string, FbxNode*, std::less<>> meshnode;

	if (pRootNode)
	{
		//ポリゴンを三角形で再生成
		FbxGeometryConverter Converter(pManager);
		Converter.Triangulate(pScene, true);

		//ノードを探す処理
		FbxCollectMeshNode(pRootNode, meshnode);

		//モデルデータを取得する処理
		for (int i = 0; i < m_nodeStr.size(); i++)
		{
			ExtractionModelData(model, meshnode, m_nodeStr[i]);
		}

		//マテリアルを取得する処理
		ExtractionMaterial(pScene);
	}

	//FbxSceneの破棄
	pScene->Destroy();

	//FbxManagerの破棄
	pManager->Destroy();

	if (m_model.count(data[0]) == 0)
	{
		m_model.insert(std::make_pair(data[0], model));
	}
	else
	{
		m_model[data[0]] = model;
	}
}

void CModel::FbxCollectMeshNode(FbxNode* node, std::map<std::string, FbxNode*, std::less<>>& list)
{
	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
	{
		FbxNodeAttribute* attr = node->GetNodeAttributeByIndex(i);

		switch (attr->GetAttributeType())
		{
		case FbxNodeAttribute::eMesh:	//メッシュだった場合
			list[node->GetName()] = node;
			m_nodeStr.push_back(node->GetName());
			break;
		}
	}

	//子メッシュの再帰処理
	for (int i = 0; i < node->GetChildCount(); i++)
	{
		FbxCollectMeshNode(node->GetChild(i), list);
	}
}

void CModel::ExtractionModelData(SModelData& data, std::map<std::string, FbxNode*, std::less<>>& list, std::string str)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	FbxMesh* mesh = list[str]->GetMesh();

	//頂点バッファの取得
	FbxVector4* vtxbuff = mesh->GetControlPoints();

	//インデックスバッファの取得
	int* idx = mesh->GetPolygonVertices();

	//頂点数の取得
	int polygonVtxCount = mesh->GetPolygonVertexCount();

	//インデックスバッファ
	for (int i = 0; i < polygonVtxCount; i++)
	{
		m_indices[str].push_back(idx[i]);
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * polygonVtxCount,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return;
	}

	//インデックスバッファの生成
	if (FAILED(pDevice->CreateIndexBuffer(sizeof(UINT) * m_indices[str].size(),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL)))
	{
		return;
	}

	//頂点座標情報の宣言
	D3DVERTEXELEMENT9 VtxDecl[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	//メッシュの生成
	if (FAILED(D3DXCreateMesh((DWORD)polygonVtxCount,
		mesh->GetControlPointsCount(),
		D3DXMESH_SYSTEMMEM,
		VtxDecl,
		pDevice,
		&data.mesh)))
	{	//メッシュの生成に失敗した場合
		assert(false);
	}

	//インデックスバッファをロック
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int i = 0; i < polygonVtxCount; i++)
	{
		pIdx[i] = idx[i];
	}

	//頂点バッファをロック
	VERTEX_3D * pVtx = nullptr;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の取得
	for (int i = 0; i < mesh->GetControlPointsCount(); i++)
	{
		m_vertices[str].push_back(D3DXVECTOR3((float)vtxbuff[i][0],
			(float)vtxbuff[i][1],
			(float)vtxbuff[i][2]));
	}

	for (int i = 0; i < polygonVtxCount; i++)
	{
		pVtx[idx[i]].pos = m_vertices[str].at(idx[i]);
	}

	//法線情報の取得
	for (int i = 0; i < mesh->GetLayerCount(); i++)
	{
		FbxLayer* layer = mesh->GetLayer(i);
		FbxLayerElementNormal* normals = layer->GetNormals();

		if (normals == 0)	//法線が見つからなかった場合
			continue;

		//マッピングモードの取得
		FbxLayerElement::EMappingMode mappingMode;
		mappingMode = normals->GetMappingMode();

		//リファレンスモードの取得
		FbxLayerElement::EReferenceMode refMode;
		refMode = normals->GetReferenceMode();

		if (mappingMode == FbxLayerElement::eByPolygonVertex)
		{	//ポリゴン単位でデータが格納されている場合
			if (refMode == FbxLayerElement::eDirect)
			{
				for (int i = 0; i < normals->GetDirectArray().GetCount(); i++)
				{
					pVtx[idx[i]].nor = D3DXVECTOR3((float)normals->GetDirectArray().GetAt(idx[i])[0],
						(float)normals->GetDirectArray().GetAt(idx[i])[1], 
						(float)normals->GetDirectArray().GetAt(idx[i])[2]);
				}
			}
		}
		else if (mappingMode == FbxLayerElement::eByControlPoint)
		{	//頂点単位でデータが格納されている場合
			if (refMode == FbxLayerElement::eDirect)
			{
				for (int i = 0; i < normals->GetDirectArray().GetCount(); i++)
				{
					pVtx[idx[i]].nor = D3DXVECTOR3((float)normals->GetDirectArray().GetAt(idx[i])[0],
						(float)normals->GetDirectArray().GetAt(idx[i])[1],
						(float)normals->GetDirectArray().GetAt(idx[i])[2]);
				}
			}
		}
	}

	//頂点カラー情報の取得
	for (int i = 0; i < mesh->GetElementVertexColorCount(); i++)
	{
		FbxGeometryElementVertexColor* color = mesh->GetElementVertexColor(i);

		FbxGeometryElement::EMappingMode mappingMode;
		mappingMode = color->GetMappingMode();

		FbxGeometryElement::EReferenceMode refMode;
		refMode = color->GetReferenceMode();

		FbxLayerElementArrayTemplate<int>* colIdx = &color->GetIndexArray();

		if (mappingMode == FbxGeometryElement::eByPolygonVertex)
		{
			if (refMode == FbxGeometryElement::eIndexToDirect)
			{
				for (int j = 0; j < colIdx->GetCount(); j++)
				{
					pVtx[j].col = D3DXCOLOR((float)color->GetDirectArray().GetAt(colIdx->GetAt(idx[j]))[0],
						(float)color->GetDirectArray().GetAt(colIdx->GetAt(idx[j]))[1],
						(float)color->GetDirectArray().GetAt(colIdx->GetAt(idx[j]))[2],
						(float)color->GetDirectArray().GetAt(colIdx->GetAt(idx[j]))[3]);
				}
			}
		}
	}

	D3DXCreateBuffer((DWORD)mesh->GetPolygonCount(), &data.buffMat);
	data.dwNum = 1;
	data.vtxBuff = m_pVtxBuff;
	data.idxBuff = m_pIdxBuff;
	data.vtxCount = polygonVtxCount;
	data.primitiveCount = polygonVtxCount;

	int nNumVtx;	// 頂点数保存用変数
	DWORD sizeFVF;	// 頂点フォーマットのサイズ

	//頂点数の取得
	nNumVtx = data.mesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(data.mesh->GetFVF());

	for (int i = 0; i < nNumVtx; i++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = pVtx[pIdx[i]].pos;

		//X
		if (vtx.x > data.maxModel.x)
		{
			data.maxModel.x = floorf(vtx.x);
		}
		if (vtx.x < data.minModel.x)
		{
			data.minModel.x = floorf(vtx.x);
		}

		//Y
		if (vtx.y >data.maxModel.y)
		{
			data.maxModel.y = floorf(vtx.y);
		}
		if (vtx.y < data.minModel.y)
		{
			data.minModel.y = floorf(vtx.y);
		}

		//Z
		if (vtx.z > data.maxModel.z)
		{
			data.maxModel.z = floorf(vtx.z);
		}
		if (vtx.z < data.minModel.z)
		{
			data.minModel.z = floorf(vtx.z);
		}
	}

	//モデルサイズ
	m_modelSize = D3DXVECTOR3(data.maxModel.x - data.minModel.x, data.maxModel.y - data.minModel.y, data.maxModel.z - data.minModel.z);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();
}

void CModel::ExtractionMaterial(FbxScene* scene)
{
	std::vector<const char*> matName;
	D3DXMATERIAL d3dxmat = {};

	//マテリアル情報の取得
	for (int i = 0; i < scene->GetMaterialCount(); i++)
	{
		FbxSurfaceMaterial* pMat = scene->GetMaterial(i);
		matName.push_back(pMat->GetName());

		if (pMat->GetClassId().Is(FbxSurfaceLambert::ClassId))
		{	//ランバートマテリアルの場合
			FbxSurfaceLambert* pLambert = (FbxSurfaceLambert*)pMat;

			float alphaVal = (float)pLambert->TransparencyFactor.Get();				//透過度

			d3dxmat.MatD3D.Ambient = D3DXCOLOR((float)pLambert->Ambient.Get()[0],	//アンビエント
				(float)pLambert->Ambient.Get()[1],
				(float)pLambert->Ambient.Get()[2],
				alphaVal);

			d3dxmat.MatD3D.Diffuse = D3DXCOLOR((float)pLambert->Diffuse.Get()[0],	//ディフューズ
				(float)pLambert->Diffuse.Get()[1],
				(float)pLambert->Diffuse.Get()[2],
				alphaVal);

			d3dxmat.MatD3D.Emissive = D3DXCOLOR((float)pLambert->Emissive.Get()[0],	//エミッシブ
				(float)pLambert->Emissive.Get()[1],
				(float)pLambert->Emissive.Get()[2],
				alphaVal);
		}
		else if (pMat->GetClassId().Is(FbxSurfacePhong::ClassId))
		{	//フォンマテリアルの場合
			FbxSurfacePhong* pPhong = (FbxSurfacePhong*)pMat;

			d3dxmat.MatD3D.Specular = D3DXCOLOR((float)pPhong->Specular.Get()[0],	//スペキュラー
				(float)pPhong->Specular.Get()[1],
				(float)pPhong->Specular.Get()[2],
				(float)pPhong->TransparencyFactor.Get());

			d3dxmat.MatD3D.Power = (float)pPhong->SpecularFactor.Get();				//スペキュラーの減衰
		}
	}
}

void CModel::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		//テクスチャのポインタ
}

LPDIRECT3DVERTEXBUFFER9 CModel::GetVtxBuff(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].vtxBuff;
}

LPDIRECT3DINDEXBUFFER9 CModel::GetIdxBuff(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].idxBuff;
}

LPD3DXBUFFER CModel::GetBuffMat(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].buffMat;
}

LPD3DXMESH CModel::GetMesh(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].mesh;
}

DWORD CModel::GetModelNum(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].dwNum;
}

D3DXVECTOR3 CModel::GetMinModel(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return D3DXVECTOR3(0.0f,0.0f,0.0f);
	}

	return m_model[model].minModel;
}

D3DXVECTOR3 CModel::GetMaxModel(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	return m_model[model].maxModel;
}

std::string CModel::GetModelMode(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return "null";
	}

	return m_model[model].modelMode;
}

int CModel::GetVertexCount(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].vtxCount;
}

int CModel::GetPrimitiveCount(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].primitiveCount;
}
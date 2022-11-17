//============================
//
// ファイル設定
// Author:hamada ryuuga
// Author:Yuda Kaito
//
//============================
#include "file.h"
#include <fstream>

CFile::CFile()
{
}

CFile::~CFile()
{
}

//============================
// 読込み
//============================
nlohmann::json CFile::LoadJsonStage(const wchar_t* cUrl)
{
	std::ifstream ifs(cUrl);

	if (ifs)
	{
		nlohmann::json list;	// リストの作成

		ifs >> list;
		return list;
	}

	/* ↓ファイルを開くのを失敗した場合↓ */

	return nullptr;
}

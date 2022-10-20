#include "application.h"
#include "renderer.h"
#include "file.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <locale.h>
#include <algorithm>
#include <vector>
#include <assert.h>

using namespace std;
using namespace nlohmann;

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファイルのリストの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
json j;	//リストの生成

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファイルのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CFile::CFile()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファイルのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CFile::~CFile()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファイルの入力処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CFile::LoadJson(const char* FileName)
{
	string Path = "data/FILE/";
	const string pathToJSON = Path += FileName;
	ifstream ifs(pathToJSON);//開くやつ

	if (ifs)
	{//成功した場合

		ifs >> j;

		int idx = j["INDEX"];

		for (int i = 0; i < idx; i++)
		{
			string name = "ENEMY";
			string Number = std::to_string(i);
			name += Number;
		}
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ファイルの出力処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CFile::SaveJson(const char* FileName)
{
	//データの入れ方サンプル
	//j["DESTCOL"] = { { "R", DataEffect.color.destCol.r },{ "G" ,DataEffect.color.destCol.g } ,{ "B", DataEffect.color.destCol.b } ,{ "A", DataEffect.color.destCol.a } };
	//j["ENDTIME"] = DataEffect.color.nEndTime; 
	int nIndex = m_Max;
	for (int i = 0; i < nIndex; i++)
	{
		string name = "ENEMY";
		string Number = to_string(i);
		name += Number;

		j[name] =
		{
			{ "POS",{ { "X", 200.0f + (100.0f * i) },{ "Y", 100.0 },{ "Z", 0.0 } } }
		};

		j["INDEX"] = nIndex;
	}

	//出力するやつ
	auto jobj = j.dump();
	ofstream writing_file;
	string Path = "data/FILE/";
	const string pathToJSON = Path += FileName;
	writing_file.open(pathToJSON, ios::out);
	writing_file << jobj << endl;
	writing_file.close();
}

void CFile::LoadText(const char* Path)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//ファイルを開く
	ifstream file(Path);

	if (file.fail())
	{//ファイルを開けなかった場合
		printf("ファイルを開けません");
		return;
	}

	getline(file, m_str);

	file.close();
}
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

//����������������������������������������
//�t�@�C���̃��X�g�̐���
//����������������������������������������
json j;	//���X�g�̐���

//����������������������������������������
//�t�@�C���̃R���X�g���N�^
//����������������������������������������
CFile::CFile()
{
}

//����������������������������������������
//�t�@�C���̃f�X�g���N�^
//����������������������������������������
CFile::~CFile()
{
}

//����������������������������������������
//�t�@�C���̓��͏���
//����������������������������������������
void CFile::LoadJson(const char* FileName)
{
	string Path = "data/FILE/";
	const string pathToJSON = Path += FileName;
	ifstream ifs(pathToJSON);//�J�����

	if (ifs)
	{//���������ꍇ

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

//����������������������������������������
//�t�@�C���̏o�͏���
//����������������������������������������
void CFile::SaveJson(const char* FileName)
{
	//�f�[�^�̓�����T���v��
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

	//�o�͂�����
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

	//�t�@�C�����J��
	ifstream file(Path);

	if (file.fail())
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("�t�@�C�����J���܂���");
		return;
	}

	string filestr;

	while(!file.eof())
	{
		getline(file, filestr);
		m_str += filestr;
	}

	vector<int> Find;
	int nCntStr = 0;

	//����̕����̈ʒu�̐��l��ۑ�
	while (nCntStr < m_str.length())
	{
		if (m_str.substr(nCntStr, 3) == "pos")
		{
			Find.push_back(nCntStr);
		}
		nCntStr++;
	}

	//����̕����̏ꏊ������
	for (const auto &pos : Find)
	{
		string destStr = m_str.substr(pos, 3);

		if (destStr == "pos")
		{//�����ɓ��Ă͂܂����ꍇ

		}
	}

	file.close();
}
//============================
//
// �t�@�C���ݒ�
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
// �Ǎ���
//============================
nlohmann::json CFile::LoadJsonStage(const wchar_t* cUrl)
{
	std::ifstream ifs(cUrl);

	if (ifs)
	{
		nlohmann::json list;	// ���X�g�̍쐬

		ifs >> list;
		return list;
	}

	/* ���t�@�C�����J���̂����s�����ꍇ�� */

	return nullptr;
}

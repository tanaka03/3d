//
//File.h
//
#ifndef _FILE_H_
#define _FILE_H_

#include "nlohmann/json.hpp"

class CFile
{
public:
	CFile();
	~CFile();

	static nlohmann::json LoadJsonStage(const wchar_t* cUrl);
private:
};

#endif
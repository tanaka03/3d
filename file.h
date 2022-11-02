//
//File.h
//
#ifndef _FILE_H_
#define _FILE_H_

#include "enemy.h"

class CFile
{
public:
	CFile();
	~CFile();

	void LoadJson(const char* FileName);
	void SaveJson(const char* FileName);
	void LoadText(const char* Path);

private:
	static const int m_Max = 10;

	std::string m_str;
};

#endif
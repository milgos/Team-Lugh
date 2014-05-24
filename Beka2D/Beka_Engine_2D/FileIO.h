#pragma once

#include <Windows.h>
#include <string>

class CFileIO
{
public:
	CFileIO(void);
	~CFileIO(void);
	
	void Init(std::string _path);
	void SetSection(std::string _section );
	void SetKey(std::string _key );
	void	Write(int _val);
	int		Read();

private:
	std::string section;
	std::string key;
	std::string path;

	std::string temp;

	char arr[255];
	int val;
};


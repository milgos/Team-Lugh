#include "FileIO.h"
#include "Core.h"

CFileIO::CFileIO(void)
{
	val = 0;
}


CFileIO::~CFileIO(void)
{
}

void CFileIO::SetSection(std::string _section )
{
	section = _section ;
}

void CFileIO::SetKey(std::string _key)
{
	key = _key;
}

void CFileIO::Init( std::string _path ) 
{
	path = _path;
	section = "Deafault";
	key = "temp";
}
void CFileIO::Write(int _val = 99)
{
	temp = "";

	//section = "Option";
	//key = "MouseSense";
	temp += itoa(_val,arr,10);
	//path = "Data\\game_option.ini";
	WritePrivateProfileStringA(section.c_str() , key.c_str() , temp.c_str() , path.c_str() );
}

int CFileIO::Read()
{
	//section = "Option";
	//key = "MouseSense";
	int temp = 0 ;
	//path = "Data\\game_option.ini";
	temp = GetPrivateProfileIntA( section.c_str() , key.c_str() , -1 , path.c_str() );

	return temp;
}



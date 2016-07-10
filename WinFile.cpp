
#include <windows.h>
#include "WinFile.h"

WinFile::WinFile(string dir)
{
	currentFilePos=0;
	m_strDir=dir;
	if(!isFolder(dir))
		throw IOException("'"+dir+"'不是目录.");
	open(dir);
}
//读取
bool WinFile::open(string strFolder)//c:\win\sys sys
{
	bool isFind=false;
	string path,name;
    if ( strFolder.length()==0)
        return false; 
    HANDLE hFind = NULL;
    WIN32_FIND_DATA data;
	strFolder += "\\*";
    hFind = FindFirstFile(strFolder.c_str(),&data);
	if(hFind == INVALID_HANDLE_VALUE)
		return false;
    while ( hFind != INVALID_HANDLE_VALUE )//查找成功
    {
        if ( ( strcmp( data.cFileName, "." ) == 0 ) || (strcmp(data.cFileName, ".." ) == 0 ) )
        {
            if ( ! FindNextFile( hFind, &data ) )
                break;
            else
                continue;
        }
		isFind=true;
		name=data.cFileName;
	    fileNames.push_back(name);   
        if (!FindNextFile(hFind,&data ))
            break;        
    }    
    return isFind;
}
bool WinFile::isFolder(string name)
{
     WIN32_FIND_DATA  wfd;
     bool isFolder = false;
     HANDLE hFile=FindFirstFile(name.c_str(),&wfd);
     if ((hFile != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
     {
         isFolder=true;
     }
     FindClose(hFile);
     return isFolder;
}
bool WinFile::getNextFileName(string& name)
{
	if(currentFilePos>=fileNames.size())
		return false;
	name=fileNames[currentFilePos++];
	return name.length()>0;
}


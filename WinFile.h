#if !defined(WinFile_H_H)
#define WinFile_H_H

#include "File.h"
using namespace bluemeiIO;

#include <vector>

class WinFile:public File
{	
public:
	WinFile(string dir);
private:
	string m_strDir;
	vector<string> fileNames;
	int currentFilePos;
public:
	bool open(string strFolder);
	bool isFolder(string name);

	bool getNextFileName(string& name);
};

#endif 

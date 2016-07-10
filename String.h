#ifndef _String_h_ 
#define _String_h_ 

#include <string>  
using namespace std;

#define CP_GBK 950

class String:public string
{
public:
	String(const char *s=""):string(s){};
public:
	static int bytesToInt(char *buf,int sizeOfInt);
	static void intToBytes(char buf[],int value);
	//static char* SocketTools::gbkToUtf8(char *strGBK);
	static int gbkToUtf8(string& strUtf8,char *strGBK);
	static int utf8ToGbk(string& strGbk,char* strUtf8);
	static void utf8ToGbk(string& szstr); 
	static int gbkToUnicode(wstring& strUnicode,char *strGBK);
	static int gb2312ToUnicode(wstring& result,char *strGb2312);
	static void urlDecode(const char* str,string& szResault);

	void replaceString(const string & strSrc, const string &strDst);
	bool replaceString(const string & strStart, const string &strStop,const string &strDst);
	void trim();
	bool endOf(const char *s);
};
#endif
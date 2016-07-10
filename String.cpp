
#include <stdio.h>
#include <winsock2.h>

#include "String.h"

//字节数组转换为整型
int String::bytesToInt(char *buf,int sizeOfInt)
{
	int value=0;
	for(int i=0;i<sizeOfInt;i++)
	{
		value+=(buf[i] & 0xff)<<8*i;
	}
	return value;
}
//整型转换为字节数组
void String::intToBytes(char buf[],int value)
{
	for(int i=0;i<sizeof(value);i++)
	{
		buf[i]=(value>>i*8) & 0xff;
	}
}
//gbk转换unicode
int String::gbkToUnicode(wstring& strUnicode,char *strGBK)
{
	//MultiByteToWideChar gb2312转换为unicode
	int len;
	wchar_t *pUnicode;	
	if (!strGBK)
	{
		return NULL;
	}
	len =::MultiByteToWideChar(CP_GBK,0,strGBK,-1,NULL,0);
	if (len <1)
	{
		return 0;
	}
	pUnicode = (wchar_t *) malloc(sizeof(wchar_t) * len);
	if (!pUnicode)
	{
		return 0;
	}
	len = ::MultiByteToWideChar(CP_GBK, 0, strGBK, -1, pUnicode, len);
	if (len<1)
	{
		free(pUnicode);
		return 0;
	}
	//*
	char *strUTF8;
	len = ::WideCharToMultiByte(CP_UTF8, 0, pUnicode, -1, NULL, 0, NULL, NULL);
	if (len<1)
	{
		free(pUnicode);
		return 0;
	}
	strUTF8 = (char *) malloc(sizeof(char) * len);
	if (!strUTF8)
	{
		free(pUnicode);
		return 0;
	}
	len = ::WideCharToMultiByte (CP_UTF8, 0, pUnicode, -1, strUTF8, len, NULL,NULL);
	free(pUnicode);
	if (len<1)
	{
		free(strUTF8);
		return 0;
	}//*/
	//strUnicode=pUnicode;
	strUnicode=(wchar_t *)strUTF8;
	free(pUnicode);
	return len;	
}
//gb2312转换unicode --有问题!
int String::gb2312ToUnicode(wstring& result,char *strGb2312)   
{   
	int n = MultiByteToWideChar( CP_ACP, 0, strGb2312, -1, NULL, 0 );   
	result.resize(n);   
	::MultiByteToWideChar( CP_ACP, 0, strGb2312, -1, (LPWSTR)result.c_str(), result.length());
	return n;
}  
//gbk转换为utf-8
int String::gbkToUtf8(string& strUtf8,char *strGBK)
{	
	int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr)
		delete[] wstr;
	strUtf8=string(str,len);
	delete[]str;
	return len;
}  
//utf8转换为gbk编码
int String::utf8ToGbk(string& strGbk,char* strUtf8)
{
    int len=MultiByteToWideChar(CP_UTF8, 0, strUtf8, -1, NULL,0);
    unsigned short * wszGBK = new unsigned short[len+1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, strUtf8, -1, wszGBK, len); 
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL); 
    char *szGBK=new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte (CP_ACP, 0, wszGBK, -1, szGBK, len, NULL,NULL); 
    strGbk = szGBK;
    delete[] szGBK;
    delete[] wszGBK;
	return len;
}
void String::utf8ToGbk(string& szstr)      
{      
    WCHAR* strSrc;      
    TCHAR* szRes;       
    int i = MultiByteToWideChar(CP_UTF8, 0, szstr.c_str(), -1, NULL, 0);      
    strSrc = new WCHAR[i + 1];      
    MultiByteToWideChar(CP_UTF8, 0, szstr.c_str(), -1, strSrc, i);      
    i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);      
    szRes = new TCHAR[i + 1];      
    WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);       
    szstr = szRes;
	delete[]strSrc;
	delete[]szRes;       

} 
//URL解码
void String::urlDecode(const char* str,string& szResault)
{
	unsigned short tmp=0;
    char ch, hex[2] = "";       
    int n = 0;
	szResault="";
    while (ch = *(str + n))       
    {       
        if (ch == '%')      
        {      
            hex[0] = *(str + n + 1);      
            hex[1] = *(str + n + 2);       
            sscanf(hex, "%x", &tmp);      
            szResault += tmp;
			n = n + 3;
			continue ;
        }
		else if(ch=='-'||ch=='-'||ch=='.'||ch=='!'||ch=='~'||ch=='*'||ch=='\''||ch=='('||ch==')')
		{
			szResault+=ch;
		}
		else if(ch=='+')
		{
			szResault+=" ";
		}
		else if(ch>='0'&&ch<='9')
		{
			szResault+=ch;
		}
		else if(ch>='A'&&ch<='z')
		{
			szResault+=ch;
		}
        n ++;       
    }
	//utf8ToGbk(szResault);
}
  
//替换字符串:将strToReplace里面的strSrc字串替换成strDst
void String::replaceString(const string& strSrc, const string& strDst)
{ 
	string::size_type pos=0; 
	string::size_type srcLen=strSrc.size(); 
	string::size_type dstLen=strDst.size();
	while( (pos=this->find(strSrc, pos)) != string::npos)
	{  
		this->replace(pos, srcLen, strDst);  
		pos += dstLen;
	}
} 
//替换字符串:将strToReplace里面的strStart到strStop字串替换成strDst
bool String::replaceString(const string & strStart, const string &strStop,const string &strDst)
{
	int start=find(strStart);
	int stop=find(strStop);
	if(start>=0 && stop>start)
	{
		replace(start,stop-start+strStop.size(),strDst);
		return true;
	}
	return false;
}
//替换首尾空格
void String::trim()
{
	int pos;
	while( (pos=this->find(" "))==0 || pos==this->length()-1 )
	{
		if(this->length()==0)
			break;
		this->erase(pos,1);
	}
}
//是否以s结束
bool String::endOf(const char *s)
{
	int pos=this->find_last_of(s)-1;
	int len=strlen(s);
	return (pos+len==this->length());
}

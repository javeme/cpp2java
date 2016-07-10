


public class String:public String
{

public String(const char s=""):String(s){};

//public static int bytesToInt(char buf,int sizeOfInt);
//public static void intToBytes(char buf[],int value);
//static char SocketToolsgbkToUtf8(char strGBK);
//public static int gbkToUtf8(String strUtf8,char strGBK);
//public static int utf8ToGbk(String strGbk,char strUtf8);
//public static void utf8ToGbk(String szstr); 
//public static int gbkToUnicode(wString strUnicode,char strGBK);
//public static int gb2312ToUnicode(wString result,char strGb2312);
//public static void urlDecode(const char str,String szResault);

//public void replaceString(const String  strSrc, const String strDst);
//public boolean replaceString(const String  strStart, const String strStop,const String strDst);
//public void trim();
//public boolean endOf(const char s);




//字节数组转换为整型
int bytesToInt(char buf,int sizeOfInt)
{
int value=0;
for(int i=0;i<sizeOfInt;i++)
{
value+=(buf[i]  0xff)<<8i;
}
return value;
}
//整型转换为字节数组
void intToBytes(char buf[],int value)
{
for(int i=0;i<sizeof(value);i++)
{
buf[i]=(value>>i8)  0xff;
}
}
//gbk转换unicode
int gbkToUnicode(wString strUnicode,char strGBK)
{
//MultiByteToWideChar gb2312转换为unicode
int len;
wchar_t pUnicode;
if (!strGBK)
{
return null;
}
len =MultiByteToWideChar(CP_GBK,0,strGBK,-1,null,0);
if (len <1)
{
return 0;
}
pUnicode = (wchar_t ) malloc(sizeof(wchar_t)  len);
if (!pUnicode)
{
return 0;
}
len = MultiByteToWideChar(CP_GBK, 0, strGBK, -1, pUnicode, len);
if (len<1)
{
free(pUnicode);
return 0;
}
//
char strUTF8;
len = WideCharToMultiByte(CP_UTF8, 0, pUnicode, -1, null, 0, null, null);
if (len<1)
{
free(pUnicode);
return 0;
}
strUTF8 = (char ) malloc(sizeof(char)  len);
if (!strUTF8)
{
free(pUnicode);
return 0;
}
len = WideCharToMultiByte (CP_UTF8, 0, pUnicode, -1, strUTF8, len, null,null);
free(pUnicode);
if (len<1)
{
free(strUTF8);
return 0;
}///
//strUnicode=pUnicode;
strUnicode=(wchar_t )strUTF8;
free(pUnicode);
return len;
}
//gb2312转换unicode --有问题!
int gb2312ToUnicode(wString result,char strGb2312)   
{   
int n = MultiByteToWideChar( CP_ACP, 0, strGb2312, -1, null, 0 );   
result.resize(n);   
MultiByteToWideChar( CP_ACP, 0, strGb2312, -1, (LPWSTR)result.c_str(), result.length());
return n;
}  
//gbk转换为utf-8
int gbkToUtf8(String strUtf8,char strGBK)
{
int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, null, 0);
wchar_t wstr = new wchar_t[len+1];
memset(wstr, 0, len+1);
MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, null, 0, null, null);
char str = new char[len+1];
memset(str, 0, len+1);
WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, null, null);
if(wstr)
//delete[] wstr;
strUtf8=String(str,len);
//delete[]str;
return len;
}  
//utf8转换为gbk编码
int utf8ToGbk(String strGbk,char strUtf8)
{
int len=MultiByteToWideChar(CP_UTF8, 0, strUtf8, -1, null,0);
short  wszGBK = new  short[len+1];
memset(wszGBK, 0, len  2 + 2);
MultiByteToWideChar(CP_UTF8, 0, strUtf8, -1, wszGBK, len); 
len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, null, 0, null, null); 
char szGBK=new char[len + 1];
memset(szGBK, 0, len + 1);
WideCharToMultiByte (CP_ACP, 0, wszGBK, -1, szGBK, len, null,null); 
strGbk = szGBK;
//delete[] szGBK;
//delete[] wszGBK;
return len;
}
void utf8ToGbk(String szstr)      
{      
WCHAR strSrc;      
TCHAR szRes;       
int i = MultiByteToWideChar(CP_UTF8, 0, szstr.c_str(), -1, null, 0);      
strSrc = new WCHAR[i + 1];      
MultiByteToWideChar(CP_UTF8, 0, szstr.c_str(), -1, strSrc, i);      
i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, null, 0, null, null);      
szRes = new TCHAR[i + 1];      
WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, null, null);       
szstr = szRes;
//delete[]strSrc;
//delete[]szRes;       

} 
//URL解码
void urlDecode(const char str,String szResault)
{
short tmp=0;
char ch, hex[2] = "";       
int n = 0;
szResault="";
while (ch = (str + n))       
{       
if (ch == '%')      
{      
hex[0] = (str + n + 1);      
hex[1] = (str + n + 2);       
sscanf(hex, "%x", tmp);      
szResault += tmp;
n = n + 3;
continue ;
}
else if(ch=='-'||ch=='-'||ch=='.'||ch=='!'||ch=='~'||ch==''||ch=='\''||ch=='('||ch==')')
{
szResault+=ch;
}
else if(ch=='+')
{
szResault+=" ";
}
else if(ch>='0'ch<='9')
{
szResault+=ch;
}
else if(ch>='A'ch<='z')
{
szResault+=ch;
}
n ++;       
}
//utf8ToGbk(szResault);
}

//替换字符串:将strToReplace里面的strSrc字串替换成strDst
void replaceString(const String strSrc, const String strDst)
{ 
Stringsize_type pos=0; 
Stringsize_type srcLen=strSrc.size(); 
Stringsize_type dstLen=strDst.size();
while( (pos=this.find(strSrc, pos)) != Stringnpos)
{  
this.replace(pos, srcLen, strDst);  
pos += dstLen;
}
} 
//替换字符串:将strToReplace里面的strStart到strStop字串替换成strDst
boolean replaceString(const String  strStart, const String strStop,const String strDst)
{
int start=find(strStart);
int stop=find(strStop);
if(start>=0  stop>start)
{
replace(start,stop-start+strStop.size(),strDst);
return true;
}
return false;
}
//替换首尾空格
void trim()
{
int pos;
while( (pos=this.find(" "))==0 || pos==this.length()-1 )
{
if(this.length()==0)
break;
this.erase(pos,1);
}
}
//是否以s结束
boolean endOf(const char s)
{
int pos=this.find_last_of(s)-1;
int len=strlen(s);
return (pos+len==this.length());
}
}



public class WinFile:public File
{

//public WinFile(String dir);

private String m_strDir;
private ArrayList<String> fileNames;
private int currentFilePos;

//public boolean open(String strFolder);
//public boolean isFolder(String name);

//public boolean getNextFileName(String name);




WinFile(String dir)
{
currentFilePos=0;
m_strDir=dir;
if(!isFolder(dir))
throw IOException("'"+dir+"'不是目录.");
open(dir);
}
//读取
boolean open(String strFolder)//c:\win\sys sys
{
boolean isFind=false;
String path,name;
if ( strFolder.length()==0)
return false; 
HANDLE hFind = null;
WIN32_FIND_DATA data;
strFolder += "\\";
hFind = FindFirstFile(strFolder.c_str(),data);
if(hFind == INVALID_HANDLE_VALUE)
return false;
while ( hFind != INVALID_HANDLE_VALUE )//查找成功
{
if ( ( strcmp( data.cFileName, "." ) == 0 ) || (strcmp(data.cFileName, ".." ) == 0 ) )
{
if ( ! FindNextFile( hFind, data ) )
break;
else
continue;
}
isFind=true;
name=data.cFileName;
fileNames.push_back(name);   
if (!FindNextFile(hFind,data ))
break;        
}    
return isFind;
}
boolean isFolder(String name)
{
WIN32_FIND_DATA  wfd;
boolean isFolder = false;
HANDLE hFile=FindFirstFile(name.c_str(),wfd);
if ((hFile != INVALID_HANDLE_VALUE)  (wfd.dwFileAttributes  FILE_ATTRIBUTE_DIRECTORY))
{
isFolder=true;
}
FindClose(hFile);
return isFolder;
}
boolean getNextFileName(String name)
{
if(currentFilePos>=fileNames.size())
return false;
name=fileNames[currentFilePos++];
return name.length()>0;
}

}
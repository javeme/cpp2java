
#include "File.h"
using namespace bluemeiIO;

#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

File::File(unsigned long bufferSize)
{
	init("","",bufferSize);
}
/*
File::File(string path,string openMode)
{
	this->File::File(path,openMode,BUFFER_SIZE);
}
*/
File::File(string path,string openMode,unsigned long bufferSize)
{
	init(path,openMode,bufferSize);
}
File::~File()
{
	close();
	delete[]buffer;
}
void File::init(string path,string openMode,unsigned long bufferSize)
{
	m_bCloseAble=false;
	m_pFile=NULL;
	m_nBufferSize=bufferSize;
	m_nUsedBufLength=0;
	buffer=new char[m_nBufferSize];
	if(path!="")
	{
		openFile(path,openMode);
	}
}
void File::openFile(string& path,string openMode)
{
	//path="./root/"+path;
	if(path=="")
		throw IOException("文件名为空.");
	if(m_pFile!=NULL)
		close();
	m_strPath=path;
	m_pFile=fopen(path.c_str(),openMode.c_str());
	if(m_pFile==NULL)
	{
		int pos=path.find_last_of("/");
		if(pos<0)
			pos=path.find_last_of("\\");
		if(pos>0)
		{
			string folder=path;
			folder.replace(pos,path.length()-pos,"");
			if(mkdir(folder.c_str())==0)
				m_pFile=fopen(path.c_str(),openMode.c_str());
		}
	}
	if(m_pFile==NULL)
		throw IOException("'"+path+"'文件打开失败.");
	m_bCloseAble=true;
}
void File::writeBytes(const char buf[],unsigned long length)
{
	if(m_nUsedBufLength<0)
	{
		throw IOException("写入文件异常.");
	}
	for(int i=0;i<length;i++)
	{
		buffer[m_nUsedBufLength++]=buf[i];
		if(m_nUsedBufLength >= m_nBufferSize)
			this->flush();
	}
}
void File::writeLine(string value)
{
	value.append("\n");
	writeBytes( (char*)value.c_str(), strlen(value.c_str()) );
}
void File::writeInt(int value)
{
	char buf[sizeof(int)];
	for(int i=0;i<sizeof(value);i++)
	{
		buf[i]=(value>>i*8) & 0xff;
	}
	writeBytes(buf,sizeof(int));
}

int File::readBytes(char buf[],unsigned long length)
{
	unsigned int nReturn=::fread(buf,sizeof(char),length,m_pFile);
	if(nReturn!=0 && nReturn!=length)
	{
		close();
		throw IOException("文件读取出错.");
	}
	return nReturn;
}
int File::readLine(string& line)
{
	int readedLen=0,tmp;
	char buf[BUFFER_SIZE]="a";
	do
	{
		tmp=readBytes(&buf[readedLen],1);
		if(tmp>0)
			readedLen+=tmp;
		if(readedLen>BUFFER_SIZE)
			throw IOException("缓冲已满.");
	}while(tmp>0 && buf[readedLen-1]!='\0' && buf[readedLen-1]!='\n');
	line=string(buf,readedLen);
	return readedLen;
}
int File::readInt()
{
	int value=0;
	char buf[sizeof(int)];
	this->readBytes(buf,sizeof(int));
	for(int i=0;i<sizeof(int);i++)
	{
		value+=(buf[i] & 0xff)<<8*i;
	}
	return value;
}
long File::getSize()
{
	long current=ftell(m_pFile);
	fseek(m_pFile,0,SEEK_END); 
	long length=ftell(m_pFile);
	//rewind(m_pFile);//重定位到开头
	fseek(m_pFile,current,SEEK_SET); 
	return length;
}
int File::readAll(char buf[],unsigned long bufSize)
{
	if(bufSize<getSize())
	{
		return -1;
	}
	return this->readBytes(buf,getSize());
}
void File::seek(unsigned long offset)
{
	::fseek(m_pFile,offset,SEEK_SET);
}
unsigned int File::write(char* buffer,unsigned int length)
{
	return ::fwrite(buffer,sizeof(char),length,m_pFile);
}
void File::flush()
{
	if(m_nUsedBufLength==0)
		return;
	unsigned int nReturn=::fwrite(buffer,sizeof(char),m_nUsedBufLength,m_pFile);
	if(nReturn!=m_nUsedBufLength)
	{
		throw IOException("写入文件'"+m_strPath+"'出错.");
	}
	m_nUsedBufLength=0;
}
void File::close()
{
	if(!m_bCloseAble)
		return;
	flush();
	if(::fclose(this->m_pFile))
		throw IOException("关闭文件'"+m_strPath+"'出错.");
	m_bCloseAble=false;
	m_pFile=NULL;	
}

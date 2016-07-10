#ifndef File_H_H
#define File_H_H


#include <iostream>
#include <string>
using namespace std;

#include "IOException.h"
using namespace bluemeiException;

namespace bluemeiIO
{
    #define BUFFER_SIZE 1024

	class File
	{
	public:
		File(unsigned long bufferSize);
		//File(string path,string openMode);
		File(string path="",string openMode="rb+",unsigned long bufferSize=BUFFER_SIZE);
		~File();
	private:
		void init(string path,string openMode,unsigned long bufferSize);
	public:
		void openFile(string& path,string openMode);

		virtual void writeBytes(const char buf[],unsigned long length);
		virtual void writeLine(string value);
		virtual void writeInt(int value);
		unsigned int write(char* buffer,unsigned intlength);//Ô­Ê¼º¯Êý

		virtual int readBytes(char buf[],unsigned long length);
		virtual int readLine(string& line);
		virtual int readInt();
		virtual long getSize();
		virtual int readAll(char buf[],unsigned long bufSize);
		
		virtual void seek(unsigned long offset);
		virtual void flush();
		virtual void close();
	private:
		FILE *m_pFile;
		string m_strPath;
		unsigned long m_nBufferSize,m_nUsedBufLength;
		char *buffer;
		bool m_bCloseAble;
	};
}
#endif
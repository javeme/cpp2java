#ifndef Exception_H_H
#define Exception_H_H

#include <iostream>
#include <string>
using namespace std;

namespace bluemeiException
{
	class Exception
	{
	public:
		Exception();
		Exception(string msg);
	public:
		virtual void setExceptionMsg(string msg);
		virtual void printException();
		virtual string toString();
	protected:
		string m_strLastError;
	};
}
#endif
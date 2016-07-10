#include "Exception.h"
using namespace bluemeiException; 

Exception::Exception()
{
	;
}
Exception::Exception(string msg)
{
	m_strLastError=msg;
}
void Exception::setExceptionMsg(string msg)
{
	m_strLastError=msg;
}
void Exception::printException()
{
	cout<<"Òì³£:"<<m_strLastError<<endl;
}
string Exception::toString()
{
	return this->m_strLastError;
}

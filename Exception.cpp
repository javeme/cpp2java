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
	cout<<"�쳣:"<<m_strLastError<<endl;
}
string Exception::toString()
{
	return this->m_strLastError;
}

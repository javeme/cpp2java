#include "IOException.h"
using namespace bluemeiException;

IOException::IOException()
{
	;
}
IOException::IOException(string msg)
{
	this->setExceptionMsg(msg);
}

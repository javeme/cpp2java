#ifndef IOException_H_H
#define IOException_H_H

#include "Exception.h"
using namespace bluemeiException;

namespace bluemeiException
{
	class IOException:public Exception
	{
	public:
		IOException();
		IOException(string msg);
	};
}
#endif
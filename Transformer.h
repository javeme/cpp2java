#ifndef _Transformer_h_ 
#define _Transformer_h_

#include "String.h" 

class Transformer
{
public:
	void transformDirect(String dir);
private:
	long transform(String& name,const String& dir);
};

#endif
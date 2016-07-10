#include <iostream>
using namespace std;

#include "Exception.h"
using namespace bluemeiException;

#include "String.h"
#include "Transformer.h"


class MainClass
{
public:
	void start();
};

void MainClass::start()
{
	char buffer[100];
	String dir;
	cout<<"请输入要文件的目录，输入'.'为当前目录:"<<endl;			
	scanf("%s",buffer);
	dir=String(buffer);
	if(dir.length()==0 || dir==".")
	{
		dir=".";
	}
	Transformer tf;
	tf.transformDirect(dir);
}

int main()
{
	MainClass app;
	try{
		app.start();
	}catch(Exception e)
	{
		e.printException();
	}
	return 0;
}

#include "Transformer.h"

#include "File.h"
using namespace bluemeiIO;
#include "WinFile.h"

#include "Time.h"
#include "windows.h" 
//long GetCurrentDirectory(long nBufferLength,char* lpBuffer); 

void Transformer::transformDirect(String dir)
{
	String name;
	long costTime=0;
	if(dir==".")
	{
		char buffer[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,buffer);
		dir=buffer;
	}
	WinFile reader(dir);
	cout<<"即将开始转换目录["<<dir<<"]下源文件,请稍后..."<<endl;
	while(reader.getNextFileName(name))
	{
		costTime+=transform(name,dir);
	}
	char time[20]; 
	sprintf(time,"%d小时%d分%d秒",costTime/60/60,costTime/60%60,costTime%60);
	cout<<endl<<"-------------------转换完毕(耗时:"<<time<<")-------------------"<<endl<<endl;//*/	
}
long Transformer::transform(String& name,const String& dir)
{
	String line,strTransformed,className;
	int i,tmp;
	bool bTranCpp=false,bExistNamespace=false,bToDeleteParentheses=false;
	bool bAppendPublic=false,bAppendPrivate=false,bAppendProtected=false;	
	//name="WinFile.h";
	name.trim();
	if(!name.endOf(".h"))
		return 0;
	File file(dir+"\\"+name);	
	className=name;
	className.replaceString(".h", "");
	cout<<"即将转换:"<<className<<endl;
	float percent,length=0;
	long total=file.getSize();
	time_t oldTime,currentTime,costTime; 
	time(&oldTime); 
	while((tmp=file.readLine(line))>0)
	{
		length+=tmp;//加上换行符?
		//cout<<"正在转换: (done:"<<percent<<"%)"<<endl<<line<<" in "<<name<<endl;
		printf("\r");
		cout<<"正在转换: "<<name<<" (done:"<<percent<<"%)";

		line.replaceString("#", "\n", "");
		line.replaceString("using", "\n", "");
		line.replaceString("#endif", "");
		line.replaceString("\t", "");
		
		line.trim();
		line.replaceString(className+"::","");
		line.replaceString("::","");
		line.replaceString("->",".");

		line.replaceString("class","public class");
		line.replaceString("unsigned","");
		line.replaceString("NULL","null");
		line.replaceString("&","");
		line.replaceString("bool","boolean");
		line.replaceString("struct","class");

		line.replaceString("delete","//delete");
		line.replaceString("*p","p");
		line.replaceString("*m_p","m_p");
		line.replaceString("string","String");
		line.replaceString("vector","ArrayList");
		line.replaceString("*","");
		line.replaceString("printf(","System.out.print(String.format(");

		//删除Namespace
		if(bToDeleteParentheses)
		{
			tmp=line.find("{");
			if(tmp>=0)
				line.erase(tmp,1);
		}
		bToDeleteParentheses=false;
		if(!bExistNamespace)
		{
			bExistNamespace=line.replaceString("namespace", "\n", "");
			bToDeleteParentheses=bExistNamespace;
		}
		//添加 public private protected						
		if((tmp=line.find("public:"))>=0)
		{
			bAppendPublic=bAppendPrivate=bAppendProtected=false;
			bAppendPublic=true;
			line.erase(tmp,strlen("public:"));
		}
		else if((tmp=line.find("private:"))>=0)
		{
			bAppendPublic=bAppendPrivate=bAppendProtected=false;
			bAppendPrivate=true;
			line.erase(tmp,strlen("private:"));
		}
		else if((tmp=line.find("protected:"))>=0)
		{
			bAppendPublic=bAppendPrivate=bAppendProtected=false;
			bAppendProtected=true;
			line.erase(tmp,strlen("protected:"));
		}
		line.trim();
		tmp=line.length();
		if(!bTranCpp && tmp>5)//int a;
		{
			tmp=line.find("//");
			if(tmp!=0)
			{
				if(bAppendPublic)
					line.insert(0,"public ");
				else if(bAppendPrivate)
					line.insert(0,"private ");
				else if(bAppendProtected)
					line.insert(0,"protected ");
			}
		}		
		//注释掉方法声明
		tmp=line.rfind(");",line.length());
		if(!bTranCpp && tmp>0)
		{
			tmp=line.find("//");
			if(tmp!=0)
				line.insert(0,"//");
		}

		strTransformed.append(line);
		percent=100*length/total;
		//转换cpp
		if(percent==100 && !bTranCpp)
		{			
			file.close();
			
			bTranCpp=true;
			//去除namespace 存在
			if(bExistNamespace)
			{
				tmp=strTransformed.find_last_of('}');
				if(tmp>0)
					strTransformed.erase(tmp,1);
			}
			tmp=strTransformed.rfind("};", strTransformed.length());
			if(tmp>0)
			{
				strTransformed.erase(tmp,strlen("};"));
			}
			//打开cpp文件
			name.replaceString(".h",".cpp");
			try
			{
				file.openFile(dir+"\\"+name, "r");//file=File(dir+"\\"+name)为何出错?
				length=0;
				total=file.getSize();
			}catch(Exception e)
			{
				e.printException();
				break;
			}
		}
	}
	strTransformed.append("}");
	printf("\r");
	for(i=0; i<50;i++)
		printf(" ");
	printf("\r");
	cout<<"转换完成: (done:"<<percent<<"%)"<<endl;
	cout<<"正在保存..."<<endl;
	className+=".java";
	File fileSave(dir+"\\java\\"+className,"w+");
	fileSave.writeBytes(strTransformed.c_str(),strTransformed.length());
	time(&currentTime);
	costTime=currentTime-oldTime;
	//difftime(currentTime,oldTime)
	return costTime;
}


public class Transformer
{

//public void transformDirect(String dir);

//private long transform(String name,const String dir);




//long GetCurrentDirectory(long nBufferLength,char lpBuffer); 

void transformDirect(String dir)
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
sSystem.out.print(String.format(time,"%d小时%d分%d秒",costTime/60/60,costTime/60%60,costTime%60);
cout<<endl<<"-------------------转换完毕(耗时:"<<time<<")-------------------"<<endl<<endl;///
}
long transform(String name,const String dir)
{
String line,strTransformed,public className;
int i,tmp;
boolean bTranCpp=false,bExistNamespace=false,bToDeleteParentheses=false;
boolean bAppendPublic=false,bAppendPrivate=false,bAppendProtected=false;
//name="WinFile.h";
name.trim();
if(!name.endOf(".h"))
return 0;
File file(dir+"\\"+name);
public className=name;
public className.replaceString(".h", "");
cout<<"即将转换:"<<public className<<endl;
float percent,length=0;
long total=file.getSize();
time_t oldTime,currentTime,costTime; 
time(oldTime); 
while((tmp=file.readLine(line))>0)
{
length+=tmp;//加上换行符?
//cout<<"正在转换: (done:"<<percent<<"%)"<<endl<<line<<" in "<<name<<endl;
System.out.print(String.format("\r");
cout<<"正在转换: "<<name<<" (done:"<<percent<<"%)";

line.replaceString("line.replaceString("line.replaceString("line.replaceString("\t", "");

line.trim();
line.replaceString(public className+"","");
line.replaceString("","");
line.replaceString(".",".");

line.replaceString("public class","public public class");
line.replaceString("","");
line.replaceString("null","null");
line.replaceString("","");
line.replaceString("boolean","booleanean");
line.replaceString("class","public class");

line.replaceString("//delete","////delete");
line.replaceString("p","p");
line.replaceString("m_p","m_p");
line.replaceString("String","String");
line.replaceString("ArrayList","ArrayList");
line.replaceString("","");
line.replaceString("System.out.print(String.format(","System.out.print(String.format(");

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
bExistNamespace=line.replaceString("bToDeleteParentheses=bExistNamespace;
}
//添加 public private protected
if((tmp=line.find(""))>=0)
{
bAppendPublic=bAppendPrivate=bAppendProtected=false;
bAppendPublic=true;
line.erase(tmp,strlen(""));
}
else if((tmp=line.find(""))>=0)
{
bAppendPublic=bAppendPrivate=bAppendProtected=false;
bAppendPrivate=true;
line.erase(tmp,strlen(""));
}
else if((tmp=line.find(""))>=0)
{
bAppendPublic=bAppendPrivate=bAppendProtected=false;
bAppendProtected=true;
line.erase(tmp,strlen(""));
}
line.trim();
tmp=line.length();
if(!bTranCpp  tmp>5)//int a;
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
if(!bTranCpp  tmp>0)
{
tmp=line.find("//");
if(tmp!=0)
line.insert(0,"//");
}

strTransformed.append(line);
percent=100length/total;
//转换cpp
if(percent==100  !bTranCpp)
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
System.out.print(String.format("\r");
for(i=0; i<50;i++)
System.out.print(String.format(" ");
System.out.print(String.format("\r");
cout<<"转换完成: (done:"<<percent<<"%)"<<endl;
cout<<"正在保存..."<<endl;
public className+=".java";
File fileSave(dir+"\\java\\"+public className,"w+");
fileSave.writeBytes(strTransformed.c_str(),strTransformed.length());
time(currentTime);
costTime=currentTime-oldTime;
//difftime(currentTime,oldTime)
return costTime;
}}
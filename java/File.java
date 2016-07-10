





public class File
{

//public File( long bufferSize);
//File(String path,String openMode);
//public File(String path="",String openMode="rb+", long bufferSize=BUFFER_SIZE);
//public ~File();

//private void init(String path,String openMode, long bufferSize);

//public void openFile(String path,String openMode);

//public virtual void writeBytes(const char buf[], long length);
//public virtual void writeLine(String value);
//public virtual void writeInt(int value);
//public int write(char buffer, intlength);//原始函数

//public virtual int readBytes(char buf[], long length);
//public virtual int readLine(String line);
//public virtual int readInt();
//public virtual long getSize();
//public virtual int readAll(char buf[], long bufSize);

//public virtual void seek( long offset);
//public virtual void flush();
//public virtual void close();

private FILE m_pFile;
private String m_strPath;
private long m_nBufferSize,m_nUsedBufLength;
private char buffer;
private boolean m_bCloseAble;





File( long bufferSize)
{
init("","",bufferSize);
}
/
File(String path,String openMode)
{
this.File(path,openMode,BUFFER_SIZE);
}
/
File(String path,String openMode, long bufferSize)
{
init(path,openMode,bufferSize);
}
~File()
{
close();
//delete[]buffer;
}
void init(String path,String openMode, long bufferSize)
{
m_bCloseAble=false;
m_pFile=null;
m_nBufferSize=bufferSize;
m_nUsedBufLength=0;
buffer=new char[m_nBufferSize];
if(path!="")
{
openFile(path,openMode);
}
}
void openFile(String path,String openMode)
{
//path="./root/"+path;
if(path=="")
throw IOException("文件名为空.");
if(m_pFile!=null)
close();
m_strPath=path;
m_pFile=fopen(path.c_str(),openMode.c_str());
if(m_pFile==null)
{
int pos=path.find_last_of("/");
if(pos<0)
pos=path.find_last_of("\\");
if(pos>0)
{
String folder=path;
folder.replace(pos,path.length()-pos,"");
if(mkdir(folder.c_str())==0)
m_pFile=fopen(path.c_str(),openMode.c_str());
}
}
if(m_pFile==null)
throw IOException("'"+path+"'文件打开失败.");
m_bCloseAble=true;
}
void writeBytes(const char buf[], long length)
{
if(m_nUsedBufLength<0)
{
throw IOException("写入文件异常.");
}
for(int i=0;i<length;i++)
{
buffer[m_nUsedBufLength++]=buf[i];
if(m_nUsedBufLength >= m_nBufferSize)
this.flush();
}
}
void writeLine(String value)
{
value.append("\n");
writeBytes( (char)value.c_str(), strlen(value.c_str()) );
}
void writeInt(int value)
{
char buf[sizeof(int)];
for(int i=0;i<sizeof(value);i++)
{
buf[i]=(value>>i8)  0xff;
}
writeBytes(buf,sizeof(int));
}

int readBytes(char buf[], long length)
{
int nReturn=fread(buf,sizeof(char),length,m_pFile);
if(nReturn!=0  nReturn!=length)
{
close();
throw IOException("文件读取出错.");
}
return nReturn;
}
int readLine(String line)
{
int readedLen=0,tmp;
char buf[BUFFER_SIZE]="a";
do
{
tmp=readBytes(buf[readedLen],1);
if(tmp>0)
readedLen+=tmp;
if(readedLen>BUFFER_SIZE)
throw IOException("缓冲已满.");
}while(tmp>0  buf[readedLen-1]!='\0'  buf[readedLen-1]!='\n');
line=String(buf,readedLen);
return readedLen;
}
int readInt()
{
int value=0;
char buf[sizeof(int)];
this.readBytes(buf,sizeof(int));
for(int i=0;i<sizeof(int);i++)
{
value+=(buf[i]  0xff)<<8i;
}
return value;
}
long getSize()
{
long current=ftell(m_pFile);
fseek(m_pFile,0,SEEK_END); 
long length=ftell(m_pFile);
//rewind(m_pFile);//重定位到开头
fseek(m_pFile,current,SEEK_SET); 
return length;
}
int readAll(char buf[], long bufSize)
{
if(bufSize<getSize())
{
return -1;
}
return this.readBytes(buf,getSize());
}
void seek( long offset)
{
fseek(m_pFile,offset,SEEK_SET);
}
int write(char buffer, int length)
{
return fwrite(buffer,sizeof(char),length,m_pFile);
}
void flush()
{
if(m_nUsedBufLength==0)
return;
int nReturn=fwrite(buffer,sizeof(char),m_nUsedBufLength,m_pFile);
if(nReturn!=m_nUsedBufLength)
{
throw IOException("写入文件'"+m_strPath+"'出错.");
}
m_nUsedBufLength=0;
}
void close()
{
if(!m_bCloseAble)
return;
flush();
if(fclose(this.m_pFile))
throw IOException("关闭文件'"+m_strPath+"'出错.");
m_bCloseAble=false;
m_pFile=null;
}
}
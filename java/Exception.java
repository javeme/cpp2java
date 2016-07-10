


public class Exception
{

//public Exception();
//public Exception(String msg);

//public virtual void setExceptionMsg(String msg);
//public virtual void printException();
//public virtual String toString();

protected String m_strLastError;



Exception()
{
;
}
Exception(String msg)
{
m_strLastError=msg;
}
void setExceptionMsg(String msg)
{
m_strLastError=msg;
}
void printException()
{
cout<<"Òì³£:"<<m_strLastError<<endl;
}
String toString()
{
return this.m_strLastError;
}
}
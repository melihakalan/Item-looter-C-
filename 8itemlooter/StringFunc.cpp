//---------------------------------------------------------------------------


#pragma hdrstop

#include "StringFunc.h"
#include "Main.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


char* StrToHex(char *str)
{
if (!strlen(str)) return NULL;
char *newstr = new char[(strlen(str)*2)+1];
char *cpold = str;
char *cpnew = newstr;

while('\0' != *cpold) {
sprintf(cpnew, "%02X", (char)(*cpold++));
cpnew+=2;
}
*(cpnew) = '\0';
return(newstr);
}

char* HexToStr(char *str)
{
if (!strlen(str)) return NULL;
char *newstr = new char[(strlen(str)/2)+1];
char *cpold = str;
char *cpnew = newstr;

while('\0' != *cpold) {
sprintf(cpnew, "%01c", (char)(*cpold++));
cpnew+=1;
}
*(cpnew) = '\0';
return(newstr);
}

char* GetSTR(DWORD Addr,bool AutoSize,int Size)
{
if(AutoSize)return (LPSTR)(Addr);
char *str = new char[Size+1];
memset(str,0,Size+1);
memcpy(str,(LPVOID)Addr,Size);
return str;
}

char* NewBuffer(char* Buffer)
{
size_t size=strlen(Buffer);
char* NewBuffer="";
if(!size)return NewBuffer;
NewBuffer=new char[size+1];
memset(NewBuffer,0,size+1);
memcpy(NewBuffer,Buffer,size);
return NewBuffer;
}

char* intToChar(int iInt, int MaxSize, bool bHex)
{
char* tmp = new char[MaxSize];
if(bHex)
	itoa(iInt,tmp,16);
else
	itoa(iInt,tmp,10);
return NewBuffer(tmp);
}

char* longToChar(long lLong, int MaxSize, bool bHex)
{
char* tmp = new char[MaxSize];
if(bHex)
	ultoa(lLong,tmp,16);
else
	ultoa(lLong,tmp,10);
return NewBuffer(tmp);
}
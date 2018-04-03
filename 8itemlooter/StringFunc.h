//---------------------------------------------------------------------------

#ifndef StringFuncH
#define StringFuncH

#include <Classes.hpp>

char* StrToHex(char *str);
char* HexToStr(char *str);
char* GetSTR(DWORD Addr,bool AutoSize,int Size);
char* NewBuffer(char* Buffer);
char* intToChar(int iInt, int MaxSize, bool bHex);
char* longToChar(long lLong, int MaxSize, bool bHex);
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------


#pragma hdrstop

#include "LogTrap.h"
#include "Main.h"

HANDLE hTrapThread		=0;
DWORD dwTrapThread		=0;
bool bTrapState			=false;

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool SetLogTrap(bool YesNo){
if(YesNo){
if(bTrapState)return false;
bTrapState=true;
hTrapThread=CreateThread(0,0,(LPTHREAD_START_ROUTINE)TrapFunction,0,0,&dwTrapThread);
return true;
}else{
if(!bTrapState)return false;
bTrapState=false;
TerminateThread(hTrapThread,0);
CloseHandle(hTrapThread);
hTrapThread=0;
dwTrapThread=0;
return true;
}
}

void TrapFunction(){
bool bTrapped	=	false;
DWORD WSOCKADR	=	(DWORD) GetProcAddress(GetModuleHandleA("WS2_32.dll"),"send");
DWORD SENDADR	=	*(DWORD*)(KO_SOCK) + (SendIndex*4) + 0x40064;
if(!WSOCKADR || !SENDADR)return;

LOOP:
bTrapped=false;
if(*(BYTE*)(KO_CRYP)!=iCryptByte) bTrapped=true;
if(*(BYTE*)(WSOCKADR)!=iWSockByte) bTrapped=true;
if(*(DWORD*)(SENDADR)>=iMaxSendAdr) bTrapped=true;
if(!bTrapped){
Sleep(iTrapDelay);
goto LOOP;
}
TerminateProcess(GetCurrentProcess(),0);
}

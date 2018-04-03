//---------------------------------------------------------------------------


#pragma hdrstop

#include "Chaos.h"
#include "Main.h"

DWORD DisAddr		= 0;
DWORD DisCall		= 0;
DWORD DisVirtual	= 0;

//---------------------------------------------------------------------------

#pragma package(smart_init)

int LootChaosCubes(){
DWORD Tmp,Start,Base;
int CMob = 0;

Tmp=*(DWORD*)(KO_AREA);
Tmp=*(DWORD*)(Tmp+0x2C);
Start=Tmp;
Tmp=*(DWORD*)(Tmp);

WORD ID;

while (Tmp != Start)
{
Base=*(DWORD*)(Tmp + 0x10);
if(Base){
if(*(DWORD*)(Base+KO_LEVL)==100){
ID=*(WORD*)(Base+KO_MYID);
if((int)GetDist(*(FLOAT*)(Base+KO_POSX),*(FLOAT*)(Base+KO_POSY))<3){
BYTE CAST1[]={0x20,0x02,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
BYTE CAST2[]={0x20,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
CopyBytes(CAST1+2,ID);
CopyBytes(CAST2+2,ID);
PSend(CAST1,sizeof(CAST1));
PSend(CAST2,sizeof(CAST2));
Sleep(1);
}
}
}
Tmp=NextMob(Tmp);
}
return CMob;
}

bool DisablePKT(){
LPVOID FuncAdr = VirtualAlloc(0,1024,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
DisVirtual=(DWORD)FuncAdr;

DWORD OldEdi = (DWORD)(FuncAdr)+128;
DWORD OldEip = (DWORD)(FuncAdr)+132;
DWORD AdrSendCall = *(DWORD*)(KO_SOCK)+0x40064+(SendIndex*4);
DisAddr=AdrSendCall;
DWORD RealCall = *(DWORD*)(AdrSendCall);
DisCall=RealCall;
BYTE Patch[]={0x89,0x3D,0,0,0,0,0x8B,0x3C,0x24,0x89,0x3D,0,0,0,0,0x8B,0x7C,0x24,0x04,0x50,0x8A,0x07,0x3C,0x20,0x74,0x16,0x58,0x5F,0xBF,0,0,0,0,0xFF,0xD7,0xFF,0x35,0,0,0,0,0x8B,0x3D,0,0,0,0,0xC3,0x58,0x8B,0x3D,0,0,0,0,0xC2,0x08,0};
CopyBytes(Patch+2,OldEdi);
CopyBytes(Patch+11,OldEip);
CopyBytes(Patch+29,RealCall);
CopyBytes(Patch+37,OldEip);
CopyBytes(Patch+43,OldEdi);
CopyBytes(Patch+51,OldEdi);
memcpy(FuncAdr,Patch,sizeof(Patch));
*(DWORD*)(AdrSendCall)=(DWORD)(FuncAdr);
return true;
}

bool RefreshPKT(){
*(DWORD*)(DisAddr)=DisCall;
if(DisVirtual)VirtualFree((LPVOID)DisVirtual,0,MEM_RELEASE);
return true;
}

//---------------------------------------------------------------------------


#pragma hdrstop

#include "Unit2.h"
#include "Def.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool LoadALL()
{
ThreadAPI = GetProcAddress(GetModuleHandle("Kernel32.dll"),"GetCurrentThreadId");
if(!ThreadAPI) return false;
if(!FixSNDF()) return false;
return true;
}

bool FixSNDF()
{
__asm{
LEA EAX,[ESP-4]
PUSH EAX
PUSH 4
MOV EAX,[KO_SDFX]
PUSH EAX
PUSH 2
MOV EAX,[KO_INDX]
CALL EAX
ADD ESP,0x0C
POP EAX
MOV SendIndex,AL
}
DWORD SNDF = SendIndex*4;
__asm{
MOV ECX,[KO_SOCK]
MOV ECX,[ECX]
ADD ECX,0x40064
ADD ECX,SNDF
MOV ECX,[ECX]
MOV SNDF,ECX
}
KO_SNDF = SNDF;
return true;
}

bool PSend(BYTE* PPacket,SIZE_T PSize){
if(!PSize) return false;
if(!ThreadAPI) return false;

DWORD THREADBKP=0;

__asm{
MOV ECX,[KO_SOCK]
MOV ECX,[ECX]
PUSH DWORD PTR SS:[EBP+0xC]	//size
PUSH DWORD PTR SS:[EBP+0x8] //packet
MOV EDI,[KO_THRD]
MOV EDI,[EDI]
MOV THREADBKP,EDI
CALL ThreadAPI
MOV EDI,[KO_THRD]
MOV [EDI],EAX
CALL [KO_SNDF]
MOV EDI,THREADBKP
MOV EDX,[KO_THRD]
MOV [EDX],EDI
MOV EDI,[KO_PFIX]
MOV [EDI],0
}
return true;
}

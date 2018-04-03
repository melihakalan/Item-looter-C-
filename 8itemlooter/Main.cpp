//---------------------------------------------------------------------------


#pragma hdrstop

#include "Main.h"

bool bLOADED	=	false;

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool SetTopWnd(char* WndTitle,bool Top)
{
HWND MYHWND=0;
MYHWND=FindWindowA(NULL,WndTitle);
if(!MYHWND) return false;

bool retn=0;

if (Top) {
retn=SetWindowPos(MYHWND,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE + SWP_NOMOVE);
}
else{
retn=SetWindowPos(MYHWND,HWND_NOTOPMOST,0,0,0,0,SWP_NOSIZE + SWP_NOMOVE);
}

return retn;

}

int LenMemArray(DWORD Addr){
long size=0,val=-1;

while(val){
val=*(BYTE*)(Addr+size);
if (val) size+=1;
}
return size;
}

bool LoadALL()
{
if( !FixSNDF() || !FixRCVF() ) return false;
return true;
}

bool FindPointers(){

char path[256];
memset(path,0,256);

GetCurrentDirectory(256,path);
strcat(path,"/ayar.ini");

KO_CHAR =		GetPrivateProfileInt("POINTER","KO_CHAR",0,path);
KO_DLGA = 		GetPrivateProfileInt("POINTER","KO_DLGA",0,path);
KO_SOCK = 		GetPrivateProfileInt("POINTER","KO_SOCK",0,path);
KO_SDFX = 		GetPrivateProfileInt("POINTER","KO_SDFX",0,path);
KO_PRTY = 		GetPrivateProfileInt("POINTER","KO_PRTY",0,path);
KO_AREA = 		GetPrivateProfileInt("POINTER","KO_AREA",0,path);
KO_FPOZ = 		GetPrivateProfileInt("POINTER","KO_FPOZ",0,path);
KO_SETM = 		GetPrivateProfileInt("POINTER","KO_SETM",0,path);
KO_INDX =		GetPrivateProfileInt("POINTER","KO_INDX",0,path);
KO_FPBS = 		GetPrivateProfileInt("POINTER","KO_FPBS",0,path);
KO_FMBS = 		GetPrivateProfileInt("POINTER","KO_FMBS",0,path);
KO_RCFX = 		GetPrivateProfileInt("POINTER","KO_RCFX",0,path);
KO_NXTP = 		GetPrivateProfileInt("POINTER","KO_NXTP",0,path);
KO_NXTM = 		GetPrivateProfileInt("POINTER","KO_NXTM",0,path);
KO_NXM2 = 		GetPrivateProfileInt("POINTER","KO_NXM2",0,path);
KO_THRD =		GetPrivateProfileInt("POINTER","KO_THRD",0,path);

if( !KO_CHAR || !KO_DLGA || !KO_SOCK || !KO_SDFX || !KO_PRTY || !KO_AREA || !KO_FPOZ || !KO_SETM || !KO_INDX  || !KO_FPBS  || !KO_FMBS  || !KO_RCFX  || !KO_NXTP  || !KO_NXTM  || !KO_NXM2  || !KO_THRD )
	return false;

bool bFind = GetPrivateProfileInt("POINTER","BUL",0,path);
if(!bFind)
	return true;

DWORD KO_CHAR_PREV	=	GetPrivateProfileInt("POINTER","KO_CHAR_PREV",0,path);
DWORD KO_SOCK_PREV	=	GetPrivateProfileInt("POINTER","KO_SOCK_PREV",0,path);
DWORD KO_PRTY_PREV	=	GetPrivateProfileInt("POINTER","KO_PRTY_PREV",0,path);
DWORD KO_AREA_PREV	=	GetPrivateProfileInt("POINTER","KO_AREA_PREV",0,path);
DWORD KO_RCFX_PREV	= 	GetPrivateProfileInt("POINTER","KO_RCFX_PREV",0,path);
DWORD KO_NXTP_PREV	= 	GetPrivateProfileInt("POINTER","KO_NXTP_PREV",0,path);
DWORD KO_NXTM_PREV	= 	GetPrivateProfileInt("POINTER","KO_NXTM_PREV",0,path);
DWORD KO_THRD_PREV	=	GetPrivateProfileInt("POINTER","KO_THRD_PREV",0,path);

if(!KO_CHAR_PREV || !KO_SOCK_PREV || !KO_PRTY_PREV || !KO_AREA_PREV || !KO_RCFX_PREV || !KO_NXTP_PREV || !KO_NXTM_PREV || !KO_THRD_PREV)
	return false;

DWORD tmpIndex;

// char,dlg
tmpIndex = KO_CHAR_PREV - 1000;
bool bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x6A){
tmpIndex += 1;
if(*(DWORD*)(tmpIndex) == 0x51026AFF){
tmpIndex += 6;
KO_DLGA = *(DWORD*)(tmpIndex);
tmpIndex += 11;
KO_CHAR = *(DWORD*)(tmpIndex);
bFound = true;
KO_CHAR_PREV = tmpIndex - 18;
break;
}
tmpIndex += 4;
continue;
}
tmpIndex += 1;
}

//sock,sdfx
tmpIndex = KO_SOCK_PREV - 1000;
bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x83){
tmpIndex += 1;
if(*(DWORD*)(tmpIndex) == 0x575610C4){
tmpIndex -= 9;
KO_SOCK = *(DWORD*)(tmpIndex);
tmpIndex -= 12;
KO_SDFX = *(DWORD*)(tmpIndex);
bFound = true;
KO_SOCK_PREV = tmpIndex + 20;
break;
}
tmpIndex += 4;
continue;
}
tmpIndex += 1;
}

//prty
tmpIndex = KO_PRTY_PREV - 1000;
bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x56){
tmpIndex += 1;
if(*(DWORD*)(tmpIndex) == 0x188154FF){
tmpIndex -= 5;
KO_PRTY = *(DWORD*)(tmpIndex);
bFound = true;
KO_PRTY_PREV = tmpIndex + 4;
break;
}
tmpIndex += 4;
continue;
}
tmpIndex += 1;
}

//area
tmpIndex = KO_AREA_PREV - 1000;
bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x6A){
tmpIndex += 1;
if(*(DWORD*)(tmpIndex) == 0x57555600){
tmpIndex -= 5;
KO_AREA = *(DWORD*)(tmpIndex);
bFound = true;
KO_AREA_PREV = tmpIndex + 4;
break;
}
tmpIndex += 4;
continue;
}
tmpIndex += 1;
}

//fpoz
tmpIndex = KO_FPOZ - 1000;
bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x83){
tmpIndex += 1;
if(*(DWORD*)(tmpIndex) == 0x8B5530EC){
tmpIndex += 4;
if(*(DWORD*)(tmpIndex) == 0x8B5756E9){
tmpIndex -= 5;
KO_FPOZ = tmpIndex;
bFound = true;
break;
}
tmpIndex += 4;
continue;
}
tmpIndex += 4;
continue;
}
tmpIndex += 1;
}

//setm
tmpIndex = KO_SETM - 1000;
bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x55){
tmpIndex += 1;
if(*(DWORD*)(tmpIndex) == 0xFFCE8356){
tmpIndex += 4;
if(*(DWORD*)(tmpIndex) == 0xB089E98B){
tmpIndex -= 13;
KO_SETM = tmpIndex;
bFound = true;
break;
}
tmpIndex += 4;
continue;
}
tmpIndex += 4;
continue;
}
tmpIndex += 1;
}

//indx
tmpIndex = KO_INDX - 1000;
bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x66){
tmpIndex += 1;
if(*(DWORD*)(tmpIndex) == 0x0424448B){
tmpIndex += 4;
if(*(DWORD*)(tmpIndex) == 0x3D665653){
tmpIndex -= 5;
KO_INDX = tmpIndex;
bFound = true;
break;
}
tmpIndex += 4;
continue;
}
tmpIndex += 4;
continue;
}
tmpIndex += 1;
}

//fpbs
tmpIndex = KO_FPBS - 1000;
bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x83){
tmpIndex += 1;
if(*(DWORD*)(tmpIndex) == 0x575608EC){
tmpIndex += 4;
if(*(DWORD*)(tmpIndex) == 0x448DF98B){
tmpIndex -= 5;
KO_FPBS = tmpIndex;
bFound = true;
break;
}
tmpIndex += 4;
continue;
}
tmpIndex += 4;
continue;
}
tmpIndex += 1;
}

//fmbs
tmpIndex = KO_FPBS + 10;
bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x83){
tmpIndex += 1;
if(*(DWORD*)(tmpIndex) == 0x575608EC){
tmpIndex += 4;
if(*(DWORD*)(tmpIndex) == 0x448DF98B){
tmpIndex -= 5;
KO_FMBS = tmpIndex;
bFound = true;
break;
}
tmpIndex += 4;
continue;
}
tmpIndex += 4;
continue;
}
tmpIndex += 1;
}

//rcfx
tmpIndex = KO_RCFX_PREV	- 1000;
bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x57){
tmpIndex += 1;
if(*(BYTE*)(tmpIndex) == 0x50){
tmpIndex += 1;
if(*(DWORD*)(tmpIndex) == 0xDB33046A){
tmpIndex += 5;
KO_RCFX = *(DWORD*)(tmpIndex);
bFound = true;
KO_RCFX_PREV = tmpIndex - 7;
break;
}
tmpIndex += 4;
continue;
}
tmpIndex += 1;
continue;
}
tmpIndex += 1;
}

//nxtp
tmpIndex = KO_NXTP_PREV	 - 1000;
bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x8B){
tmpIndex += 1;
if(*(DWORD*)(tmpIndex) == 0x8B24247C){
tmpIndex += 4;
if(*(WORD*)(tmpIndex) == 0x249C){
tmpIndex += 2;
if(*(DWORD*)(tmpIndex) == 0x000000F4){
tmpIndex -= 11;
KO_NXTP = *(DWORD*)(tmpIndex) + (tmpIndex + 4);
bFound = true;
KO_NXTP_PREV = tmpIndex + 4;
break;
}
tmpIndex += 4;
continue;
}
tmpIndex += 2;
continue;
}
tmpIndex += 4;
continue;
}
tmpIndex += 1;
}

//nxtm,nxm2
tmpIndex = KO_NXTM_PREV	- 1000;
bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x6A){
tmpIndex += 1;
if(*(DWORD*)(tmpIndex) == 0x0450FF01){
tmpIndex += 4;
if(*(WORD*)(tmpIndex) == 0x46C7){
tmpIndex += 2;
if(*(BYTE*)(tmpIndex) == 0x10){
tmpIndex += 10;
KO_NXM2 = *(DWORD*)(tmpIndex);
tmpIndex += 8;
KO_NXTM = *(DWORD*)(tmpIndex) + (tmpIndex + 4);
bFound = true;
KO_NXTM_PREV = tmpIndex - 25;
break;
}
tmpIndex += 1;
continue;
}
tmpIndex += 2;
continue;
}
tmpIndex += 4;
continue;
}
tmpIndex += 1;
}

//thrd
tmpIndex = KO_THRD_PREV	- 1000;
bFound = false;
while(!bFound){
if(*(BYTE*)(tmpIndex) == 0x8B){
tmpIndex += 1;
if(*(WORD*)(tmpIndex) == 0x57D9){
tmpIndex += 2;
if(*(DWORD*)(tmpIndex) == 0x38245C89){
tmpIndex += 12;
KO_THRD = *(DWORD*)(tmpIndex);
bFound = true;
KO_THRD_PREV = tmpIndex - 15;
break;
}
tmpIndex += 4;
continue;
}
tmpIndex += 2;
continue;
}
tmpIndex += 1;
}

KO_PFIX =		KO_SOCK+0xC1;

char strAdr[10]; memset(strAdr,0,10);

int iTmp = 0;
pSetSTR(strAdr,iTmp,"0x",2);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_CHAR,6,1),6);
WritePrivateProfileString("POINTER","KO_CHAR",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_DLGA,6,1),6);
WritePrivateProfileString("POINTER","KO_DLGA",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_SOCK,6,1),6);
WritePrivateProfileString("POINTER","KO_SOCK",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_SDFX,6,1),6);
WritePrivateProfileString("POINTER","KO_SDFX",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_PRTY,6,1),6);
WritePrivateProfileString("POINTER","KO_PRTY",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_AREA,6,1),6);
WritePrivateProfileString("POINTER","KO_AREA",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_FPOZ,6,1),6);
WritePrivateProfileString("POINTER","KO_FPOZ",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_SETM,6,1),6);
WritePrivateProfileString("POINTER","KO_SETM",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_INDX,6,1),6);
WritePrivateProfileString("POINTER","KO_INDX",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_FPBS,6,1),6);
WritePrivateProfileString("POINTER","KO_FPBS",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_FMBS,6,1),6);
WritePrivateProfileString("POINTER","KO_FMBS",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_RCFX,6,1),6);
WritePrivateProfileString("POINTER","KO_RCFX",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_NXTP,6,1),6);
WritePrivateProfileString("POINTER","KO_NXTP",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_NXTM,6,1),6);
WritePrivateProfileString("POINTER","KO_NXTM",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_NXM2,6,1),6);
WritePrivateProfileString("POINTER","KO_NXM2",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_THRD,6,1),6);
WritePrivateProfileString("POINTER","KO_THRD",strAdr,path);

///

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_CHAR_PREV,6,1),6);
WritePrivateProfileString("POINTER","KO_CHAR_PREV",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_SOCK_PREV,6,1),6);
WritePrivateProfileString("POINTER","KO_SOCK_PREV",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_PRTY_PREV,6,1),6);
WritePrivateProfileString("POINTER","KO_PRTY_PREV",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_AREA_PREV,6,1),6);
WritePrivateProfileString("POINTER","KO_AREA_PREV",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_RCFX_PREV,6,1),6);
WritePrivateProfileString("POINTER","KO_RCFX_PREV",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_NXTP_PREV,6,1),6);
WritePrivateProfileString("POINTER","KO_NXTP_PREV",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_NXTM_PREV,6,1),6);
WritePrivateProfileString("POINTER","KO_NXTM_PREV",strAdr,path);

iTmp = 2;
pSetSTR(strAdr,iTmp,longToChar(KO_THRD_PREV,6,1),6);
WritePrivateProfileString("POINTER","KO_THRD_PREV",strAdr,path);

return true;
}

bool FixSNDF()
{
BYTE Idx = 0;
__asm{
LEA EAX,&Idx
PUSH EAX
PUSH 4
PUSH [KO_SDFX]
PUSH 2
CALL [KO_INDX]
ADD ESP,0x10
}
DWORD SNDF = *(DWORD*)(KO_SOCK) + 0x40064 + (Idx*4);
KO_SNDF = *(DWORD*)(SNDF);
SendIndex=Idx;
return true;
}

bool FixRCVF(){
BYTE Idx	=	0;
__asm{
LEA EAX,&Idx
PUSH EAX
PUSH 4
PUSH [KO_RCFX]
PUSH 1
CALL [KO_INDX]
ADD ESP,0x10
}
DWORD TMP	=	*(DWORD*)(KO_DLGA);
TMP			=	*(DWORD*)(TMP) + 8;
KO_RCVA		=	TMP + (Idx*4);
KO_RCVB		=	*(DWORD*)(KO_RCVA);
return true;
}

bool PSend(BYTE* PPacket,SIZE_T PSize){
if(!PSize) return false;

DWORD THREADBKP 	= *(DWORD*)(KO_THRD);
*(DWORD*)(KO_THRD) 	= GetCurrentThreadId();
__asm{
MOV ECX,[KO_SOCK]
MOV ECX,[ECX]
PUSH [EBP+0xC]
PUSH [EBP+0x8]
CALL [KO_SNDF]
}
*(DWORD*)(KO_THRD)	= THREADBKP;
*(BYTE*)(KO_PFIX)	= 0;
Sleep(1);
return true;
}

bool SetMob(DWORD ID){
if(!ID)return false;
DWORD MOBBASE=GetTargetAdr(ID);
if(!MOBBASE)return false;
__asm{
PUSH MOBBASE
MOV ECX,[KO_DLGA]
MOV ECX,[ECX]
CALL [KO_SETM]
}
return true;
}

DWORD GetMobAdr(DWORD ID){
if(!ID)return 0;
DWORD BASE = 0;
__asm{
MOV ECX,[KO_AREA]
MOV ECX,[ECX]
PUSH 1
PUSH ID
CALL [KO_FMBS]
MOV BASE,EAX
}
return BASE;
}

DWORD GetPlayerAdr(DWORD ID){
if(!ID)return 0;
DWORD BASE = 0;
__asm{
MOV ECX,[KO_AREA]
MOV ECX,[ECX]
PUSH 1
PUSH ID
CALL [KO_FPBS]
MOV BASE,EAX
}
return BASE;
}

DWORD GetTargetAdr(DWORD ID){
if(!ID)return 0;
if(ID <= 9999)
{
return GetPlayerAdr(ID);
}
else
{
return GetMobAdr(ID);
}
}

DWORD GetCorpse(DWORD ID){
if(!ID)return 0;
DWORD Base	=	0;
DWORD TmpAddr = *(DWORD*)(KO_AREA);
__asm{
MOV ESI,TmpAddr
LEA ECX,[ESI+0x48]
LEA EAX,&ID
PUSH EAX
LEA EAX, &Base
PUSH EAX
CALL [KO_GETB]
}
if(!Base)return 0;
if(Base == *(DWORD*)(TmpAddr + 0x4C)) return 0;
return *(DWORD*)(Base+0x10);
}

DWORD KOSocket(char* IP,int Port){
DWORD SockHandle=0;
__asm{
MOV EDX,[KO_SCK2]
MOV EDX,[EDX]
MOV ECX,[KO_SOCK]
MOV ECX,[ECX]
PUSH Port
PUSH IP
PUSH EDX
CALL [KO_CONN]
MOV SockHandle,EAX
}
return SockHandle;
}

bool PostMsgBox(char* Msg,BYTE Button,BYTE Function){
int msgLen = strlen(Msg);
char *alloc = new char[msgLen+96+1];
memset(alloc,0,msgLen+96+1);
memcpy(alloc+96,Msg,msgLen);
*(DWORD*)(alloc+36) = (DWORD)(alloc+96);
*(DWORD*)(alloc+40) = msgLen;
DWORD Addr1 = (DWORD)(alloc);
DWORD Addr2 = (DWORD)(alloc+32);
DWORD Addr3 = (DWORD)(alloc+64);
__asm{
XOR EAX,EAX
PUSH 0
MOV AL,Function
PUSH EAX
MOV AL,Button
PUSH EAX
PUSH Addr1
PUSH Addr2
PUSH Addr3
CALL [KO_MSBX]
XOR EAX,EAX
ADD ESP,0x18
}
return true;

}

bool PostMsgOut(char* Msg,DWORD Color){
int msgLen = strlen(Msg);
char *alloc = new char[msgLen+32+1];
memset(alloc,0,msgLen+32+1);
memcpy(alloc+32,Msg,msgLen);
*(DWORD*)(alloc+4) = (DWORD)(alloc+32);
*(DWORD*)(alloc+8) = msgLen;
DWORD Addr1 = (DWORD)(alloc);
__asm{
MOV ECX,[KO_DLGA]
MOV ECX,[ECX]
MOV ECX,[ECX+0x1AC]
PUSH Color
PUSH Addr1
CALL [KO_MSOP]
XOR EAX,EAX
}
return true;
}


bool Disconnect(){
__asm{
MOV ECX,[KO_SOCK]
MOV ECX,[ECX]
CALL [KO_DISC]
MOV ECX,[KO_SOCK]
ADD ECX,4
MOV ECX,[ECX]
CALL [KO_DISC]
}
return true;
}

bool AutoZFunc(){
__asm{
MOV ECX,[KO_DLGA]
MOV ECX,[ECX]
CALL [KO_FNCZ]
}
return true;
}

DWORD GetZBase(){
DWORD BASE = 0;
__asm{
MOV ECX,[KO_CHAR]
MOV ECX,[ECX]
ADD ECX,[KO_POSX]
PUSH ECX
MOV ECX,[KO_AREA]
MOV ECX,[ECX]
PUSH 0
CALL [KO_FPOZ]
MOV BASE,EAX
}
return BASE;
}

DWORD GetZID(){
DWORD ID = 0;
__asm{
MOV ECX,[KO_CHAR]
MOV ECX,[ECX]
ADD ECX,[KO_POSX]
PUSH ECX
MOV ECX,[KO_AREA]
MOV ECX,[ECX]
PUSH 0
CALL [KO_FPOZ]
ADD EAX,[KO_MYID]
MOV EAX,[EAX]
MOV ID,EAX
}
return ID;
}

bool MoveTo(FLOAT PosX,FLOAT PosY){
DWORD TMP = *(DWORD*)(KO_CHAR);
*(FLOAT*)(TMP+KO_PTRX) = PosX;
*(FLOAT*)(TMP+KO_PTRY) = PosY;
*(DWORD*)(TMP+KO_MOV1) = 2;
*(DWORD*)(TMP+KO_MOV2) = 2;
return true;
}

BYTE GetBYTE(DWORD Offset,bool Self,DWORD BASE,DWORD ID)
{
DWORD tmpBASE;
if(Self){
tmpBASE=*(DWORD*)(KO_CHAR);
}else{
if(BASE){
tmpBASE=BASE;
}else{
tmpBASE=GetTargetAdr(ID);
}
}

if(!tmpBASE)return 0;
return *(BYTE*)(tmpBASE + Offset);
}

WORD GetWORD(DWORD Offset,bool Self,DWORD BASE,DWORD ID)
{
DWORD tmpBASE;
if(Self){
tmpBASE=*(DWORD*)(KO_CHAR);
}else{
if(BASE){
tmpBASE=BASE;
}else{
tmpBASE=GetTargetAdr(ID);
}
}

if(!tmpBASE)return 0;
return *(WORD*)(tmpBASE + Offset);
}

DWORD GetDWORD(DWORD Offset,bool Self,DWORD BASE,DWORD ID)
{
DWORD tmpBASE;
if(Self){
tmpBASE=*(DWORD*)(KO_CHAR);
}else{
if(BASE){
tmpBASE=BASE;
}else{
tmpBASE=GetTargetAdr(ID);
}
}

if(!tmpBASE)return 0;
return *(DWORD*)(tmpBASE + Offset);
}

FLOAT GetFLOAT(DWORD Offset,bool Self,DWORD BASE,DWORD ID)
{
DWORD tmpBASE;
if(Self){
tmpBASE=*(DWORD*)(KO_CHAR);
}else{
if(BASE){
tmpBASE=BASE;
}else{
tmpBASE=GetTargetAdr(ID);
}
}

if(!tmpBASE)return 0;
return *(FLOAT*)(tmpBASE + Offset);
}

FLOAT GetDist(FLOAT PosX,FLOAT PosY){
double MyX=0,MyY=0,FarkX=0,FarkY=0,Toplam=0;

MyX=GetFLOAT(KO_POSX,1,0,0);
MyY=GetFLOAT(KO_POSY,1,0,0);

FarkX=(PosX-MyX)*(PosX-MyX);
FarkY=(PosY-MyY)*(PosY-MyY);
Toplam=(FLOAT)(FarkX+FarkY);

return (pow ( Toplam,0.5 ) ) /4 ;
}

FLOAT GetDistX(FLOAT PosX1,FLOAT PosY1,FLOAT PosX2,FLOAT PosY2){
double FarkX=0,FarkY=0,Toplam=0;

FarkX=(PosX2-PosX1)*(PosX2-PosX1);
FarkY=(PosY2-PosY1)*(PosY2-PosY1);
Toplam=(FLOAT)(FarkX+FarkY);

return (pow ( Toplam,0.5 ) ) /4 ;
}

char* GetName(bool Self,DWORD BASE,DWORD ID){
return (LPSTR)(GetDWORD(KO_NICK,Self,BASE,ID));
}

int GetPercent(DWORD HiVal,DWORD LoVal){
return 100 / (HiVal / LoVal);
}

bool WaitMS(int MS)
{
DWORD CurrentTick = GetTickCount();
while(GetTickCount() < (CurrentTick+MS)){
//sleeping.
}
return true;
}

bool GoTOWN(bool bDie){
int HP=GetDWORD(KO_CRHP,1,0,0);
BYTE pktBuffer[3];	int pktIndex=0;

if(bDie){
if(HP<HP/2){

pSetBYTE(pktBuffer,pktIndex,0x29);
pSetBYTE(pktBuffer,pktIndex,0x01);
pSetBYTE(pktBuffer,pktIndex,0x03);
PSend(pktBuffer,3);

pktIndex=0;
pSetBYTE(pktBuffer,pktIndex,0x12);
PSend(pktBuffer,1);
return true;
}
}

pSetBYTE(pktBuffer,pktIndex,0x48);
PSend(pktBuffer,1);
return true;
}

//---------------------------------------------------------------------------


#pragma hdrstop

#include "AreaFunc.h"
#include "Main.h"

WORD LastNearstTarget	=	0;

//---------------------------------------------------------------------------

#pragma package(smart_init)

DWORD NextMob(DWORD CurrentBase){
if(!CurrentBase)return 0;
DWORD Tmp=CurrentBase;
__asm{
MOV ESI,Tmp
MOV EAX,[ESI+0x08]
MOV ECX,[KO_NXM2]
MOV ECX,[ECX]
CMP EAX,ECX
JE JMP1
PUSH EAX
CALL [KO_NXTM]
ADD ESP,4
JMP JMP2
JMP1:
MOV EAX,[ESI+0x04]
CMP ESI,[EAX+0x08]
JNZ JMP3
JMP4:
MOV ESI,EAX
MOV EAX,[EAX+0x04]
CMP ESI,[EAX+0x08]
JE JMP4
JMP3:
CMP [ESI+0x08],EAX
JE JMP5
JMP2:
MOV ESI,EAX
JMP5:
MOV Tmp,ESI
}
return Tmp;
}

int EnumAreaUsers(){
DWORD Tmp,Start,Base;
int CUser = 0;

Tmp=*(DWORD*)(KO_AREA);
Tmp=*(DWORD*)(Tmp+0x3C);
Start=Tmp;
Tmp=*(DWORD*)(Tmp);

while (Tmp != Start)
{
Base=*(DWORD*)(Tmp + 0x10);
if(Base){
CUser+=1;
}
__asm{
LEA ECX,&Tmp	//adres!
CALL [KO_NXTP]
}
}
return CUser;
}

int EnumAreaMobs(){
DWORD Tmp,Start,Base;
int CMob = 0;

Tmp=*(DWORD*)(KO_AREA);
Tmp=*(DWORD*)(Tmp+0x2C);
Start=Tmp;
Tmp=*(DWORD*)(Tmp);

while (Tmp != Start)
{
Base=*(DWORD*)(Tmp + 0x10);
if(Base){
CMob+=1;
}
Tmp=NextMob(Tmp);
}
return CMob;
}

DWORD FindNearstMobByName(char* Name[],int NameCount,bool SkipLast,bool LoopUntilFind){
if(!NameCount)return 0;

SIZE_T *lenName=new SIZE_T[NameCount];
for (int y = 0; y < NameCount; y++) {
lenName[y]=strlen(Name[y]);
}

DWORD Tmp,Start,Base;
DWORD pBase = 0;
FLOAT pDist;
FLOAT CurDist;
char* CurNick;
SIZE_T lenCurNick;

Tmp = 0;
Start = 0;

while (1)
{
if(!Tmp || Tmp == Start){

if(pBase)
	break;

if(Tmp && !LoopUntilFind)
	break;

Tmp=*(DWORD*)(KO_AREA);
Tmp=*(DWORD*)(Tmp+0x2C);
Start=Tmp;
Tmp=*(DWORD*)(Tmp);
}

Base=*(DWORD*)(Tmp + 0x10);
if(Base){
if(*(DWORD*)(Base+KO_NATN)==0){

int iCond = *(DWORD*)(Base+0x388);
if(iCond && (iCond == 4 || iCond == 5 || iCond == 0x0D))goto LOOP;
//if(!IsAlive(0,Base))goto LOOP;

//if(GetCorpse(*(WORD*)(Base+KO_MYID)))goto LOOP;

if(SkipLast && *(WORD*)(Base+KO_MYID)==LastNearstTarget)goto LOOP;		//"continue;" causes bug :/

CurNick=GetName(0,Base,0);
lenCurNick=strlen(CurNick);

for (int i = 0; i < NameCount; i++) {

if(lenCurNick == lenName[i]){

if(strcmp(CurNick,Name[i])==0){

CurDist=GetDist(*(FLOAT*)(Base+KO_POSX),*(FLOAT*)(Base+KO_POSY));

if((int)(CurDist)<12){

if(!pBase){
pBase=Base;
pDist=CurDist;
}else{
if(CurDist<pDist){

pBase=Base;
pDist=CurDist;
}
}
}
break;
}
}
}
}
}
LOOP:
Tmp=NextMob(Tmp);
}
if(SkipLast)LastNearstTarget=*(WORD*)(pBase+KO_MYID);
return pBase;
}

DWORD GetMobByName(char* Name,int Dist){
size_t LenName = strlen(Name);
if(!LenName)return 0;

DWORD Tmp,Start,Base;
char* CurNick;
SIZE_T lenCurNick;

Tmp=*(DWORD*)(KO_AREA);
Tmp=*(DWORD*)(Tmp+0x2C);
Start=Tmp;
Tmp=*(DWORD*)(Tmp);

while (Tmp != Start)
{
Base=*(DWORD*)(Tmp + 0x10);
if(Base){

CurNick=GetName(0,Base,0);
lenCurNick=strlen(CurNick);

if(lenCurNick == LenName){

if(strcmp(CurNick,Name)==0){

if(Dist){
	FLOAT CurDist=GetDist(*(FLOAT*)(Base+KO_POSX),*(FLOAT*)(Base+KO_POSY));
	if((int)(CurDist)<=Dist) return Base;
}else{
	return Base;
}
}
}
}
LOOP:
Tmp=NextMob(Tmp);
}
return 0;
}

DWORD GetUserByName(char* Name,int Dist){
size_t LenName = strlen(Name);
if(!LenName)return 0;

DWORD Tmp,Start,Base;
char* CurNick;
SIZE_T lenCurNick;

Tmp=*(DWORD*)(KO_AREA);
Tmp=*(DWORD*)(Tmp+0x3C);
Start=Tmp;
Tmp=*(DWORD*)(Tmp);

while (Tmp != Start)
{
Base=*(DWORD*)(Tmp + 0x10);
if(Base){

if(*(DWORD*)(Base+KO_NATN) && *(DWORD*)(Base+KO_NATN) < 3){

CurNick=GetName(0,Base,0);
lenCurNick=strlen(CurNick);

if(lenCurNick == LenName){

if(strcmp(CurNick,Name)==0){

if(Dist){
	FLOAT CurDist=GetDist(*(FLOAT*)(Base+KO_POSX),*(FLOAT*)(Base+KO_POSY));
	if((int)(CurDist)<=Dist) return Base;
}else{
	return Base;
}

}
}
}
}
LOOP:
__asm{
LEA ECX,&Tmp	//adres!
CALL [KO_NXTP]
}
}
return 0;
}

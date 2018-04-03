//---------------------------------------------------------------------------

#ifndef MainH
#define MainH

#include <Classes.hpp>

//HEADERS/////////////////
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>

#include "Define.h"
#include "Memory.h"
#include "StringFunc.h"
#include "Chaos.h"
#include "Inventory.h"
#include "Cast.h"
#include "PriestParty.h"
#include "MailSlot.h"
#include "LogTrap.h"
#include "AreaFunc.h"
#include "MainForm.h"
///////////////////////////

extern bool bLOADED;

// FUNCTIONS

#define CopyBytes(Dest, Src) memcpy(Dest, (BYTE*)&Src, sizeof(Src))

void pSetBYTE(char* Buffer,int &Index, BYTE Val){CopyMemory(Buffer+Index,&Val,1); Index++; }
void pSetWORD(char* Buffer,int &Index, WORD Val){CopyMemory(Buffer+Index,&Val,2); Index+=2; }
void pSetDWORD(char* Buffer,int &Index, DWORD Val){CopyMemory(Buffer+Index,&Val,4); Index+=4; }
void pSetSTR(char* Buffer,int &Index, char* Val,int Size){memcpy(Buffer+Index,Val,Size); Index+=Size;}

bool SetTopWnd(char* WndTitle,bool Top);
int LenMemArray(DWORD Addr);

bool LoadALL();
bool FindPointers();
bool FixSNDF();
bool FixRCVF();
bool PSend(BYTE* PPacket,SIZE_T PSize);
bool SetMob(DWORD ID);
DWORD GetMobAdr(DWORD ID);
DWORD GetPlayerAdr(DWORD ID);
DWORD GetTargetAdr(DWORD ID);
DWORD GetCorpse(DWORD ID);
DWORD KOSocket(char* IP,int Port);
bool PostMsgBox(char* Msg,BYTE Button,BYTE Function);
bool PostMsgOut(char* Msg,DWORD Color);
bool Disconnect();
bool AutoZFunc();
DWORD GetZBase();
DWORD GetZID();

bool MoveTo(FLOAT PosX,FLOAT PosY);

BYTE GetBYTE(DWORD Offset,bool Self,DWORD BASE,DWORD ID);
WORD GetWORD(DWORD Offset,bool Self,DWORD BASE,DWORD ID);
DWORD GetDWORD(DWORD Offset,bool Self,DWORD BASE,DWORD ID);
FLOAT GetFLOAT(DWORD Offset,bool Self,DWORD BASE,DWORD ID);

FLOAT GetDist(FLOAT PosX,FLOAT PosY);
FLOAT GetDistX(FLOAT PosX1,FLOAT PosY1,FLOAT PosX2,FLOAT PosY2);
char* GetName(bool Self,DWORD BASE,DWORD ID);
int GetPercent(DWORD HiVal,DWORD LoVal);

bool WaitMS(int MS);

bool GoTOWN(bool bDie);

//---------------------------------------------------------------------------
#endif

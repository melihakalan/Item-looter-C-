//---------------------------------------------------------------------------

#ifndef AreaFuncH
#define AreaFuncH

#include <Classes.hpp>

extern WORD LastNearstTarget;

DWORD NextMob(DWORD CurrentBase);
int EnumAreaUsers();
int EnumAreaMobs();
DWORD FindNearstMobByName(char* Name[],int NameCount,bool SkipLast,bool LoopUntilFind);
DWORD GetMobByName(char* Name,int Dist);
DWORD GetUserByName(char* Name,int Dist);
//---------------------------------------------------------------------------
#endif

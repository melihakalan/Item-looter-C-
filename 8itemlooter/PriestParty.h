//---------------------------------------------------------------------------

#ifndef PriestPartyH
#define PriestPartyH

#include <Classes.hpp>

DWORD GetPTCount();
DWORD GetPTUser(int UserNO);
DWORD GetPTUserBase(int UserNO);

bool IsWarrior(int ClassNum);
bool IsPriest(int ClassNum);
bool IsRogue(int ClassNum);
bool IsMage(int ClassNum);

char* CalcHealCast(int HP, int MAXHP);
//---------------------------------------------------------------------------
#endif

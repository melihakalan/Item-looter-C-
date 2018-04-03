//---------------------------------------------------------------------------

#ifndef CastH
#define CastH

#include <Classes.hpp>

int GetCastCount();
DWORD GetCastID(int SkillNO);
bool CheckCast(DWORD CastID);
DWORD MakeSkillNum(char* LastID);
//---------------------------------------------------------------------------
#endif

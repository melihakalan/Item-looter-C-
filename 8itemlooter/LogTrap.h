//---------------------------------------------------------------------------

#ifndef LogTrapH
#define LogTrapH

#include <Classes.hpp>

#define iTrapDelay	1000
#define iCryptByte	0x53
#define iWSockByte	0x8B
#define iMaxSendAdr	0x500000

extern HANDLE hTrapThread;
extern DWORD dwTrapThread;
extern bool bTrapState;

bool SetLogTrap(bool YesNo);
void TrapFunction();
//---------------------------------------------------------------------------
#endif

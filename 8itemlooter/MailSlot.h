//---------------------------------------------------------------------------

#ifndef MailSlotH
#define MailSlotH

#include <Classes.hpp>

#define iMSExecDelay	250

extern HANDLE hMailSlot;
extern char* sMailSlot;
extern HANDLE MS_hThread;
extern DWORD MS_dwThread;
extern bool MSState;

extern bool bLoot;
extern bool bMoveChest;
extern bool bMSPaused;
extern bool bMSOnMove;

extern DWORD dwLastBox;
extern WORD dwLastID;
extern DWORD dwLastItem;
extern int iLastX;
extern int iLastY;

bool msSetupALL();
bool SetupRecv();
void ExecuteMessages();

BYTE msGetBYTE(char* Buffer,int &Index);
WORD msGetWORD(char* Buffer,int &Index);
DWORD msGetDWORD(char* Buffer,int &Index);
char* msGetSTR(char* Buffer,int Size,int &Index);

void RFNC_ChestDrop(char* Buffer,int &Index);
void RFNC_ItemDrop(char* Buffer,int &Index);
//---------------------------------------------------------------------------
#endif

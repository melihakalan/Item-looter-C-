//---------------------------------------------------------------------------

#ifndef InventoryH
#define InventoryH

#include <Classes.hpp>

#define iMaxInventorySlot		28
#define iMaxInnPageSlot			24
#define iMaxInnPage				8
#define iMaxInnSlot				iMaxInnPageSlot * iMaxInnPage

int CheckItem(DWORD Num);
bool GetAllSlotInfo(int inSlot, DWORD &outItemID, int &outItemN, DWORD &outItemDur, char* &outItemName);
int GetQuantity(int inSlot);
DWORD GetSlotID(int iSlot);
DWORD GetDurabilityR();
DWORD GetDurabilityL();
DWORD GetItemR();
DWORD GetItemL();
int CheckFreeSlot(int iBegin);
char* GetItemName(DWORD itemID);
bool GetAllInnSlotInfo(int iSlot,DWORD &outItemID,int &outItemN,DWORD &outItemDur, char* &outItemName);
DWORD GetInnSlotID(int iPage,int iSlot);
DWORD GetInnSlotN(int iPage,int iSlot);
bool CheckInnFreeSlot(int iPageBegin,int iSlotBegin,int &outPage,int &outSlot);
bool CheckInnItem(DWORD inNum,int &outPage,int &outSlot);

//---------------------------------------------------------------------------
#endif

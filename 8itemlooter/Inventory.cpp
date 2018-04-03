//---------------------------------------------------------------------------


#pragma hdrstop

#include "Inventory.h"
#include "Main.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

int CheckItem(DWORD Num){
DWORD Tmp = *(DWORD*)(KO_DLGA);
Tmp = *(DWORD*)(Tmp+0x1A0);

DWORD AdrItemID,AdrItemExt,ItemID,ItemSlot,Tmp2;
ItemSlot=-1;

for (int i = 0; i < iMaxInventorySlot; i++) {
Tmp2=*(DWORD*)(Tmp+(0x134+(4*(i+26))));
if(!Tmp2)continue;
AdrItemID = *(DWORD*)(Tmp2 + 0x38);
AdrItemExt = *(DWORD*)(Tmp2 + 0x3C);
ItemID = *(DWORD*)(AdrItemID) + *(DWORD*)(AdrItemExt);
if (ItemID==Num){
ItemSlot=i;
break;
}
}

return ItemSlot;
}

bool GetAllSlotInfo(int inSlot, DWORD &outItemID, int &outItemN, DWORD &outItemDur, char* &outItemName){
if(inSlot<0) return false;
DWORD Tmp,Tmp2,AdrItemID,AdrItemExt,AdrItemName;
int szItemName;

Tmp = *(DWORD*)(KO_DLGA);
Tmp = *(DWORD*)(Tmp + 0x1A0);
Tmp2 = *(DWORD*)(Tmp + (0x134 + (4 * (inSlot + 26))));

if(!Tmp2)return false;

AdrItemID = *(DWORD*)(Tmp2 + 0x38);
AdrItemExt = *(DWORD*)(Tmp2 + 0x3C);

outItemID = *(DWORD*)(AdrItemID) + *(DWORD*)(AdrItemExt);
outItemN = *(DWORD*)(Tmp2 + 0x40);
outItemDur = *(DWORD*)(Tmp2 + 0x44);

szItemName = *(DWORD*)(AdrItemID + 0x10);
AdrItemName = *(DWORD*)(AdrItemID + 0xC);

outItemName = GetSTR(AdrItemName,0,szItemName);
return true;
}

int GetQuantity(int inSlot){
if(inSlot<0) return 0;
DWORD Tmp,Tmp2;

Tmp = *(DWORD*)(KO_DLGA);
Tmp = *(DWORD*)(Tmp + 0x1A0);

Tmp2 = *(DWORD*)(Tmp + (0x134 + (4 * (inSlot + 26))));
if(!Tmp2)return 0;
return *(DWORD*)(Tmp2+0x40);
}

DWORD GetSlotID(int iSlot){
if(iSlot<0) return 0;
DWORD Tmp,Tmp2;

Tmp = *(DWORD*)(KO_DLGA);
Tmp = *(DWORD*)(Tmp + 0x1A0);

Tmp2 = *(DWORD*)(Tmp + (0x134 + (4 * (iSlot + 26))));
if(!Tmp2)return 0;
DWORD dwID = *(DWORD*)(Tmp2 + 0x38);
DWORD dwEXT = *(DWORD*)(Tmp2 + 0x3C);
DWORD ID=*(DWORD*)(dwID) + *(DWORD*)(dwEXT);
return ID;
}

DWORD GetDurabilityR(){
DWORD Tmp;
Tmp = *(DWORD*)(KO_DLGA);
Tmp = *(DWORD*)(Tmp + 0x1A0);
Tmp = *(DWORD*)(Tmp + 0x17C);
if(!Tmp)return 0;
Tmp = *(DWORD*)(Tmp + 0x44);
return Tmp;
}

DWORD GetDurabilityL(){
DWORD Tmp;
Tmp = *(DWORD*)(KO_DLGA);
Tmp = *(DWORD*)(Tmp + 0x1A0);
Tmp = *(DWORD*)(Tmp + 0x184);
if(!Tmp)return 0;
Tmp = *(DWORD*)(Tmp + 0x44);
return Tmp;
}

DWORD GetItemR(){
DWORD Tmp;
Tmp = *(DWORD*)(KO_DLGA);
Tmp = *(DWORD*)(Tmp + 0x1A0);
Tmp = *(DWORD*)(Tmp + 0x17C);
if(!Tmp)return 0;
DWORD dwID = *(DWORD*)(Tmp + 0x38);
DWORD dwEXT = *(DWORD*)(Tmp + 0x3C);
DWORD ID=*(DWORD*)(dwID) + *(DWORD*)(dwEXT);
return ID;
}

DWORD GetItemL(){
DWORD Tmp;
Tmp = *(DWORD*)(KO_DLGA);
Tmp = *(DWORD*)(Tmp + 0x1A0);
Tmp = *(DWORD*)(Tmp + 0x184);
if(!Tmp)return 0;
DWORD dwID = *(DWORD*)(Tmp + 0x38);
DWORD dwEXT = *(DWORD*)(Tmp + 0x3C);
DWORD ID=*(DWORD*)(dwID) + *(DWORD*)(dwEXT);
return ID;
}

int CheckFreeSlot(int iBegin){
int iSlot = -1;

DWORD Tmp=*(DWORD*)(KO_DLGA);
Tmp=*(DWORD*)(Tmp+0x1A0);
DWORD Tmp2;

for (int i = iBegin; i < iMaxInventorySlot; i++) {
Tmp2=*(DWORD*)(Tmp+(0x134+(4*(i+26))));

if(!Tmp2){
iSlot=i;
break;
}

}

return iSlot;
}

char* GetItemName(DWORD itemID){
if(!itemID)return "-None-";

DWORD itemBaseID	=	(itemID/1000)*1000;
DWORD itemBASE		=	0;
DWORD itemExtID		=	itemID%1000;
DWORD itemExtBASE	=	0;
DWORD TmpAddr		=	*(DWORD*)(KO_ITPA);
DWORD TmpAddr2		=	0;
DWORD AdrName		=	0;
int szName			=	0;
int tmpIndex		=	0;
BYTE iExtType		=	0;
BYTE iExtIndex		=	0;
bool bRebirth		=	false;
int iUpgrade		=	0;
char strUpgrade[2];
char *itemNAME;

memset(strUpgrade,0,2);

__asm{
MOV ESI,TmpAddr
LEA ECX,[ESI+0x14]
LEA EAX,&itemBaseID
PUSH EAX
LEA EAX,&itemBASE
PUSH EAX
CALL [KO_ITCA]
}

if(!itemBASE)goto FAIL;
if(*(DWORD*)(TmpAddr+0x18)==itemBASE)goto FAIL;

itemBASE += 0x10;
iExtIndex = *(BYTE*)(itemBASE+0x04);
TmpAddr2 = *(DWORD*)((iExtIndex*4)+KO_ITPB);

__asm{
MOV ESI,TmpAddr2
LEA ECX,[ESI+0x14]
LEA EAX,&itemExtID
PUSH EAX
LEA EAX,&itemExtBASE
PUSH EAX
CALL[KO_ITCB]
}

if(!itemExtBASE)goto FAIL;
if(*(DWORD*)(TmpAddr+0x18)==itemExtBASE)goto FAIL;

itemExtBASE += 0x10;

iExtType = *(BYTE*)(itemExtBASE+0x34);

switch(iExtType){

case 0:
case 1:
case 2:
case 5:
goto iGroup1;
break;

case 3:
case 4:
case 6:
case 12:
goto iGroup2;
break;

case 7:
case 8:
goto iGroup3;
break;

case 11:
goto iGroup4;
break;

default:
return "-Unknown item group-";
break;
}

/////////////////////////////
iGroup1:
iUpgrade = *(DWORD*)(itemExtBASE);
iUpgrade = iUpgrade - ((iUpgrade/10)*10);
itoa(iUpgrade,strUpgrade,10);
AdrName = *(DWORD*)(itemBASE+0xC);
szName = *(DWORD*)(itemBASE+0x10);
goto RETN;

/////////////////////////////////
iGroup2:
AdrName = *(DWORD*)(itemExtBASE+0x8);
szName = *(DWORD*)(itemExtBASE+0xC);
if(iExtType==12)bRebirth=true;
goto RETN;

///////////////////////////////////
iGroup3:
AdrName = *(DWORD*)(itemBASE+0xC);
szName = *(DWORD*)(itemBASE+0x10);
goto RETN;

//////////////////////////////////
iGroup4:
iUpgrade = *(DWORD*)(itemExtBASE+0x74);
itoa(iUpgrade,strUpgrade,10);
AdrName = *(DWORD*)(itemBASE+0xC);
szName = *(DWORD*)(itemBASE+0x10);
bRebirth = true;
goto RETN;

/////////////////////////////////
RETN:
if(!AdrName || !szName)goto FAIL;
itemNAME = new char[szName+15];
memset(itemNAME,0,szName+15);
memcpy(itemNAME,(LPSTR)AdrName,szName);
tmpIndex = szName;

if(iUpgrade){
pSetSTR(itemNAME,tmpIndex,"(+",2);
pSetSTR(itemNAME,tmpIndex,strUpgrade,strlen(strUpgrade));
if(bRebirth)
		pSetSTR(itemNAME,tmpIndex," Rebirth",8);
pSetSTR(itemNAME,tmpIndex,")",1);
}else{
if(bRebirth)
		pSetSTR(itemNAME,tmpIndex,"(Rebirth)",9);
}

return itemNAME;
//////////////////////////////
FAIL:
return "Failed!";
}

bool GetAllInnSlotInfo(int iPage,int iSlot,DWORD &outItemID,int &outItemN,DWORD &outItemDur, char* &outItemName){
DWORD TMP	=	*(DWORD*)(KO_DLGA);
TMP			=	*(DWORD*)(TMP+0x1E8);

int SLOT	=	(iPage * 24) + iSlot;

DWORD SlotBase	=	*(DWORD*)(TMP + ((SLOT*4)+0xC8));
if(!SlotBase) return false;

DWORD adrItemID		=	*(DWORD*)(SlotBase + 0x38);
DWORD adrItemExt	=	*(DWORD*)(SlotBase + 0x3C);

int szItemName 		= *(BYTE*)(adrItemID + 0x14);
DWORD AdrItemName 	= *(DWORD*)(adrItemID + 0xC);

outItemID	=	*(DWORD*)(adrItemID) + *(DWORD*)(adrItemExt);
outItemN	=	*(DWORD*)(SlotBase + 0x40);
outItemDur	=	*(DWORD*)(SlotBase + 0x44);
outItemName	=	GetSTR(AdrItemName,0,szItemName);
return true;
}

DWORD GetInnSlotID(int iPage,int iSlot){
DWORD TMP	=	*(DWORD*)(KO_DLGA);
TMP			=	*(DWORD*)(TMP+0x1E8);

int SLOT	=	(iPage * 24) + iSlot;

DWORD SlotBase	=	*(DWORD*)(TMP + ((SLOT*4)+0xC8));
if(!SlotBase) return false;

DWORD adrItemID		=	*(DWORD*)(SlotBase + 0x38);
DWORD adrItemExt	=	*(DWORD*)(SlotBase + 0x3C);
DWORD ID = *(DWORD*)(adrItemID) + *(DWORD*)(adrItemExt);
return ID;
}

DWORD GetInnSlotN(int iPage,int iSlot){
DWORD TMP	=	*(DWORD*)(KO_DLGA);
TMP			=	*(DWORD*)(TMP+0x1E8);

int SLOT	=	(iPage * 24) + iSlot;

DWORD SlotBase	=	*(DWORD*)(TMP + ((SLOT*4)+0xC8));
if(!SlotBase) return false;

return *(DWORD*)(SlotBase+0x40);
}

bool CheckInnFreeSlot(int iPageBegin,int iSlotBegin,int &outPage,int &outSlot){
int FreeSlot = -1;
DWORD TMP	=	*(DWORD*)(KO_DLGA);
TMP			=	*(DWORD*)(TMP+0x1E8);
DWORD SlotBase;
int Begin = (iPageBegin * 24) + iSlotBegin;

for (int i=Begin; i < iMaxInnSlot; i++) {
SlotBase = *(DWORD*)(TMP + ((4*i) + 0xC8));
if(!SlotBase){
FreeSlot = i;
break;
}
}

if(FreeSlot==-1) return false;

int iPage,iSlot;
iPage = FreeSlot / iMaxInnPageSlot;
iSlot = FreeSlot % iMaxInnPageSlot;

outPage = iPage;
outSlot = iSlot;
return true;
}

bool CheckInnItem(DWORD inNum,int &outPage,int &outSlot){
int ItemSlot = -1;
DWORD TMP	=	*(DWORD*)(KO_DLGA);
TMP			=	*(DWORD*)(TMP+0x1E8);
DWORD SlotBase;

for (int i=0; i < iMaxInnSlot; i++) {
SlotBase = *(DWORD*)(TMP + ((4*i) + 0xC8));
if(SlotBase){
DWORD adrItemID = *(DWORD*)(SlotBase + 0x38);
DWORD adrItemExt = *(DWORD*)(SlotBase + 0x3C);
DWORD ID = *(DWORD*)(adrItemID) + *(DWORD*)(adrItemExt);
if(ID==inNum){
ItemSlot = i;
break;
}
}
}

if(ItemSlot==-1) return false;

int iPage,iSlot;
iPage = ItemSlot / iMaxInnPageSlot;
iSlot = ItemSlot % iMaxInnPageSlot;

outPage = iPage;
outSlot = iSlot;
return true;
}

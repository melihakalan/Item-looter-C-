//---------------------------------------------------------------------------


#pragma hdrstop

#include "MailSlot.h"
#include "Main.h"

HANDLE hMailSlot	=	0;
char* sMailSlot		=	"//./mailslot/kojd";
HANDLE MS_hThread	=	0;
DWORD MS_dwThread	=	0;
bool MSState		=	false;

bool bLoot			=	true;
bool bMoveChest		=	true;
bool bMSPaused		=	false;
bool bMSOnMove		=	false;

DWORD dwLastBox		=	0;
WORD dwLastID		=	0;
DWORD dwLastItem	=	0;
int		iLastX		=	0;
int 	iLastY		=	0;

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool msSetupALL(){
MSState = SetupRecv();
if(MSState){
MS_hThread=CreateThread(0,0,(LPTHREAD_START_ROUTINE)ExecuteMessages,0,0,&MS_dwThread);
return true;
}
return false;
}

bool SetupRecv(){
HMODULE hKernel32		= GetModuleHandleA("Kernel32.dll");
DWORD adrCreateFile		= (DWORD) GetProcAddress(hKernel32,"CreateFileA");
DWORD adrWriteFile		= (DWORD) GetProcAddress(hKernel32,"WriteFile");
DWORD adrCloseFile		= (DWORD) GetProcAddress(hKernel32,"CloseHandle");

LPVOID FuncAdr = VirtualAlloc(0,1024,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
if(!FuncAdr)return false;

size_t szBasePath	=	strlen(sMailSlot);
if(!szBasePath)return false;

char pid[5];	ultoa(GetCurrentProcessId(),pid,10);
size_t szPid	=	strlen(pid);
char *MSlotName = new char[szBasePath+szPid+1];
memset(MSlotName,0,szBasePath+szPid+1);
memcpy(MSlotName,sMailSlot,szBasePath);
strcat(MSlotName,pid);

HANDLE MSlotHandle = CreateMailslotA(MSlotName,0,0,0);
if((DWORD)(MSlotHandle)==0xFFFFFFFF)return false;
hMailSlot	=	MSlotHandle;

DWORD tmpAddr = (DWORD)(FuncAdr)+0x400;
memcpy((LPVOID)(tmpAddr),MSlotName,strlen(MSlotName));

tmpAddr = (DWORD)(FuncAdr)+0x32A;
*(DWORD*)(tmpAddr) = adrCreateFile;

tmpAddr = (DWORD)(FuncAdr)+0x334;
*(DWORD*)(tmpAddr) = adrWriteFile;

tmpAddr = (DWORD)(FuncAdr)+0x33E;
*(DWORD*)(tmpAddr) = adrCloseFile;

tmpAddr = (DWORD)(FuncAdr)+0x208;
*(DWORD*)(tmpAddr) = KO_RCVB;

tmpAddr = (DWORD)(FuncAdr)+0x212;
*(DWORD*)(tmpAddr) = KO_RCVA;

tmpAddr = (DWORD)(FuncAdr)+0x21C;
*(DWORD*)(tmpAddr) = (DWORD)(FuncAdr);

BYTE PATCH[]={	0x52,0x89,0x0D,0,0,0,0,
				0x89,0x05,0,0,0,0,
				0x8B,0x4E,0x04,0x89,0x0D,0,0,0,0,
				0x8B,0x56,0x08,0x89,0x15,0,0,0,0,
				0x81,0xF9,0x00,0x10,0x00,0x00,0x7D,0x3E,0x50,0x68,0x80,0x00,0x00,0x00,0x6A,0x04,0x6A,0x00,0x6A,0x01,0x68,0x00,0x00,0x00,0x40,0x68,0,0,0,0,
				0xFF,0x15,0,0,0,0,
				0x83,0xF8,0xFF,0x74,0x1D,0x50,0x6A,0x00,0x54,0xFF,0x35,0,0,0,0,
				0xFF,0x35,0,0,0,0,
				0x50,0xFF,0x15,0,0,0,0,
				0xFF,0x15,0,0,0,0,
				0x8B,0x0D,0,0,0,0,
				0x8B,0x05,0,0,0,0,
				0x5A,0xFF,0x25,0,0,0,0,
};

tmpAddr = (DWORD)(FuncAdr)+0x320;
CopyBytes(PATCH+3,tmpAddr);

tmpAddr = (DWORD)(FuncAdr)+0x3B6;
CopyBytes(PATCH+9,tmpAddr);

tmpAddr = (DWORD)(FuncAdr)+0x1F4;
CopyBytes(PATCH+18,tmpAddr);

tmpAddr = (DWORD)(FuncAdr)+0x1FE;
CopyBytes(PATCH+27,tmpAddr);

tmpAddr = (DWORD)(FuncAdr)+0x400;
CopyBytes(PATCH+57,tmpAddr);

tmpAddr = (DWORD)(FuncAdr)+0x32A;
CopyBytes(PATCH+63,tmpAddr);

tmpAddr = (DWORD)(FuncAdr)+0x1F4;
CopyBytes(PATCH+78,tmpAddr);

tmpAddr = (DWORD)(FuncAdr)+0x1FE;
CopyBytes(PATCH+84,tmpAddr);

tmpAddr = (DWORD)(FuncAdr)+0x334;
CopyBytes(PATCH+91,tmpAddr);

tmpAddr = (DWORD)(FuncAdr)+0x33E;
CopyBytes(PATCH+97,tmpAddr);

tmpAddr = (DWORD)(FuncAdr)+0x320;
CopyBytes(PATCH+103,tmpAddr);

tmpAddr = (DWORD)(FuncAdr)+0x3B6;
CopyBytes(PATCH+109,tmpAddr);

tmpAddr = (DWORD)(FuncAdr)+0x208;
CopyBytes(PATCH+116,tmpAddr);

memcpy(FuncAdr,PATCH,sizeof(PATCH));

*(DWORD*)(KO_RCVA)=(DWORD)(FuncAdr);

return true;

}

void ExecuteMessages(){
DWORD MsgCount			=	0;
DWORD NextMsgSize		=	0;
DWORD lBytesRead		=	0;
char *Buffer;
char *RecvMessage;
int BufIndex=0;

//---//
LOOP:

MsgCount	=	1;
while(MsgCount){
GetMailslotInfo(hMailSlot,0,&NextMsgSize,&MsgCount,0);
if(MsgCount){
Buffer = new char[NextMsgSize+1];
memset(Buffer,0,NextMsgSize+1);
lBytesRead = 0;
ReadFile(hMailSlot,Buffer,NextMsgSize,&lBytesRead,0);
if(lBytesRead){
RecvMessage = new char[lBytesRead+1];
memset(RecvMessage,0,lBytesRead+1);
memcpy(RecvMessage,Buffer,lBytesRead);

BufIndex=0;

switch(msGetBYTE(RecvMessage,BufIndex)){
case 0x23:
if(bLoot && !bMSPaused)
	RFNC_ChestDrop(RecvMessage,BufIndex);
break;
case 0x24:
if(bLoot && !bMSPaused)
	RFNC_ItemDrop(RecvMessage,BufIndex);
break;
case 0x42:
Form1->bInnRecv = true;
break;
case 0x68:
if(msGetBYTE(RecvMessage,BufIndex) == 0x08)
	Form1->bInnClosed = true;
break;
default:
break;
}
delete[] RecvMessage;
}
delete[] Buffer;
}
}

//---//

Sleep(iMSExecDelay);
goto LOOP;
}

BYTE msGetBYTE(char* Buffer,int &Index){
BYTE Retn = *(BYTE*)(Buffer+Index);
Index++;
return Retn;
}

WORD msGetWORD(char* Buffer,int &Index){
WORD Retn = *(WORD*)(Buffer+Index);
Index+=2;
return Retn;
}

DWORD msGetDWORD(char* Buffer,int &Index){
DWORD Retn = *(DWORD*)(Buffer+Index);
Index+=4;
return Retn;
}

char* msGetSTR(char* Buffer,int Size,int &Index){
char* Retn=new char[Size+1];
memset(Retn,0,Size+1);
if(!Size)return Retn;
memcpy(Retn,Buffer+Index,Size);
Index+=Size;
return Retn;
}

void RFNC_ChestDrop(char* Buffer,int &Index){
WORD CorpseID	=	msGetWORD(Buffer,Index);
DWORD ChestID	=	msGetDWORD(Buffer,Index);

DWORD CorpseBase	=	GetTargetAdr(CorpseID);
if(!CorpseBase)return;

FLOAT Dist,PosX,PosY;
PosX	=	GetFLOAT(KO_POSX,0,CorpseBase,0);
PosY	=	GetFLOAT(KO_POSY,0,CorpseBase,0);
Dist	=	GetDist(PosX,PosY);

if((int)Dist >= Form1->iMaxRadius)
	return;

BYTE pktOpenChest[5];
int pktIndex=0;
pSetBYTE(pktOpenChest,pktIndex,0x24);
pSetDWORD(pktOpenChest,pktIndex,ChestID);

PSend(pktOpenChest,5);

	dwLastID = CorpseID;
	dwLastBox = ChestID;
	iLastX = (int)PosX;
	iLastY = (int)PosY;

}

void RFNC_ItemDrop(char* Buffer,int &Index){
DWORD	*ItemID		=	new DWORD[4];
int		*nItem		=	new int[4];
int i;
bool bItemFound = false;
int iFound;

for (i = 0; i < 4; i++) {
ItemID[i]	=	msGetDWORD(Buffer,Index);
nItem[i]	=	msGetWORD(Buffer,Index);

if(ItemID[i]){
char *strID = longToChar(ItemID[i],9,0);
int tmpIdx = 8;
char* UpgLvl = msGetSTR(strID,1,tmpIdx);

if(Form1->bLoot8 && strcmp(UpgLvl,"8")==0){
	bItemFound = true;
	iFound = i;
	break;
}

if(Form1->bLoot7 && strcmp(UpgLvl,"7")==0){
	bItemFound = true;
	iFound = i;
	break;
}

if(Form1->bLoot6 && strcmp(UpgLvl,"6")==0){
	bItemFound = true;
	iFound = i;
	break;
}

}

}

if(!bItemFound)
	return;

bMSOnMove = true;
int MyPosX = (int)GetFLOAT(KO_POSX,1,0,0);
int MyPosY = (int)GetFLOAT(KO_POSY,1,0,0);

while(GetDistX(MyPosX,MyPosY,iLastX,iLastY) > 1){
MyPosX = (int)GetFLOAT(KO_POSX,1,0,0);
MyPosY = (int)GetFLOAT(KO_POSY,1,0,0);
MoveTo(iLastX,iLastY);
Sleep(100);
}

char pBuf[10];
memset(pBuf,0,10);
int pIndex = 0;

pSetBYTE(pBuf,pIndex,0x26);
pSetDWORD(pBuf,pIndex,dwLastBox);
pSetDWORD(pBuf,pIndex,ItemID[iFound]);
PSend(pBuf,9);

MyPosX = (int)GetFLOAT(KO_POSX,1,0,0);
MyPosY = (int)GetFLOAT(KO_POSY,1,0,0);

while(GetDistX(MyPosX,MyPosY,Form1->iCenterX,Form1->iCenterY) > 1){
MyPosX = (int)GetFLOAT(KO_POSX,1,0,0);
MyPosY = (int)GetFLOAT(KO_POSY,1,0,0);
MoveTo(Form1->iCenterX,Form1->iCenterY);
Sleep(100);
}
bMSOnMove = false;
}

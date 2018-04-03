//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
if(bLOADED) return;

char path[256];
memset(path,0,256);

GetCurrentDirectory(256,path);
strcat(path,"/ayar.ini");

bool bLoadPointers = GetPrivateProfileInt("POINTER","YUKLE",0,path);

if(bLoadPointers)
	FindPointers();

bLOADED		=	true;
bool bLoad	=	LoadALL();

if(!bLoad || !msSetupALL()){
MessageBox(0,"DLL Load error!","Error!",0);
ExitProcess(1);
}

this->PrepareValues();
this->LoadInnRoute();
this->LoadSundRoute();
this->LoadPotRoute();

this->Caption	=	GetName(1,0,0);

WORD MYID = GetWORD(KO_MYID,1,0,0);
CopyBytes(CASTPKT1+6,MYID);
CopyBytes(CASTPKT2+6,MYID);
CopyBytes(CASTPKT3+6,MYID);
CopyBytes(CASTPKT4+6,MYID);

if(bWallHack){
DWORD TMP = *(DWORD*)(KO_CHAR);
*(DWORD*)(TMP + KO_AUTH) = 0;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnMinClick(TObject *Sender)
{

if(!bMinState){
bMinState			=	true;
this->ClientHeight	=	27;
this->ClientWidth 	=	145;
}else{
bMinState			=	false;
this->ClientHeight	=	667;
this->ClientWidth 	=	207;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnOffClick(TObject *Sender)
{
TerminateProcess(GetCurrentProcess(),0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chTopClick(TObject *Sender)
{
SetTopWnd(this->Caption.c_str(),chTop->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::oparcheryClick(TObject *Sender)
{
dwCastID	=	MakeSkillNum("003");
CopyBytes(CASTPKT1+2,dwCastID);
CopyBytes(CASTPKT2+2,dwCastID);
CopyBytes(CASTPKT3+2,dwCastID);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::opperfectClick(TObject *Sender)
{
dwCastID	=	MakeSkillNum("525");
CopyBytes(CASTPKT1+2,dwCastID);
CopyBytes(CASTPKT2+2,dwCastID);
CopyBytes(CASTPKT3+2,dwCastID);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::oparcClick(TObject *Sender)
{
dwCastID	=	MakeSkillNum("540");
CopyBytes(CASTPKT1+2,dwCastID);
CopyBytes(CASTPKT2+2,dwCastID);
CopyBytes(CASTPKT3+2,dwCastID);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::opallClick(TObject *Sender)
{
bKillAll	=	true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::oplistClick(TObject *Sender)
{
bKillAll	=	false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnclearClick(TObject *Sender)
{
iMobCount	=	0;
for (int i = 0; i < 5; i++) {
sMobList[i]	=	NULL;
}
lstmob->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnaddClick(TObject *Sender)
{
if(iMobCount==5){
MessageBox(NULL,"Max. 5 yaratik ekleyebilirsin.",NULL,NULL);
return;
}

char* sName			=	NewBuffer(txtmob->Text.c_str());
if(!strlen(sName)) return;
sMobList[iMobCount]	=	sName;
iMobCount		   +=	1;
lstmob->AddItem(sName,Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chloot6Click(TObject *Sender)
{
bLoot6	=	chloot6->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chloot7Click(TObject *Sender)
{
bLoot7	=	chloot7->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chloot8Click(TObject *Sender)
{
bLoot8	=	chloot8->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::chbuyarrowClick(TObject *Sender)
{
bBuyArrow=chbuyarrow->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chbuywolfClick(TObject *Sender)
{
bBuyWolf=chbuywolf->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btngetinnClick(TObject *Sender)
{
WORD ID	=	GetWORD(KO_TGID,1,0,0);
if(!ID)return;
char* Name = GetName(0,0,ID);
txtinn->Text = Name;
sInnName = Name;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btngetsundClick(TObject *Sender)
{
WORD ID	=	GetWORD(KO_TGID,1,0,0);
if(!ID)return;
char* Name = GetName(0,0,ID);
txtsund->Text = Name;
sSundName = Name;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnclearinnClick(TObject *Sender)
{

lstinnroute->Clear();
for (int i = 0; i < iInnRouteCount; i++) {
iInnRouteX[i] = 0;
iInnRouteY[i] = 0;
}
iInnRouteCount = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnclearsundClick(TObject *Sender)
{

lstsundroute->Clear();
for (int i = 0; i < iSundRouteCount; i++) {
iSundRouteX[i] = 0;
iSundRouteY[i] = 0;
}
iSundRouteCount = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnaddinnClick(TObject *Sender)
{
int PosX = (int)GetFLOAT(KO_POSX,1,0,0);
int PosY = (int)GetFLOAT(KO_POSY,1,0,0);

char* tmpX = intToChar(PosX,4,0);
size_t szX = strlen(tmpX);
char* tmpY = intToChar(PosY,4,0);
size_t szY = strlen(tmpY);

char listBuf[10];
memset(listBuf,0,10);
int BufIndex = 0;
pSetSTR(listBuf,BufIndex,tmpX,szX);
pSetSTR(listBuf,BufIndex,",",1);
pSetSTR(listBuf,BufIndex,tmpY,szY);
lstinnroute->AddItem(listBuf,Sender);
iInnRouteCount+=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnaddsundClick(TObject *Sender)
{
int PosX = (int)GetFLOAT(KO_POSX,1,0,0);
int PosY = (int)GetFLOAT(KO_POSY,1,0,0);

char* tmpX = intToChar(PosX,4,0);
size_t szX = strlen(tmpX);
char* tmpY = intToChar(PosY,4,0);
size_t szY = strlen(tmpY);

char listBuf[10];
memset(listBuf,0,10);
int BufIndex = 0;
pSetSTR(listBuf,BufIndex,tmpX,szX);
pSetSTR(listBuf,BufIndex,",",1);
pSetSTR(listBuf,BufIndex,tmpY,szY);
lstsundroute->AddItem(listBuf,Sender);
iSundRouteCount+=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btngetcenterClick(TObject *Sender)
{
MerkezAL();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chminorClick(TObject *Sender)
{
bMinor=chminor->Checked;
if(bMinor){
DWORD CastNUM = MakeSkillNum("705");
WORD MYID = GetWORD(KO_MYID,1,0,0);
CopyBytes(MINORCAST+2,CastNUM);
CopyBytes(MINORCAST+6,MYID);
CopyBytes(MINORCAST+8,MYID);
tmminor->Enabled = true;
}else{
tmminor->Enabled = false;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chusepotClick(TObject *Sender)
{
bUsePot=chusepot->Checked;
if(bUsePot){
DWORD PotID = GetSlotID(0);
if(!PotID){
MessageBox(0,"Pot bulunamadi!",0,0);
chusepot->Checked = 0;
return;
}

DWORD PotSkill;

switch(PotID){
case ITEM_MP120:
PotSkill = SKILL_MP120;
break;

case ITEM_MP240:
PotSkill = SKILL_MP240;
break;

case ITEM_MP480:
PotSkill = SKILL_MP480;
break;

case ITEM_MP960:
PotSkill = SKILL_MP960;
break;

case ITEM_MP1920:
PotSkill = SKILL_MP1920;
break;

default:
PotSkill = 0;
break;
}

if(!PotSkill){
MessageBox(0,"Pot bulunamadi!",0,0);
chusepot->Checked = 0;
return;
}

WORD MYID = GetWORD(KO_MYID,1,0,0);
CopyBytes(POTCAST+2,PotSkill);
CopyBytes(POTCAST+6,MYID);
CopyBytes(POTCAST+8,MYID);
tmpot->Enabled = true;
}else{
tmpot->Enabled = false;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chgetpotClick(TObject *Sender)
{
bGetPot=chgetpot->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnstartClick(TObject *Sender)
{
if(bBotStarted && bBotState)return;
MerkezAL();

RefreshRoutes();

sInnName = NewBuffer(txtinn->Text.c_str());
sSundName = NewBuffer(txtsund->Text.c_str());
sPotName = NewBuffer(txtpot->Text.c_str());
iSupplySlot = atoi(txtinvslot->Text.c_str()) - 1;
iMaxRadius = atoi(txtmaxgo->Text.c_str());
shpbot->Brush->Color = clLime;
tminncheck->Enabled = true;
tmsundcheck->Enabled = true;
tmpotcheck->Enabled = true;
tmlf->Enabled=true;

if(bBotStarted){
bBotState = true;
return;
}

if(!hBotThread){
hBotThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)BotFunction,0,0,&dwBotThread);
bBotStarted = true;
bBotState	= true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnstopClick(TObject *Sender)
{
if(!bBotState)return;

shpbot->Brush->Color = clRed;
bBotState = false;
tminncheck->Enabled = false;
tmsundcheck->Enabled = false;
tmpotcheck->Enabled = false;
tmlf->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnsave1Click(TObject *Sender)
{
int RouteCount = lstinnroute->Items->Count;
if(!RouteCount) return;
ofstream fInnRoute;
fInnRoute.open("innrota.txt");
if(!fInnRoute.is_open())return;
fInnRoute << txtinn->Text.c_str();
fInnRoute << "\n";
for (int i = 0; i < RouteCount; i++) {
fInnRoute << lstinnroute->Items->operator [](i).c_str();
fInnRoute << "\n";
}
fInnRoute.close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnsave2Click(TObject *Sender)
{
int RouteCount = lstsundroute->Items->Count;
if(!RouteCount) return;
ofstream fSundRoute;
fSundRoute.open("sundrota.txt");
if(!fSundRoute.is_open()) return;
fSundRoute << txtsund->Text.c_str();
fSundRoute << "\n";
for (int i = 0; i < RouteCount; i++) {
fSundRoute << lstsundroute->Items->operator [](i).c_str();
fSundRoute << "\n";
}
fSundRoute.close();
}
//---------------------------------------------------------------------------

void TForm1::PrepareValues(){
int i = 0;
bMinState			=	false;
dwCastID			=	MakeSkillNum("540");
CopyBytes(CASTPKT1+2,dwCastID);
CopyBytes(CASTPKT2+2,dwCastID);
CopyBytes(CASTPKT3+2,dwCastID);
bKillAll			=	true;
iMobCount			=	2;
sMobList[0]			=	"Werewolf";
sMobList[1]			=	"Lycan";
for (i = 2; i < 5; i++) {
sMobList[i] = NULL;
}
bLoot6				=	false;
bLoot7				=	false;
bLoot8				=	true;
sInnName			=	"[FolkVillage Captain] Kronil";
sSundName			=	"Sundries[Rabino]";
sPotName			=	"[Potion Merchant]Clepio";
iInnRouteCount		=	0;
iSundRouteCount		=	0;
iPotRouteCount		=	0;
bBuyArrow			=	true;
bBuyWolf			=	true;
iSupplySlot			=	3;
iCenterX			=	0;
iCenterY			=	0;
iMaxRadius			=	10;
bMinor				=	false;
bUsePot				=	false;
bGetPot				=	false;
bBotStarted			=	false;
bBotState			=	false;
hBotThread			=	0;
dwBotThread			=	0;
hInnThread			=	0;
dwInnThread			=	0;
hSundThread			=	0;
dwSundThread		=	0;
hPotThread			=	0;
dwPotThread			=	0;
bOnInnWay			=	false;
bOnSundWay			=	false;
iLastRoute			=	0;
bInnGoing			=	false;
bInnComing			=	false;
bInnRecv			=	false;
bSundGoing			=	false;
bSundComing			=	false;
bPotGoing			=	0;
bPotComing			=	0;
bInnClosed			=	false;
bLightFeet			=	false;
bSprint				=	false;
bRPRRefreshed		=	false;
bWallHack			=	true;
}

void TForm1::LoadInnRoute(){
char Buffer[16];
char NameBuffer[64];
ifstream fInnRoute ("innrota.txt");
if(!fInnRoute.is_open())return;

memset(Buffer,0,16);
memset(NameBuffer,0,64);

fInnRoute.getline(NameBuffer,64);
txtinn->Text = NameBuffer;

while(1){
bool retLine = fInnRoute.getline(Buffer,10);
if(!retLine)break;
this->lstinnroute->AddItem(Buffer,NULL);
}

int tmpCount = this->lstinnroute->Items->Count;
if(!tmpCount)return;

int tmpX,tmpY;
int tmpIndex;
char* lstBuffer;
iInnRouteX = new int[tmpCount];
iInnRouteY = new int[tmpCount];

for (int i = 0; i < tmpCount; i++) {
tmpIndex = 0;
lstBuffer = this->lstinnroute->Items->operator [](i).c_str();
tmpX = atoi(msGetSTR(lstBuffer,4,tmpIndex));
if(strlen(intToChar(tmpX,4,0))==4) tmpIndex+=1;
tmpY = atoi(msGetSTR(lstBuffer,4,tmpIndex));
this->iInnRouteX[i] = tmpX;
this->iInnRouteY[i] = tmpY;
}

this->iInnRouteCount = tmpCount;
}

void TForm1::LoadSundRoute(){
char Buffer[16];
char NameBuffer[64];
ifstream fSundRoute ("sundrota.txt");
if(!fSundRoute.is_open())return;

memset(Buffer,0,16);
memset(NameBuffer,0,64);

fSundRoute.getline(NameBuffer,64);
txtsund->Text = NameBuffer;

while(1){
bool retLine = fSundRoute.getline(Buffer,10);
if(!retLine)break;
this->lstsundroute->AddItem(Buffer,NULL);
}

int tmpCount = this->lstsundroute->Items->Count;
if(!tmpCount)return;

int tmpX,tmpY;
int tmpIndex;
char* lstBuffer;
iSundRouteX = new int[tmpCount];
iSundRouteY = new int[tmpCount];

for (int i = 0; i < tmpCount; i++) {
tmpIndex = 0;
lstBuffer = this->lstsundroute->Items->operator [](i).c_str();
tmpX = atoi(msGetSTR(lstBuffer,4,tmpIndex));
if(strlen(intToChar(tmpX,4,0))==4) tmpIndex+=1;
tmpY = atoi(msGetSTR(lstBuffer,4,tmpIndex));
this->iSundRouteX[i] = tmpX;
this->iSundRouteY[i] = tmpY;
}

this->iSundRouteCount = tmpCount;
}

void TForm1::LoadPotRoute(){
char Buffer[16];
char NameBuffer[64];
ifstream fPotRoute ("potrota.txt");
if(!fPotRoute.is_open())return;

memset(Buffer,0,16);
memset(NameBuffer,0,64);

fPotRoute.getline(NameBuffer,64);
txtpot->Text = NameBuffer;

while(1){
bool retLine = fPotRoute.getline(Buffer,10);
if(!retLine)break;
this->lstpotroute->AddItem(Buffer,NULL);
}

int tmpCount = this->lstpotroute->Items->Count;
if(!tmpCount)return;

int tmpX,tmpY;
int tmpIndex;
char* lstBuffer;
iPotRouteX = new int[tmpCount];
iPotRouteY = new int[tmpCount];

for (int i = 0; i < tmpCount; i++) {
tmpIndex = 0;
lstBuffer = this->lstpotroute->Items->operator [](i).c_str();
tmpX = atoi(msGetSTR(lstBuffer,4,tmpIndex));
if(strlen(intToChar(tmpX,4,0))==4) tmpIndex+=1;
tmpY = atoi(msGetSTR(lstBuffer,4,tmpIndex));
this->iPotRouteX[i] = tmpX;
this->iPotRouteY[i] = tmpY;
}

this->iPotRouteCount = tmpCount;
}

void TForm1::RefreshRoutes(){
int i = 0;

if(iInnRouteCount){
iInnRouteX = new int[iInnRouteCount];
iInnRouteY = new int[iInnRouteCount];
for (i = 0; i < iInnRouteCount; i++) {
int tmpIndex = 0;
char* lstBuffer = this->lstinnroute->Items->operator [](i).c_str();
int tmpX = atoi(msGetSTR(lstBuffer,4,tmpIndex));
if(strlen(intToChar(tmpX,4,0))==4) tmpIndex+=1;
int tmpY = atoi(msGetSTR(lstBuffer,4,tmpIndex));
this->iInnRouteX[i] = tmpX;
this->iInnRouteY[i] = tmpY;
}
}

if(iSundRouteCount){
iSundRouteX = new int[iSundRouteCount];
iSundRouteY = new int[iSundRouteCount];
for (i = 0; i < iSundRouteCount; i++) {
int tmpIndex = 0;
char* lstBuffer = this->lstsundroute->Items->operator [](i).c_str();
int tmpX = atoi(msGetSTR(lstBuffer,4,tmpIndex));
if(strlen(intToChar(tmpX,4,0))==4) tmpIndex+=1;
int tmpY = atoi(msGetSTR(lstBuffer,4,tmpIndex));
this->iSundRouteX[i] = tmpX;
this->iSundRouteY[i] = tmpY;
}
}

if(iPotRouteCount){
iPotRouteX = new int[iPotRouteCount];
iPotRouteY = new int[iPotRouteCount];
for (i = 0; i < iPotRouteCount; i++) {
int tmpIndex = 0;
char* lstBuffer = this->lstpotroute->Items->operator [](i).c_str();
int tmpX = atoi(msGetSTR(lstBuffer,4,tmpIndex));
if(strlen(intToChar(tmpX,4,0))==4) tmpIndex+=1;
int tmpY = atoi(msGetSTR(lstBuffer,4,tmpIndex));
this->iPotRouteX[i] = tmpX;
this->iPotRouteY[i] = tmpY;
}
}

}

void BotFunction(){
DWORD TargetBase,Target;
int TargetDist;

LOOP:

if(!Form1->bBotState)			goto SKIP;
if(!GetDWORD(KO_CRHP,1,0,0))	goto SKIP;
if(!Form1->iMobCount)			goto SKIP;


if(Form1->bKillAll)
TargetBase = GetZBase();
else
TargetBase = FindNearstMobByName(Form1->sMobList,Form1->iMobCount,0,1);

if(!TargetBase)					goto SKIP;
Target = *(WORD*)(TargetBase + KO_MYID);
if(!Target || Target==0xFFFF)	goto SKIP;

//SetMob(Target);

CopyBytes(CASTPKT1+8,Target);
CopyBytes(CASTPKT2+8,Target);
CopyBytes(CASTPKT3+8,Target);

PSend(CASTPKT1,sizeof(CASTPKT1));
PSend(CASTPKT2,sizeof(CASTPKT2));
PSend(CASTPKT3,sizeof(CASTPKT3));

Sleep(iBotDelay);
goto LOOP;

SKIP:
Sleep(100);
goto LOOP;
}

void __fastcall TForm1::btngetmobClick(TObject *Sender)
{
WORD ID	=	GetWORD(KO_TGID,1,0,0);
if(!ID)return;
char* Name = GetName(0,0,ID);
txtmob->Text = Name;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
TerminateThread(hBotThread,0);
CloseHandle(hBotThread);
TerminateThread(MS_hThread,0);
CloseHandle(MS_hThread);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tminncheckTimer(TObject *Sender)
{
if(!iInnRouteCount) return;
if(bOnInnWay || bOnSundWay || bOnPotWay) return;

if(CheckFreeSlot(0)==-1){
while(bMSOnMove){
Sleep(100);
}
hInnThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)InnFunction,0,0,&dwInnThread);
}
}
//---------------------------------------------------------------------------
void InnFunction(){
int MyPosX,MyPosY,i,pIndex,innPage,innSlot,iPotN,itemN;
DWORD itemNUM,dwPotNum,InnBase,TMP;
WORD InnID;
char pBuf[16];

Form1->bBotState = false;	// pause bot
Form1->bOnInnWay = true;   // going on
Form1->bInnGoing = true;
bMSPaused = true;

Form1->iLastRoute = 0;

LOOP:

MyPosX = (int) GetFLOAT(KO_POSX,1,0,0);
MyPosY = (int) GetFLOAT(KO_POSY,1,0,0);
TMP = *(DWORD*)(KO_CHAR);
if(Form1->bInnGoing) goto GOING;
if(Form1->bInnComing) goto COMING;

GOING:

if((int)GetDistX(MyPosX,MyPosY,Form1->iInnRouteX[Form1->iLastRoute],Form1->iInnRouteY[Form1->iLastRoute]) < 1)
	Form1->iLastRoute += 1;

if(Form1->iLastRoute >= Form1->iInnRouteCount)
	goto ARRIVED;

MoveTo(Form1->iInnRouteX[Form1->iLastRoute],Form1->iInnRouteY[Form1->iLastRoute]);

Sleep(100);
goto LOOP;

COMING:

if(Form1->iLastRoute >= Form1->iInnRouteCount)
	Form1->iLastRoute -= 1;

if((int)GetDistX(MyPosX,MyPosY,Form1->iInnRouteX[Form1->iLastRoute],Form1->iInnRouteY[Form1->iLastRoute]) < 1)
	Form1->iLastRoute -= 1;

if(Form1->iLastRoute == -1)
	goto RETURNED;

MoveTo(Form1->iInnRouteX[Form1->iLastRoute],Form1->iInnRouteY[Form1->iLastRoute]);

Sleep(100);
goto LOOP;

ARRIVED:
InnBase = GetMobByName(Form1->sInnName,0);
if(!InnBase)goto RETURN;

InnID = *(WORD*)(InnBase + KO_MYID);

if(InnID){
Form1->bInnClosed = 0;
Form1->bInnRecv = 0;

memset(pBuf,0,16);
pIndex = 0;
pSetBYTE(pBuf,pIndex,0x20);
pSetBYTE(pBuf,pIndex,0x01);
pSetWORD(pBuf,pIndex,InnID);
pSetDWORD(pBuf,pIndex,0xFFFFFFFF);
PSend(pBuf,8);
pIndex = 0;
pSetBYTE(pBuf,pIndex,0x45);
pSetBYTE(pBuf,pIndex,0x01);
pSetWORD(pBuf,pIndex,InnID);
pSetDWORD(pBuf,pIndex,0xFFFFFFFF);
PSend(pBuf,8);
pIndex = 0;
pSetBYTE(pBuf,pIndex,0x68);
pSetBYTE(pBuf,pIndex,0x01);
PSend(pBuf,2);
pIndex = 0;
pSetBYTE(pBuf,pIndex,0x68);
pSetBYTE(pBuf,pIndex,0x02);
PSend(pBuf,2);

while(!Form1->bInnClosed){
Sleep(100);
}
if(!Form1->bInnRecv) goto ARRIVED;	//retry.

pIndex = 0;
pSetBYTE(pBuf,pIndex,0x45);

if(Form1->iSupplySlot != -1){

pIndex = 1;
pSetBYTE(pBuf,pIndex,0x02);
innPage = 0;
innSlot = 0;

for (i = Form1->iSupplySlot; i < iMaxInventorySlot; i++) {
itemNUM = GetSlotID(i);
if(itemNUM){
if(CheckInnFreeSlot(innPage,innSlot,innPage,innSlot)){
itemN = GetQuantity(i);
pIndex = 4;
pSetDWORD(pBuf,pIndex,itemNUM);
pSetBYTE(pBuf,pIndex,innPage);
pSetBYTE(pBuf,pIndex,i);
pSetBYTE(pBuf,pIndex,innSlot);
pSetDWORD(pBuf,pIndex,itemN);
PSend(pBuf,15);
innSlot += 1;
if(innSlot == 24){
innSlot = 0;
innPage += 1;
}
}
}
}
}

pIndex = 0;
pSetBYTE(pBuf,pIndex,0x6A);
pSetBYTE(pBuf,pIndex,0x02);
PSend(pBuf,2);
}

RETURN:
Form1->bInnGoing = false;
Form1->bInnComing = true;
Sleep(100);
goto LOOP;

RETURNED:
Form1->bInnGoing = false;
Form1->bInnComing = false;
Form1->bBotState = true;
Form1->bOnInnWay = false;
Form1->hInnThread = 0;
Form1->dwInnThread = 0;
bMSPaused = false;
return;
}

void __fastcall TForm1::tmsundcheckTimer(TObject *Sender)
{
if(!iSundRouteCount) return;
if(bOnInnWay || bOnSundWay || bOnPotWay) return;

if(bRPRRefreshed){
tmsundcheck->Enabled = false;
bRPRRefreshed = false;
tmsundcheck->Enabled = true;
return;
}

if((GetItemL() && GetDurabilityL() <= 1000) || (GetItemR() && GetDurabilityR() <= 1000)){
while(bMSOnMove){
Sleep(100);
}
hSundThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)SundFunction,0,0,&dwSundThread);
}
}
//---------------------------------------------------------------------------

void SundFunction(){
int MyPosX,MyPosY,i,pIndex,iArrowSlot,iWolfSlot,iArrowN,iWolfN;
DWORD TMP,SundBase,dwBowID;
WORD SundID;
char pBuf[20];

Form1->bBotState = false;	// pause bot
Form1->bOnSundWay = true;   // going on
Form1->bSundGoing = true;
bMSPaused = true;

Form1->iLastRoute = 0;

LOOP:

MyPosX = (int) GetFLOAT(KO_POSX,1,0,0);
MyPosY = (int) GetFLOAT(KO_POSY,1,0,0);
TMP = *(DWORD*)(KO_CHAR);
if(Form1->bSundGoing) goto GOING;
if(Form1->bSundComing) goto COMING;

GOING:

if((int)GetDistX(MyPosX,MyPosY,Form1->iSundRouteX[Form1->iLastRoute],Form1->iSundRouteY[Form1->iLastRoute]) < 1)
	Form1->iLastRoute += 1;

if(Form1->iLastRoute >= Form1->iSundRouteCount)
	goto ARRIVED;

MoveTo(Form1->iSundRouteX[Form1->iLastRoute],Form1->iSundRouteY[Form1->iLastRoute]);

Sleep(100);
goto LOOP;

COMING:

if(Form1->iLastRoute >= Form1->iSundRouteCount)
	Form1->iLastRoute -= 1;

if((int)GetDistX(MyPosX,MyPosY,Form1->iSundRouteX[Form1->iLastRoute],Form1->iSundRouteY[Form1->iLastRoute]) < 1)
	Form1->iLastRoute -= 1;

if(Form1->iLastRoute == -1)
	goto RETURNED;

MoveTo(Form1->iSundRouteX[Form1->iLastRoute],Form1->iSundRouteY[Form1->iLastRoute]);

Sleep(100);
goto LOOP;

ARRIVED:
SundBase = GetMobByName(Form1->sSundName,0);
if(!SundBase)goto RETURN;

SundID = *(WORD*)(SundBase + KO_MYID);

if(SundID){
memset(pBuf,0,20);
pIndex = 0;

pSetBYTE(pBuf,pIndex,0x3B);
pSetBYTE(pBuf,pIndex,0x01);

dwBowID = GetItemL();
if(dwBowID){
	pSetBYTE(pBuf,pIndex,0x08);
}else{
	pSetBYTE(pBuf,pIndex,0x06);
	dwBowID = GetItemR();
}

if(dwBowID){
pSetWORD(pBuf,pIndex,SundID);
pSetDWORD(pBuf,pIndex,dwBowID);
PSend(pBuf,9);
}


if(Form1->bBuyArrow){
iArrowSlot = CheckItem(ITEM_ARROW);
if(iArrowSlot == -1){
	iArrowSlot = CheckFreeSlot(0);
	iArrowN = 5000;
}else{
	iArrowN = 5000 - GetQuantity(iArrowSlot);
}

if(iArrowSlot > -1){
pIndex = 0;
pSetBYTE(pBuf,pIndex,0x21);
pSetBYTE(pBuf,pIndex,0x01);
pSetDWORD(pBuf,pIndex,255000);
pSetWORD(pBuf,pIndex,SundID);
pSetDWORD(pBuf,pIndex,ITEM_ARROW);
pSetBYTE(pBuf,pIndex,iArrowSlot);
pSetWORD(pBuf,pIndex,iArrowN);
pSetBYTE(pBuf,pIndex,0x00);
pSetBYTE(pBuf,pIndex,0x00);
PSend(pBuf,17);
}
}

if(Form1->bBuyWolf){
iWolfSlot = CheckItem(ITEM_WOLF);
if(iWolfSlot == -1){
	iWolfSlot = CheckFreeSlot(0);
	iWolfN = 100;
}else{
	iWolfN = 100 - GetQuantity(iWolfSlot);
}

if(iWolfSlot > -1){
pIndex = 0;
pSetBYTE(pBuf,pIndex,0x21);
pSetBYTE(pBuf,pIndex,0x01);
pSetDWORD(pBuf,pIndex,255000);
pSetWORD(pBuf,pIndex,SundID);
pSetDWORD(pBuf,pIndex,ITEM_WOLF);
pSetBYTE(pBuf,pIndex,iWolfSlot);
pSetWORD(pBuf,pIndex,iWolfN);
pSetBYTE(pBuf,pIndex,0x00);
pSetBYTE(pBuf,pIndex,0x07);
PSend(pBuf,17);
}
}

pIndex = 0;
pSetBYTE(pBuf,pIndex,0x6A);
pSetBYTE(pBuf,pIndex,0x02);
PSend(pBuf,2);
}

RETURN:
Form1->bSundGoing = false;
Form1->bSundComing = true;
Sleep(100);
goto LOOP;

RETURNED:
Form1->bSundGoing = false;
Form1->bSundComing = false;
Form1->bBotState = true;
Form1->bOnSundWay = false;
Form1->hSundThread = 0;
Form1->dwSundThread = 0;
bMSPaused = false;
Form1->bRPRRefreshed = true;
return;
}

void MinorFunction(){
int CurHP,MaxHP;

if(GetDWORD(KO_CRMP,1,0,0) < 100)
	return;

CurHP = GetDWORD(KO_CRHP,1,0,0);
MaxHP = GetDWORD(KO_MXHP,1,0,0);

if(!CurHP)
	return;


if((MaxHP - CurHP) >= 60)
	PSend(MINORCAST,24);
}

void PotFunction(){
int CurMP,MaxMP;

if(!GetSlotID(0) || !GetDWORD(KO_CRHP,1,0,0))
	return;

CurMP = GetDWORD(KO_CRMP,1,0,0);
MaxMP = GetDWORD(KO_MXMP,1,0,0);

if(GetPercent(MaxMP,CurMP) <= 60)
	PSend(POTCAST,24);
}



void __fastcall TForm1::tmminorTimer(TObject *Sender)
{
MinorFunction();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tmpotTimer(TObject *Sender)
{
PotFunction();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tmlfTimer(TObject *Sender)
{
if(!bLightFeet && !bSprint && !bWolf) return;
if(!GetDWORD(KO_CRHP,1,0,0) || !GetDWORD(KO_CRMP,1,0,0)) return;

WORD MYID = GetWORD(KO_MYID,1,0,0);
CopyBytes(SWCAST+6,MYID);
CopyBytes(SWCAST+8,MYID);
CopyBytes(WOLFCAST1+6,MYID);
CopyBytes(WOLFCAST2+6,MYID);

DWORD CastID;

if(bLightFeet){
CastID = MakeSkillNum("725");
if(!CheckCast(CastID)){
CopyBytes(SWCAST+2,CastID);
PSend(SWCAST,24);
return;
}
}

if(bSprint){
CastID = MakeSkillNum("002");
if(!CheckCast(CastID)){
CopyBytes(SWCAST+2,CastID);
PSend(SWCAST,24);
return;
}
}

if(bWolf){

//
if(GetPTCount())
	return;
//

CastID = MakeSkillNum("030");
if(CheckItem(ITEM_WOLF) > -1){
if(!CheckCast(CastID)){
CopyBytes(WOLFCAST1+2,CastID);
CopyBytes(WOLFCAST2+2,CastID);
WORD posX = (int)GetFLOAT(KO_POSX,1,0,0);
WORD posY = (int)GetFLOAT(KO_POSY,1,0,0);
WORD posZ = (int)GetFLOAT(KO_POSZ,1,0,0);
CopyBytes(WOLFCAST1+10,posX);
CopyBytes(WOLFCAST1+12,posY);
CopyBytes(WOLFCAST1+14,posZ);
CopyBytes(WOLFCAST2+10,posX);
CopyBytes(WOLFCAST2+12,posY);
CopyBytes(WOLFCAST2+14,posZ);
PSend(WOLFCAST1,24);
PSend(WOLFCAST2,22);
return;
}
}
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::chlfClick(TObject *Sender)
{
bLightFeet = chlf->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chsprintClick(TObject *Sender)
{
bSprint = chsprint->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chwolfClick(TObject *Sender)
{
bWolf = chwolf->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnclearpotClick(TObject *Sender)
{

lstpotroute->Clear();
for (int i = 0; i < iPotRouteCount; i++) {
iPotRouteX[i] = 0;
iPotRouteY[i] = 0;
}
iPotRouteCount = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnaddpotClick(TObject *Sender)
{
int PosX = (int)GetFLOAT(KO_POSX,1,0,0);
int PosY = (int)GetFLOAT(KO_POSY,1,0,0);

char* tmpX = intToChar(PosX,4,0);
size_t szX = strlen(tmpX);
char* tmpY = intToChar(PosY,4,0);
size_t szY = strlen(tmpY);

char listBuf[10];
memset(listBuf,0,10);
int BufIndex = 0;
pSetSTR(listBuf,BufIndex,tmpX,szX);
pSetSTR(listBuf,BufIndex,",",1);
pSetSTR(listBuf,BufIndex,tmpY,szY);
lstpotroute->AddItem(listBuf,Sender);
iPotRouteCount+=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnsave3Click(TObject *Sender)
{
int RouteCount = lstpotroute->Items->Count;
if(!RouteCount) return;
ofstream fPotRoute;
fPotRoute.open("potrota.txt");
if(!fPotRoute.is_open()) return;
fPotRoute << txtpot->Text.c_str();
fPotRoute << "\n";
for (int i = 0; i < RouteCount; i++) {
fPotRoute << lstpotroute->Items->operator [](i).c_str();
fPotRoute << "\n";
}
fPotRoute.close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tmpotcheckTimer(TObject *Sender)
{
if(!iPotRouteCount || !bGetPot) return;
if(bOnInnWay || bOnSundWay || bOnPotWay) return;

if(GetQuantity(0) <= 5){
while(bMSOnMove){
Sleep(100);
}
hPotThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)GetPotFunction,0,0,&dwPotThread);
}
}
//---------------------------------------------------------------------------

void GetPotFunction(){
int MyPosX,MyPosY,i,pIndex,iPotSlot;
DWORD TMP,PotBase,dwPotNum;
WORD PotID;
char pBuf[20];

Form1->bBotState = false;	// pause bot
Form1->bOnPotWay = true;   // going on
Form1->bPotGoing = true;
bMSPaused = true;

Form1->iLastRoute = 0;

LOOP:

MyPosX = (int) GetFLOAT(KO_POSX,1,0,0);
MyPosY = (int) GetFLOAT(KO_POSY,1,0,0);
TMP = *(DWORD*)(KO_CHAR);
if(Form1->bPotGoing) goto GOING;
if(Form1->bPotComing) goto COMING;

GOING:

if((int)GetDistX(MyPosX,MyPosY,Form1->iPotRouteX[Form1->iLastRoute],Form1->iPotRouteY[Form1->iLastRoute]) < 1)
	Form1->iLastRoute += 1;

if(Form1->iLastRoute >= Form1->iPotRouteCount)
	goto ARRIVED;

MoveTo(Form1->iPotRouteX[Form1->iLastRoute],Form1->iPotRouteY[Form1->iLastRoute]);

Sleep(100);
goto LOOP;

COMING:

if(Form1->iLastRoute >= Form1->iPotRouteCount)
	Form1->iLastRoute -= 1;

if((int)GetDistX(MyPosX,MyPosY,Form1->iPotRouteX[Form1->iLastRoute],Form1->iPotRouteY[Form1->iLastRoute]) < 1)
	Form1->iLastRoute -= 1;

if(Form1->iLastRoute == -1)
	goto RETURNED;

MoveTo(Form1->iPotRouteX[Form1->iLastRoute],Form1->iPotRouteY[Form1->iLastRoute]);

Sleep(100);
goto LOOP;

ARRIVED:
PotBase = GetMobByName(Form1->sPotName,0);
if(!PotBase)goto RETURN;

PotID = *(WORD*)(PotBase + KO_MYID);

if(PotID){
memset(pBuf,0,20);
pIndex = 0;

dwPotNum = GetSlotID(0);

if(!dwPotNum){
	dwPotNum = ITEM_MP960;
	iPotSlot = 9;
}else{
	switch(dwPotNum){

	case ITEM_MP120:
	iPotSlot = 6;
	break;

	case ITEM_MP240:
	iPotSlot = 7;
	break;

	case ITEM_MP480:
	iPotSlot = 8;
	break;

	case ITEM_MP960:
	iPotSlot = 9;
	break;

	case ITEM_MP1920:
	iPotSlot = 10;
	break;

	default:
	iPotSlot = -1;
	break;

	}
}

if(iPotSlot == -1)
	goto RETURN;

pIndex = 0;
pSetBYTE(pBuf,pIndex,0x21);
pSetBYTE(pBuf,pIndex,0x01);
pSetDWORD(pBuf,pIndex,253000);
pSetWORD(pBuf,pIndex,PotID);
pSetDWORD(pBuf,pIndex,dwPotNum);
pSetBYTE(pBuf,pIndex,0x00);
pSetWORD(pBuf,pIndex,100);
pSetBYTE(pBuf,pIndex,0x00);
pSetBYTE(pBuf,pIndex,iPotSlot);
PSend(pBuf,17);

pIndex = 0;
pSetBYTE(pBuf,pIndex,0x6A);
pSetBYTE(pBuf,pIndex,0x02);
PSend(pBuf,2);
}

RETURN:
Form1->bPotGoing = false;
Form1->bPotComing = true;
Sleep(100);
goto LOOP;

RETURNED:
Form1->bPotGoing = false;
Form1->bPotComing = false;
Form1->bBotState = true;
Form1->bOnPotWay = false;
Form1->hPotThread = 0;
Form1->dwPotThread = 0;
bMSPaused = false;
return;
}

void __fastcall TForm1::btngetpotClick(TObject *Sender)
{
WORD ID	=	GetWORD(KO_TGID,1,0,0);
if(!ID)return;
char* Name = GetName(0,0,ID);
txtpot->Text = Name;
sPotName = Name;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chwhClick(TObject *Sender)
{
bWallHack = chwh->Checked;
DWORD TMP = *(DWORD*)(KO_CHAR);
if(bWallHack)
*(DWORD*)(TMP + KO_AUTH) = 0;
else
*(DWORD*)(TMP + KO_AUTH) = 1;
}
//---------------------------------------------------------------------------

void TForm1::MerkezAL(){
int PosX = (int)GetFLOAT(KO_POSX,1,0,0);
int PosY = (int)GetFLOAT(KO_POSY,1,0,0);
iCenterX = PosX;
iCenterY = PosY;

char* tmpX = intToChar(PosX,4,0);
size_t szX = strlen(tmpX);
char* tmpY = intToChar(PosY,4,0);
size_t szY = strlen(tmpY);

char Buf[10];
memset(Buf,0,10);
int BufIndex = 0;
pSetSTR(Buf,BufIndex,tmpX,szX);
pSetSTR(Buf,BufIndex,",",1);
pSetSTR(Buf,BufIndex,tmpY,szY);
lbcenter->Caption = Buf;
}

void __fastcall TForm1::btndelosClick(TObject *Sender)
{
BYTE DELOS[] = {0x55,0x02,0x10,0x37,0x30,0x30,0x31,0x5F,0x64,0x75,0x6E,0x67,0x65,0x75,0x6E,0x2E,0x6C,0x75,0x61};
PSend(DELOS,sizeof(DELOS));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btntradeClick(TObject *Sender)
{
WORD ID = GetWORD(KO_TGID,1,0,0);
char* pBuf;
int pIndex = 0;
pSetBYTE(pBuf,pIndex,0x30);
pSetBYTE(pBuf,pIndex,0x01);
pSetWORD(pBuf,pIndex,ID);
pSetBYTE(pBuf,pIndex,0x01);
PSend(pBuf,5);
}
//---------------------------------------------------------------------------


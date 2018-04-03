//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------

#define iBotDelay	1350

void BotFunction();
void InnFunction();
void SundFunction();
void GetPotFunction();
void MinorFunction();
void PotFunction();

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TCheckBox *chTop;
	TButton *btnOff;
	TButton *btnMin;
	TShape *shpbot;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TGroupBox *grpcast;
	TRadioButton *oparchery;
	TRadioButton *opperfect;
	TRadioButton *oparc;
	TGroupBox *grpkill;
	TRadioButton *opall;
	TRadioButton *oplist;
	TListBox *lstmob;
	TEdit *txtmob;
	TButton *btnadd;
	TButton *btnclear;
	TButton *btngetmob;
	TCheckBox *chlf;
	TCheckBox *chsprint;
	TCheckBox *chwolf;
	TCheckBox *chwh;
	TGroupBox *grploot;
	TCheckBox *chloot6;
	TCheckBox *chloot7;
	TCheckBox *chloot8;
	TGroupBox *grpsupply;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label1;
	TLabel *Label4;
	TEdit *txtinn;
	TButton *btngetinn;
	TEdit *txtsund;
	TButton *btngetsund;
	TListBox *lstinnroute;
	TListBox *lstsundroute;
	TButton *btnaddinn;
	TButton *btnaddsund;
	TButton *btnclearsund;
	TButton *btnclearinn;
	TCheckBox *chbuyarrow;
	TCheckBox *chbuywolf;
	TButton *btnsave1;
	TButton *btnsave2;
	TEdit *txtinvslot;
	TListBox *lstpotroute;
	TButton *btnclearpot;
	TButton *btnaddpot;
	TButton *btnsave3;
	TButton *btngetpot;
	TEdit *txtpot;
	TGroupBox *grpbot;
	TLabel *Label2;
	TLabel *lbcenter;
	TLabel *Label3;
	TButton *btngetcenter;
	TEdit *txtmaxgo;
	TCheckBox *chminor;
	TCheckBox *chusepot;
	TCheckBox *chgetpot;
	TButton *btnstart;
	TButton *btnstop;
	TTimer *tminncheck;
	TTimer *tmsundcheck;
	TTimer *tmminor;
	TTimer *tmpot;
	TTimer *tmlf;
	TTimer *tmpotcheck;
	TTabSheet *TabSheet2;
	TButton *btndelos;
	TButton *btntrade;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnMinClick(TObject *Sender);
	void __fastcall btnOffClick(TObject *Sender);
	void __fastcall chTopClick(TObject *Sender);
	void __fastcall oparcheryClick(TObject *Sender);
	void __fastcall opperfectClick(TObject *Sender);
	void __fastcall oparcClick(TObject *Sender);
	void __fastcall opallClick(TObject *Sender);
	void __fastcall oplistClick(TObject *Sender);
	void __fastcall btnclearClick(TObject *Sender);
	void __fastcall btnaddClick(TObject *Sender);
	void __fastcall chloot6Click(TObject *Sender);
	void __fastcall chloot7Click(TObject *Sender);
	void __fastcall chloot8Click(TObject *Sender);
	void __fastcall chbuyarrowClick(TObject *Sender);
	void __fastcall chbuywolfClick(TObject *Sender);
	void __fastcall btngetinnClick(TObject *Sender);
	void __fastcall btngetsundClick(TObject *Sender);
	void __fastcall btnclearinnClick(TObject *Sender);
	void __fastcall btnclearsundClick(TObject *Sender);
	void __fastcall btnaddinnClick(TObject *Sender);
	void __fastcall btnaddsundClick(TObject *Sender);
	void __fastcall btngetcenterClick(TObject *Sender);
	void __fastcall chminorClick(TObject *Sender);
	void __fastcall chusepotClick(TObject *Sender);
	void __fastcall chgetpotClick(TObject *Sender);
	void __fastcall btnstartClick(TObject *Sender);
	void __fastcall btnstopClick(TObject *Sender);
	void __fastcall btnsave1Click(TObject *Sender);
	void __fastcall btnsave2Click(TObject *Sender);
	void __fastcall btngetmobClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tminncheckTimer(TObject *Sender);
	void __fastcall tmsundcheckTimer(TObject *Sender);
	void __fastcall tmminorTimer(TObject *Sender);
	void __fastcall tmpotTimer(TObject *Sender);
	void __fastcall tmlfTimer(TObject *Sender);
	void __fastcall chlfClick(TObject *Sender);
	void __fastcall chsprintClick(TObject *Sender);
	void __fastcall chwolfClick(TObject *Sender);
	void __fastcall btnclearpotClick(TObject *Sender);
	void __fastcall btnaddpotClick(TObject *Sender);
	void __fastcall btnsave3Click(TObject *Sender);
	void __fastcall tmpotcheckTimer(TObject *Sender);
	void __fastcall btngetpotClick(TObject *Sender);
	void __fastcall chwhClick(TObject *Sender);
	void __fastcall btndelosClick(TObject *Sender);
	void __fastcall btntradeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	void PrepareValues();
	void LoadInnRoute();
	void LoadSundRoute();
	void LoadPotRoute();
	void RefreshRoutes();
	void MerkezAL();
	bool bMinState;
	DWORD dwCastID;
	bool bKillAll;
	int iMobCount;
	char* sMobList[5];
	bool bLoot6;
	bool bLoot7;
	bool bLoot8;
	char* sInnName;
	char* sSundName;
	char* sPotName;
	int iInnRouteCount;
	int iSundRouteCount;
	int iPotRouteCount;
	int* iInnRouteX;
	int* iInnRouteY;
	int* iSundRouteX;
	int* iSundRouteY;
	int* iPotRouteX;
	int* iPotRouteY;
	bool bBuyArrow;
	bool bBuyWolf;
	int iSupplySlot;
	int iCenterX;
	int iCenterY;
	int iMaxRadius;
	bool bMinor;
	bool bUsePot;
	bool bGetPot;
	bool bBotStarted;
	bool bBotState;
	HANDLE hBotThread;
	DWORD dwBotThread;
	HANDLE hInnThread;
	DWORD dwInnThread;
	HANDLE hSundThread;
	DWORD dwSundThread;
	HANDLE hPotThread;
	DWORD dwPotThread;
	bool bOnInnWay;
	bool bOnSundWay;
	bool bOnPotWay;
	int iLastRoute;
	bool bInnGoing;
	bool bInnComing;
	bool bInnRecv;
	bool bInnClosed;
	bool bSundGoing;
	bool bSundComing;
	bool bPotGoing;
	bool bPotComing;
	bool bLightFeet;
	bool bSprint;
	bool bWolf;
	bool bRPRRefreshed;
	bool bWallHack;

	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

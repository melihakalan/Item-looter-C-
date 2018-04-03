//---------------------------------------------------------------------------


#pragma hdrstop

#include "PriestParty.h"
#include "Main.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

DWORD GetPTCount(){
return *(DWORD*)(*(DWORD*)(*(DWORD*)(KO_PRTY) + 0x1C8) + 0x360);
}

DWORD GetPTUser(int UserNO){
if(!GetPTCount()) return 0;

DWORD Tmp=*(DWORD*)(KO_PRTY);
Tmp = *(DWORD*)(Tmp + 0x1C8);
Tmp = *(DWORD*)(Tmp + 0x35C);

int i=0;
for (i = 0; i < UserNO; i++) {
Tmp=*(DWORD*)(Tmp);
}

return Tmp;
}

DWORD GetPTUserBase(int UserNO){
if(!GetPTCount()) return 0;

DWORD Tmp=*(DWORD*)(KO_PRTY);
Tmp = *(DWORD*)(Tmp + 0x1C8);
Tmp = *(DWORD*)(Tmp + 0x35C);

int i=0;
for (i = 0; i < UserNO; i++) {
Tmp=*(DWORD*)(Tmp);
}
Tmp = *(DWORD*)(Tmp + KO_PT_ID);
Tmp = GetPlayerAdr(Tmp);
return Tmp;

}

bool IsWarrior(int ClassNum)
{
switch(ClassNum){
case 101:
case 105:
case 106:
case 201:
case 205:
case 206:
return true;
break;
default:
return false;
break;
}
return false;
}

bool IsPriest(int ClassNum)
{
switch(ClassNum){
case 104:
case 111:
case 112:
case 204:
case 211:
case 212:
return true;
break;
default:
return false;
break;
}
return false;
}

bool IsRogue(int ClassNum)
{
switch(ClassNum){
case 102:
case 107:
case 108:
case 202:
case 207:
case 208:
return true;
break;
default:
return false;
break;
}
return false;
}

bool IsMage(int ClassNum)
{
switch(ClassNum){
case 103:
case 109:
case 110:
case 203:
case 209:
case 210:
return true;
break;
default:
return false;
break;
}
return false;
}

char* CalcHealCast(int HP, int MAXHP)
{
int FARK=MAXHP-HP;
char* CastNum=NULL;

if(FARK<1) return CastNum;

if(FARK<=15) CastNum= "002";
if(FARK<=30) CastNum= "005";
if(FARK<=60) CastNum= "500";
if(FARK<=240) CastNum= "509";
if(FARK<=360) CastNum= "518";
if(FARK<=720) CastNum= "527";
if(FARK<=960) CastNum= "536";
if(FARK>960) CastNum= "545";

return CastNum;
}

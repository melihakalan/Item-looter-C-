//---------------------------------------------------------------------------


#pragma hdrstop

#include "Cast.h"
#include "Main.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

int GetCastCount(){
DWORD TMP = *(DWORD*)(KO_DLGA);
TMP = *(DWORD*)(TMP+0x1B4);
TMP = *(DWORD*)(TMP+0x4);
TMP = *(DWORD*)(TMP+0xD0);
return TMP;
}

DWORD GetCastID(int SkillNO){
if(!GetCastCount())return 0;
DWORD TMP = *(DWORD*)(KO_DLGA);
TMP = *(DWORD*)(TMP+0x1B4);
TMP = *(DWORD*)(TMP+0x4);
TMP = *(DWORD*)(TMP+0xCC);
for (int i = 1; i <= SkillNO; i++) {
TMP = *(DWORD*)(TMP);
}
TMP = *(DWORD*)(TMP+0x8);
if(TMP){
TMP = *(DWORD*)(TMP);
return TMP;
}
return 0;
}

bool CheckCast(DWORD CastID){
int count=GetCastCount();
if(!count) return false;

for (int i=0; i <= count; i++) {
if(GetCastID(i)==CastID) return true;
}
return false;
}

DWORD MakeSkillNum(char* LastID){
DWORD Tmp=GetDWORD(KO_CLSS,1,0,0);

char temp[6];
ultoa(Tmp,temp,10);

strcpy(temp+3,LastID);
Tmp=atol(temp);
return Tmp;
}

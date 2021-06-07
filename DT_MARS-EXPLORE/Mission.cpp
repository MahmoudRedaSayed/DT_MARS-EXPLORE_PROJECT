#include "Mission.h"
//Constructor
Mission::Mission(double TLOC_x, int MDUR_x, int SIG_x, int FD_x, int ID_x, Type_G type_of_mission_x)
{
	Set_TLOC(TLOC_x);
	Set_MDUR(MDUR_x);
	Set_SIG(SIG_x);
	Set_FD(FD_x);
	Set_ID(ID_x);
	Set_Rptr(nullptr);
	Set_type_of_mission(type_of_mission_x);
	WD = 0;
	ED = 0;
	CD = 0;
	Priority = 0;
}
//Setters 
void Mission::Set_TLOC(int x)
{
	TLOC = x > 0 ? x : 1;
}
void Mission::Set_MDUR(int x)
{
	MDUR = x > 0 ? x : 1;
}
void Mission::Set_SIG(int x)
{
	SIG = x >= 0 ? x : 0;
}
void Mission::Set_FD(int x)
{
	FD = x > 0 ? x : 1;
}
void Mission::Set_ID(int x)
{
	ID = x >= 0 ? x : 0;
}
void Mission::Set_type_of_mission(Type_G type_of_mission_x)
{
	type_of_mission = type_of_mission_x;
}
//void Mission::Set_ED(int x){}
void Mission::Set_Rptr(Rover* Rptr_x)
{
	Rptr = Rptr_x;
}
//Getters
int Mission::Get_TLOC()
{
	return TLOC;
}
int Mission::Get_MDUR()
{
	return MDUR;
}
int Mission::Get_SIG()
{
	return SIG;
}
int Mission::Get_FD()
{
	return FD;
}
//const int Mission::Get_TLOC()return TLOC;}
//const int Mission::Get_MDUR(){return MDUR;}
//const int Mission::Get_SIG(){return SIG;}
//const int Mission::Get_FD(){return FD;}
int Mission::Get_WD()
{
	return WD;
}
int Mission::Get_ED()
{
	return ED;
}
int Mission::Get_CD()
{
	return CD;
}
Rover* Mission::Get_Rptr()
{
	return Rptr;
}
const int Mission::Get_ID()
{
	return ID;
}
Type_G Mission::Get_type_of_mission()
{
	return type_of_mission;
}
double Mission::Get_Priority()
{
	return Priority;
}
//Calculation
int Mission::Calculate_CD()
{
	Calculate_ED();
	CD = FD + ED + WD;
	return CD;
}
double Mission::Calculate_CD_Priority()
{
	CD = Calculate_CD();
	return -CD;
}
double Mission::Calculate_ED_Priority()
{
	Calculate_ED();
	return -ED;
}
int Mission::Calculate_WD(int CurrDay)
{
	WD = CurrDay - FD;
	return WD;
}
int Mission::Calculate_ED()
{

	ED = 2 * ((TLOC / Rptr->GetSpeed()) / 25) + MDUR;
	return ED;
}
double Mission::Calculate_priority()
{
	Priority = (10*SIG) + (TLOC / 100.0) + (MDUR)-(FD);//Priority equation
	return Priority;
}
//Counters
int Mission::NumOfMMissions = 0;
int Mission::NumOfEMissions = 0;
int Mission::NumOfPMissions = 0;
int Mission::NumOfAutoPMissions = 0;
int Mission::AutoP = 0;
int Mission::NumOfNoNAutoPMissions = 0;
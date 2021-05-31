#include "Mission.h"
Mission::Mission(double TLOC_x, int MDUR_x, int SIG_x, int FD_x, int ID_x, Type_G type_of_mission_x)
//N:we will not send WD ,ED ,CD as a parameters as theu will caculated later
//?should i make those paramter const int ?
//?should we delete int FD_x from the parameters?
//?no e7tmal that at the same time mission is being created that it will be assign to a rover ? i mean we will not right a Rptr_x as a peremeter to the constructor right?
	:TLOC(TLOC_x >= 0 ? TLOC_x : 0),//?>=0 or > only? for all the following??
	MDUR(MDUR_x > 0 ? MDUR_x : 0),
	SIG(SIG_x >= 0 ? SIG_x : 0),
	FD(FD_x > 0 ? FD_x : 0),
	ID(ID_x > 0 ? ID_x : 0)
{
	/*Set_TLOC(TLOC_x);
	Set_MDUR(MDUR_x);
	Set_SIG(SIG_x);
	Set_FD(FD_x);
	Set_ID(ID_x);*/
	//Rptr=nullptr;
	//Set_Rptr(Rptr_x);
	type_of_mission = type_of_mission_x;
	Rptr = nullptr;
	WD = 0;
	ED = 0;
	CD = 0;
	//i think the previous 3 lines are not important
}
//Setters functions
void Mission::Set_TLOC(int x)
{
	TLOC = x >= 0 ? x : 0;
}
void Mission::Set_MDUR(int x)
{
	MDUR = x >= 0 ? x : 0;
}
void Mission::Set_SIG(int x)
{
	SIG = x >= 0 ? x : 0;
}
void Mission::Set_FD(int x)
{
	FD = x >= 0 ? x : 0;
}
void Mission::Set_ID(int x)
{
	ID = x >= 0 ? x : 0;
}
int Mission::Calculate_WD(int CurrDay)
{
	WD = CurrDay - FD;
	return WD;
}
//void Mission::Set_ED(int x)//I think no need to this function
//{
//
//}
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
//
//const int Mission::Get_TLOC()
//{
//	return TLOC;
//}
//const int Mission::Get_MDUR()
//{
//	return MDUR;
//}
//const int Mission::Get_SIG()
//{
//	return SIG;
//}
//const int Mission::Get_FD()
//{
//	return FD;
//}


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
//Others
int Mission::Calculate_ED()
{

	ED = 2 * ((TLOC / Rptr->GetSpeed()) / 25) + MDUR;////Later as i need Rptr to be defined
	//? should I make ED and CD double?or it is ok to make integer divion TLOC/Rptr? 
	// ?or make (double)TLOC/Rptr then use a math built in library fun that bt2rab el result l el num el int ely b3do?ex 1.3->2 or 1.6->2....
	return ED;//?should we just call Get_ED here? 
}

//Rover Ass_Rptr(Rover Rptr_x)
//{
//	Rptr = Rptr_x;//? no need to copy right?
//}

//////////////////////////////
	//Mountain.h
int Mission::NumOfMMissions = 0;
int Mission::NumOfAutoPMissions = 0;
int Mission::AutoP = 0;
//////////////////////////////
	//Emergency.h
double Mission::Get_Priority()
{
	return Priority;
}
/*
void Mission::Cal_Prirority()
{
	Priority = Get_SIG() * Get_TLOC() * Get_MDUR() / Get_FD();
}*/
double Mission::Calculate_priority()
{
	Priority = SIG * TLOC * MDUR / FD;//equation m2ktaaa
	return Priority;
}
int Mission::NumOfEMissions = 0;
//////////////////////////////
	//Polar.h
int Mission::NumOfPMissions = 0;
///////////////////////////////
int Mission::NumOfNoNAutoPMissions = 0;
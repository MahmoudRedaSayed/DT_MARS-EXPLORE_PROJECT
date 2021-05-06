#include "Emergency_Mission.h"
Emergency_Mission::Emergency_Mission(int TLOC_x = 0, int MDUR_x = 0, int SIG_x = 0, int FD_x = 0, int ID_x = 0)
	:Mission(TLOC_x, MDUR_x, SIG_x, FD_x, ID_x)
{
	NumOfEMissions++;
	Priority = SIG_x* TLOC_x* MDUR_x / FD_x;//equation m2ktaaa
}
//Setters
//void Emergency_Mission::Set_Priority(double x)
//{
//
//}

//Getters
double Emergency_Mission::Get_Priority()
{
	return Priority;
}
void Emergency_Mission::Cal_Prirority()
{
	Priority = Get_SIG() * Get_TLOC() * Get_MDUR() / Get_FD();
}
//double Emergency_Mission::Calculate_priority()
//{
//	//by eng sabry and eng reda
//}
int Emergency_Mission::NumOfEMissions = 0;
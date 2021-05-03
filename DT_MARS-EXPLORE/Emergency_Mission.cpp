#include "Emergency_Mission.h"
Emergency_Mission::Emergency_Mission(int TLOC_x, int MDUR_x, int SIG_x, int FD_x, int ID_x)
	:Mission(TLOC_x, MDUR_x, SIG_x, FD_x, ID_x)
{
	NumOfEMissions++;
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
double Emergency_Mission::Calculate_priority()
{
	//by eng sabry and eng reda
}
int Emergency_Mission::NumOfEMissions = 0;
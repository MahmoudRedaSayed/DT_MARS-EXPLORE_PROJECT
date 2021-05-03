#include "Polar_Mission.h"

Polar_Mission::Polar_Mission(int TLOC_x, int MDUR_x, int SIG_x, int FD_x, int ID_x)
	:Mission(TLOC_x, MDUR_x, SIG_x, FD_x, ID_x)
{
	NumOfPMissions++;
}
int Polar_Mission::NumOfPMissions = 0;
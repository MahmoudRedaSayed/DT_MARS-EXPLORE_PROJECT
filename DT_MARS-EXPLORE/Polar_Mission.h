#pragma once
#include "Mission.h"
class Polar_Mission :
    public Mission
{
private:
    static int NumOfPMissions;
public:
    Polar_Mission(double TLOC_x, int MDUR_x, int SIG_x, int FD_x, int ID_x);
};


#pragma once
#include "Mission.h"
class Mountainous_Mission :
    public Mission
{
private:
   static const int AutoP;
   static int NumOfMMissions;
   static int NumOfAutoPMissions;//?check if we need Promoted events also with AutoP??
public:
    Mountainous_Mission(int TLOC_x, int MDUR_x, int SIG_x, int FD_x, int ID_x);

    //Setters
    //void Set_AutoP(int x);

    //Getters
   // const int Get_AutoP();

};


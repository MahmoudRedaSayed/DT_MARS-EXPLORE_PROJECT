#pragma once
#include "Mission.h"
class Emergency_Mission :
    public Mission
{
private:
    double Priority;//??should i make it double??
    
public:
    Emergency_Mission(int TLOC_x, int MDUR_x, int SIG_x, int FD_x, int ID_x);//?priority will not be a parameter as it calculated then?
    //Setters
    //void Set_Priority(double x);

    //Getters
    double Get_Priority();//?no need for it?

   // double Calculate_priority();//?should i make it void as its funtionality is calculating?
                                //?should i uncomment Set_Priority and use it inside this mem func?

    static int NumOfEMissions;

};


#pragma once
#include "Rover.h"
class Emergency_Rover :
    public Rover
{
private:
    static int E_Rover_Count;    //Polar. Rovers count for file output
    static int Check_ER;        //The duration (in days) of checkups that an **Emergency** rover rover needs 
                               //to perform after completing N missions.
public:
    Emergency_Rover(float Rover_Speed)
        :Rover(Rover_Speed) {
        E_Rover_Count++;
    }
    ~Emergency_Rover() {}
    //static members getters
    static const int GetE_Rover_Count() { return E_Rover_Count; }
    static const int GetCheck_ER() { return Check_ER; }
    //static setter for CheckUp Duration
    static void SetCheck_ER(int c) { Check_ER = c > 0 ? c : 5; } // Let Default checkup duration = 5 days
};
//static members initializers
int Emergency_Rover::E_Rover_Count = 0;
int Emergency_Rover::Check_ER = 5;


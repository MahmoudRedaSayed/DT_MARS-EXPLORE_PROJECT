#pragma once
#include "Rover.h"
class Mountaionous_Rover :
    public Rover
{
private:
    static int M_Rover_Count;    //Mount. Rovers count for file output
    static int Check_MR;        //The duration (in days) of checkups that a **Mountaionous** rover needs 
                               //to perform after completing N missions.
public:
    Mountaionous_Rover(float Rover_Speed)
        :Rover(Rover_Speed){
        M_Rover_Count++;
    }
    ~Mountaionous_Rover() {}
    //static members getters
    static const int GetM_Rover_Count() { return M_Rover_Count; }
    static const int GetCheck_MR() { return Check_MR; }
    //static setter for CheckUp Duration
    static void SetCheck_MR(int c) { Check_MR = c>0?c:5; } // Let Default checkup duration = 5 days
};
//static members initializers
int Mountaionous_Rover::M_Rover_Count = 0;
int Mountaionous_Rover::Check_MR = 5;
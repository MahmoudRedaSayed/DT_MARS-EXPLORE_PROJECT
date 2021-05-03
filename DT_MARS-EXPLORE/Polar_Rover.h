#pragma once
#include "Rover.h"
class Polar_Rover :
    public Rover
{
private:
    static int P_Rover_Count ;   //Polar. Rovers count for file output
    static int Check_PR;        //The duration (in days) of checkups that a **Polar** rover needs 
                               //to perform after completing N missions.
public:
    Polar_Rover(float Rover_Speed)
        :Rover(Rover_Speed) {
        P_Rover_Count++;
    }
    ~Polar_Rover() {}
    //static members getters
    static const int GetP_Rover_Count() { return P_Rover_Count; }
    static const int GetCheck_PR() { return Check_PR; }
    //static setter for CheckUp Duration
    static void SetCheck_PR(int c) { Check_PR = c > 0 ? c : 5; } // Let Default checkup duration = 5 days
};
//static members initializers
int Polar_Rover::P_Rover_Count = 0;
int Polar_Rover::Check_PR = 5;

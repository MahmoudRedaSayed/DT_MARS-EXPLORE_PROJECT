#pragma once
#include "Event.h"
#include"Mission.h"
class Formulaion_Event :
    public Event
{private:
    char Mission_Type;
    double TLOC;
    int MDUR;
    int SIG;
public:
    Formulaion_Event(char type,int Location,int Duration,int sig, int id, int ED);
    //setters function to set the values when we read the input file
    void Set_Mission_Type(char type);
   void Set_TLOC(int Location);
    void Set_MDUR(int Duration);
    void Set_SIG(int sig);
    //execute function that will create the missions  
    void Execute(PriorityQueue<Emergency_Mission*>& Eme_Missions, LinkedQueue<Polar_Mission*>& Pol_Missions, LinkedQueue<Mountainous_Mission*>& Mou_Missions);
};


#pragma once
#include "Event.h"
#include"LinkedQueue.h"
#include"Mountainous_Mission.h"
class Cancellation_Event :
    public Event
{

public:
    Cancellation_Event(int id,int ED);
    void Execute(PriorityQueue<Emergency_Mission*>& Eme_Missions, LinkedQueue<Polar_Mission*>& Pol_Missions, LinkedQueue<Mountainous_Mission*>& Mou_Missions);
    ~Cancellation_Event();
};


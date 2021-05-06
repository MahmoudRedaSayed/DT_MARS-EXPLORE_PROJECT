#pragma once
#include "Event.h"
class Promotion_Event :
    public Event
{public:
    Promotion_Event(int id, int ED);
    ~Promotion_Event();
    void Execute(PriorityQueue<Emergency_Mission*>& Eme_Missions, LinkedQueue<Polar_Mission*>& Pol_Missions, LinkedQueue<Mountainous_Mission*>& Mou_Missions);
};


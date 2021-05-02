#pragma once
#include "Event.h"
class Cancellation_Event :
    public Event
{public:
    Cancellation_Event(int id,int ED);
    void Execute();
    ~Cancellation_Event();
};


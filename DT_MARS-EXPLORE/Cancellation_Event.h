#pragma once
#include "Event.h"
class Cancellation_Event :
    public Event
{
    Cancellation_Event(int id,int ED);
    void Execute();
    ~Cancellation_Event();
};


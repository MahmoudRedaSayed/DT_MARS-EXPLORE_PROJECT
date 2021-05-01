#pragma once
#include "Event.h"
class Promotion_Event :
    public Event
{
    Promotion_Event(int id, int ED);
    ~Promotion_Event();
    void Execute();
};


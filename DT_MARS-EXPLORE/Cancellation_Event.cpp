#include "Cancellation_Event.h"

Cancellation_Event::Cancellation_Event(int id, int ED)
{
	Set_Event_Day(ED);
	Set_Mission_ID(id);
}
void Cancellation_Event::Execute()
{//need mission class
}

Cancellation_Event::~Cancellation_Event()
{
}

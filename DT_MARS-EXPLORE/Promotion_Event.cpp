#include "Promotion_Event.h"

Promotion_Event::Promotion_Event(int id, int ED)
{
	Set_Event_Day(ED);
	Set_Mission_ID(id);
}

Promotion_Event::~Promotion_Event()
{
}

void Promotion_Event::Execute()
{//need class mission
}

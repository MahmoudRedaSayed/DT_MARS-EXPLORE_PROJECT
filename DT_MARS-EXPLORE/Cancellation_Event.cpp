#include "Cancellation_Event.h"

Cancellation_Event::Cancellation_Event(int id, int ED)
{
	Set_Event_Day(ED);
	Set_Mission_ID(id);
}
////////////excaption handling if the id is not found//////////
bool Cancellation_Event::Execute(PriorityQueue<Mission*>& Eme_Missions, LinkedQueue<Mission*>& Pol_Missions, LinkedQueue<Mission*>& Mou_Missions)
{
	Mission* ITERATOR = NULL;// to make it first in first out
	Mission* ITERATOR2 = NULL;
	Mission* TOP = NULL;
	Mou_Missions.peek(TOP);
	if (TOP == nullptr)
	{
		return false;
	}
	if (TOP)
	{
		if (TOP->Get_ID() == Get_Mission_ID())
		{
			Mou_Missions.dequeue(TOP);
			delete TOP;
			return true;
		}
	}
	Mou_Missions.dequeue(TOP);
	Mou_Missions.enqueue(TOP);
	while (ITERATOR != TOP)
	{
		Mou_Missions.peek(ITERATOR);
		if (ITERATOR != TOP)
		{
			Mou_Missions.dequeue(ITERATOR);
		}
		else
		{
			break;
		}

		if (ITERATOR->Get_ID() == Get_Mission_ID())
		{

			ITERATOR2 = ITERATOR;
		}                                //And the value of the mission will be stored in pointer iterator 
		else
		{
			Mou_Missions.enqueue(ITERATOR);
		}
	}
	if (ITERATOR2)
	{
		delete ITERATOR2;
		return true;
	}
	return false;
}

Cancellation_Event::~Cancellation_Event()
{
}

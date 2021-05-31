#include "Cancellation_Event.h"

Cancellation_Event::Cancellation_Event(int id, int ED)
{
	Set_Event_Day(ED);
	Set_Mission_ID(id);
}
////////////excaption handling if the id is not found//////////
void Cancellation_Event::Execute(PriorityQueue<Mission*>& Eme_Missions, LinkedQueue<Mission*>& Pol_Missions, LinkedQueue<Mission*>& Mou_Missions)
{
	Mission* ITERATOR = NULL;
	Mission* TOP=NULL;
	Mou_Missions.peek(TOP);
	while (ITERATOR != TOP)
	{
		Mou_Missions.dequeue(ITERATOR);
		if (ITERATOR->Get_ID() == Get_Mission_ID())
			break;                                  //And the value of the mission will be stored in pointer iterator 
		else
		{
			Mou_Missions.enqueue(ITERATOR);
		}
	}
	if(ITERATOR)
	{
		delete ITERATOR;
	}
	
}

Cancellation_Event::~Cancellation_Event()
{	
}

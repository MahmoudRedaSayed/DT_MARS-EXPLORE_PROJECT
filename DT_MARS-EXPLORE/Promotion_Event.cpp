#include "Promotion_Event.h"

Promotion_Event::Promotion_Event(int id, int ED)
{
	Set_Event_Day(ED);
	Set_Mission_ID(id);
}

Promotion_Event::~Promotion_Event()
{
}
////////////excaption handling if the id is not found//////////
void Promotion_Event::Execute(PriorityQueue<Mission*>& Eme_Missions, LinkedQueue<Mission*>& Pol_Missions, LinkedQueue<Mission*>& Mou_Missions)
{
	Mission* ITERATOR=NULL;
	Mission* TOP=NULL;
	Mission* Promoted_Mission = new Mission();
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
	//Setting the data to the new mission rather than use a copy constructor
	if (ITERATOR) 
	{
		Promoted_Mission->Set_FD(ITERATOR->Get_FD());
		Promoted_Mission->Set_ID(ITERATOR->Get_ID());
		Promoted_Mission->Set_MDUR(ITERATOR->Get_MDUR());
		Promoted_Mission->Set_TLOC(ITERATOR->Get_TLOC());
		Promoted_Mission->Set_TLOC(ITERATOR->Get_TLOC());
		Promoted_Mission->Cal_Prirority();
		delete ITERATOR;
		Eme_Missions.enqueue(Promoted_Mission, Promoted_Mission->Get_Priority()); //Add the Mission to the emergency missions queue 
	}
}

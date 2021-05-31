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
		Mission* Promoted_Mission = new Mission(ITERATOR->Get_TLOC(),ITERATOR->Get_MDUR(), ITERATOR ->Get_SIG(),ITERATOR->Get_FD(), ITERATOR->Get_ID(), Emergency);
		delete ITERATOR;
		Eme_Missions.enqueue(Promoted_Mission, Promoted_Mission->Calculate_priority()); //Add the Mission to the emergency missions queue 
		Mission::NumOfEMissions++;
		Mission::NumOfNoNAutoPMissions++;
		Mission::NumOfMMissions--;
	}
}

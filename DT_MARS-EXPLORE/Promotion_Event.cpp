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
bool Promotion_Event::Execute(PriorityQueue<Mission*>& Eme_Missions, LinkedQueue<Mission*>& Pol_Missions, LinkedQueue<Mission*>& Mou_Missions)
{
	Mission* ITERATOR=NULL;
	Mission* ITERATOR2 = NULL;
	Mission* TOP=NULL;
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
			Mission* Promoted_Mission = new Mission(TOP->Get_TLOC(), TOP->Get_MDUR(), TOP->Get_SIG(), TOP->Get_FD(), TOP->Get_ID(), Emergency);
			delete TOP;
			Eme_Missions.enqueue(Promoted_Mission, Promoted_Mission->Calculate_priority()); //Add the Mission to the emergency missions queue 
			Mission::NumOfEMissions++;
			Mission::NumOfNoNAutoPMissions++;
			Mission::NumOfMMissions--;
			return true;
		}
	}

	while (ITERATOR != TOP)
	{
		Mou_Missions.dequeue(ITERATOR);
		if (ITERATOR->Get_ID() == Get_Mission_ID())
		{
			ITERATOR2 = ITERATOR;
		}                                //And the value of the mission will be stored in pointer iterator2 
		else
		{
			Mou_Missions.enqueue(ITERATOR);
		}
	}
	//Setting the data to the new mission rather than use a copy constructor
	if (ITERATOR2) 
	{
		Mission* Promoted_Mission = new Mission(ITERATOR2->Get_TLOC(),ITERATOR2->Get_MDUR(), ITERATOR2 ->Get_SIG(),ITERATOR2->Get_FD(), ITERATOR2->Get_ID(), Emergency);
		delete ITERATOR2;
		Eme_Missions.enqueue(Promoted_Mission, Promoted_Mission->Calculate_priority()); //Add the Mission to the emergency missions queue 
		Mission::NumOfEMissions++;
		Mission::NumOfNoNAutoPMissions++;
		Mission::NumOfMMissions--;
		return true;
	}
	return false;
}

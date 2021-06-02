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
			TOP->Set_type_of_mission(Emergency);
			Eme_Missions.enqueue(TOP, TOP->Calculate_priority()); //Add the Mission to the emergency missions queue 
			Mission::NumOfEMissions++;
			Mission::NumOfNoNAutoPMissions++;
			Mission::NumOfMMissions--;
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
		}                                //And the value of the mission will be stored in pointer iterator2 
		else
		{
			Mou_Missions.enqueue(ITERATOR);
		}
	}
	//Setting the data to the new mission rather than use a copy constructor
	if (ITERATOR2) 
	{
		Eme_Missions.enqueue(ITERATOR2, ITERATOR2->Calculate_priority()); //Add the Mission to the emergency missions queue 
		Mission::NumOfEMissions++;
		Mission::NumOfNoNAutoPMissions++;
		Mission::NumOfMMissions--;
		return true;
	}
	return false;
}

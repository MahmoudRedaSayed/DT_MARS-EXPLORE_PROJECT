#pragma once
#include "Event.h"
class Promotion_Event :
	public Event
{
public:
	Promotion_Event(int id, int ED);
	~Promotion_Event();
	bool Execute(PriorityQueue<Mission*>& Eme_Missions, LinkedQueue<Mission*>& Pol_Missions, LinkedQueue<Mission*>& Mou_Missions);
};


#pragma once
#include"Emergency_Mission.h"
#include"Mountainous_Mission.h"
#include"Polar_Mission.h"
#include"LinkedQueue.h"
#include"PriorityQueue.h"
#include"Mission.h"
class Event
{
private:
	int Event_Day;
	int Mission_ID;
public:
	//////////////////// constructor to initializing the data member to avoid the warnings////////////////
	Event();
	//pure virtual function to the execute function to can be implamented in each drived class
	virtual bool Execute(PriorityQueue<Mission*>& Eme_Missions, LinkedQueue<Mission*>& Pol_Missions, LinkedQueue<Mission*>& Mou_Missions) = 0;
	//getters because this data can not be accesse in the drived classes 
	int Get_Mission_ID();
	int Get_Event_Day();
	//setters functions
	void Set_Mission_ID(int id);
	void Set_Event_Day(int day);
};


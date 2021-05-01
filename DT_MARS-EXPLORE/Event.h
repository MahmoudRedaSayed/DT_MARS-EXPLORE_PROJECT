#pragma once
class Event
{private:
	int Event_Day;
	int Mission_ID;
public:
//pure virtual function to the execute function to can be implamented in each drived class
	virtual void Execute() = 0;
	//getters because this data can not be accesse in the drived classes 
	int Get_Mission_ID();
	int Get_Event_Day();
	//setters functions
	void Set_Mission_ID(int id);
	void Set_Event_Day(int day);
};


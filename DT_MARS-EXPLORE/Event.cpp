#include "Event.h"
#include<iostream>
using namespace std;
int Event::Get_Mission_ID()
{
    return Mission_ID;
}

int Event::Get_Event_Day()
{
    return Event_Day;
}

void Event::Set_Mission_ID(int id)
{
    if (id > 0)
        Mission_ID = id;
    else cout << "Error:the id value not valid" << endl;
}

void Event::Set_Event_Day(int day)
{
    if (day > 0)
        Event_Day = day;
    else cout << "Error:the value of the event day is not valid" << endl;
}

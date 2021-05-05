#include "MarsStation_Class.h"

//////////////// ASsign Emergency Missions using Priority Queue (Linked List) //////////////////////////
void MarsStation_Class::Assign_E_Missions()
{
	if (Available_ER.isEmpty() && Available_PR.isEmpty() && Available_MR.isEmpty())
	{
		return;
	}
	else
	{
		Emergency_Mission* Emergence_mission;
		Emergency_Rover* E_Rover;
		Mountaionous_Rover* M_Rover;
		Polar_Rover* P_Rover;
		while (EMission.peek(Emergence_mission))
		{
			if (Available_ER.dequeue(E_Rover))
			{

			}
			else if (Available_MR.dequeue(M_Rover))
			{

			}
			else
			{
				Available_PR.dequeue(P_Rover);
			}
		}
	}
}
/*
void MarsStation_Class::Assign_M_M()
{
	//23ml auto promoted b3d el assign el 3ady?
	Mountainous_Mission* MMptr;
	//M_Mission.peek(MMptr)
	while (!M_Mission.isEmpty()&& !Available_MR.isEmpty())
	{
		//if()
		M_Mission.dequeue(MMptr);
		MMptr->Calculate_WD(Day_count);
		EXMission.enqueue(MMptr);
	}

	

}*/

int MarsStation_Class::Day_count = 0;

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

void MarsStation_Class::Assign_M_M()
{
	//23ml auto promoted b3d el assign el 3ady?
	Mountainous_Mission* MMptr;
	Rover* ARptr;
	//M_Mission.peek(MMptr)
	while (!M_Mission.isEmpty()&& !Available_MR.isEmpty())
	{
		//if()
		M_Mission.dequeue(MMptr);
		Available_MR.dequeue(ARptr);//??
		MMptr->Calculate_WD(Day_count);
		MMptr->Set_Rptr(ARptr);
		EXMission.enqueue(MMptr, MMptr->Calculate_CD());

	}
	while (!M_Mission.isEmpty() && !Available_ER.isEmpty())
	{
		M_Mission.dequeue(MMptr);
		Available_ER.dequeue(ARptr);//??
		MMptr->Calculate_WD(Day_count);
		MMptr->Set_Rptr(ARptr);
		EXMission.enqueue(MMptr, MMptr->Calculate_CD());

	}



}

void MarsStation_Class::Assign_All_Mission()
{
	Auto_Promoting();/////?is it will be like that at the first before any assign???
	Assign_E_M();
	Assign_M_M();
	Assign_P_M();
}

void MarsStation_Class::Auto_Promoting()
{
	Mountainous_Mission* MMptr;
	Emergency_Mission* EMptr;

	while (!M_Mission.isEmpty())
	{
		M_Mission.peek(MMptr);
		if (MMptr->Calculate_WD(Day_count)== Mountainous_Mission::AutoP)
		{
			M_Mission.dequeue(MMptr);
			EMptr = new Emergency_Mission(MMptr->Get_TLOC(), MMptr->Get_MDUR(), MMptr->Get_SIG(), MMptr->Get_FD(), MMptr->Get_ID());
			EMission.enqueue(EMptr, EMptr->Get_Priority());
			Mountainous_Mission::NumOfAutoPMissions++;
			Mountainous_Mission::NumOfMMissions--;
			//D.F to add NumOfAutoPMissions with NumOfMMissions to get num of totall m mission to calculat el nsba el m2wya for ayto promoting in output file
			delete MMptr;//?delete in general and null errors......
		}
		else
			break;//or return
	}


}

int MarsStation_Class::Day_count = 0;

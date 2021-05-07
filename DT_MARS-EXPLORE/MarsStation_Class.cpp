#include "MarsStation_Class.h"
#include"Event.h"
#include"Formulaion_Event.h"
#include"Cancellation_Event.h"
#include"Promotion_Event.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
MarsStation_Class::MarsStation_Class()
{
}
//////////////// ASsign Emergency Missions using Priority Queue (Linked List) //////////////////////////
void MarsStation_Class::Assign_E_M()
{
	if (Available_ER.isEmpty() && Available_PR.isEmpty() && Available_MR.isEmpty())
	{
		return;
	}
	else
	{
		Emergency_Mission* Emergence_mission;
		Rover* E_Rover;
		Rover* M_Rover;                //// pointer to rovers
		Rover* P_Rover;
		while (E_Mission.dequeue(Emergence_mission)) 
		{
			if (Available_ER.dequeue(E_Rover))      ///// Check Emergency Rover list first
			{
				Emergence_mission->Set_Rptr(E_Rover);
			}
			else if (Available_MR.dequeue(M_Rover)) ///// Check Mountainous Rover list second
			{
				Emergence_mission->Set_Rptr(M_Rover);
			}
			else                                     ///// Check Polar Rover list Last
			{
				Available_PR.dequeue(P_Rover);
				Emergence_mission->Set_Rptr(P_Rover);
			}
			Emergence_mission->Calculate_WD(Day_count); ///// Add Mission from available to Excution Mission list 
			EX_Mission.enqueue(Emergence_mission, Emergence_mission->Calculate_CD());
		}
	}
}
void MarsStation_Class::Assign_P_M()
{
	if (Available_PR.isEmpty())
		return;
	else
	{
		Polar_Mission* Polar_mission;
		Rover* P_Rover;
		while (P_Mission.dequeue(Polar_mission))
		{
			if (Available_PR.dequeue(P_Rover))      ///// Check Emergency Rover list first
			{
				Polar_mission->Set_Rptr(P_Rover);
			}
			Polar_mission->Calculate_WD(Day_count); ///// Add Mission from available to Excution Mission list 
			EX_Mission.enqueue(Polar_mission, Polar_mission->Calculate_CD());
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
		ARptr->Increment_Mission_Count();
		MMptr->Calculate_WD(Day_count);
		MMptr->Set_Rptr(ARptr);
		EX_Mission.enqueue(MMptr, MMptr->Calculate_CD());

	}
	while (!M_Mission.isEmpty() && !Available_ER.isEmpty())
	{
		M_Mission.dequeue(MMptr);
		Available_ER.dequeue(ARptr);//??
		ARptr->Increment_Mission_Count();
		MMptr->Calculate_WD(Day_count);
		MMptr->Set_Rptr(ARptr);
		EX_Mission.enqueue(MMptr, MMptr->Calculate_CD());

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
			E_Mission.enqueue(EMptr, EMptr->Get_Priority());
			Mountainous_Mission::NumOfAutoPMissions++;
			Mountainous_Mission::NumOfMMissions--;
			//D.F to add NumOfAutoPMissions with NumOfMMissions to get num of totall m mission to calculat el nsba el m2wya for ayto promoting in output file
			delete MMptr;//?delete in general and null errors......
		}
		else
			break;//or return
	}


}


void MarsStation_Class::Check_MR_State(Rover* CMRptr)
{
	//dynamicM_Rover_Count
	if (CMRptr->GetMission_Count() == Rover::GetM_Rover_Count())
	{
		Check_up_MR.enqueue(CMRptr);
		//Rover::GetCheck_MR();
		CMRptr->Set_Day_out(Rover::GetCheck_MR()+Day_count);
	}
	else
	{
		Available_MR.enqueue(CMRptr);
	}

}
//check rover satutes

void MarsStation_Class::Check_ER_State(Rover* CERptr)
{
	//dynamicM_Rover_Count
	if (CERptr->GetMission_Count() == Rover::GetE_Rover_Count())
	{
		Check_up_ER.enqueue(CERptr);
		CERptr->Set_Day_out(Rover::GetCheck_ER() + Day_count);
	}
	else
	{
		Available_ER.enqueue(CERptr);
	}

}

void MarsStation_Class::Check_PR_State(Rover* CPRptr)
{
	//dynamicM_Rover_Count
	if (CPRptr->GetMission_Count() == Rover::GetP_Rover_Count())
	{
		Check_up_PR.enqueue(CPRptr);
		CPRptr->Set_Day_out(Rover::GetCheck_PR() + Day_count);
	}
	else
	{
		Available_PR.enqueue(CPRptr);
	}

}

void MarsStation_Class::Program_Startup()
{
	string File_Name,Line, ed=" ", id=" ", tolc=" ", mdur=" ", sig=" ";
	char Type_Event, Type_Mission;
	int Num_E_Rovers, Num_P_Rovers, Num_M_Rovers;
	int Num_Rovers;
	 int Check_UP_E_Rover;
	 int Check_UP_M_Rover;
	 int Check_UP_P_Rover;
	 int Missions_Before_Check_up;
	 int Auto_Promotion;
	 int Num_Event;
	 int j,ED,ID,TOLC,MDUR,SIG;
	cout << "Please::enter the name of the file the you want to load it" << endl;
	cin >> File_Name;
	ifstream My_File;
	My_File.open("\Files\\"+File_Name+".txt");
	if (My_File.is_open())                       //Check if the file is found or not
	{
		My_File>> Num_M_Rovers>>Num_P_Rovers>>Num_E_Rovers;
		{ /*creating the rovers*/}
		Num_Rovers = Num_E_Rovers + Num_P_Rovers + Num_M_Rovers;
		//////////////////////Read the speed of the rover///////////////
		getline(My_File, Line);
		if (Line.size() == ((2 * Num_Rovers) - 1))        //The case of the different speeds
		{
		}
		else
		{
		}
		My_File >> Missions_Before_Check_up >> Check_UP_M_Rover >> Check_UP_P_Rover >> Check_UP_E_Rover;
		             ///////////////need to the the values to the rovers ///////////////
		My_File>>Auto_Promotion;                //The value of the auto promotion limit
		My_File>>Num_Event;                       //The number of events
		for (int i = 0; i < Num_Event; i++)         //Loop to fill the list of the events
		{
			j = 0;
			getline(My_File, Line);                   //The line of the event data
			Type_Event= Line[j];                        //type of the event formulation or promotion or cancellation  
			if (Type_Event == 'F')
			{
				j++;
				while (Line[j] == ' ')
				{
					j++;
				}
				Type_Mission = Line[j];                       //type of the mission Em or moun or polar
				j++;
				while (Line[j] == ' ')
				{
					j++;
				}
				ed = Line[j];
				ED = stoi(ed);
				j++;
				while (Line[j] == ' ')
				{
					j++;
				}
				id = Line[j];
				ID = stoi(id);
				j++;
				while (Line[j] == ' ')
				{
					j++;
				}
				tolc = Line[j];
				TOLC = stoi(tolc);
				j++;
				while (Line[j] == ' ')
				{
					j++;
				}
				mdur = Line[j];
				MDUR = stoi(mdur);
				j++;
				while (Line[j] == ' ')
				{
					j++;
				}
				sig = Line[j];
				SIG = stoi(sig);
			}
			else if (Type_Event == 'P' || Type_Event == 'C')
			{
				j++;
				while (Line[j] == ' ')
				{
					j++;
				}
				ed = Line[j];
				ED = stoi(ed);
				j++;
				while (Line[j] == ' ')
				{
					j++;
				}
				id = Line[j];
				ID = stoi(id);
			}
			                              //////////////Creating the events/////////////
			if (Type_Event == 'P')
			{
				Promotion_Event Pro_Event(ID,ED);
				Event* PTR_Event = &Pro_Event;
				Events_List.enqueue(PTR_Event);
			}
			if (Type_Event == 'F')
			{
				Formulaion_Event For_Event(Type_Mission,TOLC,MDUR,SIG,ID,ED);
				Event* PTR_Event = &For_Event;
				Events_List.enqueue(PTR_Event);
			}
			if (Type_Event == 'C')
			{
				Cancellation_Event Can_Event(ID, ED);
				Event* PTR_Event = &Can_Event;
				Events_List.enqueue(PTR_Event);
			}
			ed = " ", id = " ", tolc = " ", mdur = " ", sig = " ";

		}

		                                   
	}













}

void MarsStation_Class::Check_Up_to_Available_M()
{
	Rover* MMptr;
	Check_up_MR.peek(MMptr);
	while (MMptr->Get_Day_out() == Day_count)
	{
		Check_up_MR.dequeue(MMptr);
		Available_MR.enqueue(MMptr);
		Check_up_MR.peek(MMptr);
	}
}
void MarsStation_Class::Check_Up_to_Available_E()
{
	Rover* EMptr;
	Check_up_ER.peek(EMptr);
	while (EMptr->Get_Day_out() == Day_count)
	{
		Check_up_ER.dequeue(EMptr);
		Available_ER.enqueue(EMptr);
		Check_up_ER.peek(EMptr);
	}

}
void MarsStation_Class::Check_Up_to_Available_P()
{
	Rover* PMptr;
	Check_up_PR.peek(PMptr);
	while (PMptr->Get_Day_out() == Day_count)
	{
		Check_up_PR.dequeue(PMptr);
		Available_PR.enqueue(PMptr);
		Check_up_PR.peek(PMptr);
	}

}








int MarsStation_Class::Day_count = 0;

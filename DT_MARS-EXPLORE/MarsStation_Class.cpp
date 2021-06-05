#include "MarsStation_Class.h"
#include"Event.h"
#include"Formulaion_Event.h"
#include"Cancellation_Event.h"
#include"Promotion_Event.h"
#include"Mountainous_Mission.h"
#include"Rover.h"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;
int  MarsStation_Class::files_Count = 0;//#files to be created for output(#user operations), needs discussion with team

int MarsStation_Class::Get_Day_count()
{
	return Day_count;
}

MarsStation_Class::MarsStation_Class()
	:WD_SUM(0), ED_SUM(0)
{
	files_Count++;
}
void MarsStation_Class::increment_day()
{
	Day_count++;
}
/////////////// Execute Events /////////////////
void MarsStation_Class::Execute()
{
	Event* event;
	while (Events_List.peek(event))
	{
		if (event->Get_Event_Day() == Day_count)
		{
			Events_List.dequeue(event);
			Formulaion_Event* temp_event = dynamic_cast<Formulaion_Event*> (event);
			Cancellation_Event* temp_event2 = dynamic_cast<Cancellation_Event*> (event);
			if (temp_event)
			{
				event->Execute(E_Mission, P_Mission, M_Mission);
				MarsStation_Class::waiting_missions_count++;
			}
			else if (temp_event2)
			{
				if (event->Execute(E_Mission, P_Mission, M_Mission))
				{
					MarsStation_Class::waiting_missions_count--;
				}
			}
			else
			{
				event->Execute(E_Mission, P_Mission, M_Mission);
			}
	
			delete event; // we don't need created object of Event so we delete it
			// What about dynamic cast , did object is deleted Completely or need dynamic cast ?!
		}
		else
		{
			break;
		}
	}
}
//////////////// Assign Emergency Missions using Priority Queue (Linked List) //////////////////////////
void MarsStation_Class::Assign_Mission_to_QueueRover(int& Counter,LinkedQueue<Mission*>& availble_Mission_list,
				PriorityQueue<Mission*>& EX_Mission_list, PriorityQueue<Rover*>& Rover_list)
{
	Counter = 0;
	while (!availble_Mission_list.isEmpty() && !Rover_list.isEmpty())
	{
		Mission* mission;
		availble_Mission_list.dequeue(mission);
		Rover* rover;
		Rover_list.dequeue(rover);
		mission->Set_Rptr(rover);
		rover->SetIsAssigned(true);
		rover->Increment_Mission_Count();
		mission->Calculate_WD(Day_count); ///// Add Mission from available to Excution Mission list 
		rover->set_Mission_EXtime(mission->Calculate_ED());
		EX_Mission_list.enqueue(mission, mission->Calculate_CD_Priority()); //// note: sorted ascending 
		Counter++;
	}
}
void MarsStation_Class::Assign_Mission_to_PriorityQueueRover(int& Counter, LinkedQueue<Mission*>& availble_Mission_list,
	PriorityQueue<Mission*>& EX_Mission_list, LinkedQueue<Rover*>& Rover_list)
{
	Counter = 0;
	while (!availble_Mission_list.isEmpty() && !Rover_list.isEmpty())
	{
		Mission* mission;
		availble_Mission_list.dequeue(mission);
		Rover* rover;
		Rover_list.dequeue(rover);
		mission->Set_Rptr(rover);
		rover->SetIsAssigned(true);
		rover->Increment_Mission_Count();
		rover->SetSpeed(rover->GetSpeed() / 2);
		mission->Calculate_WD(Day_count); ///// Add Mission from available to Excution Mission list 
		rover->set_Mission_EXtime(mission->Calculate_ED());
		EX_Mission_list.enqueue(mission, mission->Calculate_CD_Priority()); //// note: sorted ascending 
		Counter++;
	}
}
void MarsStation_Class::Assign_E_M()
{
	/*
	if (Available_ER.isEmpty() && Available_PR.isEmpty() && Available_MR.isEmpty())
	{
		return;
	}
	else
	{
		Mission* Emergence_mission;
		Rover* E_Rover;
		Rover* M_Rover;                //// pointer to rovers
		Rover* P_Rover;
		while (E_Mission.dequeue(Emergence_mission))
		{
			if (Available_ER.dequeue(E_Rover))      ///// Check Emergency Rover list first
			{
				Emergence_mission->Set_Rptr(E_Rover);
				E_Rover->Increment_Mission_Count();
			}
			else if (Available_MR.dequeue(M_Rover)) ///// Check Mountainous Rover list second
			{
				Emergence_mission->Set_Rptr(M_Rover);
				M_Rover->Increment_Mission_Count();
			}
			else if (Available_PR.dequeue(P_Rover))                                    ///// Check Polar Rover list Last
			{
				Emergence_mission->Set_Rptr(P_Rover);
				P_Rover->Increment_Mission_Count();
			}
			else
			{
				return;
			}
			Emergence_mission->Calculate_WD(Day_count); ///// Add Mission from available to Excution Mission list 
			Emergency_EX_Mission.enqueue(Emergence_mission, Emergence_mission->Calculate_CD_Priority());
		}
	}
	*/
	while (!E_Mission.isEmpty() &&(!Available_ER.isEmpty() || !Available_PR.isEmpty() || !Available_MR.isEmpty()))
	{
		Mission* Emergence_mission;
		Rover* rover;
		E_Mission.dequeue(Emergence_mission);
		if (Available_ER.dequeue(rover))      ///// Check Emergency Rover list first
		{
			//rover->SetIsAssigned(true);
			Emergence_mission->Set_Rptr(rover);
			rover->Increment_Mission_Count();
		}
		else if (Available_MR.dequeue(rover)) ///// Check Mountainous Rover list second
		{
			Emergence_mission->Set_Rptr(rover);
			rover->Increment_Mission_Count();
		}
		else if (Available_PR.dequeue(rover))    ///// Check Polar Rover list Last
		{
			Emergence_mission->Set_Rptr(rover);
			rover->Increment_Mission_Count();
		}
		Emergence_mission->Calculate_WD(Day_count); ///// Add Mission from available to Excution Mission list 
		rover->set_Mission_EXtime(Emergence_mission->Calculate_ED());
		Emergency_EX_Mission.enqueue(Emergence_mission, Emergence_mission->Calculate_CD_Priority());
		MarsStation_Class::waiting_missions_count--;
		MarsStation_Class::execution_missions_count++;
		MarsStation_Class::availble_Rover_count--;
	}
	while (!E_Mission.isEmpty() && (!Maintenance_ER.isEmpty() || !Maintenance_PR.isEmpty() 
									|| !Maintenance_MR.isEmpty()))
	{
		Mission* Emergence_mission;
		Rover* rover;
		E_Mission.dequeue(Emergence_mission);
		if (Maintenance_ER.dequeue(rover))      ///// Check Emergency Rover list first
		{
			rover->SetIsAssigned(true);
			Emergence_mission->Set_Rptr(rover);
			rover->Increment_Mission_Count();
			rover->SetSpeed(rover->GetSpeed() / 2);
		}
		else if (Maintenance_MR.dequeue(rover)) ///// Check Mountainous Rover list second
		{
			rover->SetIsAssigned(true);
			Emergence_mission->Set_Rptr(rover);
			rover->Increment_Mission_Count();
			rover->SetSpeed(rover->GetSpeed() / 2);
		}
		else if (Maintenance_PR.dequeue(rover))    ///// Check Polar Rover list Last
		{
			rover->SetIsAssigned(true);
			Emergence_mission->Set_Rptr(rover);
			rover->Increment_Mission_Count();
			rover->SetSpeed(rover->GetSpeed() / 2);
		}
		Emergence_mission->Calculate_WD(Day_count); ///// Add Mission from available to Excution Mission list 
		rover->set_Mission_EXtime(Emergence_mission->Calculate_ED());
		Emergency_EX_Mission.enqueue(Emergence_mission, Emergence_mission->Calculate_CD_Priority());
		MarsStation_Class::waiting_missions_count--;
		MarsStation_Class::execution_missions_count++;
		MarsStation_Class::maintenance_Rover_count--;
	}
}
void MarsStation_Class::Assign_P_M()
{
	/*
	if (Available_PR.isEmpty())
		return;
	else
	{
		Mission* Polar_mission;
		Rover* P_Rover;
		while (P_Mission.dequeue(Polar_mission))
		{
			if (Available_PR.dequeue(P_Rover))      ///// Check Emergency Rover list first
			{
				Polar_mission->Set_Rptr(P_Rover);
				P_Rover->Increment_Mission_Count();
				Polar_mission->Calculate_WD(Day_count); ///// Add Mission from available to Excution Mission list 
				Polar_EX_Mission.enqueue(Polar_mission, Polar_mission->Calculate_CD_Priority()); //// note: sorted ascending 

			}
			else
			{
				break;
			}
		}
	}*/
	int counter1 = 0, counter2 = 0;
	Assign_Mission_to_QueueRover(counter1,P_Mission, Polar_EX_Mission, Available_PR);;
	MarsStation_Class::availble_Rover_count-= counter1;
	Assign_Mission_to_PriorityQueueRover(counter2,P_Mission, Polar_EX_Mission,Maintenance_PR);
	MarsStation_Class::waiting_missions_count -= counter2+ counter1;
	MarsStation_Class::execution_missions_count += counter2+ counter1;
	MarsStation_Class::maintenance_Rover_count -= counter2;

	/*
	while (!P_Mission.isEmpty() && !Available_PR.isEmpty())
	{
		Mission* Polar_mission;
		P_Mission.dequeue(Polar_mission);
		Rover* P_Rover;
		Available_PR.dequeue(P_Rover);
		Polar_mission->Set_Rptr(P_Rover);
		P_Rover->SetIsAssigned(true);
		P_Rover->Increment_Mission_Count();
		Polar_mission->Calculate_WD(Day_count); ///// Add Mission from available to Excution Mission list 
		Polar_EX_Mission.enqueue(Polar_mission, Polar_mission->Calculate_CD_Priority()); //// note: sorted ascending 
		MarsStation_Class::waiting_missions_count--;
		MarsStation_Class::execution_missions_count++;
		MarsStation_Class::availble_Rover_count--;
	}
	*/
}

void MarsStation_Class::Assign_M_M()
{
	//23ml auto promoted b3d el assign el 3ady?
	//Mission* MMptr;
	//Rover* ARptr;
	//M_Mission.peek(MMptr)
	int counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0;
	Assign_Mission_to_QueueRover(counter1, M_Mission, Mountainous_EX_Mission, Available_MR);
	Assign_Mission_to_QueueRover(counter2, M_Mission, Mountainous_EX_Mission, Available_ER);

	MarsStation_Class::availble_Rover_count -= counter2+ counter1;
	Assign_Mission_to_PriorityQueueRover(counter3, M_Mission, Mountainous_EX_Mission, Maintenance_MR);
	Assign_Mission_to_PriorityQueueRover(counter4, M_Mission, Mountainous_EX_Mission, Maintenance_ER);
	MarsStation_Class::waiting_missions_count -= counter2 + counter1+ counter3 + counter4;
	MarsStation_Class::execution_missions_count += counter2 + counter1+ counter3 + counter4;
	MarsStation_Class::availble_Rover_count -= counter3 + counter4;
	/*
	while (!M_Mission.isEmpty() && !Available_MR.isEmpty())
	{
		//if()
		M_Mission.dequeue(MMptr);
		Available_MR.dequeue(ARptr);//??
		ARptr->Increment_Mission_Count();
		MMptr->Calculate_WD(Day_count);
		MMptr->Set_Rptr(ARptr);
		ARptr->SetIsAssigned(true);
		Mountainous_EX_Mission.enqueue(MMptr, MMptr->Calculate_CD_Priority());
		MarsStation_Class::waiting_missions_count--;
		MarsStation_Class::execution_missions_count++;
		MarsStation_Class::availble_Rover_count--;

	}
	while (!M_Mission.isEmpty() && !Available_ER.isEmpty())
	{
		M_Mission.dequeue(MMptr);
		Available_ER.dequeue(ARptr);//??
		ARptr->Increment_Mission_Count();
		MMptr->Calculate_WD(Day_count);
		MMptr->Set_Rptr(ARptr);
		ARptr->SetIsAssigned(true);
		Mountainous_EX_Mission.enqueue(MMptr, MMptr->Calculate_CD_Priority());
		MarsStation_Class::waiting_missions_count--;
		MarsStation_Class::execution_missions_count++;
		MarsStation_Class::availble_Rover_count--;
	}
	*/
}
void MarsStation_Class::Auto_Promoting()
{
	//Mission* MMptr;
	//Mission* EMptr;
	Mission* Auto_P_Mptr;

	while (!M_Mission.isEmpty())
	{
		M_Mission.peek(Auto_P_Mptr);
		if (Auto_P_Mptr->Calculate_WD(Day_count) == Mission::AutoP)
		{
			M_Mission.dequeue(Auto_P_Mptr);
			//EMptr = new Mission(MMptr->Get_TLOC(), MMptr->Get_MDUR(), MMptr->Get_SIG(), MMptr->Get_FD(), MMptr->Get_ID(), Emergency);
			Auto_P_Mptr->Set_type_of_mission(Emergency);
			E_Mission.enqueue(Auto_P_Mptr, Auto_P_Mptr->Calculate_priority());
			Mission::NumOfAutoPMissions++;
			Mission::NumOfMMissions--;
			Mission::NumOfEMissions++;
			//D.F to add NumOfAutoPMissions with NumOfMMissions to get num of totall m mission to calculat el nsba el m2wya for ayto promoting in output file
			//delete MMptr;//?delete in general and null errors......
		}
		else
			break;//or return
	}
}
void MarsStation_Class::Assign_All_Mission()
{
	Assign_E_M();
	Assign_M_M();
	Assign_P_M();
	Auto_Promoting();/////?is it will be like that at the first before any assign???
}
void MarsStation_Class::InExecution_to_Completed()
{
	//////// Check Emergency Execution List ///////
	General_InEXecution_to_Completed(Emergency_EX_Mission,E_ID);
	//////// Check Mountainous Execution List ///////
	General_InEXecution_to_Completed(Mountainous_EX_Mission,M_ID);
	//////// Check Polar Execution List ///////
	General_InEXecution_to_Completed(Polar_EX_Mission,P_ID);
}
void MarsStation_Class::General_InEXecution_to_Completed(PriorityQueue<Mission*>& Execution_list,
	string &List_ID)
{
	Mission* mission_type;
	if (List_ID != "")
	{
		List_ID = List_ID + (",");
	}
	while (Execution_list.peek(mission_type))
	{
		if (mission_type->Get_CD() == Day_count)
		{
			Execution_list.dequeue(mission_type);
			Temp_CD_Mission.enqueue(mission_type, mission_type->Calculate_ED_Priority());
			MarsStation_Class::execution_missions_count--;
			MarsStation_Class::completed_missions_count++;
			//Completed_E_Mission_ID.enqueue(mission_type->Get_ID());
			// string should take ID //
			List_ID =List_ID+(to_string(mission_type->Get_ID()));
			List_ID =List_ID+(",");

			Rover* rover = mission_type->Get_Rptr();
			rover->SetIsAssigned(false);
			if (rover->GetType() == Emergency)
			{
				if (General_Check_Maintenance(rover,Maintenance_ER, (Rover::Check_ER)/2 +1))
					General_Check_R_State(rover, Check_up_ER, Available_ER, Rover::Missions_Before_Check_Up, Rover::Check_ER);
			}
			else if (rover->GetType() == Mountainous)
			{
				if (!General_Check_Maintenance(rover, Maintenance_MR, (Rover::Check_MR) / 2 + 1))
					General_Check_R_State(rover, Check_up_MR, Available_MR, Rover::Missions_Before_Check_Up, Rover::Check_MR);

			}
			else if(rover->GetType() == Polar)
			{
				if (!General_Check_Maintenance(rover, Maintenance_PR, (Rover::Check_PR) / 2 + 1))
					General_Check_R_State(rover, Check_up_PR, Available_PR, Rover::Missions_Before_Check_Up, Rover::Check_PR);

			}
		}
		else
		{
			break;
		}
	}
}

//////////////////////////////////////// Bonus  Maintenance ////////////////////////////////////////
bool MarsStation_Class::General_Check_Maintenance(Rover* CRptr, LinkedQueue<Rover*>& Maintenance_list,
	 int Duration)
{
	if (CRptr->Check_Maintenance())
	{
		CRptr->Set_Day_out(Duration + Day_count);
		Maintenance_list.enqueue(CRptr);
		MarsStation_Class::maintenance_Rover_count++;
		return true;
	}
	else
	{
		return false;
	}
}

void MarsStation_Class::General_Check_R_State(Rover* CRptr, LinkedQueue<Rover*>& Check_up_list, PriorityQueue<Rover*>& Available_list, int Count, int Duration)
{
	if (CRptr->GetMission_Count() % Count == 0)
	{
		Check_up_list.enqueue(CRptr);
		//Rover::GetCheck_MR();
		CRptr->Set_Day_out(Duration + Day_count);
		MarsStation_Class::checkup_Rover_count++;
	}
	else
	{
		Available_list.enqueue(CRptr, CRptr->GetSpeed());
		MarsStation_Class::availble_Rover_count++;
	}
	//General_Check_R_State(mountain Rover * CRptr, Check_up_MR, Available_MR, Rover::M_Rover_Count, Rover::Check_MR);
}



//////////////////// Input File /////////////////////////
void MarsStation_Class::Program_Startup()
{
	string File_Name, Line, ed = " ", id = " ", tolc = " ", mdur = " ", sig = " ";
	string* Speeds_Str;
	char Type_Event, Type_Mission;
	int Num_E_Rovers, Num_P_Rovers, Num_M_Rovers;
	int Num_Rovers;
	int Check_UP_E_Rover;
	int Check_UP_M_Rover;
	int Check_UP_P_Rover;
	int Missions_Before_Check_up;
	int Num_Event;
	int Auto_Promotion_in;
	int j, ED, ID, TOLC, MDUR, SIG;
	Rover** Array_OF_Rovers;
	int* Speeds;
	/*cout << "Please::enter the name of the file the you want to load it" << endl;
	cin >> File_Name;*/
	File_Name = ui.read_input_file_name(1);
	ifstream My_File;
	My_File.open("\Input\\" + File_Name + ".txt");
	while (!My_File.is_open())
	{
		File_Name = ui.read_input_file_name(2);
		My_File.open("\Input\\" + File_Name + ".txt");
		if (File_Name == "0") break;
	}
	if (My_File.is_open())                       //Check if the file is found or not
	{
		My_File >> Num_M_Rovers >> Num_P_Rovers >> Num_E_Rovers;
		Num_Rovers = Num_E_Rovers + Num_P_Rovers + Num_M_Rovers;
		Array_OF_Rovers = new Rover * [Num_Rovers];
		Speeds = new int[Num_Rovers];
		Speeds_Str = new string[Num_Rovers];
		//////////////////////Read the speed of the rover///////////////
		getline(My_File, Line);                             //To avoid the reminder of the line
		getline(My_File, Line);
		int i = 1;

		int count = 0;
		while (Line[i] == ' ')
		{
			i++;
			count++;
		}
		int Spaces = 0;
		for (int k = 0; k < Line.size(); k++)
		{
			if (Line[k] == ' ')
				Spaces++;
		}
		Spaces = Spaces - 1;
		Spaces = (Spaces / count);
		Spaces = Spaces + 1;
		i = 0;
		//////////////////// Bounas case///////////////////
	 ///////////////////reading the speeds///////////////////// 
		if (Spaces == Num_Rovers)        //The case of the different speeds
		{
			for (int j = 0; j < Num_Rovers; j++)
			{
				while (Line[i] != ' ')
				{
					Speeds_Str[j]+= Line[i];
					i++;
				}
				Speeds[j] = stoi(Speeds_Str[j]);
				while (Line[i] == ' ')
				{
					i++;
				}
			}
			///////////////////////////Creating the rovers////////////////////////////
			int counter = 0;
			int j = 0;
			for (int i = 0; i < Num_M_Rovers; i++)
			{
				Array_OF_Rovers[counter] = new Rover(Speeds[counter], Mountainous);
				Available_MR.enqueue(Array_OF_Rovers[counter], Array_OF_Rovers[counter]->GetSpeed());
				counter++;
			}
			for (int i = 0; i < Num_P_Rovers; i++)
			{
				Array_OF_Rovers[counter] = new Rover(Speeds[counter], Polar);
				Available_PR.enqueue(Array_OF_Rovers[counter], Array_OF_Rovers[counter]->GetSpeed());
				counter++;
			}
			for (int i = 0; i < Num_E_Rovers; i++)
			{
				Array_OF_Rovers[counter] = new Rover(Speeds[counter], Emergency);
				Available_ER.enqueue(Array_OF_Rovers[counter], Array_OF_Rovers[counter]->GetSpeed());
				counter++;
			}

		}
		else
		{                          ////////////////the speed is const/////////////   
			for (int j = 0; j < 3; j++)
			{
				while (Line[i] != ' ')
				{
					int k = 0;
					Speeds_Str[j][k] = Line[i];
					i++;
					k++;
				}
				Speeds[j] = stoi(Speeds_Str[j]);
				while (Line[i] == ' ')
				{
					i++;
				}
			}
			int counter = 0;          //to the Array of rovers 
			int counter1 = 0;          //to the Array of speeds
			for (int i = 0; i < Num_M_Rovers; i++)
			{
				Array_OF_Rovers[counter] = new Rover(Speeds[counter1], Mountainous);
				Available_MR.enqueue(Array_OF_Rovers[counter], Array_OF_Rovers[counter]->GetSpeed());
				counter++;
			}
			counter1++;
			for (int i = 0; i < Num_P_Rovers; i++)
			{
				Array_OF_Rovers[counter] = new Rover(Speeds[counter1], Polar);
				Available_PR.enqueue(Array_OF_Rovers[counter], Array_OF_Rovers[counter]->GetSpeed());
				counter++;
			}
			counter1++;
			for (int i = 0; i < Num_E_Rovers; i++)
			{
				Array_OF_Rovers[counter] = new Rover(Speeds[counter1], Emergency);
				Available_ER.enqueue(Array_OF_Rovers[counter], Array_OF_Rovers[counter]->GetSpeed());
				counter++;
			}
		}
		My_File >> Missions_Before_Check_up >> Check_UP_M_Rover >> Check_UP_P_Rover >> Check_UP_E_Rover;
		///////////////////////select the static data to the rovers ///////////////////////
		Rover::P_Rover_Count = Num_P_Rovers;
		Rover::Check_PR = Check_UP_P_Rover;
		Rover::E_Rover_Count = Num_E_Rovers;
		Rover::Check_ER = Check_UP_E_Rover;
		Rover::M_Rover_Count = Num_M_Rovers;
		Rover::Check_MR = Check_UP_M_Rover;
		Rover::Missions_Before_Check_Up = Missions_Before_Check_up;
		Rover::NO_ofMissions_Before_Maintenance = Missions_Before_Check_up + 1;

		My_File >> Auto_Promotion_in;                //The value of the auto promotion limit
		Mission::AutoP = Auto_Promotion_in;
		My_File >> Num_Event;                       //The number of events
		Event** PTR_Event = new Event * [Num_Event];
		getline(My_File, Line);                    //To avoid the reminder of the line
		for (int i = 0; i < Num_Event; i++)         //Loop to fill the list of the events
		{
			j = 0;
			getline(My_File, Line);                   //The line of the event data
			Type_Event = Line[j];                        //type of the event formulation or promotion or cancellation  
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
				for (int i = 0; i < Line.size(); i++)
				{
					if (Line[j] != ' ')
					{
						ed += Line[j];
						j++;
					}
					else
					{
						break;
					}
				}
				ED = stoi(ed);
				while (Line[j] == ' ')
				{
					j++;
				}
				for (int i = 0; i < Line.size(); i++)
				{
					if (Line[j] != ' ')
					{
						id += Line[j];
						j++;
					}
					else
					{
						break;
					}
				}
				ID = stoi(id);
				while (Line[j] == ' ')
				{
					j++;
				}
				for (int i = 0; i < Line.size(); i++)
				{
					if (Line[j] != ' ')
					{
						tolc += Line[j];
						j++;
					}
					else
					{
						break;
					}
				}
				TOLC = stoi(tolc);
				while (Line[j] == ' ')
				{
					j++;
				}
				for (int i = 0; i < Line.size(); i++)
				{
					if (Line[j] != ' ')
					{
						mdur += Line[j];
						j++;
					}
					else
					{
						break;
					}
				}
				MDUR = stoi(mdur);
				while (Line[j] == ' ')
				{
					j++;
				}
				for (int i = 0; i < Line.size() && j < Line.size(); i++)
				{
					if (Line[j] != ' ')
					{
						sig += Line[j];
						j++;
					}
					else
					{
						break;
					}
				}
				SIG = stoi(sig);
			}
			else if (Type_Event == 'P' || Type_Event == 'X')
			{
				j++;
				while (Line[j] == ' ')
				{
					j++;
				}
				for (int i = 0; i < Line.size(); i++)
				{
					if (Line[j] != ' ')
					{
						ed += Line[j];
						j++;
					}
					else
					{
						break;
					}
				}
				ED = stoi(ed);
				while (Line[j] == ' ')
				{
					j++;
				}
				for (int i = 0; i < Line.size() && j < Line.size(); i++)
				{
					if (Line[j] != ' ')
					{
						id += Line[j];
						j++;
					}
					else
					{
						break;
					}
				}
				ID = stoi(id);
			}
			//////////////Creating the events/////////////
			if (Type_Event == 'P')
			{
				PTR_Event[i] = new Promotion_Event(ID, ED);
				Events_List.enqueue(PTR_Event[i]);
			}
			if (Type_Event == 'F')
			{
				PTR_Event[i] = new Formulaion_Event(Type_Mission, TOLC, MDUR, SIG, ID, ED);
				Events_List.enqueue(PTR_Event[i]);
			}
			if (Type_Event == 'X')
			{
				PTR_Event[i] = new Cancellation_Event(ID, ED);
				Events_List.enqueue(PTR_Event[i]);
			}
			ed = " ", id = " ", tolc = " ", mdur = " ", sig = " ";

		}
	}
	MarsStation_Class::availble_Rover_count = Rover::E_Rover_Count + Rover::M_Rover_Count +
		Rover::P_Rover_Count;
}


void MarsStation_Class::General_Check_Up_OR_maintenance_to_Available(int& n,LinkedQueue<Rover*>& Check_up_list, PriorityQueue<Rover*>& Available_list)
{
	Rover* Gptr = nullptr;
	Check_up_list.peek(Gptr);
	/*
	if (!Gptr)
	{
		return;
	}*/
	n = 0;
	while (Gptr) {

		if(Gptr->Get_Day_out() == MarsStation_Class::Day_count)
		{
			Check_up_list.dequeue(Gptr);
			Available_list.enqueue(Gptr, Gptr->GetSpeed());
			Gptr = nullptr;
			Check_up_list.peek(Gptr);
			n++;
		}
		else
		{
			break;
		}
	}
}
//////////////////////////// Bonus Maintenance ////////////////////////////////////
void MarsStation_Class::Maintenance_to_Available()
{
	int n1 = 0, n2 = 0, n3 = 0;
	General_Check_Up_OR_maintenance_to_Available(n1, Maintenance_MR, Available_MR);
	General_Check_Up_OR_maintenance_to_Available(n2, Maintenance_ER, Available_ER); // Logic??
	General_Check_Up_OR_maintenance_to_Available(n3, Maintenance_PR, Available_PR);
	MarsStation_Class::maintenance_Rover_count -= (n1 + n2 + n3);
	MarsStation_Class::availble_Rover_count += (n1 + n2 + n3);
}
void MarsStation_Class::Check_Up_to_Available_All()
{
	// Check_Up_to_Available_M();
	// Check_Up_to_Available_E();
	// Check_Up_to_Available_P();
 
	int n1 = 0, n2 = 0, n3 = 0;
	General_Check_Up_OR_maintenance_to_Available(n1,Check_up_MR, Available_MR);
	General_Check_Up_OR_maintenance_to_Available(n2,Check_up_ER, Available_ER);
	General_Check_Up_OR_maintenance_to_Available(n3,Check_up_PR, Available_PR);
	MarsStation_Class::checkup_Rover_count-= (n1+ n2+ n3);
	MarsStation_Class::availble_Rover_count+= (n1+ n2+ n3);
}
void MarsStation_Class::print() 
{
	Terminal_Mode Mode = ui.get_mode();

	if (Mode == Interactive)
	{
		cin.get();
	}
	else if(Mode == Step_By_Step)
	{
		ui.sleep(1.0);
	}
	else if (Mode == Silent)
	{
		return;
	}
	ui.print_Availble_missions(Day_count, waiting_missions_count, E_Mission,
		P_Mission, M_Mission);
	ui.Print_In_Execution_Missions_Rovers(execution_missions_count,Emergency_EX_Mission,
											Mountainous_EX_Mission,Polar_EX_Mission);
	ui.Print_Available_Rover(availble_Rover_count, Available_ER, Available_PR, Available_MR);
	ui.Print_In_Checkup_Rovers(checkup_Rover_count, Check_up_ER, Check_up_PR, Check_up_MR);
	ui.Print_In_Maintenance_Rovers(maintenance_Rover_count, Maintenance_ER, Maintenance_MR, Maintenance_PR);
	ui.Print_Completed(completed_missions_count,M_ID, P_ID, E_ID);
	}
bool MarsStation_Class::isFinished()
{
	return (Events_List.isEmpty() && P_Mission.isEmpty() && M_Mission.isEmpty() &&
		E_Mission.isEmpty() && Emergency_EX_Mission.isEmpty() && Mountainous_EX_Mission.isEmpty() &&
		Polar_EX_Mission.isEmpty());
	// check if All Lists of Missions & events is empty this mean all missions are Completed then 
	// terminate the Program
}

void MarsStation_Class::Out1()
{
	ui.read_output_file_name();
	ofstream outF;//variable to deal with output file , declared here for multiple functions
	outF.open("\Output\\" + ui.Get_Output_File_Name() + ".txt", ios::out);
	outF << "CD\tID\tFD\tWD\tED\n";
	outF.close();
}

void MarsStation_Class::Out2()
{
	ofstream outF;

	outF.open("\Output\\" + ui.Get_Output_File_Name() + ".txt", ios::app);

	Mission* dummy_mission;
	while (Temp_CD_Mission.dequeue(dummy_mission))
	{
		outF << dummy_mission->Get_CD() << "\t" << dummy_mission->Get_ID() << "\t"
			<< dummy_mission->Get_FD() << "\t" << dummy_mission->Get_WD() << "\t"
			<< dummy_mission->Calculate_ED() << "\n";
		WD_SUM += dummy_mission->Get_WD();
		ED_SUM += dummy_mission->Get_ED();
		delete dummy_mission;
	}
}

void MarsStation_Class::Out3()
{
	ofstream outF;//variable to deal with output file , declared here for multiple functions
	int MounSumTotal = Mission::NumOfMMissions + Mission::NumOfAutoPMissions+ Mission::NumOfNoNAutoPMissions ;
	int Msum = Mission::NumOfMMissions + Mission::NumOfPMissions + Mission::NumOfEMissions;

	outF.open("\Output\\" + ui.Get_Output_File_Name() + ".txt", ios::app);

	outF << ".............................................\n.............................................\n"
		<< "Missions:" << Mission::NumOfMMissions + Mission::NumOfPMissions + Mission::NumOfEMissions;
	outF << "\t[M: " << Mission::NumOfMMissions << ", P: " << Mission::NumOfPMissions
		<< ", E: " << Mission::NumOfEMissions << "]\n";
	outF << "Rovers:" << Rover::E_Rover_Count + Rover::P_Rover_Count + Rover::M_Rover_Count
		<< " \t[M: " << Rover::M_Rover_Count << ", P: " << Rover::P_Rover_Count << ", E: "
		<< Rover::E_Rover_Count << "]\n";
	outF << "Avg Wait = " << (float)WD_SUM / Msum << ", Avg Exec = " << (float)ED_SUM / Msum << endl;
	outF << "Auto-promoted: " << ((float)Mission::NumOfAutoPMissions / MounSumTotal) * 100 << "%\n";

	outF.close();

}


int MarsStation_Class::Day_count = 1;
int MarsStation_Class::waiting_missions_count = 0;
int MarsStation_Class::execution_missions_count = 0;
int MarsStation_Class::completed_missions_count = 0;
int MarsStation_Class::availble_Rover_count = 0;
int MarsStation_Class::checkup_Rover_count = 0;
int MarsStation_Class::maintenance_Rover_count = 0;

/*
void MarsStation_Class::Emergency_EX_Mission_to_completed()
{
	Mission* Emergence_mission;
	while (Emergency_EX_Mission.peek(Emergence_mission))
	{
		if (Emergence_mission->Get_CD() == Day_count)
		{
			Emergency_EX_Mission.dequeue(Emergence_mission);
			Temp_CD_Mission.enqueue(Emergence_mission, Emergence_mission->Calculate_ED_Priority());
			Completed_E_Mission_ID.enqueue(Emergence_mission->Get_ID());
			// string should take ID //
			E_ID.append(to_string(Emergence_mission->Get_ID()));
			E_ID.append(to_string(','));
			Rover* rover = Emergence_mission->Get_Rptr();
			if (rover->GetType() == Emergency)
			{
				General_Check_R_State(rover, Check_up_ER, Available_ER, Rover::E_Rover_Count, Rover::Check_ER);
				//Check_ER_State(rover);
			}
			else if (rover->GetType() == Mountainous)
			{
				General_Check_R_State(rover, Check_up_MR, Available_MR, Rover::M_Rover_Count, Rover::Check_MR);
				//Check_MR_State(rover);
			}
			else
			{
				General_Check_R_State(rover, Check_up_PR, Available_PR, Rover::P_Rover_Count, Rover::Check_PR);
				//Check_PR_State(rover);
			}
		}
		else
		{
			break;
		}
	}
}
void MarsStation_Class::Mountainous_EX_Mission_to_completed()
{
	Mission* Mountainous_mission;
	while (Mountainous_EX_Mission.peek(Mountainous_mission))
	{
		if (Mountainous_mission->Get_CD() == Day_count)
		{
			Mountainous_EX_Mission.dequeue(Mountainous_mission);
			Temp_CD_Mission.enqueue(Mountainous_mission, Mountainous_mission->Calculate_ED_Priority());
			Completed_M_Mission_ID.enqueue(Mountainous_mission->Get_ID());
			// string should take ID //
			M_ID.append(to_string(Mountainous_mission->Get_ID()));
			M_ID.append(to_string(','));
			Rover* rover = Mountainous_mission->Get_Rptr();
			if (rover->GetType() == Mountainous)
			{
				General_Check_R_State(rover, Check_up_ER, Available_ER, Rover::E_Rover_Count, Rover::Check_ER);
				//Check_MR_State(rover);
			}
			else
			{
				General_Check_R_State(rover, Check_up_MR, Available_MR, Rover::M_Rover_Count, Rover::Check_MR);
				//Check_ER_State(rover);
			}
		}
		else
		{
			break;
		}
	}
}
void MarsStation_Class::Polar_EX_Mission_to_completed()
{
	Mission* polar_mission;
	while (Polar_EX_Mission.peek(polar_mission))
	{
		if (polar_mission->Get_CD() == Day_count)
		{
			Polar_EX_Mission.dequeue(polar_mission);
			Temp_CD_Mission.enqueue(polar_mission, polar_mission->Calculate_ED_Priority());
			Completed_E_Mission_ID.enqueue(polar_mission->Get_ID());
			// string should take ID //
			P_ID.append(to_string(polar_mission->Get_ID()));
			P_ID.append(to_string(','));
			//Check_PR_State(Polar_mission->Get_Rptr());
			General_Check_R_State(polar_mission->Get_Rptr(), Check_up_PR, Available_PR, Rover::P_Rover_Count, Rover::Check_PR);
		}
		else
		{
			break;
		}
	}
}
///////////////////////////////////////////////////////////////
void MarsStation_Class::InExecution_to_Completed()
{
	Emergency_EX_Mission_to_completed();
	Mountainous_EX_Mission_to_completed();
	Polar_EX_Mission_to_completed();
	//Mamdouh : maybe here you can call out2? remember you shall send a queue of sorted completed missions ;)
}*/
/////////////////////
//void MarsStation_Class::Auto_Promoting()
//{
//	Mission* MMptr;
//	Mission* EMptr;
//
//	while (!M_Mission.isEmpty())
//	{
//		M_Mission.peek(MMptr);
//		if (MMptr->Calculate_WD(Day_count) == Mission::AutoP)
//		{
//			M_Mission.dequeue(MMptr);
//			EMptr = new Mission(MMptr->Get_TLOC(), MMptr->Get_MDUR(), MMptr->Get_SIG(), MMptr->Get_FD(), MMptr->Get_ID(), Emergency);
//			E_Mission.enqueue(EMptr, EMptr->Calculate_priority());
//			Mission::NumOfAutoPMissions++;
//			Mission::NumOfMMissions--;
//			Mission::NumOfEMissions++;
//			//D.F to add NumOfAutoPMissions with NumOfMMissions to get num of totall m mission to calculat el nsba el m2wya for ayto promoting in output file
//			delete MMptr;//?delete in general and null errors......
//		}
//		else
//			break;//or return
//	}
//
//
//}
//void MarsStation_Class::Check_MR_State(Rover* CMRptr)
//{
//	//dynamicM_Rover_Count
//	if (CMRptr->GetMission_Count() == Rover::M_Rover_Count)
//	{
//		Check_up_MR.enqueue(CMRptr);
//		//Rover::GetCheck_MR();
//		CMRptr->Set_Day_out(Rover::Check_MR + Day_count);
//	}
//	else
//	{
//		Available_MR.enqueue(CMRptr);
//	}
//
//}
////check rover satutes
//
//void MarsStation_Class::Check_ER_State(Rover* CERptr)
//{
//	//dynamicM_Rover_Count
//	if (CERptr->GetMission_Count() == Rover::E_Rover_Count)
//	{
//		Check_up_ER.enqueue(CERptr);
//		CERptr->Set_Day_out(Rover::Check_ER + Day_count);
//	}
//	else
//	{
//		Available_ER.enqueue(CERptr);
//	}
//
//}
//
//void MarsStation_Class::Check_PR_State(Rover* CPRptr)
//{
//	//dynamicM_Rover_Count
//	if (CPRptr->GetMission_Count() == Rover::P_Rover_Count)
//	{
//		Check_up_PR.enqueue(CPRptr);
//		CPRptr->Set_Day_out(Rover::Check_PR + Day_count);
//	}
//	else
//	{
//		Available_PR.enqueue(CPRptr);
//	}
//
//}


//void MarsStation_Class::Check_PR_State(Rover* CPRptr)
//{
//	//dynamicM_Rover_Count
//	if (CPRptr->GetMission_Count() == Rover::P_Rover_Count)
//	{
//		Check_up_PR.enqueue(CPRptr);
//		CPRptr->Set_Day_out(Rover::Check_PR + Day_count);
//	}
//	else
//	{
//		Available_PR.enqueue(CPRptr, CPRptr->GetSpeed());
//	}
//
//}

//void MarsStation_Class::Check_Up_to_Available_E()
//{
//	Rover* EMptr;
//	Check_up_ER.peek(EMptr);
//	while (EMptr->Get_Day_out() == Day_count)
//	{
//		Check_up_ER.dequeue(EMptr);
//		Available_ER.enqueue(EMptr, EMptr->GetSpeed());
//		Check_up_ER.peek(EMptr);
//	}

//void MarsStation_Class::Check_Up_to_Available_M()
//{
//	Rover* MMptr;
//	Check_up_MR.peek(MMptr);
//	while (MMptr->Get_Day_out() == Day_count)
//	{
//		Check_up_MR.dequeue(MMptr);
//		Available_MR.enqueue(MMptr);
//		Check_up_MR.peek(MMptr);
//	}
//}
//void MarsStation_Class::Check_Up_to_Available_E()
//{
//	Rover* EMptr;
//	Check_up_ER.peek(EMptr);
//	while (EMptr->Get_Day_out() == Day_count)
//	{
//		Check_up_ER.dequeue(EMptr);
//		Available_ER.enqueue(EMptr);
//		Check_up_ER.peek(EMptr);
//	}
//
//}
//void MarsStation_Class::Check_Up_to_Available_P()
//{
//	Rover* PMptr;
//	Check_up_PR.peek(PMptr);
//	while (PMptr->Get_Day_out() == Day_count)
//	{
//		Check_up_PR.dequeue(PMptr);
//		Available_PR.enqueue(PMptr);
//		Check_up_PR.peek(PMptr);
//	}
//
//}




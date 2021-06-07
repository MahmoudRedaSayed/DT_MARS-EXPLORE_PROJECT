#include "MarsStation_Class.h"
#include<fstream>


using namespace std;

int MarsStation_Class::Get_Day_count()
{
	return Day_count;
}

MarsStation_Class::MarsStation_Class()
	:WD_SUM(0), ED_SUM(0)
{
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

void MarsStation_Class::Assign_Mission_to_PriorityQueueRover(int& Counter, LinkedQueue<Mission*>& availble_Mission_list,
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
		rover->Increment_Mission_Count();
		mission->Calculate_WD(Day_count); ///// Add Mission from available to Excution Mission list 
		rover->set_Mission_EXtime(mission->Calculate_ED());
		EX_Mission_list.enqueue(mission, mission->Calculate_CD_Priority()); //// note: sorted ascending 
		Counter++;
	}
}
void MarsStation_Class::Assign_Mission_to_QueueRover(int& Counter, LinkedQueue<Mission*>& availble_Mission_list,
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
	while (!E_Mission.isEmpty() && (!Available_ER.isEmpty() || !Available_PR.isEmpty() || !Available_MR.isEmpty()))
	{
		Mission* Emergence_mission;
		Rover* rover;
		E_Mission.dequeue(Emergence_mission);

		if (Available_ER.dequeue(rover)) {}      ///// Check Emergency Rover list first
		else if (Available_MR.dequeue(rover)) {} ///// Check Mountainous Rover list second
		else if (Available_PR.dequeue(rover)) {}    ///// Check Polar Rover list Last

		Emergence_mission->Set_Rptr(rover);
		rover->Increment_Mission_Count();
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
		{}
		else if (Maintenance_MR.dequeue(rover)) ///// Check Mountainous Rover list second
		{}
		else if(Maintenance_PR.dequeue(rover))    ///// Check Polar Rover list Last
		{}
		Emergence_mission->Set_Rptr(rover);
		rover->Increment_Mission_Count();
		rover->SetSpeed(rover->GetSpeed() / 2);
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
	int counter1 = 0, counter2 = 0;
	Assign_Mission_to_PriorityQueueRover(counter1, P_Mission, Polar_EX_Mission, Available_PR);;
	MarsStation_Class::availble_Rover_count -= counter1;
	Assign_Mission_to_QueueRover(counter2, P_Mission, Polar_EX_Mission, Maintenance_PR);
	MarsStation_Class::waiting_missions_count -= counter2 + counter1;
	MarsStation_Class::execution_missions_count += counter2 + counter1;
	MarsStation_Class::maintenance_Rover_count -= counter2;
}

void MarsStation_Class::Assign_M_M()
{
	int counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0;
	Assign_Mission_to_PriorityQueueRover(counter1, M_Mission, Mountainous_EX_Mission, Available_MR);
	Assign_Mission_to_PriorityQueueRover(counter2, M_Mission, Mountainous_EX_Mission, Available_ER);

	MarsStation_Class::availble_Rover_count -= counter2 + counter1;
	Assign_Mission_to_QueueRover(counter3, M_Mission, Mountainous_EX_Mission, Maintenance_MR);
	Assign_Mission_to_QueueRover(counter4, M_Mission, Mountainous_EX_Mission, Maintenance_ER);
	MarsStation_Class::waiting_missions_count -= counter2 + counter1 + counter3 + counter4;
	MarsStation_Class::execution_missions_count += counter2 + counter1 + counter3 + counter4;
	MarsStation_Class::availble_Rover_count -= counter3 + counter4;
}
void MarsStation_Class::Auto_Promoting()
{
	Mission* Auto_P_Mptr;

	while (!M_Mission.isEmpty())
	{
		M_Mission.peek(Auto_P_Mptr);
		if (Auto_P_Mptr->Calculate_WD(Day_count) == Mission::AutoP)
		{
			M_Mission.dequeue(Auto_P_Mptr);
			Auto_P_Mptr->Set_type_of_mission(Emergency);
			E_Mission.enqueue(Auto_P_Mptr, Auto_P_Mptr->Calculate_priority());
			Mission::NumOfAutoPMissions++;
			Mission::NumOfMMissions--;
			Mission::NumOfEMissions++;
		}
		else
			break;
	}
}
void MarsStation_Class::Assign_All_Mission()
{
	Assign_E_M();
	Assign_M_M();
	Assign_P_M();
	Auto_Promoting();
}
void MarsStation_Class::InExecution_to_Completed()
{
	//////// Check Emergency Execution List ///////
	General_InEXecution_to_Completed(Emergency_EX_Mission, E_ID);
	//////// Check Mountainous Execution List ///////
	General_InEXecution_to_Completed(Mountainous_EX_Mission, M_ID);
	//////// Check Polar Execution List ///////
	General_InEXecution_to_Completed(Polar_EX_Mission, P_ID);
}
void MarsStation_Class::General_InEXecution_to_Completed(PriorityQueue<Mission*>& Execution_list,
	string& List_ID)
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
			List_ID = List_ID + (to_string(mission_type->Get_ID()));
			List_ID = List_ID + (",");

			Rover* rover = mission_type->Get_Rptr();
			if (rover->GetType() == Emergency)
			{
				if (!General_Check_Maintenance(rover, Maintenance_ER, (Rover::Check_ER) / 2 + 1))
					General_Check_R_State(rover, Check_up_ER, Available_ER, Rover::Missions_Before_Check_Up, Rover::Check_ER);
			}
			else if (rover->GetType() == Mountainous)
			{
				if (!General_Check_Maintenance(rover, Maintenance_MR, (Rover::Check_MR) / 2 + 1))
					General_Check_R_State(rover, Check_up_MR, Available_MR, Rover::Missions_Before_Check_Up, Rover::Check_MR);
			}
			else if (rover->GetType() == Polar)
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
		CRptr->Set_Day_out(Duration + Day_count);
		MarsStation_Class::checkup_Rover_count++;
	}
	else
	{
		Available_list.enqueue(CRptr, CRptr->GetSpeed());
		MarsStation_Class::availble_Rover_count++;
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
	int n1 = 0, n2 = 0, n3 = 0;
	General_Check_Up_OR_maintenance_to_Available(n1, Check_up_MR, Available_MR);
	General_Check_Up_OR_maintenance_to_Available(n2, Check_up_ER, Available_ER);
	General_Check_Up_OR_maintenance_to_Available(n3, Check_up_PR, Available_PR);
	MarsStation_Class::checkup_Rover_count -= (n1 + n2 + n3);
	MarsStation_Class::availble_Rover_count += (n1 + n2 + n3);
}
void MarsStation_Class::print()
{
	Terminal_Mode Mode = ui.get_mode();

	if (Mode == Interactive)
	{
		cin.get();
	}
	else if (Mode == Step_By_Step)
	{
		ui.sleep(1.0);
	}
	else if (Mode == Silent)
	{
		return;
	}
	ui.print_Availble_missions(Day_count, waiting_missions_count, E_Mission, P_Mission, M_Mission);
	ui.Print_In_Execution_Missions_Rovers(execution_missions_count, Emergency_EX_Mission,
											Mountainous_EX_Mission, Polar_EX_Mission);
	ui.Print_Available_Rover(availble_Rover_count, Available_ER, Available_PR, Available_MR);
	ui.Print_In_Checkup_Rovers(checkup_Rover_count, Check_up_ER, Check_up_PR, Check_up_MR);
	ui.Print_In_Maintenance_Rovers(maintenance_Rover_count, Maintenance_ER, Maintenance_MR, Maintenance_PR);
	ui.Print_Completed(completed_missions_count, M_ID, P_ID, E_ID);
}

bool MarsStation_Class::Rover_Exists() // check at start if there is rovers or not
{
	if ((Available_ER.isEmpty() && Available_MR.isEmpty()) || Available_PR.isEmpty())
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool MarsStation_Class::isFinished()
{
	return (Events_List.isEmpty() && P_Mission.isEmpty() && M_Mission.isEmpty() &&
		E_Mission.isEmpty() && Emergency_EX_Mission.isEmpty() && Mountainous_EX_Mission.isEmpty() &&
		Polar_EX_Mission.isEmpty());
	// check if All Lists of Missions & events is empty this mean all missions are Completed then 
	// terminate the Program
}

//////////////////// Input File /////////////////////////
void MarsStation_Class::Program_Startup()
{
	string File_Name, Line, ed = " ", id = " ", tolc = " ", mdur = " ", sig = " ";
	string* Speeds_Str;
	float* Speeds;
	int Num_Of_speeds = 0;
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
	ifstream My_File;
	File_Name = ui.read_input_file_name(1); //take the input file name from the user 
	My_File.open("\Input\\" + File_Name + ".txt");
	while (!My_File.is_open())      //Check if the file is found or not 
	{
		File_Name = ui.read_input_file_name(2);        //if not found will give the user another chance to enter the new name 
		My_File.open("\Input\\" + File_Name + ".txt");
		if (File_Name == "0") break;
	}
	if (My_File.is_open())                     
	{
		My_File >> Num_M_Rovers >> Num_P_Rovers >> Num_E_Rovers;
		Num_Rovers = Num_E_Rovers + Num_P_Rovers + Num_M_Rovers;
		Array_OF_Rovers = new Rover * [Num_Rovers];
		Speeds = new float[Num_Rovers];
		Speeds_Str = new string[Num_Rovers];
		//////////////////////Read the speed of the rover///////////////
		getline(My_File, Line);                             //To avoid the reminder of the line
		getline(My_File, Line);

		//////////////////// Bounas case///////////////////
		///////////////////reading the speeds as a string///////////////////// 
		int i = 0;
		for (int j = 0; j < Num_Rovers; j++)
		{
			while (i < Line.size() && Line[i] != ' ')
			{
				Speeds_Str[j] += Line[i];
				i++;
			}
			if (i < Line.size())
			{
				while (Line[i] == ' ')
				{
					i++;
				}
			}
		}
		for (int k = 0; k < Num_Rovers; k++)
		{
			if (Speeds_Str[k] != "")
				Num_Of_speeds++;
		}
		if (Num_Of_speeds == Num_Rovers)   
			/////////////////////////////The case of the different speeds///////////////////////////
		{
			i = 0;
			for (int j = 0; j < Num_Rovers; j++)
			{
				if (Speeds_Str[j] != "")
				{
					Speeds[i] = stoi(Speeds_Str[j]);
					i++;
				}


			}

			///////////////////////////Creating the rovers////////////////////////////
			int counter = 0;
			int j = 0;
			///////////////////////////Create Mountainous Rovers/////////////////////////////
			for (int i = 0; i < Num_M_Rovers; i++)
			{
				Array_OF_Rovers[counter] = new Rover(Speeds[counter], Mountainous);
				Available_MR.enqueue(Array_OF_Rovers[counter], Array_OF_Rovers[counter]->GetSpeed());
				counter++;
			}
			///////////////////////////Create Polar Rovers/////////////////////////////
			for (int i = 0; i < Num_P_Rovers; i++)
			{
				Array_OF_Rovers[counter] = new Rover(Speeds[counter], Polar);
				Available_PR.enqueue(Array_OF_Rovers[counter], Array_OF_Rovers[counter]->GetSpeed());
				counter++;
			}
			///////////////////////////Create Emergency Rovers/////////////////////////////
			for (int i = 0; i < Num_E_Rovers; i++)
			{
				Array_OF_Rovers[counter] = new Rover(Speeds[counter], Emergency);
				Available_ER.enqueue(Array_OF_Rovers[counter], Array_OF_Rovers[counter]->GetSpeed());
				counter++;
			}

		}
		else
		{
			i = 0;                     ////////////////the speed is const/////////////   
			for (int j = 0; j < Num_Rovers; j++)
			{
				if (Speeds_Str[j] != "")
				{
					Speeds[i] = stoi(Speeds_Str[j]);
					i++;
				}
			}
			int counter = 0;          //to the Array of rovers 
			int counter1 = 0;          //to the Array of speeds
			///////////////////////////Create Mountainous Rovers/////////////////////////////
			for (int i = 0; i < Num_M_Rovers; i++)
			{
				Array_OF_Rovers[counter] = new Rover(Speeds[counter1], Mountainous);
				Available_MR.enqueue(Array_OF_Rovers[counter], Array_OF_Rovers[counter]->GetSpeed());
				counter++;
			}
			if(Num_M_Rovers!=0)//To test if the there is no mountainous
				counter1++;
			///////////////////////////Create Polar Rovers/////////////////////////////
			for (int i = 0; i < Num_P_Rovers; i++)
			{
				Array_OF_Rovers[counter] = new Rover(Speeds[counter1], Polar);
				Available_PR.enqueue(Array_OF_Rovers[counter], Array_OF_Rovers[counter]->GetSpeed());
				counter++;
			}
			if (Num_P_Rovers != 0)//To test if the there is no polar
				counter1++;
			///////////////////////////Create Emergency Rovers/////////////////////////////
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
		//////////////////////////////////////////////////////////////////////////////////////
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


void MarsStation_Class::General_Check_Up_OR_maintenance_to_Available(int& n, LinkedQueue<Rover*>& Check_up_list, PriorityQueue<Rover*>& Available_list)
{
	Rover* Gptr = nullptr;
	Check_up_list.peek(Gptr);
	n = 0;
	while (Gptr) {

		if (Gptr->Get_Day_out() == MarsStation_Class::Day_count)
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
	int MounSumTotal = Mission::NumOfMMissions + Mission::NumOfAutoPMissions + Mission::NumOfNoNAutoPMissions;
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



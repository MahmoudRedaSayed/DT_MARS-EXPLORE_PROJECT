#include "UI.h"


UI::UI()
	:Mode(Terminal_Mode::Interactive)
{
	for (int i = 0; i < 3; i++)
		std::cout << "\n================================================================================================================\n";
	SelectMode();
}

UI::~UI()
{
	std::cout << "\nSimulation ends, Output file created\n";
	for (int i = 0; i < 3; i++)
		std::cout << "\n================================================================================================================\n";

}

void UI::SelectMode()
{
	int m;
	std::cout << "\n<<<<<<<< Please select simulation mode [default mode : step-by-step] >>>>>>>>\n" <<
		"1-Interactive Mode  (produces output file including simulation statistics, monitors & prints daily statistics\n during simulation on terminal window, you can increase simulation days manually!) \n" <<
		"2-Step-By-Step Mode (same as interactive , but increases days automatically)! \n" <<
		"3-Silent Mode		 (program produces only output files, no simulation steps will be shown on the console)!\n" <<
		"please type number of mode from (1,2 and 3)\n";
	std::cin >> m;
	switch (m)
	{
	case 1:
		Mode = Terminal_Mode::Interactive;
		break;
	case 2:
		Mode = Terminal_Mode::Step_By_Step;
		break;
	case 3:
		Mode = Terminal_Mode::Silent;
		break;
	default:
		Mode = Terminal_Mode::Step_By_Step;
		break;
	}
}

void UI::Print_In_Execution_Missions_Rovers(int NUM_OF_Missions, PriorityQueue<Mission*> Emergency_EX_Mission, PriorityQueue<Mission*> Mountainous_EX_Mission, PriorityQueue<Mission*> Polar_EX_Mission)
{
	cout << NUM_OF_Missions << "In-Execution Missions/Rovers: ";
	Mission* PTR;
	int count = 0;//To avoid the comma
	//printing the emergency
	Emergency_EX_Mission.peek(PTR);
	if (PTR)
	{
		cout << '[';
	}
    while (PTR)
    {
			if (count != 0)
			{
				cout << ',';
			}
			Emergency_EX_Mission.dequeue(PTR);
			cout << PTR->Get_ID() << '/'<<PTR->Get_Rptr()->GetID();
			count++;
    }
	if (count != 0)
	{
		cout << ']'<<" ";
	}
	//printing the polar
	count = 0;
	Polar_EX_Mission.peek(PTR);
	if (PTR)
	{
		cout << '(';
	}
	while (PTR)
	{
		if (count != 0)
		{
			cout << ',';
		}
		Polar_EX_Mission.dequeue(PTR);
		cout << PTR->Get_ID() << '/' << PTR->Get_Rptr()->GetID();
		count++;
	}
	if (count != 0)
	{
		cout << ')' << " ";
	}
	//printing the mountainous
	count = 0;
	Mountainous_EX_Mission.peek(PTR);
	if (PTR)
	{
		cout << '{';
	}
	while (PTR)
	{
		if (count != 0)
		{
			cout << ',';
		}
		Mountainous_EX_Mission.dequeue(PTR);
		cout << PTR->Get_ID() << '/' << PTR->Get_Rptr()->GetID();
		count++;
	}
	if (count != 0)
	{
		cout << '}' << " ";
	}
	cout << endl;
}

void UI::Print_Completed(int NUM_OF_Missions, string M_ID, string P_ID, string E_ID)
{
	cout << NUM_OF_Missions<<"Completed Missions: ";
	if (M_ID != " ")
	{
		M_ID = M_ID.substr(M_ID.size() - 2);
		cout << "  " << '{' << M_ID << '}';
	}

	if (P_ID != " ")
	{
		P_ID = P_ID.substr(P_ID.size() - 2);
		cout <<"  " <<'(' << P_ID << ')';
	}

	if (E_ID != " ")
	{
		E_ID = E_ID.substr(E_ID.size() - 2);
		cout<<"  "<< '[' << E_ID << ']';
	}
	
	 cout<<endl;
}

void UI::Print_In_Checkup_Rovers(int NUM_OF_Rovers, LinkedQueue<Rover*> Check_up_ER, LinkedQueue<Rover*> Check_up_PR, LinkedQueue<Rover*> Check_up_MR)
{
	cout << NUM_OF_Rovers << "In-Checkup Rovers: ";
	Rover* PTR;
	int count = 0;//To avoid the comma
	//printing the Emergency
	Check_up_ER.peek(PTR);
	if (PTR)
	{
		cout << '[';
	}
	while (PTR)
	{
		if (count != 0)
		{
			cout << ',';
		}
		Check_up_ER.dequeue(PTR);
		cout << PTR->GetID();
		count++;
	}
	if (count != 0)
		cout << ']'<<' ';
	// printing the polar 
	count = 0;
	Check_up_PR.peek(PTR);
	if (PTR)
	{
		cout << '(';
	}
	while (PTR)
	{
		if (count != 0)
		{
			cout << ',';
		}
		Check_up_ER.dequeue(PTR);
		cout << PTR->GetID();
		count++;
	}
	if (count != 0)
		cout << ')' << ' ';
	//printing the Mountainous
	count = 0;
	Check_up_MR.peek(PTR);
	if (PTR)
	{
		cout << '{';
	}
	while (PTR)
	{
		if (count != 0)
		{
			cout << ',';
		}
		Check_up_ER.dequeue(PTR);
		cout << PTR->GetID();
		count++;
	}
	if (count != 0)
		cout << '}' << ' ';
	cout << endl;
}



string UI::read_input_file_name()
{
	string FName;
	cout << "\nPlease::enter the name of the file the you want to load it\n" << endl;
	cin >> FName;
	return FName;
}



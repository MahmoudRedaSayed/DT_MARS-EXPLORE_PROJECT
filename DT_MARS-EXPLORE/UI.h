#pragma once
//#include "MarsStation_Class.h"
#include<string>
#include <iostream>
#include "Rover.h"
#include<string.h>
#include"LinkedQueue.h"
#include"PriorityQueue.h"
#include"Mission.h"
using namespace std;
enum  Terminal_Mode {
	Interactive ,
	Step_By_Step ,
	Silent
};
class UI
{
private:
	Terminal_Mode Mode;
public:
	UI();
	~UI();
	//shall make function to recieve input file name ___ talk to 7oda
	Terminal_Mode get_mode();
	void SelectMode();
	void Print_In_Execution_Missions_Rovers(int NUM_OF_Missions, PriorityQueue<Mission*> Emergency_EX_Mission, PriorityQueue<Mission*> Mountainous_EX_Mission, PriorityQueue<Mission*> Polar_EX_Mission);
	void Print_Completed(int NUM_OF_Missions, string& M_ID, string& P_ID, string& E_ID);
	void Print_In_Checkup_Rovers( int NUM_OF_Rovers, LinkedQueue<Rover*> Check_up_ER, LinkedQueue<Rover*> Check_up_PR, LinkedQueue<Rover*> Check_up_MR);
	void print_Availble(int day_count,int waiting_missions,PriorityQueue<Mission*> E_Mission,
		LinkedQueue<Mission*> P_Mission,LinkedQueue<Mission*> M_Mission);
	void Print_Availble_Rover(int availble_Rover_count,PriorityQueue<Rover*> Available_ER,
	PriorityQueue<Rover*> Available_MR,
	PriorityQueue<Rover*> Available_PR);
	/*void Print_To_Console(int Curr_Day, LinkedQueue<Mission*> P_Mission,LinkedQueue<Mission*> M_Mission, PriorityQueue<Mission*> E_Mission,
		PriorityQueue<Mission*> Emergency_EX_Mission,PriorityQueue<Mission*> Mountainous_EX_Mission,PriorityQueue<Mission*> Polar_EX_Mission,
		PriorityQueue<Rover*> Available_ER, PriorityQueue<Rover*> Available_MR, PriorityQueue<Rover*> Available_PR,
		LinkedQueue<Rover*> Check_up_ER,LinkedQueue<Rover*> Check_up_MR,LinkedQueue<Rover*> Check_up_PR,
		LinkedQueue<int> Completed_E_Mission_ID,LinkedQueue<int> Completed_P_Mission_ID,LinkedQueue<int> Completed_M_Mission_ID);*/
	    //3 waiting missions lists , 3 in exec , 3 available rovers,3 checkup lists, 3 completed lists<int>
	string read_input_file_name();
};


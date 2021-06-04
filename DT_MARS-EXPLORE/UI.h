#pragma once
//#include "MarsStation_Class.h"
#include<string>
#include <iostream>
#include "Rover.h"
#include<string.h>
#include"LinkedQueue.h"
#include"PriorityQueue.h"
#include"Mission.h"
#include <ctime>
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
	string Output_File_Name;
public:
	UI();
	~UI();
	//shall make function to recieve input file name ___ talk to 7oda
	Terminal_Mode get_mode();
	void SelectMode();
	void Print_In_Execution_Missions_Rovers(PriorityQueue<Mission*> EX_Mission); 
											
	void Print_Completed( string& M_ID, string& P_ID, string& E_ID);
	void Print_In_Checkup_Rovers(LinkedQueue<Rover*>& Check_up_R);
		
	
	void print_Availble_missions(int day_count,int waiting_missions,PriorityQueue<Mission*>& E_Mission,
								LinkedQueue<Mission*>& P_Mission,LinkedQueue<Mission*>& M_Mission);
	void Print_Availble_Rover(PriorityQueue<Rover*> Available_R);
								
	void print_Availble_missions_Queue(LinkedQueue<Mission*>& Queue_Mission_List);
	void print_Availble_missions_PriorityQueue(PriorityQueue<Mission*> PriorityQueue_Mission_List);
	void sleep(float seconds) {
		clock_t startClock = clock();
		float secondsAhead = seconds * CLOCKS_PER_SEC;
		// do nothing until the elapsed time has passed.
		while (clock() < startClock + secondsAhead);
		return;
	}
	//3 waiting missions lists , 3 in exec , 3 available rovers,3 checkup lists, 3 completed lists<int>
	string read_input_file_name(int i);
	void read_output_file_name();
	string Get_Output_File_Name();
};


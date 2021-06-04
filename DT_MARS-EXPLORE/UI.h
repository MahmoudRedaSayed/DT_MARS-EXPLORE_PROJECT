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

	//////////////////////// Printing Functions //////////////////////
	void print_Availble_missions(int day_count, int waiting_missions, PriorityQueue<Mission*>& E_Mission,
		LinkedQueue<Mission*>& P_Mission, LinkedQueue<Mission*>& M_Mission);
	void Print_In_Execution_Missions_Rovers(int execution_missions_count,PriorityQueue<Mission*>& Emergency_EX_Mission, 
		PriorityQueue<Mission*>& Mountainous_EX_Mission,
		PriorityQueue<Mission*>& Polar_EX_Mission);
	void Print_Available_Rover(int Waiting_Rovers, PriorityQueue<Rover*>& Available_ER,
		PriorityQueue<Rover*>& Available_PR, PriorityQueue<Rover*>& Available_MR);
	void Print_In_Checkup_Rovers(int Checkup_count_Rover,LinkedQueue<Rover*>& Check_up_ER,
							LinkedQueue<Rover*>& Check_up_PR, LinkedQueue<Rover*>& Check_up_MR);
	void Print_Completed(int NUM_OF_MISSIONS, string& M_ID, string& P_ID, string& E_ID);


	/////////// Print Function for Each Type (SAME LOGIC) ///////////////
	void Print_Queue_Rover(LinkedQueue<Rover*>& Check_up_R);
	void Print_PriorityQueue_Mission_Rover(PriorityQueue<Mission*> EX_Mission);
	void Print_PriorityQueue_Rover(PriorityQueue<Rover*> Available_R);		
	void Print_Queue_Mission(LinkedQueue<Mission*>& Queue_Mission_List);
	void Print_PriorityQueue_Mission(PriorityQueue<Mission*> PriorityQueue_Mission_List);
	void Print_Completed_Missions(string brakets, string& M_ID);

	////////////////////////////Function to Make the delay/////////////////////
	void sleep(float seconds);
	
	///////////// inputfile & Outfile Functions ///////////// 
	string read_input_file_name(int i);
	void read_output_file_name();
	string Get_Output_File_Name();
};


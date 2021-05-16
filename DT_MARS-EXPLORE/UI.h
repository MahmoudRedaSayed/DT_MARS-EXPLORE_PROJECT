#pragma once
//#include "MarsStation_Class.h"
#include<string>
#include <iostream>
using namespace std;
enum class Terminal_Mode {
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
	void SelectMode();

	/*void Print_To_Console(int Curr_Day, LinkedQueue<Mission*> P_Mission,LinkedQueue<Mission*> M_Mission, PriorityQueue<Mission*> E_Mission,
		PriorityQueue<Mission*> Emergency_EX_Mission,PriorityQueue<Mission*> Mountainous_EX_Mission,PriorityQueue<Mission*> Polar_EX_Mission,
		PriorityQueue<Rover*> Available_ER, PriorityQueue<Rover*> Available_MR, PriorityQueue<Rover*> Available_PR,
		LinkedQueue<Rover*> Check_up_ER,LinkedQueue<Rover*> Check_up_MR,LinkedQueue<Rover*> Check_up_PR,
		LinkedQueue<int> Completed_E_Mission_ID,LinkedQueue<int> Completed_P_Mission_ID,LinkedQueue<int> Completed_M_Mission_ID);*/
	    //3 waiting missions lists , 3 in exec , 3 available rovers,3 checkup lists, 3 completed lists<int>
	string read_input_file_name();
};


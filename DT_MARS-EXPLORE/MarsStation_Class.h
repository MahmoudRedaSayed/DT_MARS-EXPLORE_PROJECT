#pragma once
#include"Mission.h"
#include"Emergency_Mission.h"
#include"Mountainous_Mission.h"
#include"Polar_Mission.h"

#include "Event.h"
#include "Formulaion_Event.h"
#include "Cancellation_Event.h"
#include "Promotion_Event.h"

#include "Rover.h"
#include<string.h>
#include"LinkedQueue.h"
#include"PriorityQueue.h"

#include<iostream>
using namespace std;


class MarsStation_Class
{
private:
	string M_ID;
	string P_ID;
	string E_ID;

	static int files_Count;//#files to be created for output(#user operations), needs discussion with team

	LinkedQueue<Polar_Mission*> P_Mission;
	LinkedQueue<Mountainous_Mission*> M_Mission;

	LinkedQueue<Rover*> Available_ER;
	LinkedQueue<Rover*> Available_MR;
	LinkedQueue<Rover*> Available_PR;

	LinkedQueue<Rover*> Check_up_ER;
	LinkedQueue<Rover*> Check_up_MR;
	LinkedQueue<Rover*> Check_up_PR;

	LinkedQueue<int> Completed_E_Mission_ID;
	LinkedQueue<int> Completed_P_Mission_ID;
	LinkedQueue<int> Completed_M_Mission_ID;

	PriorityQueue<Emergency_Mission*> E_Mission;
	//PriorityQueue<Mission*> EX_Mission;
	///////////////// 3 separate lists ////////////////
	PriorityQueue<Emergency_Mission*> Emergency_EX_Mission;
	PriorityQueue<Mountainous_Mission*> Mountainous_EX_Mission;
	PriorityQueue<Polar_Mission*> Polar_EX_Mission;

	PriorityQueue<Mission*> Temp_CD_Mission;

	LinkedQueue<Event*> Events_List ;
	LinkedQueue<Rover*> Available_M_Rover_List;
	LinkedQueue<Rover*> Available_P_Rover_List;
	LinkedQueue<Rover*> Available_E_Rover_List;

	static int Day_count;
	//variable for waiting sum & execution sum
	//count of waiting missions & 
	


	//LinkedQueue<>
public:

	MarsStation_Class();
	static void increment_day()
	{
		Day_count++;
	}
	///////// Execute Events /////////
	void Execute();
	//////// assignment operations Functions /////////
	void Assign_E_M();
	void Assign_M_M();
	void Auto_Promoting();
	void Assign_P_M();
	void Assign_All_Mission();
	//////// Move from in execution to completed to available again //////////
	void InExecution_to_Completed();
	void Emergency_EX_Mission_to_completed();
	void Mountainous_EX_Mission_to_completed();
	void Polar_EX_Mission_to_completed();


	//void Check_R_State(Rover* CRptr);
	void Check_MR_State(Rover* CMRptr);
	void Check_ER_State(Rover* CERptr);
	void Check_PR_State(Rover* CPRptr);

	void Check_Up_to_Available_M();
	void Check_Up_to_Available_E();
	void Check_Up_to_Available_P();
	void Check_Up_to_Available_All();
	///////////////////////////The function the will read the data from the file////////////////////
	void Program_Startup();
	//////// Check is All mission is finished /////////////
	bool isFinished();
	//------------------[out Functions]-------------------
	//PS:may/will be modified later
	void Out1();//prints first line of out file
	void Out2(PriorityQueue<Mission*> &M);//prints each completed missions's info
	void Out3();//prints rest of statistics , //static counts of missions & rovers ,WDcount,#counter who?(waited missions || all mission)
};


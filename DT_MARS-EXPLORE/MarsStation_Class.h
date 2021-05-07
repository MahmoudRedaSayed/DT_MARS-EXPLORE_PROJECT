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
#include "Emergency_Rover.h"
#include "Mountaionous_Rover.h"
#include "Polar_Rover.h"

#include"LinkedQueue.h"
#include"PriorityQueue.h"

#include<iostream>
using namespace std;


class MarsStation_Class
{
private:
	LinkedQueue<Polar_Mission*> P_Mission;
	LinkedQueue<Mountainous_Mission*> M_Mission;

	LinkedQueue<Emergency_Rover*> Available_ER;
	LinkedQueue<Mountaionous_Rover*> Available_MR;
	LinkedQueue<Polar_Rover*> Available_PR;

	LinkedQueue<Emergency_Rover*> Check_up_ER;
	LinkedQueue<Mountaionous_Rover*> Check_up_MR;
	LinkedQueue<Polar_Rover*> Check_up_PR;

	LinkedQueue<int> Completed_E_Mission_ID;
	LinkedQueue<int> Completed_P_Mission_ID;
	LinkedQueue<int> Completed_M_Mission_ID;

	PriorityQueue<Emergency_Mission*> E_Mission;
	PriorityQueue<Mission*> EX_Mission;

	LinkedQueue<Event*> Events_List ;

	static int Day_count;
	
	
	//LinkedQueue<>
public:

	MarsStation_Class();
	

	void Assign_E_M();
	void Assign_M_M();
	void Auto_Promoting();
	void Assign_P_M();

	void Assign_All_Mission();


	//void Check_R_State(Rover* CRptr);
	void Check_MR_State(Mountaionous_Rover* CMRptr);
	void Check_ER_State(Emergency_Rover* CERptr);
	void Check_PR_State(Polar_Rover* CPRptr);

	void Check_Up_to_Available_M();
	void Check_Up_to_Available_E();
	void Check_Up_to_Available_P();
	///////////////////////////The function the will read the data from the file////////////////////
	void Program_Startup();


};


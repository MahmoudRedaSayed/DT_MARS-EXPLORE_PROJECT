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

	PriorityQueue<Emergency_Mission*> EMission;
	PriorityQueue<Mission*> EXMission;
public:



};


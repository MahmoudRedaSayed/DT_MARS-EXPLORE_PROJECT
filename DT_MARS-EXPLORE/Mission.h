#pragma once
#include "Rover.h"
#include <cmath>
class Mission
{
private:
	//const int TLOC, MDUR, SIG, FD, ID;
	int TLOC, MDUR, SIG, FD;
	int WD, ED, CD;
	int ID;
	Rover* Rptr;//it will not be const to handle the mission failed
	double Priority;
	Type_G type_of_mission;
public:
	//Constructor
	Mission(double TLOC_x, int MDUR_x, int SIG_x, int FD_x, int ID_x, Type_G type_of_mission_x);
	//Setters
	void Set_TLOC(int x);
	void Set_MDUR(int x);
	void Set_SIG(int x);
	void Set_FD(int x);
	void Set_ID(int x);
	void Set_type_of_mission(Type_G type_of_mission_x);
	//void Set_ED(int x);
	void Set_Rptr(Rover* Rptr_x);
	//Getters
	int Get_TLOC();
	int Get_MDUR();
	int Get_SIG();
	int Get_FD();
	const int Get_ID();
	Type_G Get_type_of_mission();
	int Get_WD();
	int Get_ED();
	int Get_CD();
	Rover* Get_Rptr();
	double Get_Priority();
	//Calculation
	int Calculate_CD();
	double Calculate_CD_Priority();
	double Calculate_ED_Priority();
	int Calculate_ED();
	int Calculate_WD(int CurrDay);
	double Calculate_priority();//Need it to calculate the priority after setting all data to the pointer in the promotion event 
	//Counters
	static int NumOfMMissions;//Number of Mountainous Missions
	static int NumOfEMissions;//Number of Emergency Missions
	static int NumOfPMissions;//Number of Polar Missions
	static int NumOfAutoPMissions;//Number of Auto Promoting Mountainous Missions
	static int AutoP;//Auto promotion limit
	static int NumOfNoNAutoPMissions;//Number of Non-Auto Promoting (by Promotion Event) Mountainous Missions
};


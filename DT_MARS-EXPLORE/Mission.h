#pragma once
#include "Rover.h"
#include <cmath>
//? in generel , mission will be dynamically allocated to delete it when we need not when the program finish?
class Mission
{
private:
	//const int TLOC, MDUR, SIG, FD, ID;
	int TLOC, MDUR, SIG, FD;// can we delete ED, CD as they calculated from another types??
	int WD, ED, CD;// should we delete it from parameter and make it as a counter , increasind ID by itself?
	//int Num_Missions ;
	int ID;
	Rover* Rptr;//it will not be const to handle the mission failed
	//////////////////////////////
	//Emergency.h
	double Priority;
	/////////////////
	Type_G type_of_mission;
public:
	//Const and Destr
	Mission(double TLOC_x, int MDUR_x, int SIG_x, int FD_x, int ID_x, Type_G type_of_mission_x);//?should i delete Rover Rptr=null from the parameter??	
	//Mission();//Later
	//should i make all the funtion -Virtual- accept ID?
	//Setters
	void Set_TLOC(int x);
	void Set_MDUR(int x);
	void Set_SIG(int x);
	void Set_FD(int x);
	void Set_ID(int x);
	void Set_type_of_mission(Type_G type_of_mission_x);
	int Calculate_WD(int CurrDay);//?no need fot it?
	//void Set_ED(int x);//I think no need to this function as there is -Calculate_ED-
	int Calculate_CD();
	double Calculate_CD_Priority();
	double Calculate_ED_Priority();
	void Set_Rptr(Rover* Rptr_x);
	//Getters
	int Get_TLOC();
	int Get_MDUR();
	int Get_SIG();
	int Get_FD();
	const int Get_ID();
	Type_G Get_type_of_mission( );
	/*const int Get_TLOC();
	const int Get_MDUR();
	const int Get_SIG();
	const int Get_FD();
	const int Get_ID();*/

	int Get_WD();
	int Get_ED();
	int Get_CD();
	Rover* Get_Rptr();
	//bool Is_Assign();//no def for it
	//Others
	int Calculate_ED();
	//////////////////////////////
	//Mountain.h
	 //////////////??shuold those static be Private??////////////////////
	static int AutoP;//?should i make it const??
	static int NumOfMMissions;
	static int NumOfAutoPMissions;//?check if we need Promoted events also with AutoP??
	//////////////////////////////
	//Emergency.h
	 //Getters
	double Get_Priority();//?no need for it?
	//void Cal_Prirority();                        //Need it to calculate the priority after setting all data to the pointer in the promotion event 
	double Calculate_priority();//?should i make it void as its funtionality is calculating?
								//?should i uncomment Set_Priority and use it inside this mem func?
	static int NumOfEMissions;
	//////////////////////////////
	//Polar.h
	static int NumOfPMissions;
	///////////////////////////////
	static int NumOfNoNAutoPMissions;
};


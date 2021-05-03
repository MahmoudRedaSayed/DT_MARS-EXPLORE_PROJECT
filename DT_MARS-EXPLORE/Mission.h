#pragma once
#include "Rover.h"
#include <cmath>
//? in generel , mission will be dynamically allocated to delete it when we need not when the program finish?
class Mission
{
private:
	const int TLOC, MDUR, SIG, FD, ID;// can we delete ED, CD as they calculated from another types??
	int WD, ED, CD;// should we delete it from parameter and make it as a counter , increasind ID by itself?
	//int Num_Missions ;
	Rover* Rptr;//it will not be const to handle the mission failed
public:
	//Const and Destr
	Mission(int TLOC_x, int MDUR_x, int SIG_x, int FD_x, int ID_x, Rover* Rptr_x = nullptr);//?should i delete Rover Rptr=null from the parameter??	
	//Mission();//Later
	//should i make all the funtion -Virtual- accept ID?
	//Setters
	/*void Set_TLOC(int x);
	void Set_MDUR(int x);
	void Set_SIG(int x);
	void Set_FD(int x);
	void Set_ID(int x);*/
	void Set_WD(int x);//?no need fot it?
	//void Set_ED(int x);//I think no need to this function as there is -Calculate_ED-
	int Calculate_CD();
	void Set_Rptr(Rover* Rptr_x);
	//Getters
	const int Get_TLOC();
	const int Get_MDUR();
	const int Get_SIG();
	const int Get_FD();
	const int Get_ID();
	int Get_WD();
	int Get_ED();
	int Get_CD();
	Rover* Get_Rptr();
	//bool Is_Assign();//no def for it
	//Others
	int Calculate_ED();


};


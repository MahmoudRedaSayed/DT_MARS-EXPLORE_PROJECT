#include "Formulaion_Event.h"
#include"Mission.h"
#include"Emergency_Mission.h"
#include"Mountainous_Mission.h"
#include"Polar_Mission.h"
#include<iostream>
using namespace std;

//////////////////// Exception Handeling /////////////////////////

Formulaion_Event::Formulaion_Event(char type, int Location, int Duration, int sig,int id,int ED)
{
	Set_Event_Day(ED);
	Set_Mission_ID(id);
	Set_Mission_Type(type);
	Set_TLOC(Location);
	Set_MDUR(Duration);
	Set_SIG(sig);
}

void Formulaion_Event::Set_Mission_Type(char type)
{
	Mission_Type = type;
}

void Formulaion_Event::Set_TLOC(int Location)
{
	if (Location > 0)
		TLOC = Location;
	else cout << "Error:the target loction must be treu value" << endl;
}

void Formulaion_Event::Set_MDUR(int Duration)
{
	if (Duration > 0)
		MDUR = Duration;
	else cout << "Error:mission duration must be positive value" << endl;
}

void Formulaion_Event::Set_SIG(int sig)
{
	if (sig > 0)
		SIG = sig;
	else cout << "Error:the signficance must be positive value" << endl;
}

void Formulaion_Event::Execute(PriorityQueue<Emergency_Mission*>& Eme_Missions, LinkedQueue<Polar_Mission*>& Pol_Missions, LinkedQueue<Mountainous_Mission*>& Mou_Missions)
{//check which type will be created
	if (Mission_Type == 'E')
	{
		//create emergency mission
		Emergency_Mission Created_Mission(TLOC,MDUR,SIG, Get_Event_Day(), Get_Mission_ID());
		Emergency_Mission* PTR_MISSION = &Created_Mission;
		Eme_Missions.enqueue(PTR_MISSION, PTR_MISSION->Get_Priority());
		return;
	}
	if (Mission_Type == 'P')
	{
		//create polar mission
		Polar_Mission Created_Mission(TLOC, MDUR, SIG, Get_Event_Day(), Get_Mission_ID());
		Polar_Mission* PTR_MISSION = &Created_Mission;
		Pol_Missions.enqueue(PTR_MISSION);
		return;
	}
	if (Mission_Type == 'M')
	{//create Mountainous mission
		Mountainous_Mission Created_Mission(TLOC, MDUR, SIG, Get_Event_Day(), Get_Mission_ID());
		Mountainous_Mission* PTR_MISSION = &Created_Mission;
		Mou_Missions.enqueue(PTR_MISSION);
		return;
	}
}

#include "Formulaion_Event.h"
#include<iostream>
using namespace std;

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

void Formulaion_Event::Execute()
{//need mission class
}

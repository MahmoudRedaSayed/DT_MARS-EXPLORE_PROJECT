#include"Rover.h"
int Rover::ID_Count = 0;
int Rover::P_Rover_Count = 0;
int Rover::Check_PR = 5;
int Rover::E_Rover_Count = 0;
int Rover::Check_ER = 5;
int Rover::M_Rover_Count = 0;
int Rover::Check_MR = 5;
int Rover::Missions_Before_Check_Up=1;
int Rover::NO_ofMissions_Before_Maintenance = 1;

Type_G Rover::GetType() const
{
	return Type;
}

int Rover::GetID() const
{
	return ID;
}

float Rover::GetSpeed() const
{
	return speed;
}

bool Rover::GetIsInCheckup() const
{
	return IsInCheckup;
}

int Rover::GetMission_Count() const
{
	return Mission_Count;
}

void Rover::SetIsInCheckup(bool c)
{
	IsInCheckup = c;
}

void Rover::Increment_Mission_Count()
{
	Mission_Count++;
}

void Rover::SetCheck_PR(int c)
{
	Check_PR = c > 0 ? c : 5;
}

void Rover::SetCheck_ER(int c)
{
	Check_ER = c > 0 ? c : 5;
}

void Rover::SetCheck_MR(int c)
{
	Check_MR = c > 0 ? c : 5;
}

void Rover::Set_Day_out(int x)
{
	Day_out = (x > 0) ? x : 1;
}

int Rover::Get_Day_out()
{
	return Day_out;
}

Rover::Rover(float Rover_Speed, Type_G T) :ID(++ID_Count), speed((Rover_Speed > 0) ? Rover_Speed : 3.0) 
, Mission_Count(0), Type(T)
, IsInCheckup(false)
{//no need to it look at the input file
		/*if (T == Mountainous)
			M_Rover_Count++;
		else if (T == Emergency)
			E_Rover_Count++;
		else if (T == Polar)
			P_Rover_Count++;*/

}
////////// Bonus    Maintenance /////////////////
void Rover::set_Mission_EXtime(double ED)
{
	Current_Mission_EX_Time += ED;
}
bool Rover::Check_Maintenance()
{
	if (Mission_Count % NO_ofMissions_Before_Maintenance == 0 || Current_Mission_EX_Time > 100)  // constant threshold 
	{
		Current_Mission_EX_Time = 0;
		return true;
	}
	else
	{
		return false;
	}
}
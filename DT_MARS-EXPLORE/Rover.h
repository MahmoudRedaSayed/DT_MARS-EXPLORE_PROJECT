#pragma once
enum Rover_Type {
	Emergency,
	Mountainous,
	Polar
};
class Rover
{
private:
	//static Data Members
	static int ID_Count;			 //Count of Rovers & assigning each new rover latest ID count

	static int P_Rover_Count;      //Polar. Rovers count for file output
	static int M_Rover_Count;     //Mount. Rovers count for file output
	static int E_Rover_Count;    //Polar. Rovers count for file output

	
	static int Check_PR;      //The duration (in days) of checkups that a **Polar** rover needs 
							 //to perform after completing N missions.
	static int Check_MR;    //The duration (in days) of checkups that a **Mountaionous** rover needs 
						   //to perform after completing N missions.
	static int Check_ER;  //The duration (in days) of checkups that an **Emergency** rover rover needs 
						 //to perform after completing N missions.
	//Non-Static Data Members
	Rover_Type Type;			// Rover Type
	float speed;			   // Rover Speed read from input file _ assumed to be float not int to avoid truncation,
					          //in maintenance Condition that makes speed = 0.5 previous speed 
	const int ID;            //Rover ID , assigned from latest ID_Count
	bool IsAssigned;        //Is this rover assigned to a certain mission or not?
	bool IsInCheckup;      //Is this rover undergoing a checkup or not?
	int Mission_Count;    //no. of missions that rover had executed
	//bool IsInMaintenance;//Is the rover undergoing Maintenance or not?
					    //\Rovers\ need maintenance when ://To be discussed with team
	//samaa
	int Day_out;
	//

public:
	//Constructor & Destructor
	Rover(float Rover_Speed, Rover_Type T)
		:ID(++ID_Count), speed((Rover_Speed > 0) ? Rover_Speed : 3.0), IsAssigned(false)
		, Mission_Count(0), Type(T)
		, IsInCheckup(false) 
	{
		if (T == Mountainous)
			M_Rover_Count++;
		else if (T == Emergency)
			E_Rover_Count++;
		else if (T == Polar)
			P_Rover_Count++;
	}
	//Let Default speed for rover is 3 km/hour (Although we may not need this condition :D )
	//just added in case of invalid input
	~Rover() {}
	//Getters
	const Rover_Type GetType() { return Type; }
	const int GetID() { return ID; }
	const float GetSpeed() { return speed; }
	const bool GetIsAssigned() { return IsAssigned; }
	const bool GetIsInCheckup() { return IsInCheckup;}
	const int GetMission_Count() {return Mission_Count;}
	//const bool GetIsInMaintenance() { return IsInMaintenance; }
	//Static members getters
	static const int GetID_Count(){return ID_Count;}

	static const int GetP_Rover_Count() { return P_Rover_Count; }
	static const int GetCheck_PR() { return Check_PR; }
	static const int GetE_Rover_Count() { return E_Rover_Count; }
	static const int GetCheck_ER() { return Check_ER; }
	static const int GetM_Rover_Count() { return M_Rover_Count; }
	static const int GetCheck_MR() { return Check_MR; }
	//Setters
	void SetIsAssigned(bool a) { IsAssigned = a; }
	void SetIsInCheckup(bool c) { IsInCheckup = c; }
	void Increment_Mission_Count() { Mission_Count++; }// if(0%4 == 0 && Mission_Count !=0)
	//static Members Getters
	 static void SetCheck_PR(int c) { Check_PR = c > 0 ? c : 5; } // Let Default checkup duration = 5 days
	 static void SetCheck_ER(int c) { Check_ER = c > 0 ? c : 5; } // Let Default checkup duration = 5 days
	 static void SetCheck_MR(int c) { Check_MR = c > 0 ? c : 5; } // Let Default checkup duration = 5 days

	 //samaa
	 void Set_Day_out(int x) { Day_out = (x > 0 ? x : 1); }//?is yhat condition ok??
	 int Get_Day_out() { return Day_out; }
	 //
	
	//void SetIsInMaintenance(bool m) { IsInMaintenance = m; }
	//Move Rover to maintenance 
	/*void Move_To_Maintenance() {
		//To be discussed with team ISA
	}*/

};
//static members initializers
int Rover::ID_Count = 0;
int Rover::P_Rover_Count = 0;
int Rover::Check_PR = 5;
int Rover::E_Rover_Count = 0;
int Rover::Check_ER = 5;
int Rover::M_Rover_Count = 0;
int Rover::Check_MR = 5;


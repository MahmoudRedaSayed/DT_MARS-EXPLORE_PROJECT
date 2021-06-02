#pragma once
//enum Rover_Type {
//	Emergency,
//	Mountainous,
//	Polar
//};
enum Type_G {
	Emergency,
	Mountainous,
	Polar
};
class Rover
{
private:
	
	//Non-Static Data Members
	Type_G Type;			// Rover Type
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

	///////////// Bonus Maintanence ////////////////
	/* int Current_Mission_EX_Time;*/
public:
	//static Data Members
	static int ID_Count;			 //Count of Rovers & assigning each new rover latest ID count
	static int Missions_Before_Check_Up;

	static int P_Rover_Count;      //Polar. Rovers count for file output
	static int M_Rover_Count;     //Mount. Rovers count for file output
	static int E_Rover_Count;    //Polar. Rovers count for file output


	static int Check_PR;      //The duration (in days) of checkups that a **Polar** rover needs 
							//to perform after completing N missions.
	static int Check_MR;    //The duration (in days) of checkups that a **Mountaionous** rover needs 
						  //to perform after completing N missions.
	static int Check_ER;  //The duration (in days) of checkups that an **Emergency** rover rover needs 
						//to perform after completing N missions.
	//Constructor & Destructor
	Rover(float Rover_Speed, Type_G T)
		:ID(++ID_Count), speed((Rover_Speed > 0) ? Rover_Speed : 3.0), IsAssigned(false)
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
	//Let Default speed for rover is 3 km/hour (Although we may not need this condition :D )
	//just added in case of invalid input
	~Rover() { /*Current_Mission_EX_Time = 0;*/ }
	//Getters
	Type_G GetType() const { return Type; }
	int GetID()const { return ID; }
	float GetSpeed()const { return speed; }
	bool GetIsAssigned()const { return IsAssigned; }
	bool GetIsInCheckup()const 
	{ 
		return IsInCheckup;
	}
	int GetMission_Count()const 
	{
		return Mission_Count;
	}
	//const bool GetIsInMaintenance() { return IsInMaintenance; }
	//Static members getters
    /*const int GetID_Count(){return ID_Count;}

	 const int GetP_Rover_Count() { return P_Rover_Count; }
     const int GetCheck_PR() { return Check_PR; }
	 const int GetE_Rover_Count() { return E_Rover_Count; }
     const int GetCheck_ER() { return Check_ER; }
     const int GetM_Rover_Count() { return M_Rover_Count; }
	 const int GetCheck_MR() { return Check_MR; }*/
	//Setters
	void SetIsAssigned(bool a) { IsAssigned = a; }
	void SetIsInCheckup(bool c) { IsInCheckup = c; }
	void Increment_Mission_Count() { Mission_Count++; }// if(0%4 == 0 && Mission_Count !=0)
	//static Members Getters
	 void SetCheck_PR(int c) { Check_PR = c > 0 ? c : 5; } // Let Default checkup duration = 5 days
	 void SetCheck_ER(int c) { Check_ER = c > 0 ? c : 5; } // Let Default checkup duration = 5 days
	 void SetCheck_MR(int c) { Check_MR = c > 0 ? c : 5; } // Let Default checkup duration = 5 days

	 //samaa
	 void Set_Day_out(int x) { Day_out = (x > 0) ? x : 1; }//?is that condition ok??//Mamdouh:I think it's fine
	 int Get_Day_out()
	 { 
		 return Day_out; 
	 }
	 //
	 //////////////////// Bonus Maintenance ////////////////////////////
	 /*
	 void set_Mission_EXtime(double ED )
	 {
		 Current_Mission_EX_Time = ED;
	 }
	 void Check_Maintenance()
	 {

	 }
	 */


	//void SetIsInMaintenance(bool m) { IsInMaintenance = m; }
	//Move Rover to maintenance 
	/*void Move_To_Maintenance() {
		//To be discussed with team ISA
	}*/

};
//static members initializers



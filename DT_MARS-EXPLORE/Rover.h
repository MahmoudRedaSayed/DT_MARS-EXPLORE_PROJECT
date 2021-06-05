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
	bool IsInMaintenance;//Is the rover undergoing Maintenance or not?
					    //\Rovers\ need maintenance when ://To be discussed with team
	//samaa
	int Day_out;
	//

	///////////// Bonus Maintanence ////////////////
	float Current_Mission_EX_Time;

public:
	//static Data Members
	static int ID_Count;			 //Count of Rovers & assigning each new rover latest ID count
	static int Missions_Before_Check_Up;

	static int P_Rover_Count;      //Polar. Rovers count for file output
	static int M_Rover_Count;     //Mount. Rovers count for file output
	static int E_Rover_Count;    //Polar. Rovers count for file output

	///////////// Bonus Maintanence ////////////////
	static int NO_ofMissions_Before_Maintenance;

	static int Check_PR;      //The duration (in days) of checkups that a **Polar** rover needs 
							//to perform after completing N missions.
	static int Check_MR;    //The duration (in days) of checkups that a **Mountaionous** rover needs 
						  //to perform after completing N missions.
	static int Check_ER;  //The duration (in days) of checkups that an **Emergency** rover rover needs 
						//to perform after completing N missions.
	//Constructor & Destructor
	Rover(float Rover_Speed, Type_G T);
	//Let Default speed for rover is 3 km/hour (Although we may not need this condition :D )
	//just added in case of invalid input
	~Rover() { /*Current_Mission_EX_Time = 0;*/ }
	//Getters
	Type_G GetType() const;
	int GetID()const;
	float GetSpeed()const;
	bool GetIsAssigned()const;
	bool GetIsInCheckup()const;
	int GetMission_Count()const;
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
	void SetSpeed(float x)
	{
		if (x > 0)
		{
			speed = x;
		}
		else
		{
			speed = 1;
		}
	}
	void SetIsAssigned(bool a);
	void SetIsInCheckup(bool c);
	void Increment_Mission_Count();// if(0%4 == 0 && Mission_Count !=0)
	//static Members Getters
	void SetCheck_PR(int c); // Let Default checkup duration = 5 days
	void SetCheck_ER(int c); // Let Default checkup duration = 5 days
	void SetCheck_MR(int c); // Let Default checkup duration = 5 days

	 //samaa
	void Set_Day_out(int x);//?is that condition ok??//Mamdouh:I think it's fine
	int Get_Day_out();

	///////////////////// Bonus Maintenance ////////////////////////////
	 
	void set_Mission_EXtime(double ED);
	bool Check_Maintenance();

};



#pragma once

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
	float speed;			// Rover Speed read from input file _ assumed to be float not int to avoid truncation,
	const int ID;           //Rover ID , assigned from latest ID_Count
	int Mission_Count;      //no. of missions that rover had executed

	int Day_out;			//#out of maintenance(if finished maintenance)/Checkup day

	///////////// Bonus Maintanence ////////////////
	float Current_Mission_EX_Time;
	float Maintanence_count;

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
	Rover(float Rover_Speed, Type_G T);
	//Let Default speed for rover is 3 km/hour (Although we may not need this condition :D )
	//just added in case of invalid input
	~Rover() {}
	//Getters
	Type_G GetType() const;
	int GetID()const;
	float GetSpeed()const;
	int GetMission_Count()const;
	
	//Setters
	void Increment_Mission_Count();// if(0%4 == 0 && Mission_Count !=0)
	//static Members Getters
	void SetCheck_PR(int c); // Let Default checkup duration = 5 days
	void SetCheck_ER(int c); // Let Default checkup duration = 5 days
	void SetCheck_MR(int c); // Let Default checkup duration = 5 days


	void Set_Day_out(int x);
	int Get_Day_out();

	///////////////////// Bonus Maintenance ////////////////////////////
	void SetSpeed(float x);
	void set_Mission_EXtime(double ED);
	bool Check_Maintenance();

};



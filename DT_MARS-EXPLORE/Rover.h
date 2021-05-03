#pragma once
class Rover
{
private:
	static int ID_Count;       //Count of Rovers & assigning each new rover latest ID count
	float speed;			  // Rover Speed read from input file _ assumed to be float not int to avoid truncation,
						     //in maintenance Condition that makes speed = 0.5 previous speed 
	const int ID;           //Rover ID , assigned from latest ID_Count
	bool IsAssigned;       //Is this rover assigned to a certain mission or not?
	bool IsInCheckup;     //Is this rover undergoing a checkup or not?
	//bool IsInMaintenance;//Is the rover undergoing Maintenance or not?
						//\Rovers\ need maintenance when ://To be discussed with team
public:
	//Constructor & Destructor
	Rover(float Rover_Speed)
		:ID(++ID_Count), speed((Rover_Speed > 0) ? Rover_Speed : 3.0), IsAssigned(false)
		, IsInCheckup(false) {}
	//Let Default speed for rover is 3 km/hour (Although we may not need this condition :D )
	//just added in case of invalid input
	~Rover() {}
	//Getters
	const int GetID() { return ID; }
	const float GetSpeed() { return speed; }
	const bool GetIsAssigned() { return IsAssigned; }
	const bool GetIsInCheckup() { return IsInCheckup; }
	//const bool GetIsInMaintenance() { return IsInMaintenance; }
	//Static members getters
	static const int GetID_Count(){return ID_Count;}
	//Setters
	void SetIsAssigned(bool a) { IsAssigned = a; }
	void SetIsInCheckup(bool c) { IsInCheckup = c; }
	//void SetIsInMaintenance(bool m) { IsInMaintenance = m; }
	//Move Rover to maintenance 
	/*void Move_To_Maintenance() {
		//To be discussed with team ISA
	}*/
};

int Rover::ID_Count = 0;
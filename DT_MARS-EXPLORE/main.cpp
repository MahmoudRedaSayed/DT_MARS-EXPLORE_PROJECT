#include"MarsStation_Class.h"
int main()
{
	MarsStation_Class object;
	object.Program_Startup();
	if (object.Rover_Exists()) // Check if there are rovers
	{
		object.Out1();// to be called in mars station
		while (!object.isFinished())
		{
			object.Execute();                  // Execute Events
			object.Assign_All_Mission();       // Assign Missions
			object.InExecution_to_Completed(); // Move missions
			object.Maintenance_to_Available();
			object.Check_Up_to_Available_All();
			/////////// printting functions & outputfile read /////////
			object.print();
			object.Out2();
			object.increment_day();
		}
		object.Out3(); // finalize Outputfile
		object.Final_print();
	}
}
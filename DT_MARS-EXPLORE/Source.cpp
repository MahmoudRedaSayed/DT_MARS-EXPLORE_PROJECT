#include"MarsStation_Class.h"
int main()
{

	MarsStation_Class object;
	object.Program_Startup();
	object.Out1();// to be called in mars station
	while (!object.isFinished())
	{
		object.Execute();
		object.Assign_All_Mission();
		object.InExecution_to_Completed();
		object.Check_Up_to_Available_All();
		/////////// printting functions & outputfile read /////////
		object.increment_day();
		object.Out2();
	}
	object.Out3();
}
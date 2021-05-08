#include"MarsStation_Class.h"
int main()
{

	MarsStation_Class object;
	object.Program_Startup();
	while (!object.isFinished())
	{
		object.Execute();
		object.Assign_All_Mission();
		object.InExecution_to_Completed();
		/////////// printting functions & outputfile read /////////
		object.increment_day();
	}

}
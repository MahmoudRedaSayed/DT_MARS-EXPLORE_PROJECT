#include"MarsStation_Class.h"
int main(){
	
	MarsStation_Class object;
	object.Program_Startup();
	object.Out1();// to be called in mars station
	while (!object.isFinished())
	{
		object.Execute();
		object.InExecution_to_Completed();
		object.Assign_All_Mission();
		//object.Assign_All_Mission();
		//object.InExecution_to_Completed();
		//object.Assign_All_Mission();
		object.Check_Up_to_Available_All();
		/////////// printting functions & outputfile read /////////
		object.print();
		object.Out2();
		object.increment_day();
	}
	object.Out3();

}
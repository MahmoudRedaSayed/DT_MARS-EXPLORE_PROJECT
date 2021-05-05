#include "MarsStation_Class.h"

void MarsStation_Class::Assign_M_M()
{
	//23ml auto promoted b3d el assign el 3ady?
	Mountainous_Mission* MMptr;
	//M_Mission.peek(MMptr)
	while (!M_Mission.isEmpty()&& !Available_MR.isEmpty())
	{
		//if()
		M_Mission.dequeue(MMptr);
		MMptr->Calculate_WD(Day_count);
		EXMission.enqueue(MMptr);
	}

	

}

int MarsStation_Class::Day_count = 0;

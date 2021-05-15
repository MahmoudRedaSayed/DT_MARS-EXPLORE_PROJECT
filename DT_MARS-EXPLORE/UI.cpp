#include "UI.h"
#include <iostream>
using namespace std;

UI::UI()
	:Mode(Terminal_Mode::Interactive)
{
	for (int i = 0; i < 3; i++)
		cout << "\n========================================================\n";
}

UI::~UI()
{
	cout << "\nSimulation ends, Output file created\n";
	for (int i = 0; i < 3; i++)
		cout << "\n========================================================\n";

}

void UI::SelectMode()
{
	
	cout << "\n<<<<<<<< Please select simulation mode >>>>>>>>\n" <<
		"1-Interactive Mode  (produces output file including simulation statistics, monitors & prints daily statistics during simulation on terminal window, you can increase simulation days manually!) \n" <<
		"2-Step-By-Step Mode (same as interactive , but increases days automatically)! \n" <<
		"3-Silent Mode		 (program produces only output files, no simulation steps will be shown on the console)!\n" <<
		"please type number of mode from (1,2 and 3)\n";


}

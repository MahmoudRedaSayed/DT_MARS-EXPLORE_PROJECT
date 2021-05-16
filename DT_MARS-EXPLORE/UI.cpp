#include "UI.h"


UI::UI()
	:Mode(Terminal_Mode::Interactive)
{
	for (int i = 0; i < 3; i++)
		std::cout << "\n================================================================================================================\n";
	SelectMode();
}

UI::~UI()
{
	std::cout << "\nSimulation ends, Output file created\n";
	for (int i = 0; i < 3; i++)
		std::cout << "\n================================================================================================================\n";

}

void UI::SelectMode()
{
	int m;
	std::cout << "\n<<<<<<<< Please select simulation mode [default mode : step-by-step] >>>>>>>>\n" <<
		"1-Interactive Mode  (produces output file including simulation statistics, monitors & prints daily statistics\n during simulation on terminal window, you can increase simulation days manually!) \n" <<
		"2-Step-By-Step Mode (same as interactive , but increases days automatically)! \n" <<
		"3-Silent Mode		 (program produces only output files, no simulation steps will be shown on the console)!\n" <<
		"please type number of mode from (1,2 and 3)\n";
	std::cin >> m;
	switch (m)
	{
	case 1:
		Mode = Terminal_Mode::Interactive;
		break;
	case 2:
		Mode = Terminal_Mode::Step_By_Step;
		break;
	case 3:
		Mode = Terminal_Mode::Silent;
		break;
	default:
		Mode = Terminal_Mode::Step_By_Step;
		break;
	}
}



string UI::read_input_file_name()
{
	string FName;
	cout << "\nPlease::enter the name of the file the you want to load it\n" << endl;
	cin >> FName;
	return FName;
}



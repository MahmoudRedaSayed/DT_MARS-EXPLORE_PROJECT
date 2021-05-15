#pragma once
enum class Terminal_Mode {
	Interactive ,
	Step_By_Step ,
	Silent
};
class UI
{
private:
	Terminal_Mode Mode;
public:
	UI();
	~UI();
	//shall make function to recieve input file name ___ talk to 7oda
	void SelectMode();
	void Print_To_Console(int Curr_Day );//3 waiting missions lists , 1 in exec , 3 available rovers,3 checkup lists, 3 completed lists<int>
};


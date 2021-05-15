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
};


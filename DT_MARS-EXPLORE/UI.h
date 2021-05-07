#pragma once
enum Terminal_Mode {
	Interactive,
	Step_By_Step,
	Silent
};
class UI
{
private:
	Terminal_Mode Mode;
public:
	UI();
	~UI();

	//void SelectMode
};


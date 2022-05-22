#include "UI.h"
#include <iostream>
#include "Company.h"
#include "promote.h"
//
UI::UI(Company* comp)
{
	Shipco = comp;

}

void UI::startinterface() {

	if (mode == 3) return;

	cout << "-----------------------------Interface-----------------------------------" << endl;
	cout << "Current Time(Day: Hour): ";
	PrintTime(Shipco->getCurrTime());
	cout << endl;
	Shipco->PrintWaitingCargos();
	cout << endl;
	cout << "-----------------------------------------------------------------" << endl;
	Shipco->PrintLoadingTrucks();
	cout << endl;
	cout << "-----------------------------------------------------------------" << endl;
	Shipco->PrintEmptyTrucks();
	cout << endl;
	cout << "-----------------------------------------------------------------" << endl;
	Shipco->PrintMovingCargos();
	cout << endl;
	cout << "-----------------------------------------------------------------" << endl;
	Shipco->PrintInCheckupTrucks();
	cout << endl;
	cout << "-----------------------------------------------------------------" << endl;
	Shipco->PrintDeliveredCargos();
	cout << endl;
	cout << "-----------------------------------------------------------------" << endl;
	switch (mode)
	{
	case 1:
		cout << endl;
		cout << "Press any key to continue.... " << endl;
		char cont;
		cin >> cont;
		break;
	case 2:
		Sleep(3000);
		break;
	default:
		break;

	}


}
void UI::chooseMode()
{

	cout << "Shipping Company Simulator" << endl;
	cout << endl;
	Sleep(300);
	cout << "1 - Interactive Mode" << endl;
	cout << "2 - Step-By-Step Mode" << endl;
	cout << "3 - Silent mode" << endl;
	cout << "Please, select the Program mode (Enter number of mode) : " << endl;
	cin >> mode;
	switch (mode) {
	case 1:
		cout << "Interactive Mode" << endl;
		break;
	case 2:
		cout << "Step-By-Step Mode" << endl;
		break;
	case 3:
		cout << "Silent Mode" << endl;
		cout << "Simulation Starts....." << endl;
		cout << "Simulation Ended, Output File is ready" << endl;
		return;
		break;


	default:
		//error statement to be done later 
		cout << "ERROR, Wrong entry" << endl;
		break;
	}
}
void UI::endline()
{
	cout << endl;
}
void UI::PrintTime(const Time& t)
{
	cout << t.getDays() << ":" << t.gethour();
}
/*template<typename T>
 void UI::inputData(T& data)
{
	cin >> data;
}

template<typename T>
 void UI::printData(const T data) const
{
	cout << data;

}*/
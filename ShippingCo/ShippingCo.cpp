#include <iostream>
#include"cargo.h"
#include "defs.h"
#include "Company.h"
#include<fstream>
using namespace std;

int main()
{
	//create company
	Company Shipco;

	//ifstream object
	ifstream ifile;

	//Program starts
	if (Shipco.startup(ifile))
	{
		//gets the interface mode from the user
		Shipco.chooseModee();

		//still dont know the condition
		while (true)
		{
			//events excecution function
			Shipco.Excutevents();

			//Cargo assigning fuctiom
			Shipco.assigncargototruck();

			//Moves a truck to start a delivery if its moving time comes
			Shipco.movetruck();

			//Delivring function
			Shipco.Deliver();

			//Printing function
			Shipco.StartInterface();

			//Saving functiom
			Shipco.SaveUp();
		}
	}

	system("pause");
	return 0;
}
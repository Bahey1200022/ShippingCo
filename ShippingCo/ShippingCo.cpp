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
		//Shipco.Excutevents();
		//still dont know the condition

		while (Shipco.Excutevents() || Shipco.operate() )
		{
			

			//Cargo assigning fuctiom
			Shipco.assigncargototruck();

			//Moves a truck to start a delivery if its moving time comes
			Shipco.movetruck();

			//Delivring function
			Shipco.Deliver();

			//Returns the trucks 
			Shipco.returnTruck();

			//Printing function
			Shipco.StartInterface();

		}

		//Saving functiom
		Shipco.SaveUp();
	}
	
	//cout << "code is working" << endl;
	system("pause");
	return 0;
}
#pragma once
#include "defs.h"
#include "truck.h"




class truck;

class cargo
{
	int ID;
	char type;
	int Cost;
	//loading time and unloading time
	int LT;
	//preparation time
	Time PT;
	//Cargo Distance
	int dist;

	char cargostatus;
	//?
	truck* truckassi;
	//Waiting Time
	Time WT;
	//priority
	int p;
	//calcultate waiting TIme
	void calcWT();
	//Calculate Priority
	void calcP();
	//cargo delivery time
	Time CDT;
	//calculate cargo Delivery Time
	void calcCDT();

public:
	//constructors
	cargo();
	cargo(int id, char typ, int cost, int load, Time pt, int distance, truck* truck_assign = nullptr);

	//getters
	int getdist();
	char getType();
	int getID();
	int getcost();
	int getlt();
	Time getCDT();

	truck* gettruck();

	Time getpt();

	int getP();

	//setters 
	void settype();
	void setCDT(Time t);
	int getwt(Time c);

};

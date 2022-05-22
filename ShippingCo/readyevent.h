#pragma once

#include "events.h"



class readyevent :public events
{
	//Event Time
	Time ET;
	//cargo Id
	int ID;
	//Cargo Distance
	int Dist;
	//Cargo loading/unloadiing time
	int LT;
	//cargo cost
	int Cost;
	//cargo Type
	char type;


public:
	//constructors
	readyevent();
	readyevent(int id, char cargotype, Time et, int dist, int lt, int cost, Company* com);

	//void setcargot(char type);
	// 
	//Setters
	void setET(Time Et);
	void setID(int id);
	void setDist(int dist);
	void setLT(int lt);
	void setcost(int c);

	//getters
	Time getET() const;
	int getID() const;
	int getDist();
	int getCost();
	int getLT();

	//RaadyEvent execute function
	void Excute();

	~readyevent();
};
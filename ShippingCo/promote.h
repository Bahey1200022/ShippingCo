#pragma once

#include "events.h"


//class company;
class promote :public events
{
	//Event Time
	Time ET;
	//Cargo ID
	int ID;
	//Promotion fees
	int extramoney;
public:
	//constructors
	promote();
	promote(int id, Time t, int extra, Company* com);
	//Promotion event execute functiom
	void Excute();
	//getters
	Time getET() const;
	int getID() const;
	//destructor
	~promote();
};
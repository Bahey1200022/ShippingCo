#pragma once
#include "events.h"
#include"defs.h"
//class Company;
class cancellationevent :public events
{
	//Event Time
	Time ET;
	//Cargo ID
	int ID;
public:
	//constructor
	cancellationevent();
	cancellationevent(int id, Time et, Company* co);
	//getters
	Time getET() const;
	int getID() const;
	//Cancellation event execute function
	void Excute();
};
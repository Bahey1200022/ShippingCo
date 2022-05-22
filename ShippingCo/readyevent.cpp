#include "readyevent.h"
#include "cargo.h"
#include"Company.h"


readyevent::readyevent()
{
}

readyevent::readyevent(int id, char cargotype, Time et, int dist, int lt, int cost, Company* com) {
	ID = id;
	type = cargotype;
	ET = et;
	Dist = dist;
	LT = lt;
	Cost = cost;
	shipco = com;
}

void readyevent::setET(Time Et) {

	ET = Et;
}

void readyevent::setID(int id) {
	ID = id;
}

void readyevent::setDist(int dist) {
	Dist = dist;
}

void readyevent::setLT(int lt) {
	LT = lt;
}

void readyevent::setcost(int c) {
	Cost = c;
}

//ctype readyevent :: getcargot() { return TYPE;}

int readyevent::getCost() { return Cost; }

int readyevent::getDist() { return Dist; }

Time readyevent::getET()const { return ET; }

int readyevent::getLT() { return LT; }

int readyevent::getID()const { return ID; }



void readyevent::Excute() {

	cargo* cargoo;

	if (type == 'V')
	{
		cargoo = new cargo(ID, type, Cost, LT, ET, Dist);
		shipco->addcargo(cargoo);
	}

	if (type == 'N') {

		cargoo = new cargo(ID, type, Cost, LT, ET, Dist);
		shipco->addcargo(cargoo);
	}

	if (type == 'S')
	{

		cargoo = new cargo(ID, type, Cost, LT, ET, Dist);
		shipco->addcargo(cargoo);
	}




}


readyevent::~readyevent()
{
}


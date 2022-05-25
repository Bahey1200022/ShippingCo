#include "cargo.h"


cargo::cargo()
{
}


cargo::cargo(int id, char typ, int cost, int load, Time pt, int distance, truck* truck_assign) :truckassi(nullptr) {

	ID = id;
	type = typ;
	Cost = cost;
	LT = load;
	PT = pt;
	dist = distance;
	truckassi = truck_assign;
}

char cargo::getType() { return type; }

int cargo::getID() { return ID; }

int cargo::getcost() { return Cost; }

int cargo::getlt() { return LT; }

Time cargo::getCDT()
{
	return CDT;
}

int cargo::getP() { calcP(); return p; }

truck* cargo::gettruck() { return truckassi; }

void cargo::calcWT() {}

void cargo::calcCDT() {}

void cargo::settype() { type = 'V'; }

void cargo::setCDT(Time t)
{
	CDT = t;
}

void cargo::settruckid(int c)
{
	truckid = c;
}

void cargo::calcP() { p = Cost / (2*dist + LT); }

Time cargo::getpt() { return PT; }

int cargo::getdist() { return dist; }

int cargo::getwt(Time c) {

	int d1 = c.getDays();
	int h1 = c.gethour();
	int d2 = PT.getDays();
	int h2 = PT.gethour();
	
	return (d1 - d2) * 24 + h1 - h2;
}
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

int cargo::getP() { calcP(); return p; }

truck* cargo::gettruck() { return truckassi; }

void cargo::calcWT() {}

void cargo::calcCDT() {}

void cargo::settype() { type = 'V'; }

void cargo::calcP() { p = Cost / (dist + LT); }

Time cargo::getpt() { return PT; }

int cargo::getdist() { return dist; }
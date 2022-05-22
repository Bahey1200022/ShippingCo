#include "promote.h"
#include "cargo.h"
#include"Company.h"

promote::promote() {}

promote::promote(int id, Time t, int extra, Company* com) {
	ID = id;
	ET = t;
	extramoney = extra;
	shipco = com;

}

void promote::Excute() {

	cargo* cargotobepromoted;

	cargotobepromoted = shipco->searchnormc(ID);
	if (cargotobepromoted)
	{
		cargotobepromoted->settype();
		shipco->addcargo(cargotobepromoted);
	}

}
Time promote::getET() const {

	return ET;
}
int promote::getID() const { return ID; }

promote::~promote()
{
}
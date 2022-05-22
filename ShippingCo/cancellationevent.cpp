#include "cancellationevent.h"
#include "cargo.h"
#include"Company.h"

cancellationevent::cancellationevent(int id, Time et, Company* co)
{
	ID = id;
	ET = et;
	shipco = co;
}

void cancellationevent::Excute() {


	shipco->cancelcargo(ID);

}


Time cancellationevent::getET() const {

	return ET;
}
int cancellationevent::getID() const { return ID; }

cancellationevent::cancellationevent() {}
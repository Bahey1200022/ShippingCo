#include "truck.h"

int truck::id = 0;

void truck::CalculateMovingTime()
{
	//LoadingEntry time days
	int CurrDay = loadingentry.getDays();
	//LoadingENtry time hours
	int CurrHour = loadingentry.gethour();
	//adds the current hours to the sum of the total caargos' loading time
	int newH = CurrHour + sumlt;
	//calculates moving time
	MT.calculateTime(CurrDay, newH);
}

cargo* truck::getFirstCargo()
{
	//ptr to the first cargo in the pQueue
	cargo* cPtr;
	cargosassigned.peek(cPtr);
	return cPtr;
}

truck::truck() :ID(id)
{
	id++;
}

truck::truck(char t, int c, int s, int jbc, int ti) : ID(id) {
	ttype = t;
	capacity = c;
	speed = s;
	J = jbc;
	checkupt = ti;
	id++;
	journeys = 0;
	sumlt = 0;
	cargoscontained = 0;
	cargosd = 0;
	totaljourneys = 0;

}

int truck::getID() { return ID; }

void truck::resetj() {
	journeys = 0;
}

PriQueue<cargo*, int> truck::getcargos() {
	return cargosassigned;
}

int truck::getcheckupt() {
	return checkupt;
}

void truck::CalculateActiveTime()
{
	
	ActiveTime = ActiveTime + (FT - loadingentry);
}

void truck::setFT(Time t)
{
	FT = t;
}

Time truck::getcheckupentry() { return checkupentry; }

void truck::setcheckupentry(Time t) { checkupentry = t; }

char truck::getType()
{
	return ttype;
}
void truck::PrintCargos()
{
	cargosassigned.Print1();
}

void truck::assigncargo(cargo* c) {

	int dist = c->getdist();
	sumlt = sumlt + (c->getlt());

	cargosassigned.enqueueAsc(c, dist);
	cargoscontained++;


}
int truck::gettotalj() { return journeys; }
int truck::getj() { return J; }

void truck::getFurtherestCargoDist()
{
	cargo* cPtr;
	cargosassigned.peekLast(cPtr);
	getFurtherestCargo = cPtr->getdist();
	
}

bool truck::DeliverCargo(cargo*& DeliveredCargo)
{
	//if (cargoscontained == 0) cargoscontained = 0;
	cargoscontained--;
	return(cargosassigned.dequeue(DeliveredCargo));
	

}
int truck::getcargoscount() { return cargoscontained; }
void truck::caculateCDt()
{
	//ptr to the first cargo in the pQueue
	cargo* cPtr;
	cPtr = getFirstCargo();

	int truckSpeed = speed;
	int cargoDistance = cPtr->getdist();
	int cargoUnloadTIme = cPtr->getlt();
	int hours = (cargoDistance / truckSpeed) + cargoUnloadTIme;
	//TIme object
	Time t1;
	t1.settime(0, hours);
	t1 = t1 + MT;  //t1 now is the CDt

	//CDT is now calculated in the first cargo in the Pqueue
	cPtr->setCDT(t1);
}

Time truck::getCDT()
{
	cargo* c;
	c = getFirstCargo();
	return(c->getCDT());
}

void truck::DI(Time currTime) {
	//int furthDist = getFurtherestCargoDist();
	int hours = (getFurtherestCargo / speed) * 2 +sumlt;
	Time t(0, hours);
	Di = t + currTime;

}
int truck::getltsum() {
	
	return sumlt;
}

Time truck::getMT() {

	Time l(0, getltsum());

	MT = l + loadingentry;

	return MT;



}

void truck::CalculateTimeUntilMoving(const Time& currtime)
{
	//truck's moving time
	int d1 = MT.getDays();
	int h1 = MT.gethour();
	//passed object days and hours
	int d2 = currtime.getDays();
	int h2 = currtime.gethour();
	//in hours
	TimeUntilMoving = (d1 - d2) * 24 + (h1 - h2);
}



int truck::getTimeUntilMoving()
{
	return TimeUntilMoving;
	return 0;
}

Time truck::getloadentry() {

	return loadingentry;
}

void truck::setloadentry(Time k) {
	loadingentry = k;
}

Time truck::getDI()
{
	
	return Di;
}

void truck::setcargotype(char t) { cargotype = t; }
char truck::getcargotype() { return cargotype; }

int truck::gettotaljourneys()
{
	return totaljourneys;
}

int truck::gettotalcargosd()
{
	return cargosd;
}

PriQueue<cargo*, int> truck::getqcargos() { return cargosassigned; }




void truck::incrementjourneys()
{
	totaljourneys++;
	journeys++;
}

void truck::incrementcargosd()
{
	cargosd++;
}

truck::~truck()
{
	/////////////////////////////////////////////////////////////////////////////////
	//=====================================================================================//
	//=============================================destructor============================///
}
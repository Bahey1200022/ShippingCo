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


}

int truck::getID() { return ID; }

void truck::resetj() {
	journeys = 0;
}

PriQueue<cargo*> truck::getcargos() {
	return cargosassigned;
}

int truck::getcheckupt() {
	return checkupt;
}

Time truck::getcheckupentry() { return checkupentry; }

void truck::setcheckupentry(Time t) { checkupentry = t; }

char truck::getType()
{
	return ttype;
}


void truck::assigncargo(cargo* c) {

	int dist = c->getdist();
	sumlt = sumlt + (c->getlt());

	cargosassigned.enqueueAsc(c, dist);



}

int truck::DI() {
	int di;int sumloadingt = 0;
	cargo* c;
	queue<cargo*>q;
	while (cargosassigned.dequeue(c)) {
		sumloadingt = c->getlt() + sumloadingt;
		q.enqueue(c);
	}
	cargo* f;
	while (q.dequeue(f)) {
		cargosassigned.enqueueAsc(f, f->getdist());
	}
	int furthestd = c->getdist();//furthest distance cargo

	di = furthestd / speed + sumloadingt + furthestd / speed;//?!?!?!?!?!?!
	return di;

}
int truck::getltsum() {
	/*PriQueue<cargo*>q(cargosassigned);
	int c = 0;
	cargo* f;
	while (q.dequeue(f)) {
		c = c + f->getlt();
	}*/
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








truck::~truck()
{
}
#pragma once
#include "cargo.h"
#include "defs.h"
#include "queue.h"
#include"Priqueue.h"


class cargo;

class truck
{
	//truck id
	static int id;

	const int ID;

	//truck's type
	char ttype;
	//truck's capacity
	int capacity;
	//checkup time in hours
	int checkupt;
	//truck's speed
	int speed;

	//moving time
	Time MT;

    //Active
	Time ActiveTime;

	//the time at which the truck enters the loading queue
	Time loadingentry;

	//time at which the truck must return to the company
	Time Di;

	//the time at which the truck enters the loading queue
	Time loadingentry;

	//time the truck entered checkUp
	Time checkupentry;

	//finish time (the time the truck finishes delivering)
	Time FT;

	//time at which the truck must return to the company
	Time Di;

	char truckstatus;

	//cargos assigned to the truck
	PriQueue<cargo*, int>cargosassigned;

	int cargoscontained;
	//num of journeys before checkup
	int J;
	//num of journeys the truck performed
	int journeys;

	//for stats
	int totaljourneys;
	//total c deliv.
	int cargosd;
	
	//Time between the current time and moving time(used in the loading trucks priority queue)
	int TimeUntilMoving;

	
	int getFurtherestCargo;
	
	//the total loading time of the assigned carrgos
	int sumlt;

	char cargotype; //type of c a tr. is carrying 
public:
	//constructors
	truck();
	truck(char t, int c, int s, int jbc, int ti);

	int getID();

	//resets journeys back to zero
	void resetj();
	void PrintCargos();

	///
	PriQueue<cargo*, int> getcargos();

	int getcheckupt();

	//function that sums the Total active time
	void CalculateActiveTime();
	
	//setter
	void setFT(Time t);

	Time getcheckupentry();

	void setcheckupentry(Time t);
	
	int getcargoscount();
	//gets type of the truck
	char getType();

	//returns the total loading time of the cargos
	int getltsum();

	//assigns a cargo to the truck
	void assigncargo(cargo* c);


	//reruens a pointer to the first cargo in the pQueue(utility fn)
	cargo* getFirstCargo();


	//reruens a pointer to the first cargo in the pQueue(utility fn)
	void getFurtherestCargoDist();

	//Removes the 1st cargo in the queue
	bool DeliverCargo(cargo*& DeliveredCargo);

	//calculates the CDT for the first cargo in the pQueue
	void caculateCDt();

	//gets the CDT of the first crago in the truck pQueue
	Time getCDT();

	//calc delivery interval and returns it
	void DI(Time);

	int gettotalj();
	int getj();

	//calculates the time at which a truck will start moving to deliver the cargos 
	void CalculateMovingTime();

	//loading q entry time +loading time
	Time getMT();

	//calculates the time until Mt in hours 
	void CalculateTimeUntilMoving(const Time& currtime);
	PriQueue<cargo*, int> getqcargos();
	//getter
	int getTimeUntilMoving();

	Time getloadentry();
	//sets the the time the truck entered the loading trucks queue
	void setloadentry(Time k);

	Time getDI();
		
	void setcargotype(char t);
	char getcargotype();


	int gettotaljourneys();
	int gettotalcargosd();

	void incrementjourneys();
	void incrementcargosd();
	~truck();
};
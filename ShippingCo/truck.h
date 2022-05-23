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
	char truckstatus;
	//cargos assigned to the truck
	PriQueue<cargo*>cargosassigned;
	//num of journeys before checkup
	int J;
	//num of journeys the truck performed
	int journeys;
	//moving time
	Time MT;
	//Time between the current time and moving time(used in the loading trucks priority queue)
	int TimeUntilMoving;
	//time the truck entered checkUp
	Time checkupentry;
	//the time at which the truck enters the loading queue
	Time loadingentry;

	//the total loading time of the assigned carrgos
	int sumlt;
public:
	//constructors
	truck();
	truck(char t, int c, int s, int jbc, int ti);

	int getID();

	//resets journeys back to zero
	void resetj();

	PriQueue<cargo*> getcargos();

	int getcheckupt();

	Time getcheckupentry();

	void setcheckupentry(Time t);

	//gets type of the truck
	char getType();

	//returns the total loading time of the cargos
	int getltsum();

	//assigns a cargo to the truck
	void assigncargo(cargo* c);

	//calc delivery interval
	int DI();

	//calculates the time at which a truck will start moving to deliver the cargos 
	void CalculateMovingTime();

	//loading q entry time +loading time
	Time getMT();

	//calculates the time until Mt in hours 
	void CalculateTimeUntilMoving();

	//getter
	int getTimeUntilMoving();

	Time getloadentry();
	//sets the the time the truck entered the loading trucks queue
	void setloadentry(Time k);
	~truck();
};
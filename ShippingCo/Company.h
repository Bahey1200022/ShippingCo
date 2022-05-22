#pragma once
#include"events.h"
#include"queue.h"
#include"Priqueue.h"
#include "cargo.h"
#include"Node.h"
#include "LinkedList.h"
#include"promote.h"
#include<fstream>
#include"cancellationevent.h"
#include "readyevent.h"
#include"UI.h"

using namespace std;
class UI;
class Company
{
private:

	//current time
	Time currtime;
	//UI POINTER
	UI* uiPtr;
	//total no.  of trucks and no each type of trucks
	int totalnumtrucks, numtspecial, numtVIP, numtnorm;
	// trucks' capacity
	int cavip, canorm, casp;
	//Autop(days) MaxW(hours)
	int autoplimit, maxW;


	int totalcargos;
	int numcspecial, numcVIP, numcnorm;//total no.s of each type of cargos
	int mnumspecial, mnumcVIP, mnumcnorm;//moving cargos
	int  wnumcspecial, wnumcVIP, wnumcnorm; //waiting cargos



	//no. of promoted cargos
	int promotedcargos;
	//no. of auto promoted cargos
	int autopromotedcargos;
	//no. of deliveredCargos
	int totalDeliveredCargos;
	//No. of events
	int EventCount;


	///////////////////   LISTS   /////////////////////////

	//Events Queue
	queue<events*>eventss;

	/// waiting cargo lists
	PriQueue<cargo*>vipcargos;
	LinkedList<cargo*>normcargos;
	queue<cargo*>spcargos;

	////Ready trucks' lists
	queue<truck*>sptrucks;
	queue<truck*>normtrucks;
	queue<truck*>viptrucks;

	/////check up trucks
	queue<truck*>checkuptnormal;
	queue<truck*> checkuptspecial;
	queue<truck*>checkuptvip;


	/////

	//Delivered Cargo list

	queue<cargo*> DelieveredCargos; //

	//Loading trucks
	PriQueue<truck*>loadingtrucks;//pri least sum of lt 

	//Moving trucks
	PriQueue<truck*>movingtrucks; //pri:least Delivery interval


	/////phase 1 moving cargos list 
	//queue<cargo*> movingc;





public:
	//constructor
	Company();

	//Input file reading functiom
	bool startup(ifstream& ifile);

	//Adds a cargo to the appropriate list
	void addcargo(cargo*& cargoo);

	//Adds an event to the events queue
	void addevent(events* eventsqueue);

	void deccargos();//

	//deletes a cargo from the normal cargo waiting list
	void cancelcargo(int id);

	//executes the event 
	bool Excutevents();

	//saving function
	bool SaveUp();

	//searches the normal crgo waiting list for a specific cargo
	cargo* searchnormc(int id);

	//increments the currtime by one hour
	void nexttimestep();

	//checks if all the cargo waiting lists are empty
	bool nocargosleft();

	//checks if there are no available trucks
	bool noavailabletruck();

	//return the currtime TIme object
	Time getCurrTime();

	//Gets the interfaceMode from the user
	void chooseModee();

	//calls the interface function from class UI
	void StartInterface();

	//the auto promotion function
	void  autopromotion();

	void truckscheckup();

	//the cargo assiging function
	void assigncargototruck();

	//Rmoves a truck from the loading list if and when its moving time comes
	void movetruck();

	//Delivering cargos function
	void Deliver();

	//printing functions
	void PrintWaitingCargos();
	void PrintLoadingTrucks(); //
	void PrintEmptyTrucks();
	void PrintMovingCargos();//
	void PrintInCheckupTrucks(); //
	void PrintDeliveredCargos();



	//Destructor
	~Company();



	//phase 1 functions not needed 
	//queue<cargo*>&getshipped();
	//LinkedList<cargo*>getnormalcargos();
	//void movenormcargostomoving();
	//void movespcargostomoving();
	//void movevipcargostomoving();
	//void Simulation();
	///////////////////////////////////////////////////////////////////////////////////////////////////


};
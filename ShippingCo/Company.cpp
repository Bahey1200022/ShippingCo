#include "Company.h"
Company::Company() : EventCount(0) {
	currtime.settime(0, 0);
	totalcargos = 0;
	totalnumtrucks = 0;
	numcnorm = 0;
	numcspecial = 0;
	numcVIP = 0;
	numtnorm = 0;
	numtspecial = 0;
	numtVIP = 0;
	promotedcargos = 0;
	maxW = 0;
	autoplimit = 0;
	wnumcnorm = 0;
	wnumcspecial = 0;
	wnumcVIP = 0;
	autopromotedcargos = 0;
	totalDeliveredCargos = 0;
	promotedcargos = 0;
	uiPtr = new UI(this);
}

bool Company::startup(ifstream& ifile)
{
	int Nt, St, Vt, Ns, Ss, Vs, Nc, Sc, Vc, j, NCh, VCh, SCh, AutoP, MaxW, E, ID, Dist, Lt;
	char EventType, cargoType;
	float Money;
	int days, hours;
	Time t1, t2, t3;
	char dot;
	//Time t1;
	/*
	Nt: no of normal trucks
	St: no of special trucks
	Vt: no of vip trucks
	Ns(km/s):normal trucks' speed
	Ss(km/s):special trucks' speed
	Vs(km/s): vip trucks' speed
	Nc: normal trucks' Capacity
	Sc: special trucks' Capacity
	Vc: vip trucks' Capacity
	J: max trips without a checkup
	Cn: normal trucks' checkup duration
	Sn: special trucks' checkup duration
	Vn: vip trucks checkup duration
	E: no of events
	ID: cargo id
	Dist(km): cargo dist
	Lt(hrs):time to load/unload cargo
	Money:cargo cost (R)
	extra fees (p)
	t1: Time object
	*/
	string filename;
	uiPtr->printData("Insert File name");
	uiPtr->inputData(filename);
	ifile.open(filename);
	if (ifile.is_open())
	{
		ifile >> Nt >> St >> Vt;
		ifile >> Ns >> Ss >> Vs;
		ifile >> Nc >> Sc >> Vc;
		ifile >> j >> NCh >> SCh >> VCh;
		ifile >> AutoP >> MaxW;
		ifile >> E;

		//	EventList = new events * [E];
		totalnumtrucks = Nt + St + Vt;
		numtspecial = St;
		numtVIP = Vt;
		numtnorm = Nt;
		autoplimit = AutoP;
		maxW = MaxW;
		cavip = Vc;
		canorm = Nc;
		casp = Sc;
		//
		for (int i = 0;i < St;i++) {
			truck* t = new truck('S', Sc, Ss, j, SCh);
			sptrucks.enqueue(t);
		}
		for (int i = 0;i < Vt;i++) {
			truck* t = new truck('V', Vc, Vs, j, VCh);
			viptrucks.enqueue(t);
		}
		for (int i = 0;i < Nt;i++) {
			truck* t = new truck('N', Nc, Ns, j, NCh);
			normtrucks.enqueue(t);
		}


		//
		for (int i = 0;i < E;i++)
		{
			ifile >> EventType;
			switch (EventType)
			{
			case 'R':
				ifile >> cargoType >> days >> dot >> hours >> ID >> Dist >> Lt >> Money;
				t1.settime(days, hours);
				events* p1;
				p1 = new readyevent(ID, cargoType, t1, Dist, Lt, Money, this);
				if (eventss.enqueue(p1))
				{
					EventCount++;
					totalcargos++;
				}
				break;
			case 'P':
				ifile >> days >> dot >> hours >> ID >> Money;
				t2.settime(days, hours);
				events* p2;
				p2 = new promote(ID, t2, Money, this);
				if (eventss.enqueue(p2))
					EventCount++;
				break;
			case 'X':
				ifile >> days >> dot >> hours >> ID;
				t3.settime(days, hours);
				events* p3;
				p3 = new cancellationevent(ID, t3, this);
				if (eventss.enqueue(p3))
				{
					EventCount++;
					totalcargos--;
				}
				break;
			default:
				//condition to bemade if data in file is incorrect (maybe use exception handling)
				break;


			}

		}
		ifile.close();
		return true;
	}

	else {
		uiPtr->printData("Error in openning input file");
		uiPtr->endline();
		return false;
	}


}

Company::~Company() {

	uiPtr->printData("Simulation ended");
	uiPtr->endline();
	delete uiPtr;
}
void Company::addcargo(cargo*& cargoo) {

	if (cargoo->getType() == 'N')
	{
		normcargos.InsertEnd(cargoo);
		wnumcnorm++;
	}
	else if (cargoo->getType() == 'V')
	{
		vipcargos.enqueueDesc(cargoo, cargoo->getP());
		wnumcVIP++;
	}

	else if (cargoo->getType() == 'S')
	{
		spcargos.enqueue(cargoo);
		wnumcspecial++;
	}


}



void Company::deccargos() {
	numcnorm--;
	totalcargos--;
	wnumcnorm--;
}

bool Company::SaveUp()
{
	return false;
}

cargo* Company::searchnormc(int id) {//used to promote a cargo by searchung for it

	Node<cargo*>* wantedcargo = normcargos.getHead();

	while (wantedcargo != nullptr)
	{
		if (wantedcargo->getItem()->getID() == id) {
			cargo* car = wantedcargo->getItem();
			normcargos.deleteNode(wantedcargo->getItem());
			numcVIP++;
			numcnorm;
			wnumcnorm--;
			return car;
			break;
		}
		else wantedcargo = wantedcargo->getNext();

	}
	return 0;
}

void Company::addevent(events* eventsqueue) {

	eventss.enqueue(eventsqueue);

}

void Company::nexttimestep() {

	currtime++;

}

void Company::cancelcargo(int id) {//cancelling a node from a linked list 

	if (normcargos.getHead() == nullptr)
		return;


	Node<cargo*>* prev = normcargos.getHead();
	Node<cargo*>* current = prev->getNext();

	if (prev->getItem()->getID() == id)
	{
		normcargos.setHead(normcargos.getHead()->getNext());
		normcargos.decreaseSize();
		deccargos();
		return;

	}

	while (current != nullptr)
	{
		if (current->getItem()->getID() == id)
		{
			prev->setNext(current->getNext());
			normcargos.decreaseSize();
			deccargos();
			return;
		}
		else
		{
			prev = prev->getNext();
			current = current->getNext();
		}
	}

}

bool Company::Excutevents() {
	bool z = false; //found an even or not
	events* E;
	while (eventss.peek(E))
	{
		if (E->getET() == currtime)
		{
			eventss.dequeue(E);
			E->Excute();
			z = true;
		}
		else break;
	}
	currtime++;
	return z;
}

bool Company::nocargosleft() {
	if (normcargos.getSize() == 0 && vipcargos.isEmpty() && spcargos.Isempty() && checkuptnormal.Isempty() && checkuptspecial.Isempty() && checkuptvip.Isempty())
		return true;
	else return false;
}

Time Company::getCurrTime()
{
	return currtime;
}

void Company::chooseModee()
{
	//calls the originl function from UI class
	uiPtr->chooseMode();
}

void Company::StartInterface()
{
	//calls the interface function from class UI
	uiPtr->startinterface();
}

void Company::autopromotion() { /// autop days after a cargo is waiting then promoted ,normal c

	Node<cargo*>* c = normcargos.getHead();

	cargo* l;//to store the cargo in another variable to delete it
	while (c) {
		l = c->getItem();
		if (currtime.getDays() - l->getpt().getDays() >= autoplimit) {
			c = c->getNext();
			normcargos.deleteNode(l);
			l->settype();
			vipcargos.enqueueDesc(l, l->getP());
			numcnorm--;numcVIP++;
			autopromotedcargos++;
		}
		else c = c->getNext();
	}

}

void Company::truckscheckup() { //check if trucks are done with their check up

	truck* t;

	///vip trucks
	if (!checkuptvip.Isempty()) {
		bool keeploop = true;
		while (keeploop) {
			checkuptvip.peek(t);
			Time h(0, t->getcheckupt());
			if (t->getcheckupentry() + h == currtime && !checkuptvip.Isempty()) {

				checkuptvip.dequeue(t);
				t->resetj();
				viptrucks.enqueue(t);


			}
			else keeploop = false;
		}


	}
	///special
	if (!checkuptspecial.Isempty()) {
		bool keeploop = true;
		while (keeploop) {
			checkuptspecial.peek(t);
			Time h(0, t->getcheckupt());
			if (t->getcheckupentry() + h == currtime && !checkuptspecial.Isempty()) {

				checkuptspecial.dequeue(t);
				t->resetj();
				sptrucks.enqueue(t);


			}
			else keeploop = false;
		}


	}
	//normal trucks
	if (!checkuptnormal.Isempty()) {
		bool keeploop = true;
		while (keeploop) {
			checkuptnormal.peek(t);
			Time h(0, t->getcheckupt());
			if (t->getcheckupentry() + h == currtime && !checkuptnormal.Isempty()) {

				checkuptnormal.dequeue(t);
				t->resetj();
				normtrucks.enqueue(t);


			}
			else keeploop = false;
		}


	}

}

bool Company::noavailabletruck() {
	return (sptrucks.Isempty() && normtrucks.Isempty() && viptrucks.Isempty());
}

void Company::assigncargototruck() {

	//truckscheckup();

	//autopromotion();
	//checkss if company is in its working hours
	if (currtime.gethour() > 5 && currtime.gethour() < 23)
	{

		if (!noavailabletruck() && !nocargosleft())
		{

			///vip trucks assignment
			if (!vipcargos.isEmpty()) {
				//check vip cargos

				if (!viptrucks.Isempty()) {
					if (vipcargos.size() >= cavip) {
						///loading rule
						truck* t;
						//removes Vip truck from ready trucks list
						viptrucks.dequeue(t);

						for (int i = 0; i < cavip; i++) {
							cargo* c;
							vipcargos.dequeue(c);
							t->assigncargo(c);
						}
						//insert the truck into the loading truck list
						t->setloadentry(currtime);
						//calculates the tuck's moving time
						t->CalculateMovingTime();
						//inserts the truck in the loading trucks 
						loadingtrucks.enqueueAsc(t, t->getTimeUntilMoving());


					}


				}
				//if there are no vip trucks try assigning to no normal

				//checks if there are available normal trucks
				else if (!normtrucks.Isempty())
				{
					//checks if the ready cargos are equal or more than the truck's capacity
					if (vipcargos.size() >= canorm) {
						///loading rule
						truck* t;
						//removes normal truck from ready trucks' list
						normtrucks.dequeue(t);

						//assign the cargos to the truck 
						for (int i = 0; i < canorm; i++)
						{
							cargo* c;
							//removes VIP cargos from ready VIP cargo list
							vipcargos.dequeue(c);
							t->assigncargo(c);
						}
						//insert the truck into the loading truck list
						t->setloadentry(currtime);
						//calculates the tuck's moving time
						t->CalculateMovingTime();
						//inserts the truck in the loading trucks 
						loadingtrucks.enqueueAsc(t, t->getTimeUntilMoving());


					}


				}
				//checks if there are available special trucks
				else if (!sptrucks.Isempty())
				{
					//checks if the ready cargos are equal or more than the truck's capacity
					if (vipcargos.size() >= casp)
					{
						///loading rule
						truck* t;
						//removes Special truck from ready trucks list
						sptrucks.dequeue(t);
						//assign the cargos to the truck 
						for (int i = 0; i < casp; i++)
						{
							cargo* c;
							//removes VIP cargos from ready VIP cargo list
							vipcargos.dequeue(c);
							t->assigncargo(c);
						}
						//insert the truck into the loading truck list
						t->setloadentry(currtime);

						//calculates the tuck's moving time
						t->CalculateMovingTime();
						//inserts the truck in the loading trucks 
						loadingtrucks.enqueueAsc(t, t->getTimeUntilMoving());


					}
				}





			}
			//End of VIP assigning 

			//Special trucks assiging 
			//Checks if there are ready special cargo
			if (!spcargos.Isempty())
			{
				//checks if there is an available special truck
				if (!sptrucks.Isempty())
				{
					//checks if no of special cargos is equal or more than the truck's capacity
					if (spcargos.getsize() >= casp)
					{
						truck* t;
						//removes a special truck from the available trucks list
						sptrucks.dequeue(t);
						//assigns the cargo to the truck
						for (int i = 0; i < casp; i++)
						{
							cargo* c;
							//removes the cargo from the ready list
							spcargos.dequeue(c);
							t->assigncargo(c);
						}
						//insert the truck into the loading truck list
						t->setloadentry(currtime);
						//calculates the tuck's moving time
						t->CalculateMovingTime();
						//inserts the truck in the loading trucks 
						loadingtrucks.enqueueAsc(t, t->getTimeUntilMoving());


					}

				}
			}
			//END of Special cargo assigning 


			//normal trucks assiging 
			//Checks if there are ready normal cargo
			if (normcargos.getSize() != 0)
			{
				//checks if there is an available normal truck
				if (!normtrucks.Isempty())
				{
					//checks if the number of normal cargos is equal or more than the truck's capacity
					if (normcargos.getSize() >= canorm)
					{

						truck* t;
						//removes a normal truck from the available trucks list
						normtrucks.dequeue(t);
						//assigns the cargo to the truck
						for (int i = 0; i < canorm; i++)
						{
							cargo* c;
							//removes the cargo from the waiting list
							normcargos.RemoveFirst(c);
							t->assigncargo(c);

						}
						// insert the truck into the l. truck list
						t->setloadentry(currtime);
						//calculates the tuck's moving time
						t->CalculateMovingTime();
						//inserts the truck in the loading trucks 
						loadingtrucks.enqueueAsc(t, t->getTimeUntilMoving());


					}
				}
				//if there are no available normal trucks check vip trucks
				else if (!viptrucks.Isempty())
				{

					//checks if the number of normal cargos is equal or more than the truck's capacity
					if (normcargos.getSize() >= cavip)
					{
						truck* t;
						//removes a VIP truck from the available trucks list
						viptrucks.dequeue(t);
						//assigns the cargo to the truck
						for (int i = 0; i < cavip; i++)
						{
							cargo* c;
							//removes the cargo from the ready list
							normcargos.RemoveFirst(c);
							t->assigncargo(c);
						}
						// insert the truck into the l truck list
						t->setloadentry(currtime);
						//calculates the tuck's moving time
						t->CalculateMovingTime();
						//inserts the truck in the loading trucks 
						loadingtrucks.enqueueAsc(t, t->getTimeUntilMoving());

					}
				}
			}
			//End of normal cargos assigning  












		}





	}

}

void Company::movetruck() {
	truck* t;
	//checks if the Truck(s) MT came or not
	while (loadingtrucks.peek(t))
	{
		//moves the truck to the moving trucks list to start delivering 
		if (t->getMT() == currtime)
		{
			loadingtrucks.dequeue(t);
			movingtrucks.enqueueAsc(t, t->DI());
		}
		//if the first truck will not move none will
		else break;
	}

}



void Company::Deliver()
{

}


void Company::PrintWaitingCargos()
{
	int TotalWaitingCargos; //total waiting cargos
	int TotalWaitingNormal; //total waiting normal cargos
	int TotalWaitingSpecial; //total waiting special cargos
	int	TotalWaitingVIP; //total waiting vip cargos


	TotalWaitingNormal = normcargos.getSize();
	TotalWaitingSpecial = spcargos.getsize();
	TotalWaitingVIP = vipcargos.size();

	//Adds them all up
	TotalWaitingCargos = TotalWaitingNormal + TotalWaitingSpecial + TotalWaitingVIP;
	uiPtr->printData(TotalWaitingCargos);
	uiPtr->printData(" ");
	uiPtr->printData("Waiting Cargos: ");


	//starts to print Normal Cargos
	uiPtr->printData("[");
	normcargos.Printlist();
	uiPtr->printData("] ");

	//starts to print Special cargos
	uiPtr->printData("(");
	spcargos.print();
	uiPtr->printData(") ");

	//starts to print VIP Cargos
	uiPtr->printData("{");
	vipcargos.Print();
	uiPtr->printData("} ");



}

void Company::PrintLoadingTrucks()
{
	int TotalLoadingTrucks = loadingtrucks.size();
	uiPtr->printData(TotalLoadingTrucks);
	uiPtr->printData(" ");
	uiPtr->printData("Loading Trucks: ");




}

void Company::PrintEmptyTrucks()
{
	int TotalEmptyTrucks;
	int TotalEmptyNormal = normtrucks.getsize();
	int	TotalEmptySpecial = sptrucks.getsize();
	int	TotalEmptyVip = viptrucks.getsize();

	//Adds them all up
	TotalEmptyTrucks = TotalEmptyNormal + TotalEmptySpecial + TotalEmptyVip;
	uiPtr->printData(TotalEmptyTrucks);
	uiPtr->printData(" ");
	uiPtr->printData("Empty Trucks: ");

	//prints Normal trucks
	uiPtr->printData("[");
	normtrucks.print();
	uiPtr->printData("] ");

	//prints Special trucks
	uiPtr->printData("(");
	sptrucks.print();
	uiPtr->printData(") ");

	//prints VIP tricks
	uiPtr->printData("{");
	viptrucks.print();
	uiPtr->printData("} ");

}

void Company::PrintMovingCargos() //
{
	uiPtr->printData(0);
	uiPtr->printData(" ");
	uiPtr->printData("Moving Cargos: ");
	uiPtr->printData("[], ");
	uiPtr->printData("(), ");
	uiPtr->printData("{} ");
}

void Company::PrintInCheckupTrucks()
{
	/**int TotalTrucksInCheckup = CheckUpQueue.getsize();
	uiPtr->printData(TotalTrucksInCheckup);
	uiPtr->printData(" ");
	uiPtr->printData("In-Checkup Trucks: ");

	//prints Normal trucks in checkUps
	uiPtr->printData("[");
	checkuptnormal.print()
		uiPtr->printData("] ");

	//prints Special trucks
	uiPtr->printData("(");
	checkuptspecial.print();
	uiPtr->printData(") ");

	//prints VIP tricks
	uiPtr->printData("{");
	checkuptvip.print();
	uiPtr->printData("} ");


	*/
}

void Company::PrintDeliveredCargos()
{
	//int TotalDeliveredCargos;  //total delivered
	//int TotalDeliveredNormalCargos; //total delivered normal cargos
	//int TotalDeliveredSpecialCargos; //total delivered special cargos
	//int TotalDeliveredVIPCargos; //total delivered vip cargos*?*/

	//
	////adds them all up
	////TotalDeliveredCargos = TotalDeliveredNormalCargos + TotalDeliveredSpecialCargos + TotalDeliveredVIPCargos;
	//uiPtr->printData(TotalDeliveredCargos);
	//uiPtr->printData(" ");
	//uiPtr->printData("Delivered Cargos: ");

	////starts to print  delivered cargos
	//uiPtr->printData("[");
	//finishednormcargos.print();
	//uiPtr->printData("] ");
	//
	////starts to print delivered special cargos
	//uiPtr->printData("(");
	//finishedspcargos.print();
	//uiPtr->printData(") ");

	////starts to print delivered vip cargos
	//uiPtr->printData("{");
	//finishedvipcargos.print();
	//uiPtr->printData("} ");

	//total delivered
	int TotalDeliveredCargos = DelieveredCargos.getsize();
	uiPtr->printData(TotalDeliveredCargos);
	uiPtr->printData(" ");
	uiPtr->printData("Delivered Cargo: ");

	//Prints Delivered cargos in order of delivery 
	DelieveredCargos.print();




}


//////////////////////////////////////////////////////////////////////////////////////////////////

/*phase 1 functions not needed for phase 2
void Company::movenormcargostomoving() {
	if (normcargos.getSize() == 0) return;
Node<cargo*>* curr = normcargos.getHead();
movingc.enqueue(curr->getItem());
normcargos.deleteNode(curr->getItem());
numcnorm--;
}
void Company::movespcargostomoving() {
	if (spcargos.getsize() == 0) return;
cargo* x;
spcargos.dequeue(x);
movingc.enqueue(x);
numcspecial--;
}
void Company::movevipcargostomoving() {
	if (vipcargos.size() == 0) return;
cargo* y;
vipcargos.dequeue(y);
movingc.enqueue(y);
numcVIP--;
}
queue<cargo*> &Company::getshipped() { return movingc; }
void Company::Simulation(){
	uiPtr->chooseMode();
	int c1 = 0; //corner cases
	int c = 0;
	//Excutevents();
	//c++;c1++;
	uiPtr->startinterface();
	while (!nocargosleft() || !eventss.Isempty() || c1==5 ) {
		if (c1 == 5) c1 = 0;
		Excutevents();
		uiPtr->startinterface();
		c++;c1++;
		if (c == 5) {
			movenormcargostomoving();
			movespcargostomoving();
			movevipcargostomoving();
			c = 0;
		}
	}
	uiPtr->printData("The simulation ended ");
}*/

////////////////////////////////////////////////////////////////////////////////////////////////////////
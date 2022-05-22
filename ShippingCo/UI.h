#pragma once
#include <fstream>
#include <windows.h>
#include "queue.h"
#include "defs.h"
#include "events.h"
#include "cargo.h"
#include "Company.h"
#include "promote.h"
#include "cancellationevent.h"
#include "readyevent.h"
#include "LinkedList.h"
using namespace std;
//class Company;

class UI
{
	int mode;
	Company* Shipco;

public:
	UI(Company* comp);
	void startinterface(); //the company's interface function
	void chooseMode();//gets the mode from the user

	void endline();
	void PrintTime(const Time& t);

	template <typename T>
	void inputData(T& data) { cin >> data; }

	template <typename T>
	void printData(const T data)const { cout << data; }



};


#pragma once
#include"defs.h"
class Company;
class events {
protected:

	Company* shipco;
public:

	virtual Time getET() const = 0;
	virtual int getID() const = 0;
	virtual void  Excute() = 0;

};



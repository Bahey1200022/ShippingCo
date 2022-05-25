#pragma once 
#include "priorityN.h"

using namespace std;

template < typename T, typename U>
class PriQueue
{
	priorityN<T, U>* backPtr;
	priorityN<T, U>* frontPtr;
	int Count;

public:
	PriQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool enqueueAsc(const T& newEntry, U priority);
	bool enqueueDesc(const T& newEntry, U priority);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	bool peekLast(T& data) const;
	int size();
	void Print() const;
	void Print1() const;
	~PriQueue();
	void PrintTruck() const;
	PriQueue(const PriQueue<T, U>& LQ);
};

template < typename T, typename U>
PriQueue<T, U>::PriQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	Count = 0;

}

template < typename T, typename U>
bool PriQueue<T, U>::isEmpty() const
{
	return (frontPtr == nullptr);
}

template < typename T, typename U>
bool PriQueue<T, U>::enqueueAsc(const T& newEntry, U priority)
{
	priorityN<T, U>* tmp, * q;
	tmp = new priorityN<T, U>;
	tmp->setItem(newEntry);
	tmp->setPriority(priority);
	if (frontPtr == nullptr || priority < frontPtr->getPriority())
	{
		tmp->setNext(frontPtr);
		frontPtr = tmp;
	}
	else
	{
		q = frontPtr;
		while (q->getNext() != nullptr && q->getNext()->getPriority() <= priority)
			q = q->getNext();
		tmp->setNext(q->getNext());
		q->setNext(tmp);
	}
	priorityN<T, U>* t = frontPtr;
	while (t->getNext()) { t = t->getNext(); }
	backPtr = t;
	Count++;
	return true;
}

template < typename T, typename U>
bool PriQueue<T, U>::enqueueDesc(const T& newEntry, U priority)
{
	priorityN<T, U>* tmp, * q;
	tmp = new priorityN<T, U>;
	tmp->setItem(newEntry);
	tmp->setPriority(priority);
	if (frontPtr == nullptr || priority > frontPtr->getPriority())
	{
		tmp->setNext(frontPtr);
		frontPtr = tmp;
	}
	else
	{
		q = frontPtr;
		while (q->getNext() != nullptr && q->getNext()->getPriority() >= priority)
			q = q->getNext();
		tmp->setNext(q->getNext());
		q->setNext(tmp);
	}
	priorityN<T, U>* t = frontPtr;
	while (t->getNext()) { t = t->getNext(); }
	backPtr = t;
	Count++;
	return true;
}

template < typename T, typename U>
bool PriQueue<T, U>::enqueue(const T& newEntry)
{
	priorityN<T, U>* newNodePtr = new priorityN<T, U>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now

	Count++;
	return true;
}

template < typename T, typename U>
bool PriQueue<T, U>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	priorityN<T, U>* NodePriToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (NodePriToDeletePtr == backPtr)
		backPtr = nullptr;

	delete NodePriToDeletePtr;

	Count--;
	return true;

}

template < typename T, typename U>
bool PriQueue<T, U>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

template<typename T, typename U>
bool PriQueue<T, U>::peekLast(T& data) const
{
	if (isEmpty())
		return false;

	data = backPtr->getItem();
	return true;

}

template < typename T, typename U>
PriQueue<T, U>::~PriQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}

template < typename T, typename U>
PriQueue<T, U>::PriQueue(const PriQueue<T, U>& LQ)
{
	priorityN<T, U>* NodePriPtr = LQ.frontPtr;
	if (!NodePriPtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first NodePri
	priorityN<T, U>* ptr = new priorityN<T, U>(NodePriPtr->getItem());
	frontPtr = backPtr = ptr;
	NodePriPtr = NodePriPtr->getNext();

	//insert remaining NodePris
	while (NodePriPtr)
	{
		priorityN<T, U>* ptr = new priorityN<T, U>(NodePriPtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePriPtr = NodePriPtr->getNext();
	}
}

template < typename T, typename U>
int PriQueue<T, U>::size()
{
	return Count;
}

template < typename T, typename U>
void PriQueue<T, U>::Print() const {
	priorityN<T, U>* tmp = frontPtr;
	while (tmp) {
		cout << tmp->getItem()->getID() << ", ";
		tmp = tmp->getNext();
	}
}
template<typename T, typename U>///for the cargos
void PriQueue<T, U>::Print1() const
{
	priorityN<T, U>* tmp = frontPtr;

	char type = tmp->getItem()->getType();
	switch (type)
	{
	case 'N':
		cout << "[";
		break;
	case 'S':
		cout << "(";
		break;
	case 'V':

		cout << "{";
		break;
	default:
		break;
	}
	while (tmp)
	{



		cout << tmp->getItem()->getID() << ", ";
		tmp = tmp->getNext();
	}
	switch (type)
	{
	case 'N':
		cout << "] ";
		break;
	case 'S':
		cout << ") ";
		break;
	case 'V':

		cout << "} ";
		break;
	default:
		break;
	}

}

template<typename T, typename U>
void PriQueue<T, U>::PrintTruck() const
{
	priorityN<T, U>* tmp = frontPtr;
	while (tmp)
	{
		cout << tmp->getItem()->getID();
		tmp->getItem()->PrintCargos();
		cout << " ";
		tmp = tmp->getNext();
	}
}
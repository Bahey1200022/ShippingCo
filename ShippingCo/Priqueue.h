#pragma once 
#include "priorityN.h"
using namespace std;

template < typename T>
class PriQueue
{
	priorityN<T>* backPtr;
	priorityN<T>* frontPtr;
	int Count;

public:
	PriQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool enqueueAsc(const T& newEntry, int priority);
	bool enqueueDesc(const T& newEntry, int priority);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	int size();
	void Print() const;
	~PriQueue();

	PriQueue(const PriQueue<T>& LQ);
};

template <typename T>
PriQueue<T>::PriQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	Count = 0;

}

template <typename T>
bool PriQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

template <typename T>
bool PriQueue<T>::enqueueAsc(const T& newEntry, int priority)
{
	priorityN<T>* tmp, * q;
	tmp = new priorityN<T>;
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
	Count++;
	return true;
}

template <typename T>
bool PriQueue<T>::enqueueDesc(const T& newEntry, int priority)
{
	priorityN<T>* tmp, * q;
	tmp = new priorityN<T>;
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
	Count++;
	return true;
}

template <typename T>
bool PriQueue<T>::enqueue(const T& newEntry)
{
	priorityN<T>* newNodePtr = new priorityN<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now

	Count++;
	return true;
}

template <typename T>
bool PriQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	priorityN<T>* NodePriToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (NodePriToDeletePtr == backPtr)
		backPtr = nullptr;

	delete NodePriToDeletePtr;

	Count--;
	return true;

}

template <typename T>
bool PriQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

template <typename T>
PriQueue<T>::~PriQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}

template <typename T>
PriQueue<T>::PriQueue(const PriQueue<T>& LQ)
{
	priorityN<T>* NodePriPtr = LQ.frontPtr;
	if (!NodePriPtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first NodePri
	priorityN<T>* ptr = new priorityN<T>(NodePriPtr->getItem());
	frontPtr = backPtr = ptr;
	NodePriPtr = NodePriPtr->getNext();

	//insert remaining NodePris
	while (NodePriPtr)
	{
		priorityN<T>* ptr = new priorityN<T>(NodePriPtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePriPtr = NodePriPtr->getNext();
	}
}

template <typename T>
int PriQueue<T>::size()
{
	return Count;
}

template <typename T>
void PriQueue<T>::Print() const {
	priorityN<T>* tmp = frontPtr;
	while (tmp) {
		cout << tmp->getItem()->getID() << ", ";
		tmp = tmp->getNext();
	}
}
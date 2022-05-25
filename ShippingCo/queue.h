#pragma once
#include "Node.h"
#include<iostream>
using namespace std;
template<typename T>
class queue {
private:
	Node<T>* back;
	Node<T>* front;
	int s; //size of queue
public:
	queue();
	bool Isempty() const;
	bool enqueue(const T& N_entry);
	bool dequeue(T& fr);//front
	bool peek(T& fr) const;
	int getsize();
	void print() const;
	void print2() const;
	void printtruck() const;
	~queue();
	//copy constructor
	queue(const queue<T>& LQ);
};

template <typename T>
queue<T>::queue() : s(0)
{
	back = nullptr;
	front = nullptr;

}

template <typename T>
bool queue<T>::Isempty() const
{
	return (front == nullptr);
}

template <typename T>
bool queue<T>::enqueue(const T& N_entry) {

	Node<T>* newNodePtr = new Node<T>(N_entry);
	if (Isempty()) //special cases
	{
		front = newNodePtr;
		back = newNodePtr;

	}
	else
	{
		back->setNext(newNodePtr);
		newNodePtr->setNext(nullptr);
		back = newNodePtr;
	}
	s++;
	return true;
}

template <typename T>
bool queue<T>::dequeue(T& fr)
{
	if (Isempty())
		return false;

	Node<T>* nodeToDeletePtr = front;
	fr = front->getItem();
	front = front->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == back)	 // Special case: last node in the queue
		back = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	s--;
	return true;

}


template <typename T>
bool queue<T>::peek(T& fr) const
{
	if (Isempty())
		return false;

	fr = front->getItem();
	return true;

}

template <typename T>
queue<T>::~queue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}

template <typename T>
queue<T>::queue(const queue<T>& LQ)
{
	Node<T>* NodePtr = LQ.front;
	if (!NodePtr) //LQ is empty
	{
		front = back = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	front = back = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		back->setNext(ptr);
		back = ptr;
		NodePtr = NodePtr->getNext();
	}
}

template <typename T>
int queue<T>::getsize()
{
	return s;
}

template <typename T>
void queue<T>::print() const {
	Node<T>* tmp = front;
	while (tmp) {
		cout << tmp->getItem()->getID() << ", ";
		tmp = tmp->getNext();
	}
}

template<typename T>
void queue<T>::print2() const
{
	Node<T>* tmp = front;
	while (tmp)
	{
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
		cout << tmp->getItem()->getID();
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

		
		tmp = tmp->getNext();
	}
}
template<typename T>
void queue<T> ::printtruck() const {
	Node<T>* tmp = front;
	while (tmp) {
		cout << tmp->getItem()->getID() << ", ";
		tmp = tmp->getNext();
	}
}
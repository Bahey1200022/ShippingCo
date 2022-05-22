#pragma once 
//node with a priority property to form a pri. queue

template < typename T>
class priorityN
{
private:
	T item;
	priorityN<T>* next;
	int Priority;
public:
	priorityN();
	priorityN(const T& it);
	priorityN(const T& it, priorityN<T>* nextp);
	void setItem(const T& it);
	void setNext(priorityN<T>* nextp);
	void setPriority(int P);
	T getItem() const;
	priorityN<T>* getNext() const;
	int getPriority();
};


template < typename T>
priorityN<T>::priorityN()
{
	next = nullptr;
}

template < typename T>
priorityN<T>::priorityN(const  T& it)
{
	item = it;
	next = nullptr;
}

template < typename T>
priorityN<T>::priorityN(const T& it, priorityN<T>* nextp)
{
	item = it;
	next = nextp;
}
template < typename T>
void priorityN<T>::setItem(const T& it)
{
	item = it;
}

template < typename T>
void priorityN<T>::setNext(priorityN<T>* nextp)
{
	next = nextp;
}

template < typename T>
T priorityN<T>::getItem() const
{
	return item;
}

template < typename T>
priorityN<T>* priorityN<T>::getNext() const
{
	return next;
}

template < typename T>
int priorityN<T>::getPriority()
{
	return Priority;
}

template < typename T>
void priorityN<T>::setPriority(int P)
{
	Priority = P;
}
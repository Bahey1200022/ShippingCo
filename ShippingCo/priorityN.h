#pragma once 
//node with a priority property to form a pri. queue

template < typename T, typename U>
class priorityN
{
private:
	T item;
	priorityN<T, U>* next;
	U Priority;
public:
	priorityN();
	priorityN(const T& it);
	priorityN(const T& it, priorityN<T, U>* nextp);
	void setItem(const T& it);
	void setNext(priorityN<T, U>* nextp);
	void setPriority(U P);
	T getItem() const;
	priorityN<T, U>* getNext() const;
	U getPriority();
};


template < typename T, typename U>
priorityN<T, U>::priorityN()
{
	next = nullptr;
}

template < typename T, typename U>
priorityN<T, U>::priorityN(const  T& it)
{
	item = it;
	next = nullptr;
}

template < typename T, typename U>
priorityN<T, U>::priorityN(const T& it, priorityN<T, U>* nextp)
{
	item = it;
	next = nextp;
}

template < typename T, typename U>
void priorityN<T, U>::setItem(const T& it)
{
	item = it;
}

template < typename T, typename U>
void priorityN<T, U>::setNext(priorityN<T, U>* nextp)
{
	next = nextp;
}

template < typename T, typename U>
T priorityN<T, U>::getItem() const
{
	return item;
}

template < typename T, typename U>
priorityN<T, U>* priorityN<T, U>::getNext() const
{
	return next;
}

template < typename T, typename U>
U priorityN<T, U>::getPriority()
{
	return Priority;
}

template < typename T, typename U>
void priorityN<T, U>::setPriority(U P)
{
	Priority = P;
}
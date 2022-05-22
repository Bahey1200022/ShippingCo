#pragma once
template < typename T>
class Node
{
	T item;  //data members for node
	Node<T>* next;
public:
	Node();//setters and getters
	Node(const T& it);
	Node(const T& it, Node<T>* nextp);
	void setItem(const T& it);
	void setNext(Node<T>* nextp);
	T getItem() const;
	Node<T>* getNext() const;
};
//implementaion

template < typename T>
Node<T>::Node()
{
	next = nullptr;
}

template < typename T>
Node<T>::Node(const  T& it)
{
	item = it;
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& it, Node<T>* nextp)
{
	item = it;
	next = nextp;
}
template < typename T>
void Node<T>::setItem(const T& it)
{
	item = it;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextp)
{
	next = nextp;
}

template < typename T>
T Node<T>::getItem() const
{
	return item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}

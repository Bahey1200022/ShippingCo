
#pragma once
#include "Node.h"
#include<iostream>

template <typename T>
class LinkedList
{
private:
	Node<T>* head;
	int size;
public:
	LinkedList()
	{
		head = nullptr;
		size = 0;
	}
	void InsertBeg(const T& event)
	{
		Node<T>* newNode = new Node<T>(event);
		newNode->setNext(head);
		head = newNode;
		size++;
	}
	void InsertEnd(const T& data)
	{
		Node<T>* NodeToBeInserted = new Node<T>(data);
		Node<T>* ptr = head;
		Node<T>* temp = ptr;
		if (head == nullptr)
		{
			head = NodeToBeInserted;
			head->setNext(nullptr);
		}
		else
		{
			while (ptr->getNext())
			{
				ptr = ptr->getNext();
				temp = ptr;
			}
			temp->setNext(NodeToBeInserted);
			NodeToBeInserted->setNext(nullptr);
		}
		size++;
	}

	bool deleteNode(const T& value)
	{
		Node<T>* nodeToBeDeleted = nullptr;
		Node<T>* beforeTheDeleted = head;
		Node<T>* temp = head;
		if (!head)
			return false;
		if (head->getItem() == value)
		{
			nodeToBeDeleted = head;
			head = head->getNext();
			nodeToBeDeleted->setNext(nullptr);
			//delete nodeToBeDeleted;
			nodeToBeDeleted = nullptr;
			size--;
			return true;
		}
		while (temp != nullptr)
		{
			if (temp->getItem() == value)
			{
				nodeToBeDeleted = temp;
				break;
			}
			else
			{
				beforeTheDeleted = temp;
				temp = temp->getNext();
			}
		}
		if (nodeToBeDeleted == nullptr)
			return false;
		else
		{
			beforeTheDeleted->setNext(nodeToBeDeleted->getNext());
			nodeToBeDeleted->setNext(nullptr);
			delete nodeToBeDeleted;
			nodeToBeDeleted = nullptr;
			size--;
			return true;
		}
	}
	int getSize()
	{
		return size;
	}
	Node<T>* getHead()
	{
		return head;
	}
	void setHead(Node<T>* head)
	{
		this->head = head;
	}
	void decreaseSize()
	{
		size--;
	}

	void Printlist() {
		Node<T>* curr = head;
		while (curr) {
			cout << curr->getItem()->getID() << ",";
			curr = curr->getNext();
		}
	}
	bool RemoveLast(T& data)
		//removes the last node in the linked lis and return it by reference
	{
		if (!head)
			return false;
		Node<T>* currPtr = head;
		Node<T>* prevPtr = NULL;
		if (size == 1)
		{
			data = head->getItem();
			head = NULL;
			size--;
			return true;
		}
		while (currPtr->getNext())
		{
			prevPtr = currPtr;
			currPtr = currPtr->getNext();

		}
		data = currPtr->getItem();
		prevPtr->setNext(NULL);
		delete currPtr;
		size--;
		return true;

	}
	bool RemoveFirst(T& data)
		//removes the first node and returns it by reference 
	{
		if (!head)
			return false;
		Node<T>* currPtr = head;
		if (head->getNext())
		{
			head = head->getNext();

		}
		else
		{
			head = NULL;
		}
		data = currPtr->getItem();
		delete currPtr;
		size--;
		return true;


	}
	bool peekList(T& d) {
		if (size==0)
			return false;

		d = head->getItem();
		return true;
	}
};
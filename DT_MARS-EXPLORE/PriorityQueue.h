#pragma once
#ifndef PRIORITY_QUEUE_
#define PRIORITY_QUEUE_
//#define LINKED_QUEUE_

#include "Node.h"
#include "PriorityQueueADT.h"
#include <vector>
using namespace std;


template <typename T>
class PriorityQueue :public PriorityQueueADT<T>
{
private:
	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	PriorityQueue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;
	}
	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}


	bool enqueue(const T& newEntry, double priority)
	{
		Node<T>* newNodePtr = new Node<T>(newEntry, priority);
		// Insert the new node
		if (isEmpty()) {	//special case if this is the first node to insert
			frontPtr = newNodePtr;
			backPtr = newNodePtr;
			return true;
		}                   // The queue is empty
		else if (priority > frontPtr->getpriority())
		{
			newNodePtr->setNext(frontPtr);
			frontPtr = newNodePtr;
			return true;
		}
		else
		{
			Node<T>* temp = frontPtr;
			while (temp->getNext())
			{
				if (temp->getNext()->getpriority() < priority)
				{
					newNodePtr->setNext(temp->getNext());
					temp->setNext(newNodePtr);
					return true;
				}
				temp = temp->getNext();
			}
			temp->setNext(newNodePtr);
			backPtr = newNodePtr; // New node is the last node now
		}
		return true;

	}



	bool dequeue(T& frntEntry)
	{
		if (isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = frontPtr;
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
			backPtr = nullptr;

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;

		return true;
	}

	bool peek(T& frntEntry)  const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		return true;
	}
	~PriorityQueue()
	{
		T temp;

		//Free (Dequeue) all nodes in the queue
		while (dequeue(temp));
	}

	//copy constructor
	PriorityQueue(const PriorityQueue<T>& LQ)
	{
		Node<T>* NodePtr = LQ.frontPtr;
		if (!NodePtr) //LQ is empty
		{
			frontPtr = backPtr = nullptr;
			return;
		}

		//insert the first node
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		frontPtr = backPtr = ptr;
		NodePtr = NodePtr->getNext();

		//insert remaining nodes
		while (NodePtr)
		{
			Node<T>* ptr = new Node<T>(NodePtr->getItem());
			backPtr->setNext(ptr);
			backPtr = ptr;
			NodePtr = NodePtr->getNext();
		}
	}

};




#endif


#ifndef _NODE
#define _NODE
template < typename T>
class Node
{
private :
	T item; // A data item
	Node<T>* next; // Pointer to next node
	double priority;
public :
	Node();
	Node( const T & r_Item, double p = 0);
	Node( const T & r_Item, Node<T>* nextNodePtr, double p = 0);
	void setItem( const T & r_Item);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const ;
	double getpriority() const;
	Node<T>* getNext() const ;
}; // end Node

template < typename T>
Node<T>::Node()
{
	next = nullptr;
	priority = 0;
} 

template < typename T>
Node<T>::Node( const T& r_Item,double p)
{
	item = r_Item;
	next = nullptr;
	priority = p;
} 

template < typename T>
Node<T>::Node( const T& r_Item, Node<T>* nextNodePtr,double p)
{
	item = r_Item;
	next = nextNodePtr;
	priority = p;
}
template < typename T>
void Node<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
} 

template < typename T>
T Node<T>::getItem() const
{
	return item;
} 

template < typename T>
double Node<T>::getpriority() const
{
	return priority;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
} 
#endif

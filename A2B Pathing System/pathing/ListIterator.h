/*************************************************************************
*
*	Template:
*		ListIterator
*	
*	Constructors:
*		ListIterator() - Default constructor
*		ListIterator(DoubleLinkedList*) - 1 Arg constructor; Copies the pointer 
*			to a list to traverse.
*		~ListIterator() - Destructor
*		ListIterator(const ListIterator&) - Copy constructor
*		ListIterator& operator=(const ListIterator&) - Operator =
*
*	Mutators:
*		string GetDesc() - Returns the description of the ListIterator.
*		Vertex* GetDest() - Returns the pointer to the vertex.
*		int GetWeight() - Returns the weight of the ListIterator.
*
*	Methods:
*		
*
*************************************************************************/

#ifndef LISTITERATOR
#define LISTITERATOR

#include "AbstractIterator.h"
#include "DoubleLinkedList.h"
#include "Node.h"

template <typename T>
class ListIterator: public AbstractIterator<T>
{
public:
	//1 arg constructor
	ListIterator(DoubleLinkedList<T> *list);
	//defualt constructor
	ListIterator();
	//copy constructor
	ListIterator(const ListIterator<T> &copy);
	//operator=
	ListIterator<T>& operator=(const ListIterator<T> &rhs);
	//destructor
	virtual ~ListIterator();

	virtual void First()=0;			//implemented in the derived classes
	virtual void MoveNext()=0;		//implemented in the derived classes
	bool IsDone();					//has the list reached the end
	Node<T>* GetCurrent();			//returns the current node in the list

protected:
	Node<T>* GetHead();				//gets the head of the list for First()
	Node<T>* GetTail();				//gets the tail of the list for First()
	Node<T>* GetNext();				//moves the current node to the next
	Node<T>* GetPrev();				//moves the current not the the next

	DoubleLinkedList<T>* _list;		//pointer to the list being traversed
	Node<T>* current;				//current node in the list
};

/*************************************************************************
*
*		Constructors
*
*************************************************************************/
template <typename T>
ListIterator<T>::ListIterator(DoubleLinkedList<T> *list): _list(list), current(0)
{
}

template <typename T>
ListIterator<T>::ListIterator(): current(0), _list(0)
{
}

template <typename T>
ListIterator<T>::ListIterator(const ListIterator<T> &copy)
{
	*this = copy;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator= (const ListIterator<T> &rhs)
{
	this = rhs;
	return this;
}

template <typename T>
ListIterator<T>::~ListIterator()
{
}

/*************************************************************************
*		End Constructors
*************************************************************************/

/*************************************************************************
*
*	Purpose:		Returns a boolean value representing whether the 
*					traversal has finished or not.
*	Entry:			Nothing.
*	Exit:			Returns true if the current node points to trash.
*
*************************************************************************/
template <typename T>
bool ListIterator<T>::IsDone()
{
	return (current == 0);
}

/*************************************************************************
*
*	Purpose:		Returns the current node.
*	Entry:			Nothing.
*	Exit:			Returns a pointer to the current node in the list.
*
*************************************************************************/
template <typename T>
Node<T>* ListIterator<T>::GetCurrent()
{
	return current;
}

/*************************************************************************
*
*	Purpose:		Gets the head of the list being traversed.
*	Entry:			Nothing.
*	Exit:			Returns a pointer to the head of the list.
*
*************************************************************************/
template <typename T>
Node<T>* ListIterator<T>::GetHead()
{
	return _list->head;
}

/*************************************************************************
*
*	Purpose:		Gets the tail of the list being traversed.
*	Entry:			Nothing.
*	Exit:			Returns a pointer to the tail of the list.
*
*************************************************************************/
template <typename T>
Node<T>* ListIterator<T>::GetTail()
{
	return _list->tail;
}

/*************************************************************************
*
*	Purpose:		Gets the next node in the list.
*	Entry:			Nothing.
*	Exit:			Returns a pointer to the next node.
*
*************************************************************************/
template <typename T>
Node<T>* ListIterator<T>::GetNext()
{
	return current->GetNext();
}

/*************************************************************************
*
*	Purpose:		Gets the previous node in the list.
*	Entry:			Nothing.
*	Exit:			Returns a pointer to the previous node in the list.
*
*************************************************************************/
template <typename T>
Node<T>* ListIterator<T>::GetPrev()
{
	return current->GetPrev();
}

#endif
/*************************************************************************
*
*	Template:
*		ForwardIterator
*	
*	Constructors:
*		ForwardIterator() - Default constructor
*		ForwardIterator(DoubleLinkedList) - 1 Arg constructor; Points to
*			the list that is being iterated.
*		~ForwardIterator() - Destructor
*		ForwardIterator(const ForwardIterator&) - Copy constructor
*		ForwardIterator& operator=(const ForwardIterator&) - Operator =
*
*	Mutators:
*		None
*
*	Methods:
*		void First() - Implements placing the current node at the start of 
*			the list.
*		void MoveNext() - Moves the current node to the next node in the list.
*
*************************************************************************/

#ifndef FORWARDITERATOR
#define FORWARDITERATOR

#include "ListIterator.h"
#include "Node.h"

template <typename T>
class ForwardIterator: public ListIterator<T>
{

public:
	//1 arg constructor
	ForwardIterator(DoubleLinkedList<T> *list);
	//defualt constructor
	ForwardIterator();
	//copy constructor
	ForwardIterator(const ForwardIterator<T> &copy);
	//operators=
	ForwardIterator<T>& operator=(const ForwardIterator<T> &rhs);
	//destructor
	~ForwardIterator();

	void First();
	void MoveNext();
};

/*************************************************************************
*
*		Constructors
*
*************************************************************************/
template <typename T>
ForwardIterator<T>::ForwardIterator(DoubleLinkedList<T> *list): ListIterator(list)
{
	First();
}

template <typename T>
ForwardIterator<T>::ForwardIterator()
{
}

template <typename T>
ForwardIterator<T>::ForwardIterator(const ForwardIterator<T> &copy)
{
}
template <typename T>
ForwardIterator<T>& ForwardIterator<T>::operator =(const ForwardIterator<T> &rhs)
{
}

template <typename T>
ForwardIterator<T>::~ForwardIterator()
{
}

/*************************************************************************
*		End Constructors
*************************************************************************/

/*************************************************************************
*
*	Purpose:		Sets the current node to the first in the list.
*	Entry:			Nothing.
*	Exit:			Returns nothing.
*
*************************************************************************/
template <typename T>
void ForwardIterator<T>::First()
{
	current = GetHead();
}

/*************************************************************************
*
*	Purpose:		Sets the current node to the next in the list.
*	Entry:			Nothing.
*	Exit:			Returns nothing.
*
*************************************************************************/
template <typename T>
void ForwardIterator<T>::MoveNext()
{
	current = GetNext();
}

#endif
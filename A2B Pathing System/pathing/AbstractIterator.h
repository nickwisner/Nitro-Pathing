/*************************************************************************
*
*	PureVirtualClass:
*		AbstractIterator
*
*	An Abstract class for a linked list iterator
*	
*	Constructors:
*		None
*
*	Mutators:
*		None
*
*	Methods:
*		void First() - Sets the current node to the start of the list.
*		bool IsDone() - Returns true when at the end of the list.
*		void MoveNext() - Moves the current node to the next node in the
*			list.
*		Node* GetCurrent() - Returns a pointer to the current node.
*
*************************************************************************/

#ifndef ABSTRACTITERATOR
#define ABSTRACTITERATOR

#include "Node.h"

template <typename T>
class AbstractIterator
{
public:
	virtual void First() = 0;
	virtual bool IsDone() = 0;
	virtual void MoveNext() = 0;
	virtual Node<T>* GetCurrent() = 0;
};

#endif
/*************************************************************************
*
*	Template:
*		ListStack
*	
*	Constructors:
*		ListStack() - Creates linked list implementation of a stack.
*		~ListStack() - Destructs the stack.
*		ListStack(const ListStack &copy) - Copies the stack into this object.
*		ListStack& operator=(const ListStack &rhs) - Assigns the rhs stack
*			to this stack.
*
*	Mutators:
*		None
*
*	Methods:
*		void Push(T) - Pushes the data onto the top of the stack.
*		T& Peek() - Returns the data on the top of the stack.
*		T Pop() - Returns the data on the top of the stack and removes it
*			from the stack.
*		unsigned int Size() - Returns count.
*		bool isEmpty() - Returns true if count = 0
*
*************************************************************************/

#ifndef LISTSTACK
#define LISTSTACK

#include "DoubleLinkedList.h"

template <typename T>
class ListStack
{
public:
	//default constructor
	ListStack();
	//destructor
	~ListStack();
	//operator=
	ListStack& operator=(const ListStack<T> &rhs);
	//copy constructor
	ListStack(const ListStack<T> &copy);

	void Push(T insert);
	T& Peek();
	T Pop();
	unsigned int Size();
	bool isEmpty();

private:
	DoubleLinkedList<T> data;
	unsigned int count;		//number of nodes in the stack

};

/*************************************************************************
*
*		Constructors
*
*************************************************************************/
template <typename T>
ListStack<T>::ListStack(): count(0)
{
}

template <typename T>
ListStack<T>::~ListStack()
{
	count = 0;
}

template <typename T>
ListStack<T>::ListStack(const ListStack<T> &copy)
{
	*this = copy;
}

template <typename T>
ListStack<T>& ListStack<T>::operator =(const ListStack<T> &rhs)
{
	if(this != &rhs)
	{
		data = rhs.data;
		count = rhs.count;
	}

	return *this;
}
/*************************************************************************
*		End Constructors
*************************************************************************/

/*************************************************************************
*
*	Purpose:		Adds data to the top of the stack.
*	Entry:			Requires the data to add be passed in.
*	Exit:			Adds the data to the top of the stack and increments
*					count.
*
*************************************************************************/
template <typename T>
void ListStack<T>::Push(T insert)
{
	data.Append(insert);
	count++;
}

/*************************************************************************
*
*	Purpose:		Returns data to the top of the stack.
*	Entry:			Requires nothing.
*	Exit:			Returns a reference to the data on the top of the stack.
*
*************************************************************************/
template <typename T>
T& ListStack<T>::Peek()
{
	if(count == 0)
	{
		throw "Error: Underflow";
	}
	else
	{
		return data.Last();
	}
}

/*************************************************************************
*
*	Purpose:		Returns data to the top of the stack and removes it.
*	Entry:			Requires nothing.
*	Exit:			Returns the data on the top of the stack.
*
*************************************************************************/
template <typename T>
T ListStack<T>::Pop()
{
	if(count == 0)
	{
		throw "Error: Underflow";
	}
	else
	{
		T temp = data.Last();

		data.DeleteEnd();

		count--;
		return temp;
	}
}

/*************************************************************************
*
*	Purpose:		Returns the size of the stack.
*	Entry:			Requires nothing.
*	Exit:			Returns count.
*
*************************************************************************/
template <typename T>
unsigned int ListStack<T>::Size()
{
	return count;
}

/*************************************************************************
*
*	Purpose:		Returns whether the stack is empty or not.
*	Entry:			Requires nothing.
*	Exit:			Returns true if count = 0.
*
*************************************************************************/
template <typename T>
bool ListStack<T>::isEmpty()
{
	return (count == 0);
}

#endif
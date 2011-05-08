/*************************************************************************
*
*	Template:
*		Queue
*	
*	Constructors:
*		Queue() - Default constructor
*		Queue(Vertex*, string, int) - 3 Arg constructor; Copies the pointer 
*			to a vertex into the locale variable holding a pointer to a 
*			vertex, also sets the description to the string and the weight 
*			to the int.
*		~Queue() - Destructor
*		Queue(const Queue&) - Copy constructor
*		Queue& operator=(const Queue&) - Operator =
*
*	Mutators:
*		None
*
*	Methods:
*		T& Front() - Returns the item at the front of the queue.
*		T Dequeue() - Pops the front of the queue and returns it.
*		bool IsEmpty() - Returns true if count = 0.
*		void Enqueue(T) - Pushes the data onto the queue.
*		unsigned int Size() - Returns count.
*
*************************************************************************/

#ifndef QUEUE
#define QUEUE

#include "DoubleLinkedList.h"

template <typename T>
class Queue
{
public:
	//default constructor
	Queue();
	//destructor
	~Queue();
	//copy constructor
	Queue(const Queue<T> &copy);
	//operator =
	Queue<T>& operator=(const Queue<T> &rhs);

	void Enqueue(T _data);
	T Dequeue();
	T& Front();
	unsigned int Size();
	bool isEmpty();

private:
	DoubleLinkedList<T> data;	//link list holding the data
	unsigned int count;			//number of items in the queue
};

/*************************************************************************
*
*		Constructors
*
*************************************************************************/
template <typename T>
Queue<T>::Queue(): count(0)
{
}

template <typename T>
Queue<T>::~Queue()
{
	count = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T> &copy): count(copy.count), data(copy.data)
{
}

template <typename T>
Queue<T>& Queue<T>::operator =(const Queue<T> &rhs)
{
	if(this != &rhs)
	{
		count = rhs.count;
		data = rhs.data;
	}

	return *this;
}
/*************************************************************************
*		End Constructors
*************************************************************************/

/*************************************************************************
*
*	Purpose:		Returns true if the queue is empty.
*	Entry:			Nothing.
*	Exit:			Returns true if count = 0.
*
*************************************************************************/
template <typename T>
bool Queue<T>::isEmpty()
{
	return (count == 0);
}

/*************************************************************************
*
*	Purpose:		Returns the number of items in the queue.
*	Entry:			Nothing.
*	Exit:			Returns the number of items in the queue.
*
*************************************************************************/
template <typename T>
unsigned int Queue<T>::Size()
{
	return count;
}

/*************************************************************************
*
*	Purpose:		Returns the item at the front of the queue.
*	Entry:			Nothing.
*	Exit:			Returns the item by reference.
*
*************************************************************************/
template <typename T>
T& Queue<T>::Front()
{
	if(count == 0)
	{
		throw "Error: Underflow";
	}
	else
	{
		T& temp = data.First();
		return temp;
	}
}

/*************************************************************************
*
*	Purpose:		Removes the item at the front of the queue.
*	Entry:			Nothing.
*	Exit:			Returns the item at the front of the list.
*
*************************************************************************/
template <typename T>
T Queue<T>::Dequeue()
{
	if(count == 0)
	{
		throw "Error: Underflow";
	}
	else
	{
		T temp = data.First();

		data.Extract(temp);

		count--;
		return temp;
	}
}

/*************************************************************************
*
*	Purpose:		Pushes the item onto the queue.
*	Entry:			Nothing.
*	Exit:			Returns nothing.
*
*************************************************************************/
template <typename T>
void Queue<T>::Enqueue(T _data)
{
	data.Append(_data);
	count++;
}

#endif
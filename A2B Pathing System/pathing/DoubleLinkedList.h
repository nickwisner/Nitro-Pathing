/*************************************************************************
*
*	Template:
*		DoubleLinkedList
*	
*	Constructors:
*		DoubleLinkedList() - Creates a double linked list.
*		~DoubleLinkedList() - Destructs the double linked list.
*		DoubleLinkedList(const DoubleLinkedList &copy) - Copies the list
*			into this object.
*		DoubleLinkedList& operator=(const DoubleLinkedList &rhs) - Assigns
*			the rhs list to this list.
*
*	Mutators:
*		void PrintForwards() - Prints the list starting at the head.
*		void PrintBackwards() - Prints the list starting at the tail.
*
*	Methods:
*		bool isEmpty() - Returns true if no nodes are in the list.
*		T& First() - Returns the data at the first node.
*		T& Last() - Returns the data at the last node.
*		void Prepend(T) - Inserts the data at the head of the list.
*		void Append(T) - Inserts the data at the tail of the list.
*		void Purge() - Erases all values in the list.
*		void InsertBefore(T, T) - Inserts the data(first T) before the
*			data supplied (second T).
*		void InsertAfter(T, T) - Inserts the data(first T) after the data
*			supplied (second T).
*		void Extract(T) - Removes the first occurence of the supplied data
*			from the list; starts at head.
*		void DeleteEnd() - Removes the last element from the list.
*
*************************************************************************/

#ifndef DOUBLELINKEDLIST
#define DOUBLELINKEDLIST

#include "Node.h"
#include "ListIterator.h"

#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class DoubleLinkedList
{
	friend class ListIterator<T>;
public:
	//default constructor
	DoubleLinkedList();

	//copy constructor
	DoubleLinkedList(const DoubleLinkedList &copy);

	//operator=
	DoubleLinkedList& operator= (const DoubleLinkedList &rhs);

	//destructor
	~DoubleLinkedList();

	//Mutators
	void PrintForwards();
	void PrintBackwards();

//	Node<T> * getHead();	for testing purposes
//	Node<T> * getTail();	for testing purposes


	//Methods
	bool isEmpty() const;
	T& First() const;
	T& Last() const;
	void Prepend(T _data);
	void Append(T _data);
	void Purge();
	void Extract(T _find);
	void InsertAfter(T _data, T _find);
	void InsertBefore(T _data, T _find);

	void DeleteEnd();

private:
	Node<T> *head;		//head of the list
	Node<T> *tail;		//tail of the list
};

/*************************************************************************
*
*					Constructors
*
*************************************************************************/
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(): head(0), tail(0)
{
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T> &copy)
{
	*this = copy;
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator= 
	(const DoubleLinkedList<T> &rhs)
{
	if(this != &rhs)	// not assigning self to self
	{
		if(rhs.head == 0 && rhs.tail == 0)	// assigning an empty list
		{
			head = 0;
			tail = 0;
		}

		else	// assigning a list with nodes
		{
			Node<T>* currentRhs = rhs.head;

			// make a head and assign it the rhs' data
			head = new Node<T>(currentRhs->Data());
			Node<T>* current = head;
			tail = head;

			currentRhs = currentRhs->next;

			while(currentRhs != 0)	// milisec the rest of the nodes in
			{
				Append(currentRhs->Data());
				currentRhs = currentRhs->next;
			}
		}
	}

	return *this;
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
	Purge();
}
/*************************************************************************
*					End Constructors
*************************************************************************/

/*************************************************************************
*
*		Mutators
*
*************************************************************************/
template <typename T>
void DoubleLinkedList<T>::PrintForwards()
{
	Node<T>* current = head;

	while(current != 0)
	{
		cout << current->Data() << endl;
		current = current->next;
	}
}

template <typename T>
void DoubleLinkedList<T>::PrintBackwards()
{
	Node<T>* current = tail;

	while(current != 0)
	{
		cout << current->Data() << endl;
		current = current->prev;
	}
}


/*************************************************************************
*		End Mutators
*************************************************************************/

/*************************************************************************
*
*		Methods
*
*************************************************************************/

/*************************************************************************
*
*	Purpose:		Determine if the list is empty.
*	Entry:			Nothing.
*	Exit:			Returns true if the list is empty.
*
*************************************************************************/
template <typename T>
bool DoubleLinkedList<T>::isEmpty() const
{
	return (head == 0);
}

/*************************************************************************
*
*	Purpose:		Adds the data to the end of the list.
*	Entry:			Requires the data to be passed in.
*	Exit:			Returns nothing.
*
*************************************************************************/
template <typename T>
void DoubleLinkedList<T>::Append(T _data)
{
	Node<T>* temp = new Node<T>(_data);

	// empty list
	if(tail == 0 && head == 0)
	{
		tail = temp;
		head = temp;
	}
	else
	{
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}
}

/*************************************************************************
*
*	Purpose:		Adds the data to the beginning of the list.
*	Entry:			Requires the data to be passed in.
*	Exit:			Returns nothing.
*
*************************************************************************/
template <typename T>
void DoubleLinkedList<T>::Prepend(T _data)
{
	Node<T>* temp = new Node<T>(_data);

	// empty list
	if(head == 0 && tail == 0)
	{
		tail = temp;
		head = temp;
	}
	else
	{
		temp->next = head;
		head->prev = temp;
		head = temp;
	}

}

/*************************************************************************
*
*	Purpose:		Gets the data in the first element of the list.
*	Entry:			Nothing.
*	Exit:			Returns the data at the first element of the list.
*
*************************************************************************/
template <typename T>
T& DoubleLinkedList<T>::First() const
{
	if(head == 0)
	{
		throw "List is empty.";
	}
	else
	{
		return (head->Data());
	}
}

/*************************************************************************
*
*	Purpose:		Gets the data in the last element of the list.
*	Entry:			Nothing.
*	Exit:			Returns the data at the last element of the list.
*
*************************************************************************/
template <typename T>
T& DoubleLinkedList<T>::Last() const
{
	if(tail == 0)
	{
		throw "List is empty.";
	}
	else
	{
		return (tail->Data());
	}
}

/*************************************************************************
*
*	Purpose:		Deletes all nodes in the list.
*	Entry:			Nothing.
*	Exit:			Returns nothing.
*
*************************************************************************/
template <typename T>
void DoubleLinkedList<T>::Purge()
{
	Node<T>* trail = head;

	// delete each node til we find the end
	while(head != tail)
	{
		trail = head;
		head = head->next;

		delete trail;
	}

	delete head;

	tail = 0;
	head = 0;
}

/*************************************************************************
*
*	Purpose:		Inserts the supplied data before the supplied node in 
*					the list.
*	Entry:			The data to insert as well as the data to insert before
*					must be passed in.
*	Exit:			Returns nothing.
*
*************************************************************************/
template <typename T>
void DoubleLinkedList<T>::InsertBefore(T _data, T _find)
{
	if(isEmpty())
	{
		throw ("List is empty.");
	}
	else
	{
		Node<T>* current = head;
		Node<T>* temp = new Node<T>(_find);

		// traverse the list until we find data
		while(current != 0 && current->Data() != temp->Data())
		{
			current = current->next;
		}

		delete temp;
		temp = 0;

		if(current == 0)
		{
			throw("Data not found. Aborting insertion.");
		}
		else	// insert it
		{
			Node<T>* insert = new Node<T>(_data);

			if(current->prev != 0)
			{
				current->prev->next = insert;
			}

			insert->next = current;
			insert->prev = current->prev;
			current->prev = insert;
		
			if(insert->prev == 0)
			{
				head = insert;
			}
		}
	}
}

/*************************************************************************
*
*	Purpose:		Inserts the supplied data after the supplied node in 
*					the list.
*	Entry:			The data to insert as well as the data to insert after
*					must be passed in.
*	Exit:			Returns nothing.
*
*************************************************************************/
template <typename T>
void DoubleLinkedList<T>::InsertAfter(T _data, T _find)
{
	if(isEmpty())
	{
		throw ("List is empty.");
	}
	else
	{
		Node<T>* current = head;
		Node<T>* temp = new Node<T>(_find);

		// traverse the list until we find data
		while(current != 0 && current->Data() != temp->Data())
		{
			current = current->next;
		}

		delete temp;
		temp = 0;

		if(current == 0)
		{
			throw("Data not found. Aborting insertion.");
		}
		else	// insert it
		{
			Node<T>* insert = new Node<T>(_data);

			insert->prev = current;
			insert->next = current->next;
			current->next = insert;
			
			if(insert->next == 0)
			{
				tail = insert;
			}
		}
	}
}

/*************************************************************************
*
*	Purpose:		Removes a node from the list.
*	Entry:			The data to remove must be passed in. Will remove the
*					first occurence of the data. Starts at the head.
*	Exit:			Returns nothing.
*
*************************************************************************/
template <typename T>
void DoubleLinkedList<T>::Extract(T _find)
{
	if(isEmpty())
	{
		throw ("List is empty.");
	}
	else
	{
		Node<T>* current = head;
		Node<T>* temp = new Node<T>(_find);

		// traverse the list until we find data
		while(current != 0 && current->Data() != temp->Data())
		{
			current = current->next;
		}

		delete temp;
		temp = 0;

		if(current == 0)
		{
			throw("Data not found. Aborting insertion.");
		}
		else if(current->next == 0 && current->prev == 0)	// only node in list
		{
			delete current;
			head = 0;
			tail = 0;
		}
		else	// multiple node list
		{
			if(current == head)
			{
				head = current->next;
				head->prev = 0;
			}
			else if(current == tail)
			{
				tail = current->prev;
				tail->next = 0;
			}
			else
			{
				Node<T>* trail = current->prev;
				Node<T>* after = current->next;

				trail->next = after;
				after->prev = trail;
			}

			delete current;
		}
	}
}


/*************************************************************************
*
*	Purpose:		Removes the last node in the list.
*	Entry:			Nothing.
*	Exit:			Returns nothing.
*
*************************************************************************/
template <typename T>
void DoubleLinkedList<T>::DeleteEnd()
{
	Node<T>* temp = tail;
	tail = tail->prev;
	delete temp;

	if(tail == 0)
	{
		head = 0;
	}
}
/*************************************************************************
*					End Methods
*************************************************************************/
#endif
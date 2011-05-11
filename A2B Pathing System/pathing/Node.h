/*************************************************************************
*
*	Template:
*		Node
*	
*	Constructors:
*		Node() - Creates a node object that stores data and a next and 
*			previous pointer to other nodes.
*		~Node() - Destructs the node.
*		Node(T _data, Node *, Node *) - Creates a new node with _data 
*			assigned to data and the pointers assigned to their corresping
*			nodes.
*		Node(const Node &copy) - Copies the node into this object.
*		Node& operator=(const Node &rhs) - Assigns the rhs node
*			to this node.
*
*	Mutators:
*		None
*
*	Methods:
*		Node<T>* GetNext() - Returns a node pointer to the next node.
*		Node<T>* GetPrev() - Returns a node pointer to the previous node.
*		T& Data() - Returns the data held in the node.
*
*************************************************************************/

#ifndef NODE
#define NODE

template <typename T>
class DoubleLinkedList;

template <typename T>
class Node
{
	friend class DoubleLinkedList<T>;

public:
	T& Data();
	Node<T>* GetNext();
	Node<T>* GetPrev();

private:
	
	//default constructor
	Node();

	//copy constructor
	Node(const Node &copy);

	//operator =
	Node& operator= (const Node &rhs);

	//destructor
	~Node();

	//3 arg constructor
	Node(T _data, Node *_next=0, Node *_prev=0);

	T data;			//holds the data
	Node *next;		//next element in the list
	Node *prev;		//previous element in the list
};

	/****************************************************************
	*
	*					Constructors
	*
	****************************************************************/
template <typename T>
Node<T>::Node(): next(0), prev(0), data(0)
{
}

template <typename T>
Node<T>::Node(const Node<T> &copy)
{
	*this = copy;
}

template <typename T>
Node<T>& Node<T>::operator =(const Node<T> &rhs)
{
	if(this != &rhs)
	{
		if(&rhs == 0)	// empty node
		{
			next = 0;
			prev = 0;
			data = 0;
		}
		else
		{
			next = rhs.next;
			prev = rhs.prev;
			data = rhs.data;
		}
	}
	return *this;
}

template <typename T>
Node<T>::~Node()
{
}

template <typename T>
Node<T>::Node(T _data, Node *_next=0, Node *_prev=0): data(_data), next(_next),
	prev(_prev)
{
}
	/****************************************************************
	*					End Constructors
	****************************************************************/

/*************************************************************************
*
*	Purpose:		Returns the data held in the node.
*	Entry:			Nothing.
*	Exit:			Returns the data in the node.
*
*************************************************************************/
template <typename T>
T& Node<T>::Data()
{
	return data;
}

/*************************************************************************
*
*	Purpose:		Returns the pointer to the next node.
*	Entry:			Nothing.
*	Exit:			Returns the next pointer in the node.
*
*************************************************************************/
template <typename T>
Node<T>* Node<T>::GetNext()
{
	return next;
}

/*************************************************************************
*
*	Purpose:		Returns the pointer to the previous node.
*	Entry:			Nothing.
*	Exit:			Returns the previous pointer in the node.
*
*************************************************************************/
template <typename T>
Node<T>* Node<T>::GetPrev()
{
	return prev;
}
#endif
/*************************************************************************
*
*	Template:
*		Vertex
*	
*	Constructors:
*		Vertex() - Default constructor
*		Vertex(Vertex*, string, int) - 3 Arg constructor; Copies the pointer 
*			to a vertex into the locale variable holding a pointer to a 
*			vertex, also sets the description to the string and the weight 
*			to the int.
*		~Vertex() - Destructor
*		Vertex(const Vertex&) - Copy constructor
*		Vertex& operator=(const Vertex&) - Operator =
*
*	Mutators:
*		T& GetData() - Returns the data in the vertex.
*		bool IsEmpty() - returns true if DEdge list is empty.
*		SetProcessed(bool) - Sets the bool controlling whether 


	//Mutators
	T& GetData();
	bool IsEmpty();
	void SetProcessed(bool proc);
	bool GetProcessed();
	
	void FirstEdge();
	DEdge<T,U>& GetCurrentEdge();
	void NextEdge();
	bool EdgeIsDone();
*		
*
*	Methods:
*		bool operator==(const Vertex&) - Overloaded operator==; Compares the
*			data in both vertices. Returns true if equal.
*		bool operator!=(const Vertex&) - Overloaded operator!=; Compares the
*			data in both vertices. Returns true if not equal.
*		void AddEdge(Vertex&, string, int) - Inserts the DEdge into the list.
*		void RemoveEdge(Vertex&) - Removes the DEdge from the list.
*
*************************************************************************/

#ifndef VERTEX
#define VERTEX

#include "DEdge.h"
#include "DoubleLinkedList.h"
#include "AbstractIterator.h"
#include "ListIterator.h"
#include "ForwardIterator.h"

#include <string>
using std::string;

template <typename T, typename U>
class Vertex
{
public:
	//default constructor
	Vertex();
	//1 arg constructor
	Vertex(T _data);
	//destructor
	~Vertex();
	//copy constructor
	Vertex(const Vertex<T,U> &copy);
	//operator=
	Vertex<T,U>& operator=(const Vertex<T,U> &rhs);

	//Mutators
	T& GetData();
	bool IsEmpty();
	void SetProcessed(bool proc);
	bool GetProcessed();
	
	void FirstEdge();
	DEdge<T,U>& GetCurrentEdge();
	void NextEdge();
	bool EdgeIsDone();

	//Methods
	bool operator==(const Vertex<T,U> &rhs);	//compares the data
	bool operator!=(const Vertex<T,U> &rhs);	//compares the data

	void AddEdge(Vertex<T,U> &_add, int pathId, int weight);
	void RemoveEdge(Vertex<T,U> &_remove);

private:
	DoubleLinkedList<DEdge <T,U> > edges;
	DEdge<T,U>* current;		//current DEdge

	T data;					//vertex data
	bool processed;
};

/*************************************************************************
*
*		Constructors
*
*************************************************************************/
template <typename T, typename U>
Vertex<T,U>::Vertex(): processed(false)
{
}

template <typename T, typename U>
Vertex<T,U>::Vertex(T _data): data(_data), processed(false)
{
}

template <typename T, typename U>
Vertex<T,U>::~Vertex()
{
}

template <typename T, typename U>
Vertex<T,U>::Vertex(const Vertex<T,U> &copy): data(copy.data), processed(copy.processed)
{
	*this = copy;
}

template <typename T, typename U>
Vertex<T,U>& Vertex<T,U>::operator= (const Vertex<T,U> &rhs)
{
	if(this != &rhs)
	{
		processed = rhs.processed;
		data = rhs.data;

		edges.Purge();
		edges = rhs.edges;
	}

	return *this;
}
/*************************************************************************
*		End Constructors
*************************************************************************/

/*************************************************************************
*
*	Purpose:		Returns the description of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the string value of description.
*
*************************************************************************/
template <typename T, typename U>
bool Vertex<T,U>::operator ==(const Vertex<T,U> &rhs)
{
	return (this->data == rhs.data);
}

/*************************************************************************
*
*	Purpose:		Returns the description of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the string value of description.
*
*************************************************************************/
template <typename T, typename U>
bool Vertex<T,U>::operator !=(const Vertex<T,U> &rhs)
{
	return (this->data != rhs.data);
}

/*************************************************************************
*
*	Purpose:		Returns the description of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the string value of description.
*
*************************************************************************/
template <typename T, typename U>
void Vertex<T,U>::AddEdge(Vertex<T,U> &_add, int pathId, int weight)
{
	if(*this != _add)
	{
		ForwardIterator<DEdge <T,U> > travelEdges(&edges);

		bool present = false;
		for(travelEdges.First(); !travelEdges.IsDone() && present == false; travelEdges.MoveNext())
		{
			if(travelEdges.GetCurrent()->Data().GetDest()->GetData() == _add.data)
			{
				present = true;
			}
		}

		if(present == false)
		{
			edges.Append(DEdge<T,U>(&_add, pathId, weight));
		}
		else
		{
			throw "DEdge already exists.";
		}
	}
	else
	{
		throw "Can't insert an DEdge pointing to the same vertex";
	}
}

/*************************************************************************
*
*	Purpose:		Returns the description of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the string value of description.
*
*************************************************************************/
template <typename T, typename U>
void Vertex<T,U>::RemoveEdge(Vertex<T,U> &_remove)
{
	if(*this != _remove)
	{
		ForwardIterator<DEdge <T,U> > travelEdges(&edges);

		bool present = false;
		for(travelEdges.First(); !travelEdges.IsDone() && present == false; travelEdges.MoveNext())
		{
			if(travelEdges.GetCurrent()->Data().GetDest()->GetData() == _remove.data)
			{
				present = true;
				edges.Extract(travelEdges.GetCurrent()->Data());
			}
		}

		if(present == false)
		{
			throw "DEdge doesn't exist.";
		}
	}
	else
	{
		throw "Can't remove an DEdge pointing to the same vertex";
	}
}

/*************************************************************************
*
*	Purpose:		Returns the description of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the string value of description.
*
*************************************************************************/
template <typename T, typename U>
T& Vertex<T,U>::GetData()
{
	return data;
}

/*************************************************************************
*
*	Purpose:		Returns the description of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the string value of description.
*
*************************************************************************/
template <typename T, typename U>
bool Vertex<T,U>::IsEmpty()
{
	return edges.isEmpty();
}

/*************************************************************************
*
*	Purpose:		Returns the description of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the string value of description.
*
*************************************************************************/
template <typename T, typename U>
void Vertex<T,U>::SetProcessed(bool proc)
{
	processed = proc;
}

/*************************************************************************
*
*	Purpose:		Returns the description of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the string value of description.
*
*************************************************************************/
template <typename T, typename U>
bool Vertex<T,U>::GetProcessed()
{
	return processed;
}

/*************************************************************************
*
*	Purpose:		Returns the description of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the string value of description.
*
*************************************************************************/
template <typename T, typename U>
void Vertex<T,U>::FirstEdge()
{
	ForwardIterator<DEdge <T,U> > travelEdges(&edges);
	travelEdges.First();
	current = &(travelEdges.GetCurrent()->Data());
}

/*************************************************************************
*
*	Purpose:		Returns the description of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the string value of description.
*
*************************************************************************/
template <typename T, typename U>
DEdge<T,U>& Vertex<T,U>::GetCurrentEdge()
{
	return *current;
}

/*************************************************************************
*
*	Purpose:		Returns the description of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the string value of description.
*
*************************************************************************/
template <typename T, typename U>
void Vertex<T,U>::NextEdge()
{
	ForwardIterator<DEdge <T,U> > travelEdges(&edges);

	while(current != &(travelEdges.GetCurrent()->Data()))
	{
		travelEdges.MoveNext();
	}
	travelEdges.MoveNext();

	if(!travelEdges.IsDone())
	{
		current = &(travelEdges.GetCurrent()->Data());
	}
	else
	{
		current = 0;
	}
}

/*************************************************************************
*
*	Purpose:		Returns the description of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the string value of description.
*
*************************************************************************/
template <typename T, typename U>
bool Vertex<T,U>::EdgeIsDone()
{
	ForwardIterator<DEdge <T,U> > travelEdges(&edges);

	while(current != &(travelEdges.GetCurrent()->Data()))
	{
		travelEdges.MoveNext();
	}

	return travelEdges.IsDone();
}

#endif
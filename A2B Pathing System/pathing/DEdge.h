/*************************************************************************
*
*	Template:
*		DEdge
*	
*	Constructors:
*		DEdge() - Default constructor
*		DEdge(Vertex*, string, int) - 3 Arg constructor; Copies the pointer 
*			to a vertex into the locale variable holding a pointer to a 
*			vertex, also sets the description to the string and the weight 
*			to the int.
*		~DEdge() - Destructor
*		DEdge(const DEdge&) - Copy constructor
*		DEdge& operator=(const DEdge&) - Operator =
*
*	Mutators:
*		string GetDesc() - Returns the description of the DEdge.
*		Vertex* GetDest() - Returns the pointer to the vertex.
*		int GetWeight() - Returns the weight of the DEdge.
*
*	Methods:
*		bool operator==(const DEdge&) - Overloaded operator==; Compares the
*			pointers to teh two vertices. Returns true if equal.
*		bool operator!=(const DEdge&) - Overloaded operator!=; Compares the
*			pointers to teh two vertices. Returns true if not equal.
*
*************************************************************************/

#ifndef DEDGE_H
#define DEDGE_H

template <typename T, typename U>
class Vertex;

template <typename T, typename U>
class DEdge
{
public:
	//default constructor
	DEdge();
	//3 arg constructor
	DEdge(Vertex<T,U> *_dest, int pathId, int _weight=1);
	//destructor
	~DEdge();
	//copy constructor
	DEdge(const DEdge<T,U> &copy);
	//operator=
	DEdge<T,U>& operator=(const DEdge<T,U> &rhs);

	//Mutators
	int GetId();
	Vertex<T,U>* GetDest();
	int GetWeight();

	//MEthods
	bool operator==(const DEdge<T,U> &rhs);
	bool operator!=(const DEdge<T,U> &rhs);

private:
	Vertex<T,U> *destination;	//location of the data
	int weight;					//weight of this DPath
	int m_id;			//description of the data
};

/*************************************************************************
*
*		Constructors
*
*************************************************************************/
template <typename T, typename U>
DEdge<T,U>::DEdge(): destination(0), weight(0)
{
}

template <typename T, typename U>
DEdge<T,U>::DEdge(Vertex<T,U> *_dest, int id, int _weight=0): destination(_dest), weight(_weight), m_id(id)
{
}

template <typename T, typename U>
DEdge<T,U>::~DEdge()
{
}

template <typename T, typename U>
DEdge<T,U>::DEdge(const DEdge<T,U> &copy): destination(copy.destination), weight(copy.weight), m_id(copy.m_id)
{
}

template <typename T, typename U>
DEdge<T,U>& DEdge<T,U>::operator =(const DEdge<T,U> &rhs)
{
	if(this != &rhs)
	{
		destination = rhs.destination;
		weight = rhs.weight;
		description = rhs.description;
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
int DEdge<T,U>::GetId()
{
	return m_id;
}

/*************************************************************************
*
*	Purpose:		Returns the pointer to the vertex.
*	Entry:			Nothing.
*	Exit:			Returns the pointer to the vertex.
*
*************************************************************************/
template <typename T, typename U>
Vertex<T,U>* DEdge<T,U>::GetDest()
{
	return destination;
}

/*************************************************************************
*
*	Purpose:		Returns the weight of the DEdge.
*	Entry:			Nothing.
*	Exit:			Returns the int value of weight.
*
*************************************************************************/
template <typename T, typename U>
int DEdge<T,U>::GetWeight()
{
	return weight;
}

/*************************************************************************
*
*	Purpose:		Compares the destination of the two vertices.
*	Entry:			Nothing.
*	Exit:			Returns true if the edges point to the same destination.
*
*************************************************************************/
template <typename T, typename U>
bool DEdge<T,U>::operator ==(const DEdge<T,U> &rhs)
{
	return (this->destination == rhs.destination);
}

/*************************************************************************
*
*	Purpose:		Compares the destination of the two vertices.
*	Entry:			Nothing.
*	Exit:			Returns false if the edges point to the same destination.
*
*************************************************************************/
template <typename T, typename U>
bool DEdge<T,U>::operator !=(const DEdge<T,U> &rhs)
{
	return (this->destination != rhs.destination);
}

#endif
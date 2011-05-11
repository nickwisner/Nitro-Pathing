/*************************************************************************
*
*	Template:
*		Graph
*	
*	Constructors:
*		Graph() - Default constructor
*		~Graph() - Destructor
*		Graph(const Graph&) - Copy constructor
*		Graph& operator=(const Graph&) - Operator =
*
*	Mutators:
*		bool isEmpty() - Returns true if the graph is empty.
*		int GetCount() - Returns the number of vertices in the graph.
*		void BFT() - Breadth first traversal to display the graph.
*		void DFT() - Depth first traversal to display the graph.
*
*	Methods:
*		void InsertVertex(T) - Inserts the vertex at the end of the graph 
*			after making sure that it does not already exist.
*		void RemoveVertex(T) - Removes the supplied vertex from the graph.
*		void InsertEdge(T, T, string, int) - Connects two vertices if they 
*			exist and places the string and int into the DEdge respectively.
*		void RemoveEdge(T, T) - Disconnects the two vertices.
*		Vertex RetreiveVertex(T) - Returns the vertex.
*		void FirstVertex() - Moves the iterator to the first vertex in the 
*			list.
*		bool VertexIsDone() - Returns true if the iterator has traversed 
*			through the entire list.
*		void NextVertex() - Moves the current pointer to the next in the 
*			iterator.
*		Vertex GetCurrentVertex() - Returns the current vertex in the iterator.
*
*************************************************************************/

#ifndef GRAPH
#define GRAPH

#include "Vertex.h"
#include "DoubleLinkedList.h"
#include "AbstractIterator.h"
#include "ListIterator.h"
#include "ForwardIterator.h"
#include "Queue.h"
#include "ListStack.h"

#include <string>
using std::string;

template <typename T, typename U>
//T = data type for vertex
//U = data type for DEdge
class Graph
{
public:
	//default constructor
	Graph();
	//destructor
	~Graph();
	//copy constructor
	Graph(const Graph<T,U> &copy);
	//operator=
	Graph<T,U>& operator=(const Graph<T,U> &rhs);

	//Mutators
	unsigned int GetCount();
	void BFT();					//breadth first traversal
	void DFT();					//depth first traversal
	bool isEmpty();

	//Methods
	void InsertVertex(T _data);
	void RemoveVertex(T _vertex);
	void InsertEdge(T _from, T _to, int edgeId, int wieght=1);
	void RemoveEdge(T _from, T _to);
	Vertex<T,U>& RetrieveVertex(T _vertex);

	//Iterator wrappers
	void FirstVertex();
	Vertex<T,U>& GetCurrentVertex();
	void NextVertex();
	bool VertexIsDone();

private:
	DoubleLinkedList<Vertex <T,U> > vertices;	//linked list of vertex
	Vertex<T,U> *current;			//current pointer in the list

	ForwardIterator<Vertex <T,U> > travelVerts;	//forward iterator
	unsigned int count;		//number of vertices
	bool present;
};

/*************************************************************************
*
*		Constructors
*
*************************************************************************/
template <typename T, typename U>
Graph<T,U>::Graph(): count(0), travelVerts(&vertices)
{
}

template <typename T, typename U>
Graph<T,U>::~Graph()
{
	count = 0;
}

template <typename T, typename U>
Graph<T,U>::Graph(const Graph<T,U> &copy): count(0)
{
	*this = copy;
}

template <typename T, typename U>
Graph<T,U>& Graph<T,U>::operator =(const Graph<T,U> &rhs)
{
	if(this != &rhs)
	{
		count = 0;
		vertices.Purge();

		Graph<T,U> &tempGraph = const_cast<Graph<T,U> & >(rhs);
		ForwardIterator<Vertex <T,U> > travelVertsRhs(&tempGraph.vertices);
		
		for(travelVertsRhs.First(); !travelVertsRhs.IsDone(); travelVertsRhs.MoveNext())
		{
			InsertVertex(travelVertsRhs.GetCurrent()->Data().GetData());
		}

		ForwardIterator<Vertex <T,U> > travelVerts(&vertices);

		for(travelVertsRhs.First(), travelVerts.First(); !travelVerts.IsDone(); travelVertsRhs.MoveNext(), travelVerts.MoveNext())
		{
			travelVertsRhs.GetCurrent()->Data().FirstEdge();
			while(!travelVertsRhs.GetCurrent()->Data().EdgeIsDone())
			{
				try
				{
					InsertEdge(travelVertsRhs.GetCurrent()->Data().GetData(), 
						travelVertsRhs.GetCurrent()->Data().GetCurrentEdge().GetDest()->GetData(),
						travelVertsRhs.GetCurrent()->Data().GetCurrentEdge().GetWeight(), 
						travelVertsRhs.GetCurrent()->Data().GetCurrentEdge().GetDesc());
				}
				catch(char * e)
				{
				}

				travelVertsRhs.GetCurrent()->Data().NextEdge();
			}
		}
	}

	return *this;
}
/*************************************************************************
*		End Constructors
*************************************************************************/

/*************************************************************************
*
*	Purpose:		Inserts the vertex into the graph.
*	Entry:			Data to be inserted.
*	Exit:			Returns nothing. Throws an exception if the vertex is
*					already in the graph.
*
*************************************************************************/
template <typename T, typename U>
void Graph<T,U>::InsertVertex(T _data)
{
	present = false;
		
	// changing this to a while loop 
//	for(travelVerts.First(); !travelVerts.IsDone() && present == false; travelVerts.MoveNext())
	travelVerts.First();

	while( !travelVerts.IsDone() && present == false)
	{
		Vertex<T,U> temp = travelVerts.GetCurrent()->Data();

		if(temp.GetData() == _data)
		{
			present = true;
		}

		travelVerts.MoveNext();
	}
	
	if(present == false)
	{
		vertices.Append(Vertex<T,U>(_data));
		count++;
	}
	else
	{
		throw "Vertex already present.";
	}
}

/*************************************************************************
*
*	Purpose:		Inserts the DEdge into the graph.
*	Entry:			The two vertices to be connected must be passed in, 
*					along with the description. Weight is optional and set
*					to 0 if not provided.
*	Exit:			Returns nothing. Throws an exception if either vertex
*					is not in the list.
*
*************************************************************************/
template <typename T, typename U>
void Graph<T,U>::InsertEdge(T _from, T _to, int edgeId, int weight)
{
	Vertex<T,U> *from = 0;
	Vertex<T,U> *to = 0;

	try
	{
		from = &RetrieveVertex(_from);
	}
	catch(char * e)
	{
		throw e;
	}

	if(present == true)
	{
		present = false;
		try
		{
			to = &RetrieveVertex(_to);
		}
		catch(char * e)
		{
			throw e;
		}

		if(present == true)
		{
			from->AddEdge(*to, edgeId, weight);
			to->AddEdge(*from, edgeId, weight);
		}
	}
}

/*************************************************************************
*
*	Purpose:		Removes the vertex from the graph.
*	Entry:			Data to be removed.
*	Exit:			Returns nothing. Throws an exception if the data is
*					not present to be removed.
*
*************************************************************************/
template <typename T, typename U>
void Graph<T,U>::RemoveVertex(T _vertex)
{
	bool present = false;

	// changing this to a while loop from a for loop 05/10/11
//	for(travelVerts.First(); !travelVerts.IsDone() && present == false; travelVerts.MoveNext())
	travelVerts.First(); 

	while(!travelVerts.IsDone() && present == false)
	{
		if(travelVerts.GetCurrent()->Data() == _vertex)
		{
			present = true;
			while(!(travelVerts.GetCurrent()->Data().IsEmpty()))	// find the vertex
			{
				travelVerts.GetCurrent()->Data().FirstEdge();
				travelVerts.GetCurrent()->Data().GetCurrentEdge().GetDest()->RemoveEdge(travelVerts.GetCurrent()->Data());
				travelVerts.GetCurrent()->Data().RemoveEdge(*travelVerts.GetCurrent()->Data().GetCurrentEdge().GetDest());
			}

			vertices.Extract(travelVerts.GetCurrent()->Data());
		}

		travelVerts.MoveNext();
	}
	
	if(present == true)
	{
		count--;
	}
	else
	{
		throw "Vertex not found.";
	}
}

/*************************************************************************
*
*	Purpose:		Removes the DEdge from the graph.
*	Entry:			Data to be removed.
*	Exit:			Returns nothing. Throws an exception if either vertex 
*					is not present.
*
*************************************************************************/
template <typename T, typename U>
void Graph<T,U>::RemoveEdge(T _from, T _to)
{
	Vertex<T,U> *from = 0;
	Vertex<T,U> *to = 0;

	try
	{
		from = &RetrieveVertex(_from);
	}
	catch(char * e)
	{
		throw e;
	}

	if(present == true)
	{
		present = false;
		try
		{
			to = &RetrieveVertex(_to);
		}
		catch(char * e)
		{
			throw e;
		}

		if(present == true)
		{
			from->RemoveEdge(*to);
			to->RemoveEdge(*from);
		}
	}
}

/*************************************************************************
*
*	Purpose:		Return true if the graph is empty.
*	Entry:			Nothing.
*	Exit:			Returns bool value whether the graph is empty or not.
*
*************************************************************************/
template <typename T, typename U>
bool Graph<T,U>::isEmpty()
{
	return (count == 0);
}

/*************************************************************************
*
*	Purpose:		Return number of vertices in the graph.
*	Entry:			Nothing.
*	Exit:			Returns integer count of the graph.
*
*************************************************************************/
template <typename T, typename U>
unsigned int Graph<T,U>::GetCount()
{
	return count;
}

/*************************************************************************
*
*	Purpose:		Returns the vertex in the graph.
*	Entry:			Vertex to be returned has to be supplied.
*	Exit:			Returns the address of the vertex. Throws an exception
*					if the vertex is not in the graph.
*
*************************************************************************/
template <typename T, typename U>
Vertex<T,U>& Graph<T,U>::RetrieveVertex(T _vertex)
{
	for(travelVerts.First(); !travelVerts.IsDone() && travelVerts.GetCurrent()->Data() != _vertex; travelVerts.MoveNext())
	{
	}

	if(!travelVerts.IsDone() && travelVerts.GetCurrent()->Data() == _vertex)
	{
		present = true;
		return travelVerts.GetCurrent()->Data();
	}
	else
	{
		throw "Vertex not found.";
	}
}

/*************************************************************************
*
*	Purpose:		Display the graph in a breadth first traversal.
*	Entry:			Nothing.
*	Exit:			Returns nothing. Displays the vertices in the graph in
*					a breadth first traversal.
*
*************************************************************************/
template <typename T, typename U>
void Graph<T,U>::BFT()
{
	Queue<Vertex<T,U> * > queue;
	Vertex<T,U> * temp = 0;
	
	travelVerts.First();
	if(travelVerts.GetCurrent() != 0)
	{
		queue.Enqueue(&(travelVerts.GetCurrent()->Data()));
	}

	while(!queue.isEmpty())
	{
		temp = queue.Front();
		if(!temp->GetProcessed())
		{
			cout << temp->GetData().GetId() << endl;
		}
		queue.Dequeue();
		temp->SetProcessed(true);

		for(temp->FirstEdge(); !temp->EdgeIsDone(); temp->NextEdge())
		{
			if(!(temp->GetCurrentEdge().GetDest()->GetProcessed()))
			{
				queue.Enqueue(temp->GetCurrentEdge().GetDest());
			}
		}
	}

	for(travelVerts.First(); !travelVerts.IsDone(); travelVerts.MoveNext())
	{
		travelVerts.GetCurrent()->Data().SetProcessed(false);
	}
}

/*************************************************************************
*
*	Purpose:		Display the graph in a depth first traversal.
*	Entry:			Nothing.
*	Exit:			Returns nothing. Displays the vertices in the graph in
*					a depth first traversal.
*
*************************************************************************/
template <typename T, typename U>
void Graph<T,U>::DFT()
{
	ListStack<Vertex<T,U> * > stack;
	Vertex<T,U> * temp = 0;
	
	travelVerts.First();
	if(travelVerts.GetCurrent() != 0)
	{
		stack.Push(&(travelVerts.GetCurrent()->Data()));
	}

	while(!stack.isEmpty())
	{
		temp = stack.Peek();
		cout << temp->GetData().GetData() << endl;
		stack.Pop();
		temp->SetProcessed(true);

		for(temp->FirstEdge(); !temp->EdgeIsDone(); temp->NextEdge())
		{
			if(!(temp->GetCurrentEdge().GetDest()->GetProcessed()))
			{
				stack.Push(temp->GetCurrentEdge().GetDest());
			}
		}
	}

	for(travelVerts.First(); !travelVerts.IsDone(); travelVerts.MoveNext())
	{
		travelVerts.GetCurrent()->Data().SetProcessed(false);
	}
}

/*************************************************************************
*
*	Purpose:		Sets the iterator's current pointer to the first node
*					in the list.
*	Entry:			Nothing.
*	Exit:			Returns nothing.
*
*************************************************************************/
template <typename T, typename U>
void Graph<T,U>::FirstVertex()
{
	travelVerts.First();
}

/*************************************************************************
*
*	Purpose:		Return the iterators current pointer.
*	Entry:			Nothing.
*	Exit:			Returns the pointer to the current vertex pointed at
*					by the iterator.
*
*************************************************************************/
template <typename T, typename U>
Vertex<T,U>& Graph<T,U>::GetCurrentVertex()
{
	return travelVerts.GetCurrent()->Data();
}

/*************************************************************************
*
*	Purpose:		Moves the iterators current pointer to the next node
*					in the list.
*	Entry:			Nothing.
*	Exit:			Returns nothing.
*
*************************************************************************/
template <typename T, typename U>
void Graph<T,U>::NextVertex()
{
	travelVerts.MoveNext();
}

/*************************************************************************
*
*	Purpose:		Returns whether the end of the list has been traversed
*					to.
*	Entry:			Nothing.
*	Exit:			Returns bool value whether the current iterator is at 
*					the end of the list.
*
*************************************************************************/
template <typename T, typename U>
bool Graph<T,U>::VertexIsDone()
{
	return travelVerts.IsDone();
}

#endif
/*************************************************************************
*
*	Class:
*		Dijkstra
*	
*	Constructors:
*		Dijkstra() - Default constructor
*		~Dijkstra() - Destructor
*		Dijkstra(const Dijkstra&) - Copy constructor
*		Dijkstra& operator=(const Dijkstra&) - Operator =
*
*	Mutators:
*		None
*
*	Methods:
*		void Start() - Control method for the program.
*		void Display() - Breadth First Traversal for debugging.
*		void Print() - Prints the travel route to the screen.
*		void BuildMap() - Builds the graph from the file.
*		void Calculate() - Calculates the shortest DPath between two cities.
*		void Travel() - Handles the users input of cities and delegates 
*			calculations after making sure that the cities are present in 
*			the graph.
*
*************************************************************************/

#ifndef DIJKSTRA
#define DIJKSTRA

#include <istream>
#include <fstream>
using std::ifstream;

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <list>
using std::list;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "Graph.h"
#include "DPath.h"
#include "Space.h"
#include "Vertex.h"
#include "../A2BUtilities.h"
#include <stdlib.h>

class Dijkstra
{
public:
	//default constructor
	Dijkstra(int rowSize, int colSize);
	//destructor
	~Dijkstra();
	//copy constructor
	Dijkstra(const Dijkstra &copy);
	//operator =
	Dijkstra& operator=(const Dijkstra &rhs);

	//builds the map to calculate shortest paths from
	void BuildMap();
	//controller for the program
	vector<int> Start(int startSpace, int destSpace, bool* obstacleMap);
	
private:
	//calculates the shortest DPath
	vector<int> Calculate(Vertex<Space, DPath> *_from, Vertex<Space, DPath> *_to);
	//handles the users input and delegates calculation
	vector<int> Travel(int startSpace, int destSpace);
	//displays bft for debugging purposes
	void Display();
	//displays the route to travel
	void Print(int junctions, int miles);
	// creates the list of points on the route
	vector<int> CompileRoute(int junctions);
	// sets the obstacles with a bool array
	void SetObstacles(bool* obstacleMap);

	int m_rowSize;
	int m_colSize;
	int m_boardSize;
	Graph<Space, DPath> map;
	int size;			//number of cities in the map
	int *distance;		//distance array
	int *predecessor;	//predecessor array
	int *travel;		//array that stores the route
	int *travel2;		//stores the distances between the cities on the route
	bool *travel3;		//stores true if the highway is a freeway between the
						//cities
	Vertex<Space, DPath> *lookUpTable;	//lookup table for the graph cities

	Vertex<Space, DPath> *_from;	//city to travel from
	Vertex<Space, DPath> *_to;		//city to travel to
};

#endif
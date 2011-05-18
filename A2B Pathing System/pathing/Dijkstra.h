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
	Dijkstra(int rowSize, int colSize, int travelerWidth = 0);
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
	vector<int> Calculate(int _from, int _to);
	//handles the users input and delegates calculation
	vector<int> Travel(int startSpace, int destSpace);
	//displays bft for debugging purposes
	void Display();
	// creates the list of points on the route
	vector<int> CompileRoute(int junctions);
	// sets the obstacles with a bool array
	void SetObstacles(bool* obstacleMap);

	// sees if the traveler has room to move to the left
	bool IsValidWestMove(int fromSpace);
	// sees if the traveler has room to move to the right
	bool IsValidEastMove(int fromSpace);
	// sees if the travler has room to move up
	bool IsValidNorthMove(int fromSpace);
	// sees if the traveler has room to move down
	bool IsValidSouthMove(int fromSpace);
	// checks if is in the leftmost column
	bool IsWestmost(int space);
	// checks if is in the rightmost column
	bool IsEastmost(int space);
	// checks if is in the topmost row
	bool IsNorthmost(int space);
	// checks if is in the bottommost row
	bool IsSouthmost(int space);

	int m_rowSize;
	int m_colSize;
	int m_gridSize;
	int m_travelerWidth; // used to see how big of path is needed to fit through
	bool* m_obstacleMap;	// holds the obstacle map
	int *distance;		//distance array
	int *predecessor;	//predecessor array
	vector<int> m_travelRoute;	// stores the route's spaces in order
	bool* m_spaceProcessed; // array that shows if space has been touched by the pathing algorithm

};

#endif
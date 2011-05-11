#include "Dijkstra.h"

// Dijkstra's is a pathing algorithm that will look for a 

/*************************************************************************
*
*		Constructors
*
*************************************************************************/
Dijkstra::Dijkstra(int rowSize, int colSize): travel(0), travel2(0), travel3(0), predecessor(0), distance(0)
{
	m_rowSize = rowSize;
	m_colSize = colSize;
	m_boardSize = m_rowSize * m_colSize;

	BuildMap();
	size = map.GetCount();
}

Dijkstra::~Dijkstra()
{
	map.~Graph();
	
	if(travel != 0)
	{
		delete travel;
		travel = 0;
		delete travel2;
		travel2 = 0;
		delete travel3;
		travel3 = 0;
		delete distance;
		distance = 0;
		delete predecessor;
		predecessor = 0;
		delete []lookUpTable;
		lookUpTable = 0;
	}
}

Dijkstra::Dijkstra(const Dijkstra &copy)
{
	*this = copy;
}

Dijkstra& Dijkstra::operator=(const Dijkstra&rhs)
{
	if(this != &rhs)
	{
	}

	return *this;
}
/*************************************************************************
*		End Constructors
*************************************************************************/

/*************************************************************************
*
*	Purpose:		Starts the program.  Runs the pathing and returns the result
*	Entry:			starting space and destination by its id.  Also a map of obstacles (true = there is an obstacle in that space)
*	Exit:			A list of the spaces in order they should be traveled.  An empty list means no path was found.
*
*************************************************************************/
vector<int> Dijkstra::Start(int startSpace, int destSpace, bool* obstacleMap)
{
	SetObstacles(obstacleMap);	

	return Travel(startSpace, destSpace);
}

/*************************************************************************
*
*	Purpose:		Builds the graph.  Empty (no obstacles)
*	Entry:			Nothing.
*	Exit:			Returns nothing. Builds the graph from the file.
*
*************************************************************************/
void Dijkstra::BuildMap()
{
	int currPathId(60000);	// to assign new DPath ids

	for(int space(0); space < m_boardSize-1; space++)	// lower right corner will be made automatically so we don't need to make it
	{
		// all spaces above the current space will already have been inserted
		// all spaces left of the current space will already have been inserted
		// all spaces below a space will already have been inserted
		if(space == 0)
		{			
			map.InsertVertex(Space(space));
		}

		if(space % m_rowSize != m_rowSize - 1)	// not a rightmost space
		{
			if(space < m_rowSize)	// top row ( no spaces to the right have been made yet )
			{
				map.InsertVertex(Space(space+1));	// insert a space to the right
			}
			
			map.InsertEdge(space, space+1, currPathId--);	// make a connection between the two
		}

		if(m_boardSize - space > m_rowSize)		// not bottom row
		{
			map.InsertVertex(Space(space+m_rowSize));	// insert a space below
			map.InsertEdge(space, space+m_rowSize, currPathId--);		// make a connection
		}
	}
}

/*************************************************************************
*
*	Purpose:		Gets the users input for the spaces to travel from and 
*					to. Checks to make sure that the spaces are in the list.
*					Calls calculate.
*	Entry:			Nothing.
*	Exit:			Returns nothing. Catches the exceptions thrown if either
*					space is not present.
*
*************************************************************************/
vector<int> Dijkstra::Travel(int from, int to)
{
	vector<int> travelPath;

	bool present = true;

	if(present == true)	// should always be true.
	{
		// check if starting space is valid
		try
		{
			_from = &(map.RetrieveVertex(from));
		}
		catch(char *e)
		{
			cout << "Error: " << e << "\nStarting Space does not exist." << endl;
			present = false;
		}


		if(present == true)	// if start space was found
		{
			// check if ending space is valid
			try
			{
				_to = &(map.RetrieveVertex(Space(to)));
			}
			catch(char *e)
			{
				cout << "Error: " << e << "\nDestination does not exist." << endl;
				present = false;
			}
		}
	}

	if(present == true)	// if start and destination were found
	{
		travelPath = Calculate(_from, _to);	// calculate the shortest path
	}

	return travelPath;
}

/*************************************************************************
*
*	Purpose:		Calculates the shortest path between two spaces.
*	Entry:			Requires the starting and ending spaces to be passed in.
*	Exit:			Returns nothing. Builds the arrays that handle traveling
*					along the shortest path.
*
*************************************************************************/
vector<int> Dijkstra::Calculate(Vertex<Space, DPath> *_from, Vertex<Space, DPath> *_to)
{
	distance = new int[size];	// the distance traveled
	predecessor = new int[size];	// each spaces space that was traveled before this one
	travel = new int[size];		// the path (will be in reverse at the end of this)
	lookUpTable = new Vertex<Space, DPath>[size];
	vector<int> travelPath;	// what spaces we are going through (what will be returned back)

	int i = 0;				//trash variable
	int host = 0;			//the vertice that is being examined currently
	int completed = 0;		//# of completed vertices
	int dist = 0;			//distance to find the next vertex to evaluate
	int dest = 0;			//location of the destination in the array
	int orig = 0;			//location of the original vertex to start from
	int current = 0;		//current location in the array

	// initializes the data (invalidating it so we know which ones we haven't checked)
	for(map.FirstVertex(); i < size; map.NextVertex())
	{
		distance[i] = -1;
		predecessor[i] = -1;
		travel[i] = -1;
		lookUpTable[i] = map.GetCurrentVertex();
		i++;
	}

	// find which one is the starting space
	while(lookUpTable[host].GetData() != _from->GetData())
	{
		host++;
	}

	orig = host;

	// find which one is the destination space
	while(lookUpTable[dest].GetData() != _to->GetData())
	{
		dest++;
	}

	distance[host] = 0;

	// haven't looked through all possibilities
	while(completed < size)
	{
		// for each path from the space we are looking at
		for(lookUpTable[host].FirstEdge(); !lookUpTable[host].EdgeIsDone(); lookUpTable[host].NextEdge())
		{
				// current space from host does not have an obstacle
			if(!(lookUpTable[host].GetCurrentEdge().GetDest()->GetData().IsObstacle()))
			{
				current = 0;

				// find a path to the current space
				while(lookUpTable[current].GetData() != lookUpTable[host].GetCurrentEdge().GetDest()->GetData())
				{
					current++;
				}

				// if we haven't looked at the current path or the distance to this path isn't more
				if((distance[current] == -1) || (distance[current] > (lookUpTable[host].GetCurrentEdge().GetWeight() + dist)))
				{
					// if it is an obstacle
					if(lookUpTable[host].GetCurrentEdge().GetDest()->GetData().IsObstacle())
						distance[current] = 9999;	// don't want to travel through an obstacle (a longer distance than will want to travel)
					else	// define this path with its distance
						distance[current] = lookUpTable[host].GetCurrentEdge().GetWeight() + dist;
					
					predecessor[current] = host;
					host = host;
				}
			}
		}


		lookUpTable[host].SetProcessed(true);
		completed++;

		for(i = 0; i < size; i++)
		{
			// find the next path to look at.
			if((!lookUpTable[i].GetProcessed()) && distance[i] > 0)
			{
				host = i;
				dist = distance[host];
			}
		}

		for(i = 0; i < size; i++)
		{
			if((distance[i] > 0) && (!lookUpTable[i].GetProcessed()) && (distance[i] <= dist))
			{
				host = i;
				dist = distance[host];
			}
		}
	}

	host = orig;
	current = dest;
	travel[0] = dest;

	i = 1;	// start right before the destination going backwards

	// haven't made it back to the start and path is valid
	while(current != host && current > 0)
	{
		travel[i] = predecessor[current];
		current = predecessor[current];

		i++;	// go backwards one more
	}

	// not a valid path
	if(current < 0)
		travelPath.clear();	// make sure we are sending back an empty path
	else
		travelPath = CompileRoute(i);	// put the path together

	return travelPath;
}


/*************************************************************************
*
*	Purpose:		Performs a breadth first traversal.
*	Entry:			Nothing.
*	Exit:			Returns nothing. Prints the traversal to the screen.
*
*************************************************************************/
void Dijkstra::Display()
{
	map.BFT();
}

/*************************************************************************
*
*	Purpose:		Prints the shortest route between two spaces.
*	Entry:			Requires the number of junctions and distance traveled to
*					be passed in.
*	Exit:			Returns nothing. Displays the DPath
*
*************************************************************************/
void Dijkstra::Print(int junctions, int distance)
{
//	system("CLS");
	int junc = junctions;
	junctions--;

	// for all the junctions print them
	while(junctions > 0)
	{
		cout << lookUpTable[travel[junctions]].GetData().GetId() << " -> " ;

		lookUpTable[travel[junctions]].FirstEdge();
		Space temp = lookUpTable[travel[junctions - 1]].GetData();
		Space temp2 = lookUpTable[travel[junctions]].GetCurrentEdge().GetDest()->GetData();
		while(temp != temp2)
		{
			lookUpTable[travel[junctions]].NextEdge();
			temp2 = lookUpTable[travel[junctions]].GetCurrentEdge().GetDest()->GetData();
		}

		cout << lookUpTable[travel[junctions]].GetCurrentEdge().GetId() << " -> "
			 << lookUpTable[travel[junctions - 1]].GetData().GetId() << endl;

		travel2[junctions] = lookUpTable[travel[junctions]].GetCurrentEdge().GetWeight();
		junctions--;
	}
}

vector<int> Dijkstra::CompileRoute(int junctions)
{
	vector<int> travelPath;
	junctions--;

	// if we need the starting point as part of the route then we will need to get the first point here;
	for(int junc(junctions); junc > 0; junc--)
	{
		travelPath.push_back(lookUpTable[travel[junc - 1]].GetData().GetId());
	}

	return travelPath;
}

void Dijkstra::SetObstacles(bool* obstacleMap)
{
	map.FirstVertex();	// start from first space

	// for all spaces on the board
	for(int space(0); space < BOARD_SIZE; space++)
	{
		map.GetCurrentVertex().GetData().SetObstacle(obstacleMap[space]);
		map.NextVertex();
	}
}
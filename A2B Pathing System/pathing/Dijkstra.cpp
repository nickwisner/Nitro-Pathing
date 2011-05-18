#include "Dijkstra.h"

// Dijkstra's is a pathing algorithm that will look for a 

/*************************************************************************
*
*		Constructors
*
*************************************************************************/
Dijkstra::Dijkstra(int rowSize, int colSize, int travelerWidth):predecessor(0), distance(0), m_travelerWidth(travelerWidth)
{
	m_rowSize = rowSize;
	m_colSize = colSize;
	m_gridSize = m_rowSize * m_colSize;

	distance = new int[m_gridSize];	// the distance traveled
	predecessor = new int[m_gridSize];	// each spaces space that was traveled before this one
	m_spaceProcessed = new bool[m_gridSize];	// for each space shows if pathing algorithm has touched it
	m_travelRoute.clear();

	BuildMap();
}

Dijkstra::~Dijkstra()
{
	m_travelRoute.clear();
	delete distance;
	distance = 0;
	delete predecessor;
	predecessor = 0;
	delete m_spaceProcessed;
	m_spaceProcessed = 0;
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
	// allocate the map
	m_obstacleMap = new bool[m_rowSize * m_colSize];

	// make it a map empty of obstacles
	for(int space(0); space < m_gridSize; space++)
		m_obstacleMap[space] = false;

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

	// make sure the path is empty
	travelPath.clear();

	// both to and from spaces exist
	if(from < m_gridSize && from >= 0 && to < m_gridSize && to >= 0)
	{
		travelPath = Calculate(from, to);	// calculate the shortest path
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
vector<int> Dijkstra::Calculate(int _from, int _to)
{
	vector<int> travelPath;	// what spaces we are going through (what will be returned back)

	int host = 0;			//the vertice that is being examined currently
	int dist = 0;			//distance to find the next vertex to evaluate
	int dest = 0;			//location of the destination in the array
	int orig = 0;			//location of the original vertex to start from
	int currSpace(0);		// space location that is being processed
	int spacesTraveled(0);	//how many spaces the final route goes through

	// initializes the data (invalidating it so we know which ones we haven't checked)
	for(int space(0); space < m_gridSize; space++)
	{
		distance[space] = -1;
		predecessor[space] = -1;
//		travelRoute[space] = -1;
		m_spaceProcessed[space] = false;
	}

	m_travelRoute.clear();

	// should be clear but making sure it is
	travelPath.clear();

	// set the start space
	host = _from;
	orig = host;

	// set the destination space
	dest = _to;

	// set the distance of the start space to itself to zero
	distance[host] = 0;

	// for all spaces on the grid
	for(int completed(0); completed < m_gridSize; completed++)
	{

		currSpace = host-1;	// west of host

		// check the space west of current space
		if(!m_spaceProcessed[currSpace] && IsValidWestMove(host))
		{
			distance[currSpace] = distance[host] + 1;
			predecessor[currSpace] = host;
		}
		else if(!IsWestmost(host) && m_obstacleMap[currSpace])	// an obstacle
		{
			distance[currSpace] = 9999;	// make it an unnecessarily large distance to travel to this space
		}

		currSpace = host+1;	// east of host

		// check the space east of current space
		if(!m_spaceProcessed[currSpace] && IsValidEastMove(host))
		{
			distance[currSpace] = distance[host] + 1;
			predecessor[currSpace] = host;
		}
		else if(!IsEastmost(host) && m_obstacleMap[currSpace])	// an obstacle
		{
			distance[currSpace] = 9999;	// make it an unnecessarily large distance to travel to this space
		}

		currSpace = host - m_rowSize;	// north of host

		// check the space north of current space
		if(!m_spaceProcessed[currSpace] && IsValidNorthMove(host))
		{
			distance[currSpace] = distance[host] + 1;
			predecessor[currSpace] = host;
		}
		else if(!IsNorthmost(host) && m_obstacleMap[currSpace])	// an obstacle
		{
			distance[currSpace] = 9999;	// make it an unnecessarily large distance to travel to this space
		}

		currSpace = host + m_rowSize;	// south of host

		// check the space south of current space
		if(!m_spaceProcessed[currSpace] && IsValidSouthMove(host))
		{
			distance[currSpace] = distance[host] + 1;
			predecessor[currSpace] = host;
		}
		else if(!IsSouthmost(host) && m_obstacleMap[currSpace])	// an obstacle
		{
			distance[currSpace] = 9999;	// make it an unnecessarily large distance to travel to this space
		}

		m_spaceProcessed[host] = true;

		bool newHostFound(false);
		int space(0);
		
		// find a possible new path host
		while(!newHostFound && space < m_gridSize)
		{
			// found a possibility to compare other candidates to
			if(!m_spaceProcessed[space] && distance[space] > 0)
			{
				host = space;
				dist = distance[host];
				newHostFound = true;
			}

			space++;
		}
		
		// find the space that is the least distance out from the original for the next check
		for(int space(0); space < m_gridSize; space++)
		{
			if((distance[space] > 0) && !m_spaceProcessed[space] && distance[space] <= dist)
			{
				host = space;
				dist = distance[host];
			}
		}
	}

	vector<int> finalTravel;
	host = orig;
	currSpace = dest; // start at end
	finalTravel.insert(finalTravel.begin(), dest);

	m_travelRoute.push_back(dest);
	spacesTraveled++;	

	// haven't made it back to the start and path is still valid
	while(currSpace != host && currSpace > 0)
	{
		// insert the space at the beginning of the list because it is closer to the start space
		m_travelRoute.insert(m_travelRoute.begin(), predecessor[currSpace]);
		currSpace = predecessor[currSpace];	// prime the next space
	}

	// not a valid path
	if(currSpace < 0)
		m_travelRoute.clear();	// make sure we are sending back an empty path

	return m_travelRoute;
}

// unnnecessary now how it is written... can be removed after testing
vector<int> Dijkstra::CompileRoute(int junctions)
{
	vector<int> travelPath;
	junctions--;

	// if we need the starting point as part of the route then we will need to get the first point here;
	for(int junc(junctions); junc > 0; junc--)
	{
//		travelPath.push_back(lookUpTable[travel[junc - 1]].GetData().GetId());
	}

	return travelPath;
}

void Dijkstra::SetObstacles(bool* obstacleMap)
{
	// for all spaces on the board
	for(int space(0); space < m_gridSize; space++)
	{
		// update the space with the passed obstacle map
		m_obstacleMap[space] = obstacleMap[space];
	}
}

// sees if the traveler has room to move to the left
bool Dijkstra::IsValidWestMove(int fromSpace)
{
	bool validMove(true);
	int numChecksLeft(0);	// number of spaces to check in a direction
	int rightCheckSpace(0);	// the space we are checking if it is obstacle free and on the grid for the right side of the robot
	int leftCheckSpace(0);	// the space we are checking if is is obstacle free and on the grid for the left side of the robot

	// already as far left as can be?
	if(IsWestmost(fromSpace))
		validMove = false;

	// how many spaces to check on either side to cover the size of the traveler
	numChecksLeft = m_travelerWidth/2 + m_travelerWidth%2;
	
	// if on the top or bottom row and traveler is bigger than one space
	if( numChecksLeft && (IsNorthmost(fromSpace) || IsSouthmost(fromSpace)) )
		validMove = false;

	// initialize checkSpaces to the middle space
	rightCheckSpace = leftCheckSpace = fromSpace-1;	// one left of fromSpace

	// checking above the space we are moving to to make sure there is room
	do
	{
		// if on top row and still need more space above or has obstacle
		if( (IsNorthmost(rightCheckSpace) && numChecksLeft) || m_obstacleMap[rightCheckSpace])
			validMove = false;

		// if on bottom row and still need more space above or has obstacle
		if( (IsSouthmost(leftCheckSpace) && numChecksLeft) || m_obstacleMap[leftCheckSpace])
			validMove = false;

		rightCheckSpace -= m_rowSize;	// go a row up
		leftCheckSpace += m_rowSize;	// go a row down
	}
	while(numChecksLeft-- && validMove);

	return validMove;
}

// sees if the traveler has room to move to the right
bool Dijkstra::IsValidEastMove(int fromSpace)
{
	bool validMove(true);
	int numChecksLeft(0);	// number of spaces to check in a direction
	int rightCheckSpace(0);	// the space we are checking if it is obstacle free and on the grid for the right side of the robot
	int leftCheckSpace(0);	// the space we are checking if is is obstacle free and on the grid for the left side of the robot

	// already as far right as can be?
	if(IsEastmost(fromSpace))
		validMove = false;

	// how many spaces to check on either side to cover the size of the traveler
	numChecksLeft = m_travelerWidth/2 + m_travelerWidth%2;
	
	// if on the top or bottom row and traveler is bigger than one space
	if( numChecksLeft && (IsNorthmost(fromSpace) || IsSouthmost(fromSpace)) )
		validMove = false;

	// initialize checkSpaces to the middle space
	rightCheckSpace = leftCheckSpace = fromSpace+1;	// one right of fromSpace

	// checking above the space we are moving to to make sure there is room
	do
	{

		// if on top row and still need more space above or has obstacle
		if( (IsSouthmost(rightCheckSpace) && numChecksLeft) || m_obstacleMap[rightCheckSpace])
			validMove = false;

		// if on bottom row and still need more space above or has obstacle
		if( (IsNorthmost(leftCheckSpace) && numChecksLeft) || m_obstacleMap[leftCheckSpace])
			validMove = false;

		rightCheckSpace += m_rowSize;	// go a row down
		leftCheckSpace -= m_rowSize;	// go a row up
	}
	while(numChecksLeft-- && validMove);

	return validMove;
}

// sees if the travler has room to move up
bool Dijkstra::IsValidNorthMove(int fromSpace)
{
	bool validMove(true);
	int numChecksLeft(0);	// number of spaces to check in a direction
	int rightCheckSpace(0);	// the space we are checking if it is obstacle free and on the grid for the right side of the robot
	int leftCheckSpace(0);	// the space we are checking if is is obstacle free and on the grid for the left side of the robot

	// already as far up as can be?
	if(IsNorthmost(fromSpace))
		validMove = false;

	// how many spaces to check on either side to cover the size of the traveler
	numChecksLeft = m_travelerWidth/2 + m_travelerWidth%2;
	
	// if on the left or rightmost column and traveler is bigger than one space
	if( numChecksLeft && (IsWestmost(fromSpace) || IsEastmost(fromSpace)) )
		validMove = false;

	// initialize checkSpaces to the middle space
	rightCheckSpace = leftCheckSpace = fromSpace - m_rowSize;	// one space north of fromSpace

	// checking above the space we are moving to to make sure there is room
	do
	{
		// if at rightmost column and still need more space above or has obstacle
		if( (IsEastmost(rightCheckSpace) && numChecksLeft) || m_obstacleMap[rightCheckSpace])
			validMove = false;

		// if at leftmost column and still need more space above or has obstacle
		if( (IsWestmost(leftCheckSpace) && numChecksLeft) || m_obstacleMap[leftCheckSpace])
			validMove = false;

		rightCheckSpace++;	// go a column right
		leftCheckSpace--;	// go a column left
	}
	while(numChecksLeft-- && validMove);

	return validMove;
}

// sees if the traveler has room to move down
bool Dijkstra::IsValidSouthMove(int fromSpace)
{
	bool validMove(true);
	int numChecksLeft(0);	// number of spaces to check in a direction
	int rightCheckSpace(0);	// the space we are checking if it is obstacle free and on the grid for the right side of the robot
	int leftCheckSpace(0);	// the space we are checking if is is obstacle free and on the grid for the left side of the robot

	// already as far down as can be?
	if(IsSouthmost(fromSpace))
		validMove = false;

	// how many spaces to check on either side to cover the size of the traveler
	numChecksLeft = m_travelerWidth/2 + m_travelerWidth%2;
	
	// if on the left or rightmost column and traveler is bigger than one space
	if( numChecksLeft && (IsWestmost(fromSpace) || IsEastmost(fromSpace)) )
		validMove = false;

	// initialize checkSpaces to the middle space
	rightCheckSpace = leftCheckSpace = fromSpace + m_rowSize;	// one space south of fromSpace

	// checking above the space we are moving to to make sure there is room
	do
	{
		// if at leftmost column and still need more space above or has obstacle
		if( (IsWestmost(rightCheckSpace) && numChecksLeft) || m_obstacleMap[rightCheckSpace])
			validMove = false;

		// if at rightmost column and still need more space above or has obstacle
		if( (IsEastmost(leftCheckSpace) && numChecksLeft) || m_obstacleMap[leftCheckSpace])
			validMove = false;

		rightCheckSpace--;	// go a column left
		leftCheckSpace++;	// go a column right
	}
	while(numChecksLeft-- && validMove);

	return validMove;
}

// checks if is in the leftmost column
bool Dijkstra::IsWestmost(int space)
{
	bool westMost(false);

	// farthest to the left in the grid
	if(space % m_rowSize == 0)
		westMost = true;

	return westMost;
}

// checks if is in the rightmost column
bool Dijkstra::IsEastmost(int space)
{
	bool eastMost(false);

	// farthest to the right in the grid
	if(space % m_rowSize == m_rowSize-1)
		eastMost = true;

	return eastMost;
}

// checks if is in the topmost row
bool Dijkstra::IsNorthmost(int space)
{
	bool northMost(false);

	// topmost row
	if(space < m_rowSize)
		northMost = true;

	return northMost;
}

// checks if is in the bottommost row
bool Dijkstra::IsSouthmost(int space)
{
	bool southMost(false);

	// on the bottom row
	if(m_gridSize - space < m_rowSize)
		southMost = true;

	return southMost;
}

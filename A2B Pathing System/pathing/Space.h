/*************************************************************************
*
*	Class:
*		Space
*	
*	Constructors:
*		Space() - Default constructor
*		Space(int, bool) - 2 Arg constructor; initializes id to the value
*			passed in, and sets if an obstacle is present.
*		~Space() - Destructor
*		Space(const Space&) - Copy constructor
*		Space& operator=(const Space&) - Operator =
*
*	Mutators:
*		int GetId() - Returns the value stored in id.
*		void SetId(int) - Sets space number to the value passed in.
*
*	Methods:
*		bool operator==(const Space&) - Overloaded operator==; Compares the
*			numbers of the two spaces. Returns true if equal.
*		bool operator!=(const Space&) - Overloaded operator!=; Compares the
*			ints of two space numbers. Returns true if not equal.
*
*************************************************************************/

#ifndef SPACE_H
#define SPACE_H


class Space
{
public:
	//default constructor
	Space();
	//1 arg constructor
	Space(int id, bool obstacle = false);
	//destructor
	~Space();
	//copy constructor
	Space(const Space &copy);
	//operator =
	Space& operator=(const Space &rhs);

	int GetId();
	void SetId(int id);
	bool IsObstacle();
	void SetObstacle(bool obstacle);

	bool operator==(const Space &rhs);	//compares the names
	bool operator!=(const Space &rhs);	//compares the names

private:
	int m_id;
	bool m_obstacle;
};

#endif
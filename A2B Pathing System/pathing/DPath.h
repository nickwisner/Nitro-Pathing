/*************************************************************************
*
*	Class:
*		DPath
*	
*	Constructors:
*		DPath() - Default constructor
*		DPath(string) - 1 Arg constructor; initializes name to the value
*			passed in.
*		~DPath() - Destructor
*		DPath(const DPath&) - Copy constructor
*		DPath& operator=(const DPath&) - Operator =
*
*	Mutators:
*		string GetData() - Returns the value stored in name.
*		void SetName(string) - Sets name to the value passed in.
*
*	Methods:
*		bool operator==(const DPath&) - Overloaded operator==; Compares the
*			string names of the two highways. Returns true if equal.
*		bool operator!=(const DPath&) - Overloaded operator!=; Compares the
*			string names of the two highways. Returns true if not equal.
*
*************************************************************************/

#ifndef PATH_H
#define PATH_H

class DPath
{
public:
	//default constructor
	DPath();
	//1 arg constructor
	DPath(int id);
	//destructors
	~DPath();
	//copy constructor
	DPath(const DPath &copy);
	//operator=
	DPath& operator=(const DPath &rhs);

	//Mutators
	int GetId();
	void SetId(int id);

	bool operator==(const DPath &rhs);	//compares the names
	bool operator!=(const DPath &rhs);	//compares the names

private:
	int m_id;		//id of the DPath
};

#endif
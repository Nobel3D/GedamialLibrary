#ifndef GEDAMIAL_H
#define GEDAMIAL_H
/*
	GEDAMIAL LIBRARY
	CREATION DATE: 31/10/2015
	LAST UPDATES 
	04/01/2016 - added GArray class
	06/01/2016 - added more operator overloading to GArray class
	07/01/2016 - some adjustements
	08/01/2016 - bug fix in GArray
	09/01/2016 - added GString class
	11/01/2016 - added GList class
	12/01/2016 - added == and != operators to GString class
	15/01/2016 - added G3DVector class	
	15/01/2016 - added operator overloading functions in GList class
	18/01/2016
	19/01/2016 - overloaded operator= in GFraction class
	25/01/2016 - added code to reverse a GList	
	31/01/2016 - added Append function for GStrings
	07/02/2016 - added GStack class
	08/03/2016 - renamed G3DVector to GVector3
	12/03/2016 - GString: separated interface from implementation in operator overloading and added comments
*/

// MATHEMATICS
#include "Mathematics/GFraction.h"
#include "Mathematics/GVector3.h"
#include "Mathematics/Point.h"
#include "Mathematics/Segment.h"

// DATA
#include "Data/GArray.h"
#include "Data/GString.h"
#include "Data/GList.h"
#include "Data/GStack.h"
#include "Data/GTree.h"

// GAME ALGORITHMS
// character


/*
TEMPLATIZED FUNCTIONS
template<typename T>
bool InputFailed(T& var)
{
	std::cin >> var;

	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return true;
	}

	else
		return false;
}	
*/

#endif
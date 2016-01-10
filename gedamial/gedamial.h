#ifndef GEDAMIAL_H
#define GEDAMIAL_H
/*
	GEDAMIAL LIBRARY
	CREATION DATE: 31/10/2015
	LAST UPDATE: 04/01/2016 - added GArray class
	LAST UPDATE: 06/01/2016 - added more operator overloading to GArray class
	LAST UPDATE: 07/01/2016 - some adjustements
	LAST UPDATE: 08/01/2016 - bug fix in GArray
	LAST UPDATE: 9/01/2016 - added GString class
*/

// STANDARD INCLUDES
#include <iostream>
#include <limits>

// MATHEMATICS
#include "Mathematics/GFraction.h"

// DATA
#include "Data/GArray.h"
#include "Data/GString.h"
#include "Data/GList.h"
	
// TEMPLATIZED FUNCTIONS
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

#endif

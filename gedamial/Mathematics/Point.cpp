#include "Point.h"

Point::Point(float xCoord, float yCoord) : x{ xCoord }, y{yCoord}
{
}

float Point::getX()
{
	return x;
}

float Point::getY()
{
	return y;
}

void Point::setX(float xCoord)
{
	x = xCoord;
}

void Point::setY(float yCoord)
{
	y = yCoord;
}

Point::~Point()
{
}

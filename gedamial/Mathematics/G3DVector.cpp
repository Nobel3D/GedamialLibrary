#include "G3DVector.h"

float ged::Mathematics::G3DVector::GetX() const
{
	return x;
}

float ged::Mathematics::G3DVector::GetY() const
{
	return y;
}

float ged::Mathematics::G3DVector::GetZ() const
{
	return z;
}

float ged::Mathematics::G3DVector::GetMagnitude() const
{
	return magnitude;
}

std::ostream & ged::Mathematics::operator<<(std::ostream & s, const G3DVector & other)
{
	std::cout << "(" << other.x << ", " << other.y << ", " << other.z << ")" << std::endl;
	return s;
}

ged::Mathematics::G3DVector& ged::Mathematics::operator+(const G3DVector& right, const G3DVector& left)
{
	G3DVector result = G3DVector(right.x + left.x, right.y + left.y, right.z + left.z);
	return result;
}

ged::Mathematics::G3DVector& ged::Mathematics::operator-(const G3DVector& right, const G3DVector& left)
{
	G3DVector result = G3DVector(right.x - left.x, right.y - left.y, right.z - left.z);
	return result;
}
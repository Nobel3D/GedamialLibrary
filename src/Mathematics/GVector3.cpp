#include "GVector3.h"
#include <iostream>
#include <cmath> //for pow and sqrt

/* GETTER AND SETTER METHODS */

namespace ged
{
	namespace Mathematics
	{
		GVector3::GVector3()
		{

		}

		GVector3::GVector3(float _x, float _y, float _z) : x{ _x }, y{ _y }, z{ _z }
		{

		}

		float GVector3::GetX() const
		{
			return x;
		}

		float GVector3::GetY() const
		{
			return y;
		}

		float GVector3::GetZ() const
		{
			return z;
		}

		float GVector3::GetMagnitude() const
		{
			return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		}

		void GVector3::SetX(float newX)
		{
			x = newX;
		}

		void GVector3::SetY(float newY)
		{
			y = newY;
		}

		void GVector3::SetZ(float newZ)
		{
			z = newZ;
		}

		/* OPERATOR OVERLOADING */

		std::ostream& operator<<(std::ostream& s, const GVector3& other)
		{
			std::cout << "(" << other.x << ", " << other.y << ", " << other.z << ")" << std::endl;
			return s;
		}

		GVector3& operator+(const GVector3& right, const GVector3& left)
		{
			GVector3* result = new GVector3{ right.x + left.x, right.y + left.y, right.z + left.z };
			return *result;
		}

		GVector3& operator-(const GVector3& right, const GVector3& left)
		{
			GVector3* result = new GVector3{ right.x - left.x, right.y - left.y, right.z - left.z };
			return *result;
		}
	}
}

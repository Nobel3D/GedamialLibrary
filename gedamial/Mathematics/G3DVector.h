#pragma once
#include <iostream>
#include <math.h>

namespace ged
{
	namespace Mathematics
	{
		class G3DVector
		{
		private:
			float x = 0, y = 0, z = 0;
			float magnitude = 0;
		public:
			G3DVector() {}
			G3DVector(float _x, float _y, float _z) : x(_x), y(_y), z(_z), magnitude(sqrt(pow(x,2)+pow(y,2)+pow(z,2)))
			{}

			/* GETTER METHODS */
			float GetX() const;
			float GetY() const;
			float GetZ() const;
			float GetMagnitude() const;

		private:
			/* OPERATOR OVERLOADING */
			friend std::ostream& operator<<(std::ostream& s, const G3DVector& other);
			friend G3DVector& operator+(const G3DVector& right, const G3DVector& left);
			friend G3DVector& operator-(const G3DVector& right, const G3DVector& left);
		};
	}
}



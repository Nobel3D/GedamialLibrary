#ifndef VECTOR_H
#define VECTOR_H
#include <ostream>

namespace ged
{
	namespace Mathematics
	{
		class GVector3
		{
		private:
			float x = 0, y = 0, z = 0;
		public:
			GVector3();
			GVector3(float _x, float _y, float _z);

			/* GETTER METHODS */
			float GetX() const;
			float GetY() const;
			float GetZ() const;
			float GetMagnitude() const;

			/* SETTER METHODS */
			void SetX(float newX);
			void SetY(float newY);
			void SetZ(float newZ);

			/* OPERATOR OVERLOADING */
		private:			
			friend std::ostream& operator<<(std::ostream& s, const GVector3& other);
			friend GVector3& operator+(const GVector3& right, const GVector3& left);
			friend GVector3& operator-(const GVector3& right, const GVector3& left);
		};
	}
}
#endif



#include "GFraction.h"
#include <iostream>
#include <sstream>
#include <math.h>

namespace ged
{
	namespace Mathematics
	{
		int getMCD(int a, int b)
		{
			do
			{
				if (a>b)
					a = (a - b);

				else if (a<b)
					b = (b - a);

			} while (a != b);

			return a;
		}

		int getMCM(int a, int b)
		{
			return ((a * b) / getMCD(a, b));
		}

		GFraction::GFraction() {}
		GFraction::~GFraction() {}
		GFraction::GFraction(int num, int den) : numerator(num)
		{
			if (den < 1)
				denominator = 1;
		}		

		void GFraction::setNum(int num)
		{
			numerator = num;
		}

		void GFraction::setDen(int den)
		{
			denominator = den;
		}

		int GFraction::GetNumerator()
		{
			return numerator;
		}

		int GFraction::GetDenominator()
		{
			return denominator;
		}

		GFraction GFraction::changeSign()
		{
			GFraction result;
			result.numerator = this->numerator*(-1);
			result.denominator = this->denominator;

			return result;
		}

		GFraction GFraction::POW(GFraction f)
		{
			GFraction result;
			result.numerator = pow(f.numerator, 2);
			result.denominator = pow(f.denominator, 2);
			return result;
		}

		GFraction GFraction::SQRT(GFraction f)
		{
			GFraction result;

			result.numerator = sqrt(f.numerator);
			result.denominator = sqrt(f.denominator);

			return result;
		}

		std::string GFraction::printGFraction()
		{
			std::stringstream ss;
			ss << numerator << "/" << denominator;
			return ss.str();
		}

		bool GFraction::isZero()
		{
			if (numerator == 0 || denominator == 0)
				return true;
			else
				return false;
		}

		bool GFraction::isLessThanZero()
		{
			if (numerator < 0)
				return true;
			else
				return false;
		}

		GFraction GFraction::Sum(const GFraction& first, const GFraction& second)
		{
			GFraction result;
			result.denominator = getMCM(first.denominator, second.denominator);
			result.numerator = ((result.denominator / first.denominator)*first.numerator) + ((result.denominator / second.denominator)*second.numerator);

			return result;
		}

		GFraction GFraction::Difference(const GFraction& first, const GFraction& second)
		{
			GFraction result;
			result.denominator = getMCM(first.denominator, second.denominator);
			result.numerator = ((result.denominator / first.denominator)*first.numerator) - ((result.denominator / second.denominator)*second.numerator);

			return result;
		}

		GFraction GFraction::Multiplication(const GFraction& first, const GFraction& second)
		{
			GFraction result;

			result.numerator = first.numerator * second.numerator;
			result.denominator = first.denominator * second.denominator;

			return result;
		}

		GFraction GFraction::Multiplication(int num, const GFraction& f)
		{
			GFraction result;

			result.numerator = num * f.numerator;
			result.denominator = f.denominator;

			return result;
		}

		GFraction GFraction::Division(const GFraction& first, const GFraction& second)
		{
			GFraction result;

			if (first.denominator == 1 && second.denominator == 1)
			{
				result.numerator = first.numerator;
				result.denominator = second.numerator;
			}

			else
			{
				result.numerator = first.numerator / second.numerator;
				result.denominator = first.denominator / second.denominator;
			}

			return result;
		}

		std::ostream& operator<<(std::ostream& s, const GFraction& other)
		{
			std::cout << other.numerator << "/" << other.denominator << std::endl;

			return s;
		}
	}
}

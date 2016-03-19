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

		GFraction::GFraction() : numerator{ 1 }, denominator{ 1 }
		{}

		GFraction::GFraction(const GFraction& copy)
		{
			std::cout << "copy ctor" << std::endl;
		}

		GFraction::GFraction(GFraction&& move)
		{
			std::cout << "move ctor" << std::endl;
		}

		GFraction::~GFraction() {}

		GFraction::GFraction(int Numerator, int Denominator) : numerator{ Numerator }
		{
			setDenominator(Denominator);
		}		

		void GFraction::setNumerator(int num)
		{
			numerator = num;
		}

		void GFraction::setDenominator(int den)
		{
			if (den == 0)
				denominator = 1;
			else
				denominator = den;
		}

		int GFraction::GetNumerator() {	return numerator; }
		int GFraction::GetDenominator()	{ return denominator; }

		GFraction GFraction::changeSign()
		{			
			return GFraction(numerator*-1, denominator);
		}

		// static
		GFraction GFraction::POW(GFraction f)
		{
			return GFraction(pow(f.numerator,2), pow(f.denominator,2));
		}

		// static
		GFraction GFraction::SQRT(GFraction f)
		{
			return GFraction(sqrt(f.numerator), sqrt(f.denominator));
		}

		GFraction GFraction::Simplify()
		{
			int MCD = getMCD(numerator, denominator);
			numerator /= MCD;
			denominator /= MCD;

			return *this;
		}

		std::string GFraction::printGFraction()
		{
			std::stringstream ss;
			ss << numerator << "/" << denominator;
			return ss.str();
		}

		bool GFraction::isZero()
		{
			if (numerator == 0)
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

		// static
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
			return GFraction(first.numerator*second.numerator, first.denominator * second.denominator);
		}

		GFraction GFraction::Multiplication(int num, const GFraction& f)
		{
			return GFraction(num*f.numerator, f.denominator);
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

		/* OPERATOR OVERLOADING */
		std::ostream& operator<<(std::ostream& s, const GFraction& other)
		{
			std::cout << other.numerator << "/" << other.denominator;

			return s;
		}

		GFraction& GFraction::operator=(const GFraction & other)
		{
			numerator = other.numerator;
			denominator = other.denominator;

			return *this;
		}
	}
}

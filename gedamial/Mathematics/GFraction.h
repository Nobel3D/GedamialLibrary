#ifndef GFraction_H
#define GFraction_H
#include <string>

namespace ged
{
	namespace Mathematics
	{
		int getMCD(int a, int b);
		int getMCM(int a, int b);

		class GFraction
		{
		private:
			int numerator;
			int denominator;

		public:
			// CTOR
			GFraction();
			GFraction(const GFraction& copy);
			GFraction(GFraction&& move);
			GFraction(int Numerator, int Denominator);

			// DTOR
			~GFraction();

			// Setter methods
			void setNumerator(int num);
			void setDenominator(int den);

			// Getter methods
			int GetNumerator();
			int GetDenominator();

			// Sum
			static GFraction Sum(const GFraction& first, const GFraction& second);

			// Difference
			static GFraction Difference(const GFraction& first, const GFraction& second);

			// Multiplication
			static GFraction Multiplication(const GFraction& first, const GFraction& second);
			static GFraction Multiplication(int num, const GFraction& f);

			// Division
			static GFraction Division(const GFraction& first, const GFraction& second);

			// Operations
			GFraction changeSign();
			static GFraction POW(GFraction f);
			static GFraction SQRT(GFraction f);
			GFraction Simplify();			

			// Utility
			std::string printGFraction();

			// Checks
			bool isZero();
			bool isLessThanZero();

			/* OPERATOR OVERLOADING */
			friend std::ostream& operator<<(std::ostream& s, const GFraction& other);			
			operator int() const { return numerator / denominator; }
			operator float() const { return static_cast<float>(numerator) / denominator; }
			operator double() const { return static_cast<double>(numerator) / denominator; }
			GFraction& operator=(const GFraction& other);			
		};
	}
}
#endif

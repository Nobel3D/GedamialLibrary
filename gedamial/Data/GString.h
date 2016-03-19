#ifndef GSTRING_H
#define GSTRING_H

#include <iostream>
#include "GArray.h"

namespace ged
{
	namespace Data
	{
		class GString
		{
		private:
			char* mainString;
			int size;
		public:
			// There is no need for an empty constructor like the one commented above
			// since we are making a constructor taking either a string or an empty one
			//GString();
			GString(const char* CstyleString = "");
			// copy constructor
			GString(const GString& copy);
			// move constructor - some performance boost
			GString(GString&& move);
			// destructor
			~GString();

			// returns the string in a Upper Case format
			GString ToUpper();
			// returns the string in a Lower Case format
			GString ToLower();						

			// appends a char* to the GString
			void Append(const char* toAdd);
			// appends a char to the GString
			void Append(char toAdd);

			// finds a single character in the GString and returns the index of it
			int Find(const char charToSearch, int start) const;
			// returns how many times the character appears in the GString
			int HowManyTimes(const char charToSearch) const;
			// reverses the GString (e.g.: hello -> olleh)
			static GString Reverse(const GString& str);
			// determines if a given GString is palindrome or not (e.g.: poop -> yes, it's palindrome)
			static bool bIsPalindrome(const GString& str);

			// takes a substring that begins from BEGING and ends at END
			GString SubString(int begin, int end) const;

			// still need to find the right algorithm for this...
			//static GArray<GString>& Split(const char Splitter, GString& str);


			/* GETTER METHODS */

			// returns the size EXCLUDING the \0 NULL character
			int Size() const;		
			// returns the number of vowels in the string
			int Vowels() const;
			// returns the number of consonants in the string
			int Consonants() const;


			/* OPERATOR OVERLOADING */			
			char& operator[](int Index);
			const char& operator[](int Index) const;

			friend std::ostream& operator<<(std::ostream& s, const GString& other);
			
			GString& operator=(const GString& other);
			GString& operator=(GString&& other);

			friend bool operator==(const GString& first, const GString& second);
			friend bool operator!=(const GString& first, const GString& second);
			friend bool operator<(const GString& first, const GString& second);

			GString& operator+=(const char* right);			
			GString& operator+=(const GString& right);
			GString& operator+=(char right);

			// Converts GString to const char*
			operator const char*() const;
			operator char*() const;
		};
	}
}
#endif



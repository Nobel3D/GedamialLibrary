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
			size_t size;
		public:
			// There is no need for an empty constructor,
			// since we are making a constructor taking either a string or an empty one
			GString(const char* CstyleString = "");
			// copy constructor
			GString(const GString& copy);
			// move constructor - some performance boost
			GString(GString&& move);
			// destructor
			~GString();

			// returns the string in Upper Case format
			GString ToUpper();
			// returns the string in Lower Case format
			GString ToLower();						

			// appends a c-style string to the GString
			void Append(const char* toAdd);
			// appends a single char to the GString
			void Append(char toAdd);

			// finds a single character in the GString and returns its index
			int Find(const char charToSearch, int start) const;
			// returns how many times the character appears in the GString
			int Occurrences(const char charToSearch) const;

			// reverses a given GString (hello -> olleh) and returns it
			static GString Reverse(const GString& str);
			// determines if a given GString is palindrome or not (poop -> yes)
			static bool IsPalindrome(const GString& str);
			// Checks whether a GString (substr) is contained in another (source)
			static bool StrStr(GString source, GString substr);

			// takes a substring that begins from BEGIN and ends at END
			GString SubString(int beginIndex, int endIndex) const;

			// still need to find the right algorithm for this...
			//static GArray<GString>& Split(const char Splitter, GString& str);


			/* GETTER METHODS */

			// returns the size of the string (no \0)
			size_t Size() const;		
			// returns the number of vowels in the string
			int Vowels() const;
			// returns the number of consonants in the string
			int Consonants() const;


			/* OPERATOR OVERLOADING */			
			char& operator[](int Index);
			const char& operator[](int Index) const;

			friend std::ostream& operator<<(std::ostream& s, const GString& other);
			friend std::istream& operator>>(std::istream& s, GString& other);

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



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
			char* mainString = nullptr;
			size_t size;

			void Create(const char* source);
			void Clear();


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

			// Returns the GString in Upper Case format
			GString ToUpper();
			// returns the GString in Lower Case format
			GString ToLower();						

			// Appends a c-style string to the GString
			void Append(const char* toAdd);
			// Appends a single char to the GString
			void Append(char toAdd);

			// Finds a single character in the GString and returns its index
			size_t Find(const char charToSearch, size_t start = 0) const;
			// returns how many times the character appears in the GString
			int Occurrences(const char charToSearch) const;

			// Reverses a given GString (hello -> olleh) and returns a copy of it
			static GString Reverse(const GString& str);
			// Determines if a given GString is palindrome or not (poop -> yes)
			static bool IsPalindrome(const GString& str);
			// Checks whether a GString (substr) is contained in another (source)
			static bool StrStr(GString source, GString substr);
			// Deletes all the consecutive correspondences of a given character from the beginning and the end of the string
			void Trim(char toDelete = ' ');
			//
			static GArray<GString> Split(GString str, char token = ' ');

			// takes a substring that begins from BEGIN and ends at END
			GString SubString(const size_t beginIndex, const size_t endIndex) const;

			// still need to find the right algorithm for this...
			//static GArray<GString>& Split(const char Splitter, GString& str);


			/* GETTER METHODS */

			// returns the size of the string (without \0)
			size_t Size() const;		
			// returns the number of vowels in the string
			int Vowels() const;
			// returns the number of consonants in the string
			int Consonants() const;
			// checks whether a given character is a letter or not
			static bool isLetter(char c);
			// checks whether a given character is a digit or not
			static bool isDigit(char c);

			/* RANGE FOR LOOP SUPPORT */
			char* begin()
			{
				return &mainString[0];
			}

			char* end()
			{
				return &mainString[size];
			}

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
			friend bool operator>(const GString& first, const GString& second);

			GString operator+(GString& other);
			GString& operator+=(const char* right);			
			GString& operator+=(const GString& right);
			GString& operator+=(char right);

			/* IMPLICIT CONVERTIONS */
			operator const char*() const;
			operator char*() const;
			operator char() const;	      // returns the first letter of the string
		};
	}
}
#endif



#pragma once
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
			GString();
			GString(const char* CstyleString);
			GString(const GString& copy);

			GString& ToUpper();
			GString& ToLower();			

			static GString Reverse(const GString& str);
			static bool bIsPalindrome(const GString& str);

			static GString SubString(const GString& str, int begin, int end);
			GArray<GString> Split(const char Splitter, const GString& str);

			/* OPERATOR OVERLOADING */
			char& operator[](int Index);
			const char& operator[](int Index) const;
			friend std::ostream& operator<<(std::ostream& s, const GString& other);
			GString& operator=(const GString& other);

			/* GETTER METHODS */
			int Size() const { return size; }
			int Vowels() const;
			int Consonants() const;
			char* GetString() const { return mainString; }
			~GString();
		};
	}
}



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

			void Append(const char* toAdd);

			static GString Reverse(const GString& str);
			static bool bIsPalindrome(const GString& str);

			static GString SubString(const GString& str, int begin, int end);
			static GArray<GString> Split(const char Splitter, const GString& str);

			/* GETTER METHODS */
			int Size() const { return size; }			// returns the size EXCLUDING the \0 NULL character
			int Vowels() const;
			int Consonants() const;
			char* GetString() const { return mainString; }
			~GString();

			/* OPERATOR OVERLOADING */
			char& operator[](int Index);
			const char& operator[](int Index) const;
			friend std::ostream& operator<<(std::ostream& s, const GString& other);
			GString& operator=(const GString& other);
			friend bool operator==(const GString& first, const GString& second)
			{
				bool areDifferent = false;

				if (first.size == second.size)
				{
					for (int i = 0; i < first.size; i++)
					{
						if (first[i] == second[i])
						{
							continue;
						}
						else
						{
							areDifferent = true;
							break;
						}
					}

					if (areDifferent)
						return false;
					else
						return true;
				}
				else
				{
					return false;
				}
			}
			friend bool operator!=(const GString& first, const GString& second) { return !(first == second); }	
			GString& operator+=(const char& right)
			{
				GString result = this->mainString + right;

				return result;
			}
		};
	}
}



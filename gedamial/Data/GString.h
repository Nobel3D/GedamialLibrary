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
			//GString();
			GString(const char* CstyleString = "");
			GString(const GString& copy);
			GString(GString&& move);
			~GString();

			GString ToUpper();
			GString ToLower();						

			void Append(const char* toAdd);
			void Append(char toAdd);

			int Find(const char charToSearch, int start) const;
			int HowManyTimes(const char charToSearch) const;
			static GString Reverse(const GString& str);
			static bool bIsPalindrome(const GString& str);

			GString& SubString(int begin, int end) const;

			//static GArray<GString>& Split(const char Splitter, GString& str);

			/* GETTER METHODS */
			int Size() const { return size; }			// returns the size EXCLUDING the \0 NULL character
			int Vowels() const;
			int Consonants() const;
			char* GetString() const { return mainString; }			

			/* OPERATOR OVERLOADING */
			char& operator[](int Index);
			const char& operator[](int Index) const;

			friend std::ostream& operator<<(std::ostream& s, const GString& other);
			
			GString& operator=(const GString& other);
			GString& operator=(GString&& other);

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
			friend bool operator!=(const GString& first, const GString& second)
			{
				return !(first == second);
			}
			friend bool operator<(const GString& first, const GString& second)
			{
				int minSize = first.Size() < second.Size() ? first.Size() : second.Size();

				for (int i{ 0 }; i < minSize; i++)
				{
					if (static_cast<int>(first[i]) < static_cast<int>(second[i]))
						return true;
				}

				return false;
			}
			
			GString& operator+=(const char* right)
			{
				this->Append(right);

				return *this;
			}
			GString& operator+=(const GString& right)
			{
				this->Append(right.mainString);

				return *this;
			}
			GString& operator+=(char right)
			{
				this->Append(right);
				return *this;
			}

			operator const char*() const;
		};
	}
}
#endif



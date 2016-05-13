#include "GString.h"
#include <string>

using std::cout;
using std::endl;

namespace ged
{
	namespace Data
	{
		GString::GString(const char* CstyleString)
		{
			if (CstyleString == nullptr)
				CstyleString = "";
			
			size = strlen(CstyleString);
			// +1 for the NULL character at the end (/0)
			mainString = new char[size + 1];

			int i = 0;
			for (i = 0; i < size; i++)
				mainString[i] = CstyleString[i];

			// Now 'i' is the last element, that must be the NULL character
			mainString[i] = '\0';
		}

		GString::GString(const GString& copy)
		{
			size = copy.size;
			mainString = new char[size];

			int i = 0;
			for (; i < size; i++)
			{
				mainString[i] = copy.mainString[i];
			}

			mainString[i] = '\0';
		}

		GString::GString(GString&& move)
		{
			size = move.size;
			mainString = new char[size];

			int i = 0;
			for (; i < size; i++)
			{
				mainString[i] = move.mainString[i];
			}

			mainString[i] = '\0';
		}

		GString::~GString()
		{
			delete[] mainString;
			mainString = nullptr;
			size = 0;
		}

		GString GString::ToUpper()
		{
			GString result{ *this };

			for (int i{ 0 }; i < size; ++i)
				result[i] = toupper(mainString[i]);

			return result;
		}

		GString GString::ToLower()
		{
			GString result{ *this };

			for (int i{ 0 }; i < size; ++i)
			{
				result[i] = tolower(mainString[i]);
			}

			return result;
		}

		void GString::Append(const char* toAdd)
		{
			/*
				WITHOUT DYNAMIC ALLOCATION!
				void Cat(char* prima, char* seconda)
				{
					int j = Lunghezza(prima);
					int k = 0;

					for (int i = 0; i < Lunghezza(seconda); i++)
					{
					prima[j] = seconda[k];

					j++;
					k++;
					}

					prima[j] = '\0';
				}
			*/
			
			const int finalSize = size + strlen(toAdd);

			char* finale = new char[finalSize];

			// Insert the original string characters (hell)
			int j = 0;
			for (j = 0; j < size; j++)
			{
				finale[j] = mainString[j];
			}

			// And now insert the characters of the string to append (o)
			int k = j;
			for (int i = 0; i < strlen(toAdd); k++, i++)
			{
				finale[k] = toAdd[i];
			}

			finale[k] = '\0';
			
			delete[] mainString;
			mainString = finale;
		}

		void GString::Append(char toAdd)
		{
			char* finale = new char[size + 1];

			// Insert the original string characters (hell)
			int j = 0;
			for (j = 0; j < size; j++)
			{
				finale[j] = mainString[j];
			}

			// And now insert the characters of the string to append (o)
			finale[j] = toAdd;
			finale[j + 1] = '\0';

			delete[] mainString;
			mainString = finale;
		}

		size_t GString::Size() const
		{
			return size;
		}

		int GString::Vowels() const
		{
			int vowels = 0;

			GString tmp(*this);
			tmp.ToLower();

			for (int i{ 0 }; i < Size(); ++i)
			{
				if (tmp[i] == 'a' ||
					tmp[i] == 'e' ||
					tmp[i] == 'i' ||
					tmp[i] == 'o' ||
					tmp[i] == 'u')
					vowels++;
			}

			return vowels;
		}

		int GString::Consonants() const
		{
			return Size() - Vowels();
		}

		int GString::Find(const char charToSearch, int start) const
		{
			int pos = -1;

			for (int i = start; i < this->Size(); i++)
			{
				if ((*this)[i] == charToSearch)
					return i;
			}

			// Returns -1 if the character wasn't found

			return pos;
		}

		int GString::Occurrences(const char charToSearch) const
		{
			int counter = 0;

			for (int i = 0; i < Size(); i++)
			{
				if (mainString[i] == charToSearch)				
					counter++;				
			}

			return counter;
		}

		GString GString::Reverse(const GString& str)
		{
			GString tmp(str);

			// tmp.Size()-1 because we don't want the NULL character (\0) to be placed at the beginning of the string (because that's not the end)
			for (int i = tmp.Size() - 1, j = 0; i > -1; i--, j++)
			{
				tmp[i] = str[j];
			}

			return tmp;
		}

		bool GString::IsPalindrome(const GString& str)
		{
			// Points to the first character
			const char* first = &str[0];
			// Points to the last character
			const char* last = &str[str.Size() - 1];

			for (int i{ 0 }; first != last && i<str.Size() - 1; i++, first++, last--)
			{
				if (*first != *last)
					break;
				else
					continue;
			}

			if (*first == *last)			
				return true;			

			else			
				return false;
		}

		bool GString::StrStr(GString source, GString substr)
		{
			int i = 0;

			while (source[i] != '\0')
			{
				// Finds the first character of the SUBSTR inside the SOURCE
				if (source[i] == substr[0])
				{
					int k = i + 1;
					int j = 1;
					int counter = 0;

					// If the next character in the SOURCE is equal to the second one of the SUBSTR (and so forth...)
					// AND, AT THE SAME TIME, we haven't reached the SUBSTR stopper yet
					while (source[k] == substr[j] && substr[j] != '\0')
					{
						counter++;
						k++;
						j++;
					}

					// If the number of letters we've found in the first string (+1, because at the beginning we exclude the first char)
					// IS EQUAL TO the lenght of the second string -> we've found the sub-string =)
					if (counter + 1 == substr.Size())					
						return true;					
				}

				i++;
			}

			return false;			
		}

		GString GString::SubString(const int beginIndex, const int endIndex) const
		{
			// The last "+1" is for the NULL character (\0) 
			char* tmp = new char[(endIndex - beginIndex) + 1 + 1];

			int i = beginIndex;
			for (int j = 0; i <= endIndex; i++, j++)
				tmp[j] = (*this)[i];

			tmp[i] = '\0';
			
			return GString(tmp);
		}

		//ged::Data::GArray<ged::Data::GString>& ged::Data::GString::Split(const char Splitter, GString& str)
		//{
		//	
		//	// DELETE THE SPLITTERS AT THE BEGINNING OF THE STRING
		//	int i = 0;
		//	while (str[i] == Splitter)
		//	{
		//	i++;
		//	}
		//
		//	str = str.SubString(i, str.Size());
		//
		//	int splitterNumber = str.HowManyTimes(Splitter);
		//	GArray<GString>* result = new GArray<GString>();
		//
		//	int splitterPos = 0;
		//	int currentPos = 0;
		//	int previousPos = 0;
		//
		//	do
		//	{
		//	splitterPos = str.Find(Splitter, currentPos);
		//
		//	if (splitterPos >= 0)
		//	{
		//	currentPos = splitterPos;
		//	result->Add(str.SubString(previousPos, currentPos - 1));
		//	currentPos++;
		//	previousPos = currentPos;
		//	}
		//
		//	else
		//	result->Add(str.SubString(currentPos, str.Size()));
		//
		//	} while (splitterPos >= 0);
		//
		//	return *result;
		//	
		//}	


		/* OPERATOR OVERLOADING */

		char& GString::operator[](int Index)
		{
			return mainString[Index];
		}

		const char& GString::operator[](int Index) const
		{
			return mainString[Index];
		}

		GString& GString::operator=(const GString& other)
		{
			size = other.size;

			delete[] mainString;
			mainString = new char[size];

			int i = 0;
			for (; i < size; i++)
			{
				mainString[i] = other.mainString[i];
			}

			mainString[i] = '\0';

			return *this;
		}

		GString& GString::operator=(GString&& other)
		{
			//std::cout << "[String] Move Assignment" << endl;
			size = other.size;

			delete[] mainString;
			mainString = new char[size];

			int i = 0;
			for (; i < size; i++)
			{
				mainString[i] = other.mainString[i];
			}

			mainString[i] = '\0';

			return *this;
		}

		std::ostream& operator<<(std::ostream & s, const GString & other)
		{
			std::cout << other.mainString;
			return s;
		}

		std::istream& operator>>(std::istream & s, GString & other)
		{
			// allocating random space
			const int buffSz = 100;
			char buff[buffSz];

			// getting the string from the stream
			s.get(buff, buffSz, '\n');

			// copying buff into myString
			other = GString(buff);

			// clearing the stream buffer
			s.clear();
			s.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			return s;
		}

		bool operator==(const GString & first, const GString & second)
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
				return false;
		}

		bool operator!=(const GString & first, const GString & second)
		{
			return !(first == second);
		}

		bool operator<(const GString & first, const GString & second)
		{
			int minSize = first.Size() < second.Size() ? first.Size() : second.Size();

			for (int i{ 0 }; i < minSize; i++)
				if (static_cast<int>(first[i]) < static_cast<int>(second[i]))
					return true;

			return false;
		}

		GString& GString::operator+=(const char * right)
		{
			this->Append(right);
			return *this;
		}

		GString& GString::operator+=(const GString & right)
		{
			this->Append(right.mainString);
			return *this;
		}

		GString& GString::operator+=(char right)
		{
			this->Append(right);
			return *this;
		}

		GString::operator const char*() const
		{
			return mainString;
		}

		GString::operator char*() const
		{
			return mainString;
		}

		/*
		ged::Data::GString::GString()
		{
		const char* CstyleString = "";

		// +1 for the NULL character at the end (\0)
		size = strlen(CstyleString);
		mainString = new char[size + 1];

		int i = 0;

		// -1 because we want to set the NULL character AFTER the copy of the character from one vector to another
		for (i = 0; i < size; i++)
		mainString[i] = CstyleString[i];

		mainString[i] = '\0';
		}
		*/
	}
}





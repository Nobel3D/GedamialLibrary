#include "GString.h"
#include <string>

using std::cout;
using std::endl;

#define USE_DEBUG false

namespace ged
{
	namespace Data
	{
		GString::GString(const char* CstyleString)
		{
			if (USE_DEBUG)
			{
				cout << "***************" << endl;
				if (CstyleString) cout << "Creation process started for (" << CstyleString << ")" << endl;
				else			  cout << "Creation process started for ( #nullptr# )" << endl;
			}

			Create(CstyleString);

			if(USE_DEBUG)
			{
				cout << "Creation process ended" << endl;
				cout << "***************" << endl << endl;
			}
		
		}

		GString::GString(const GString& copy) //: GString((const char*)copy)
		{
			if (USE_DEBUG) cout << "COPY CTOR" << endl;
			Create(copy);
		}

		GString::GString(GString&& move)
		{
			if(USE_DEBUG) cout << "MOVE CTOR" << endl;

			// let's steal the resources
			size = move.size;
			mainString = move.mainString;

			move.size = 0;
			// this is VERY important: since this temporary is going to be destructed,
			// we want to make sure that the temporary's mainString is set to *nullptr*
			// Otherwise, the temporary's destructor will free the data we've previously moved inside our mainString (above)!!!
			move.mainString = nullptr;
		}

		GString::~GString()
		{
			if (USE_DEBUG)
			{
				cout << "***************" << endl;
				// bug solved! crash if printing a NULLPTR
				if (mainString) cout << "Destructor process started for (" << mainString << ")" << endl;
				else		   cout << "Destructor process started for ( #nullptr# )" << endl;
			}

			Clear();

			if (USE_DEBUG)
			{
				cout << "Destruction process ended" << endl;
				cout << "***************" << endl << endl;
			}
		}

		void GString::Create(const char* source)
		{
			Clear();
			
			// with 'source = ""' we are changing the pointer, not the element pointed
			// for this reason the compiler doesn't complain about the CONST qualifier
			// if we put *source = "" - then the compiler complains
			if (source == nullptr)
				source = "";

			size = strlen(source);

			// +1 for the NULL character at the end (/0)
			mainString = new char[size + 1];

			for (int i = 0; i < size; i++)
				mainString[i] = source[i];

			// Now 'size' is the last element, that must be the NULL character
			mainString[size] = '\0';
		}

		void GString::Clear()
		{
			// delete old string	
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
				result[i] = tolower(mainString[i]);			

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
			
			// The last "+1" is for the NULL character (\0)
			const int finalSize = size + strlen(toAdd) + 1;

			char* finale = new char[finalSize];

			// example: hell + o

			// Insert the original string characters (hell)
			int j = 0;
			for (j = 0; j < size; j++)
			{
				finale[j] = mainString[j];
			}

			// And now insert the characters of the string to append (o)
			int k = j;
			for (int i = 0; i < strlen(toAdd); k++, i++)			
				finale[k] = toAdd[i];			

			finale[k] = '\0';

			Create(finale);

			// don't forget to release resources!
			delete[] finale;
		}

		void GString::Append(char toAdd)
		{
			// The first "+1" is for the new character which is going to be appended
			// The last "+1" is for the NULL character (\0)
			char* finale = new char[ (size + 1) + 1 ];

			// Insert the original string characters (hell)
			int j = 0;
			for (j = 0; j < size; j++)			
				finale[j] = mainString[j];
			
			// And now insert the character at the end (o)
			finale[j] = toAdd;
			// NULL character 
			finale[j + 1] = '\0';

			Create(finale);

			// don't forget to release resources!
			delete[] finale;
		}

		size_t GString::Size() const
		{
			return size;
		}

		int GString::Vowels() const
		{
			int vowels = 0;

			GString tmp{ *this };

			tmp.ToLower();

			for (int i{ 0 }; i < size; ++i)
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
			return size - Vowels();
		}

		size_t GString::Find(const char charToSearch, size_t start) const
		{
			for (int i = start; i < size; i++)
			{
				if (mainString[i] == charToSearch)
					return i;
			}

			// Returns -1 if the character wasn't found
			return -1;
		}

		int GString::Occurrences(const char charToSearch) const
		{
			int counter = 0;

			for (int i = 0; i < size; i++)			
				if (mainString[i] == charToSearch)				
					counter++;			

			return counter;
		}

		GString GString::Reverse(const GString& str)
		{
			GString tmp{ str };

			// tmp.size-1 because we don't want the NULL character (\0) to be placed at the beginning of the string (because that's not the end)
			for (int i = tmp.size - 1, j = 0; i >= 0; i--, j++)		
				tmp[i] = str[j];			

			return tmp;
		}

		bool GString::IsPalindrome(const GString& str)
		{
			/* 
			//old algorithm

			// Points to the first character
			const char* first = &str[0];
			// Points to the last character
			const char* last = &str[str.Size() - 1];

			for (int i{ 0 }; first != last && i <str.size - 1; i++, first++, last--)
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
			*/
		
			if (str == Reverse(str))
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
					if (counter + 1 == substr.size)					
						return true;					
				}

				i++;
			}

			return false;			
		}

		void GString::Trim(char toDelete)
		{
			/* 
			old algorithm, inefficient 
			//int i = 0, cont = 0;
			//bool finished = false;

			//while (mainString[i] != '\0' && !finished)
			//{
			//	if (mainString[i] == toDelete)
			//		cont++;

			//	else
			//		finished = true;

			//	i++;
			//}

			//// build new string
			//char* result = new char[this->Size() - cont + 1];

			//for (int j = cont, k = 0; j < this->Size(); j++, k++)
			//	result[k] = mainString[j];

			//result[this->Size() - cont] = '\0';

			//Create(result);
			*/

			size_t start{ 0 }, end{ size - 1 };

			char* left = mainString;
			while (*left == toDelete)
			{
				++left;
				++start;
			}

			char* right = mainString + size - 1;
			while (right > left && *right == toDelete)
			{
				--right;
				--end;
			}

			Create(SubString(start, end));
		}

		GString GString::SubString(const size_t beginIndex, const size_t endIndex) const
		{
			/*			
			// The last "+1" is for the NULL character (\0) 
			char* tmp = new char[(endIndex - beginIndex) + 1 + 1];

			for (int i = beginIndex, j = 0; i <= endIndex; i++, j++)
				tmp[j] = mainString[i];

			tmp[(endIndex - beginIndex) + 1] = '\0';
			
			return GString(tmp);
			*/
			
			// IF NOT-IN-RANGE, return empty string
			if (!(beginIndex >= 0 && beginIndex < size    &&    endIndex >= 0 && endIndex < size))
				return GString();

			// The last "+1" is for the NULL character (\0) 
			int totalSize = (endIndex - beginIndex + 1) + 1;
			char* tmp = new char[totalSize];					// this space must be freed after

			for (int i = beginIndex, j = 0; i <= endIndex; i++, j++)
				tmp[j] = mainString[i];

			tmp[totalSize - 1] = '\0';

			// direct initialization
			GString result{ tmp };
			delete[] tmp;										// HERE we free that space

			return result;

			/* 
				It could have been more readable to do

				return { tmp };  calling the (converting) constructor of GString

				However, the function would have terminated without RELEASING the space dynamically allocated by 'tmp' (memory leak)
			*/
		}

		GArray<GString> GString::Split(GString str, char token)
		{
			str.Trim(token);
			GArray<GString> arr;

			size_t lastPos = 0;
			size_t tokenPos = str.Find(token);

			while (tokenPos != -1)
			{
				arr.Add(str.SubString(lastPos, tokenPos - 1));

				lastPos = tokenPos + 1;

				tokenPos = str.Find(token, tokenPos + 1);
			}

			arr.Add(str.SubString(lastPos, str.Size() - 1));

			return arr;
		}	
		

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
			if (USE_DEBUG) cout << "ASSIGNMENT OPERATOR" << endl;

			// Create() already frees the old string to replace it with the new one
			Create(other);

			return *this;
		}

		GString& GString::operator=(GString&& other)
		{
			if (USE_DEBUG) std::cout << "MOVE ASSIGNMENT OPERATOR" << "   " << this->mainString << " = " << other.mainString << endl;

			// Here we can't use the Create() function, because it would be inefficient in this case
			this->Clear();

			size = other.size;
			mainString = other.mainString;

			other.size = 0;
			other.mainString = nullptr;

			return *this;
		}

		std::ostream& operator<<(std::ostream & s, const GString & other)
		{
			s << other.mainString;
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

		bool operator==(const GString& first, const GString& second)
		{			
			if (first.size != second.size)
				return false;
			
			for (int i = 0; i < first.size; i++)
			{
				if (first[i] != second[i])					
					return false;					
			}

			return true;
		}

		bool operator!=(const GString& first, const GString& second)
		{
			return !(first == second);
		}

		bool operator<(const GString & first, const GString & second)
		{
			int minSize = first.size < second.size ? first.size : second.size;

			// Compare the ASCII code
			for (int i{ 0 }; i < minSize; i++)
				if (static_cast<int>(first[i]) < static_cast<int>(second[i]))
					return true;

			return false;
		}

		GString& GString::operator+=(const char* right)
		{
			if(USE_DEBUG) cout << "operator+=(const char*)" << endl;

			this->Append(right);
			return *this;
		}

		GString& GString::operator+=(const GString& right)
		{
			if (USE_DEBUG) cout << "operator+=(const GString&)" << endl;

			this->Append(right.mainString);
			return *this;
		}

		GString& GString::operator+=(char right)
		{
			if (USE_DEBUG) cout << "operator+=(char)" << endl;

			this->Append(right);
			return *this;
		}

		GString::operator const char*() const
		{
			if(USE_DEBUG) cout << "conversion GString to const char*" << endl;

			return mainString;
		}

		GString::operator char*() const
		{
			if(USE_DEBUG) cout << "conversion GString to char*" << endl;

			return mainString;
		}

		GString::operator char() const
		{
			return mainString[0];
		}
	}
}
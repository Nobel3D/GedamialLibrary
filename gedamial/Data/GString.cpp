#include "GString.h"
#include <string>

using std::cout;
using std::endl;

ged::Data::GString::GString()
{
	const char* CstyleString = "";
	// +1 for the NULL character at the end (/0)
	size = strlen(CstyleString);
	mainString = new char[size + 1];

	int i = 0;
	// -1 because we want to set the NULL character AFTER the copy of the character from one vector to another
	for (i = 0; i < size; i++)
		mainString[i] = CstyleString[i];

	mainString[i] = '\0';
}

ged::Data::GString::GString(const char* CstyleString)
{
	if (CstyleString == nullptr)
	{
		// TODO...
	}

	else
	{

	}

	// +1 for the NULL character at the end (/0)
	size = strlen(CstyleString);
	mainString = new char[size+1];

	int i = 0;
	// -1 because we want to set the NULL character AFTER the copy of the character from one vector to another
	for (i = 0; i < size; i++)
		mainString[i] = CstyleString[i];

	mainString[i] = '\0';
}

ged::Data::GString::GString(const GString & copy)
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

ged::Data::GString& ged::Data::GString::ToUpper()
{
	for (int i{ 0 }; i < size; ++i)
	{
		mainString[i] = toupper(mainString[i]);
	}

	return *this;
}

ged::Data::GString& ged::Data::GString::ToLower()
{
	for (int i{ 0 }; i < size; ++i)
	{
		mainString[i] = tolower(mainString[i]);
	}

	return *this;
}

void ged::Data::GString::Append(const char* toAdd)
{
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

	mainString = finale;
}

int ged::Data::GString::Vowels() const
{
	int vocals = 0;

	GString tmp(*this);
	tmp.ToLower();


	for (int i{ 0 }; i < this->Size(); ++i)
	{
		if (tmp[i] == 'a' ||
			tmp[i] == 'e' ||
			tmp[i] == 'i' ||
			tmp[i] == 'o' ||
			tmp[i] == 'u')
			++vocals;
	}

	return vocals;
}

int ged::Data::GString::Consonants() const
{
	return this->Size() - this->Vowels();
}

ged::Data::GString ged::Data::GString::Reverse(const GString& str)
{
	GString tmp(str);

	// tmp.Size()-1 because we don't want the NULL character (\0) to be placed at the beginning of the string (because that's not the end)
	for (int i = tmp.Size()-1, j = 0;	 i > -1;	 i--, j++)
	{
		tmp[i] = str[j];
	}

	return tmp;
}

bool ged::Data::GString::bIsPalindrome(const GString& str)
{
	const char* first = &str[0];	
	const char* last = &str[str.Size() - 1];

	for (int i{ 0 }; first != last && i<str.Size()-1; i++, first++, last--)
	{
		if (*first != *last)
			break;
		else
			continue;
	}

	if (*first == *last)
	{		
		return true;
	}

	else
	{
		return false;
	}
}

ged::Data::GString ged::Data::GString::SubString(const GString& str, const int begin, const int end)
{
	// The last "+1" is for the NULL character (\0) 
	char* tmp = new char[(end-begin) + 1 + 1];

	int i = begin;
	for (int j = 0; i <= end; i++,j++)
	{
		tmp[j] = str[i];
	}

	tmp[i] = '\0';

	GString result(tmp);
	return result;
}

ged::Data::GArray<ged::Data::GString> ged::Data::GString::Split(const char Splitter, const GString& str)
{
	GArray<GString> result(str.Size());

	for (int i = 0; i < str.Size(); i++)
	{
		if (str[i] == Splitter)
		{
			GString taken;

			for (int j = 0; j < i; j++)
			{
				//taken = taken + str[j];
			}
		}
	}
	
	return result;
}

char& ged::Data::GString::operator[](int Index)
{
	return mainString[Index];	 
}

const char& ged::Data::GString::operator[](int Index) const
{
	return mainString[Index];
}

ged::Data::GString& ged::Data::GString::operator=(const GString & other)
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

ged::Data::GString::~GString()
{
	delete mainString;
	size = 0;
}

std::ostream& ged::Data::operator<<(std::ostream & s, const GString & other)
{
	std::cout << other.mainString;
	return s;
}
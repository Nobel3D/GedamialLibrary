#include "StringManagement.h"

std::string ged::Strings::strToUpper(std::string& str, bool modify = false)
{
	if (modify)
	{
		for (int i{ 0 }; i < str.size(); ++i)
		{
			str[i] = toupper(str[i]);
		}

		return str;
	}

	else if (!modify)
	{
		std::string _copy = str;
		for (int i{ 0 }; i < str.size(); ++i)
		{
			_copy[i] = toupper(str[i]);
		}

		return _copy;
	}
}

std::string ged::Strings::strToLower(std::string& str, bool modify = false)
{
	if (modify)
	{
		for (int i{ 0 }; i<str.size(); ++i)
		{
			str[i] = tolower(str[i]);
		}

		return str;
	}

	else if (!modify)
	{
		std::string _copy = str;
		for (int i{ 0 }; i<str.size(); ++i)
		{
			_copy[i] = tolower(str[i]);
		}

		return _copy;
	}
}

int ged::Strings::countVocals(const std::string& str)
{
	int vocals = 0;

	for (int i{ 0 }; i<str.size(); ++i)
	{
		if (str[i] == 'a' ||
			str[i] == 'e' ||
			str[i] == 'i' ||
			str[i] == 'o' ||
			str[i] == 'u')
			++vocals;
	}

	return vocals;
}

int ged::Strings::countCons(const std::string& str)
{
	return str.size() - countVocals(str);
}

std::string ged::Strings::Reverse(const std::string& str)
{
	std::string _copy;

	for (int i = str.length()-1; i > -1; i--)
		_copy += str[i];

	return _copy;
}

bool ged::Strings::bIsPalindrome(const std::string& str)
{
	const char* first = &str[0];
	const char* last = &str[str.length() - 1];

	for (int i{ 0 }; first != last && i<str.length(); i++, first++, last--)
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

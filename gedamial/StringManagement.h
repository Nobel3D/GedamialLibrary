#ifndef	STRINGMANAGEMENT_H
#define STRINGMANAGEMENT_H
#include <string>

namespace ged
{
	namespace Strings
	{
		std::string strToUpper(std::string& str, bool modify);
		std::string strToLower(std::string& str, bool modify);

		int countVocals(const std::string& str);
		int countCons(const std::string& str);

		std::string Reverse(const std::string& str);
		bool bIsPalindrome(const std::string& str);
	}
}

#endif
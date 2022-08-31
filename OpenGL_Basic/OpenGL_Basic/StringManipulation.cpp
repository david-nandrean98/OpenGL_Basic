#include "StringManipulation.h"

namespace core
{
	std::vector<std::string> delimitByToken(const std::string& str, const std::string& token)
	{
		std::vector<std::string> result;
		std::string tmp_str = str;
		size_t pos;

		while ((pos = tmp_str.find(token)) != std::string::npos)
		{
			result.push_back(tmp_str.substr(0, pos));
			tmp_str.erase(0, pos + token.length());
		}
		result.push_back(tmp_str);

		return result;
	}
}
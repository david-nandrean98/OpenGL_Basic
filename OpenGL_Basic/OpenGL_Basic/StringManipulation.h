#pragma once

#include <string>
#include <vector>

namespace core
{
	std::vector<std::string> delimitByToken(const std::string& str, const std::string& token);
}
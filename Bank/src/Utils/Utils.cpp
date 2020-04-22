#include "Utils.h"


std::string Utils::GenerateNumberedStringWithPrefix(const std::string& prefix, const unsigned int counter)
{
	std::string result{ prefix };

	result.append(std::to_string(counter));

	return result;
}
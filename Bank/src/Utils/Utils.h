#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <string>


class Utils
{
public:
	static std::string GenerateNumberedStringWithPrefix(const std::string& prefix, const unsigned int counter);

};


#endif // !UTILS_H
